#include "GameScene.h"
#include "SelectScene.h"
#include "EndScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include "FreeCamera.h"
#include "Collision.h"
#include "TestWave.h"
#include "FlickWave.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete cross;
	delete modelGround;
	delete objGround;
	delete wave;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	audio->Stop();

	// 汎用的初期化
	{
		// カメラ生成
		camera = new FreeCamera(WinApp::window_width, WinApp::window_height);
		camera->SetInput(input);

		// 3Dオブジェクトにカメラをセット
		Object3d::SetCamera(camera);

		// デバッグテキスト初期化
		text = Text::GetInstance();

		// ライト生成
		lightGroup = LightGroup::Create();
		// 3Dオブエクトにライトをセット
		Object3d::SetLightGroup(lightGroup);
	}

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			//Sprite::LoadTexture(1, L"Resources/Title1.png");
			Sprite::LoadTexture(10, L"Resources/centerDot.png");
		}

		// スプライト生成
		{
			//title1 = Sprite::Create(1, { 0, 0 });
			cross = Sprite::Create(10, { centerX, centerY });
			cross->SetAnchorPoint({ 0.5f, 0.5f });
			cross->SetSize({ 16, 16 });
		}

		// スプライト初期設定
		{
		}
	}

	// 3Dオブジェクト初期設定
	{
		// モデル読み込み
		{
			modelGround = Model::CreateFromOBJ("ground");
		}

		// 3Dオブジェクト生成
		{
			objGround = Object3d::Create(modelGround);
		}

		// 3Dオブジェクト初期設定
		{
			objGround->Initialize();
			objGround->SetPosition({ 0,-5, 0 });
		}
	}

	// 各クラスの初期化
	{
		// 感度設定
		sensi = camera->GetSensi();

		// ウェーブの初期化
		wave = new FlickWave();
		wave->Initialize(input, camera);
	}

	// カーソルを消す
	ShowCursor(false);
	option = false;
}

void GameScene::Update()
{
	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN))
	{
		if (!option)
		{
			ShowCursor(true);
		}
		
		nextScene = new EndScene();
	}

	// Rでリスタート
	if (input->TriggerKey(DIK_R))
	{
		//nextScene = new TestScene();
	}

	// クリアフラグでゲームクリア
	if (wave->GetClearFlag())
	{
		if (!option)
		{
			ShowCursor(true);
		}

		nextScene = new EndScene();
	}

	// ESCAPEでゲーム終了
	if (input->TriggerKey(DIK_ESCAPE))
	{
		option = !option;
		ShowCursor(option);
	}

	// フルスクリーン用（使用禁止）
	if (input->TriggerKey(DIK_F1))
	{
		dxCommon->ChengeFullScreen();
	}

	if (!option)
	{
		// カーソルを中心固定
		SetCursorPos(centerX, centerY);

		// カメラ感度切り替え
		{
			if (input->TriggerKey(DIK_UP))
			{
				sensi += 0.001f;
				camera->SetSensi(sensi);
			}
			if (input->TriggerKey(DIK_DOWN))
			{
				sensi -= 0.001f;
				camera->SetSensi(sensi);
			}
			if (input->TriggerKey(DIK_RIGHT))
			{
				sensi += 0.01f;
				camera->SetSensi(sensi);
			}
			if (input->TriggerKey(DIK_LEFT))
			{
				sensi -= 0.01f;
				camera->SetSensi(sensi);
			}
			// 感度を表示
			text->Printf("%d", (int)(sensi * 1000));
		}

		// 3Dオブジェクト更新
		{
			objGround->Update();
		}

		// 各クラス更新
		{
			lightGroup->Update();
			camera->Update();

			// ウェーブの更新
			wave->Update();
		}
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライト描画
	{
		// 背景スプライト
		Sprite::PreDraw(cmdList);
		{

		}
		Sprite::PostDraw();

		// 深度バッファクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3D描画
	{
		// 3Dオブジェクトの描画
		Object3d::PreDraw(cmdList);
		{
			objGround->Draw();

			wave->Draw();
		}
		Object3d::PostDraw();
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画前処理
		Sprite::PreDraw(cmdList);
		{
			cross->Draw();
			wave->DrawUi(cmdList);

			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}
}