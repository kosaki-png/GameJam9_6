#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

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
			Sprite::LoadTexture(1, L"Resources/Tutorial1.png");
			Sprite::LoadTexture(2, L"Resources/Tutorial2.png");
		}

		// スプライト生成
		{
			Tutorial1 = Sprite::Create(1, { 0,0 });
			Tutorial2 = Sprite::Create(2, { 0,0 });
		}

		// スプライトのサイズ変更
		{
		}
	}

	// 3Dオブジェクト初期設定
	{
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(10.0f);

	// 各クラスの初期化
	{
	}
}

void SelectScene::Update()
{
	// コントローラの更新
	xinput.Update();

	// シーン移行
	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN) && page == true)
	{
		change = true;
		page = false;
	}
	else if (input->TriggerKey(DIK_RETURN) && page == false)
	{
		//ゲームシーンへ
		nextScene = new GameScene();
	}
	else if (input->TriggerKey(DIK_LEFTARROW) && page == false)
	{
		change = false;
		page = true;
	}

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

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3Dオブジェクト更新
	{}
	// 各クラスの更新
	{}
}

void SelectScene::Draw()
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

		if (page == true)
		{
		Tutorial1->Draw();
		}
		else
		{
		Tutorial2->Draw();
		}

		// デバッグテキストの描画
		text->DrawAll(cmdList);

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}