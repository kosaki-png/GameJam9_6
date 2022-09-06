#include "GameScene.h"
#include "EndScene.h"
#include"TitleScene.h"
#include"SelectScene.h"
#include"Collision.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(objMng);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	audio->Stop();

	// 汎用的初期化
	{
		// カメラ生成
		camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

		// 3Dオブジェクトにカメラをセット
		Object3d::SetCamera(camera);

		// デバッグテキスト用テクスチャ読み込み
		if (!Sprite::LoadTexture(texNumber, L"Resources/font_sharp.png")) {
			assert(0);
			return;
		}

		// デバッグテキスト初期化
		text = Text::GetInstance();
		text->Initialize(texNumber);

		// ライト生成
		lightGroup = LightGroup::Create();
		// 3Dオブエクトにライトをセット
		Object3d::SetLightGroup(lightGroup);

		// パーティクルマネージャ生成
		particleMan = ParticleManager::GetInstance();
		particleMan->SetCamera(camera);

	}

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
		}

		// スプライト生成
		{
		}
	}

	// 3Dオブジェクト初期設定
	{
		// モデル読み込み
		{
		}

		// 3Dオブジェクト生成
		{
		}

		// 3Dオブジェクト初期位置設定
		{
		}
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(20.0f);

	audio->PlayLoop(L"Resources/game.wav");

	time = 0;

	objMng = new ObjManager();
	objMng->Initialize(input);
}

void GameScene::Update()
{
	// コントローラの更新
	//xinput.Update();

	// シーン移行
	//if (input->TriggerKey(DIK_SPACE)/* || xinput.TriggerButtom(0, xinput_A)*/)
	//{
	//	// 選択したマップでエンドシーンへ
	//	nextScene = new EndScene(1, time, damage, sign);
	//}

	// ESCAPEでゲーム終了
	if (input->PushKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// マウスポイント
	{
		static POINT p;
		GetCursorPos(&p);
		WinApp* win = nullptr;
		win = new WinApp();
		ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	// クリア
	//if (objMng->GetClear())
	//{
	//	nextScene = new EndScene(1, time, damage, sign);
	//}

	text->Printf("%f", time);

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3Dオブジェクト更新
	{}
	// 各クラスの更新
	{
		objMng->Update();
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライト描画
	{
		// 背景スプライト描画前処理
		Sprite::PreDraw(cmdList);

		/// <summary>
		/// ここに背景スプライトの描画処理を追加
		/// </summary>

		// スプライト描画後処理
		Sprite::PostDraw();
		// 深度バッファクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3D描画
	{
		// 3Dオブジェクトの描画
		Object3d::PreDraw(cmdList);

		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加
		/// </summary>

		Object3d::PostDraw();
		// パーティクルの描画
		particleMan->Draw(cmdList);
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画前処理
		Sprite::PreDraw(cmdList);

		/// <summary>
		/// ここに前景スプライトの描画処理を追加
		/// </summary>

		objMng->Draw();

		// デバッグテキストの描画
		text->DrawAll(cmdList);

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}

void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// 追加
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}