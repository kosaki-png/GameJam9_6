#include "EndScene.h"
#include "TitleScene.h"
#include"SelectScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

EndScene::EndScene(bool clear, float time, bool damage, bool sign)
{
	isClear = clear;
	this->time = time;
	this->damage = damage;
	sign1 = sign;
}

EndScene::~EndScene()
{
	safe_delete(clear);
	safe_delete(over);
}

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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

	// スプライト用テクスチャ読み込み
	{
		Sprite::LoadTexture(1, L"Resources/GameClear.png");
		Sprite::LoadTexture(2, L"Resources/GaneOver.png");
		Sprite::LoadTexture(3, L"Resources/king.png");
		Sprite::LoadTexture(4, L"Resources/sign.png");
	}

	// スプライト生成
	{
		clear = Sprite::Create(1, { 0,0 });
		over = Sprite::Create(2, { 0,0 });

		king = Sprite::Create(3, { 0,0 });
		sign = Sprite::Create(4, { 0,0 });
	}

	// スプライト初期設定
	{
	}

	// モデル読み込み
	{
	}

	// 3Dオブジェクト生成
	{
	}

	// 3Dオブジェクト初期位置設定
	{
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);

	if (clear)
	{
		audio->PlayWave(L"Resources/clear.wav");
	}
	else
	{
		audio->PlayWave(L"Resources/over.wav");
	}
}

void EndScene::Update()
{
	xinput.Update();

	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN))
	{
		// タイトルシーンへ
		nextScene = new TitleScene();
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

	text->Print("time...", 480, 380, 1);
	text->Print(std::to_string(time), 500, 490, 1);

	// パーティクル生成
	//CreateParticles();

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3Dオブジェクト更新
	{
	}
}

void EndScene::Draw()
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

		if (isClear == true)
		{
			if (damage)
			{
				clear->Draw();
			}
			else
			{
				king->Draw();
			}
			if (sign1)
			{
				sign->Draw();
			}
		}
		else
		{
			over->Draw();
		}

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

		// デバッグテキストの描画
		text->DrawAll(cmdList);

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}