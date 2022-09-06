#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	safe_delete(title1);
	safe_delete(title2);
	safe_delete(sharp1);
	safe_delete(sharp2);
}

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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
			Sprite::LoadTexture(1, L"Resources/Title1.png");
			Sprite::LoadTexture(2, L"Resources/Title2.png");
			Sprite::LoadTexture(3, L"Resources/sharp_01.png");
			Sprite::LoadTexture(4, L"Resources/sharp_02.png");
		}

		// スプライト生成
		{
			title1 = Sprite::Create(1, { 0, 0 });
			title2 = Sprite::Create(2, { 0, 0 });
			sharp1 = Sprite::Create(3, { 0, 0 });
			sharp2 = Sprite::Create(4, { 0, 0 });
		}

		// スプライト初期設定
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

		// 3Dオブジェクト初期設定
		{
		}
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, -1, 0 });
	camera->SetDistance(25.0f);

	count = 0;
	sharpMode = false;

	audio->PlayLoop(L"Resources/title.wav");
}

void TitleScene::Update()
{
	// コントローラの更新
	xinput.Update();

	if (input->TriggerKey(DIK_W)) //選択切り替え
	{
		change = true;
	}
	if (input->TriggerKey(DIK_S)) //選択切り替え
	{
		change = false;
		count = 0;
	}

	// 隠し要素
	if (count < 30)
	{
		if (input->TriggerKey(DIK_S))
		{
			sharpCnt++;
			if (sharpCnt > 4)
			{
				sharpMode = !sharpMode;
				sharpCnt = 0;
				if (sharpMode)
				{
					audio->Stop();
					audio->PlayLoop(L"Resources/アンゴラたちの踊り.wav");
				}
				else
				{
					audio->Stop();
					audio->PlayLoop(L"Resources/title.wav");
				}
			}
		}
	}
	else
	{
		sharpCnt = 0;
	}

	count++;

	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN) && change == true)
	{
		//ゲームシーンへ
		nextScene = new GameScene();
	}
	else if (input->TriggerKey(DIK_RETURN) && change == false)
	{
		nextScene = new SelectScene();
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

	// パーティクル生成
	//CreateParticles();

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3Dオブジェクト更新
	{
	}
}

void TitleScene::Draw()
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

		if (!sharpMode)
		{
			if (change)
			{
				title1->Draw();
			}
			else
			{
				title2->Draw();
			}
		}
		if (sharpMode)
		{
			if (change)
			{
				sharp1->Draw();
			}
			else
			{
				sharp2->Draw();
			}
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