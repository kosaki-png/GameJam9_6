#include "TestScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include "FreeCamera.h"
#include "Collision.h"
#include "TestWave.h"
#include "FlickWave.h"
#include "EasyWave.h"
#include "ScaleWave.h"

using namespace DirectX;

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
	delete cross;
	delete objGround;
	delete wave;
}

void TestScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new FreeCamera(WinApp::window_width, WinApp::window_height);
		camera->SetInput(input);

		// 3Dオブジェクトにカメラをセット
		Object3d::SetCamera(camera);

		// テキストの初期化
		text = Text::GetInstance();

		// ライト生成
		lightGroup = LightGroup::Create();
		// 3Dオブエクトにライトをセット
		Object3d::SetLightGroup(lightGroup);

		audio->Stop();
	}

	// スプライト初期設定
	{
		// スプライト生成
		{
			//title1 = Sprite::Create(1, { 0, 0 });
			cross = Sprite::Create(CROSS, { centerX, centerY });
			cross->SetAnchorPoint({ 0.5f, 0.5f });
			cross->SetSize({ 16, 16 });
		}

		// スプライト初期設定
		{
		}
	}

	// 3Dオブジェクト初期設定
	{
		// 3Dオブジェクト生成
		{
			objGround = Object3d::Create(modelMng->GetModel(FIELD));
		}

		// 3Dオブジェクト初期設定
		{
			objGround->Initialize();
			objGround->SetPosition({0,-5, 0});
		}
	}

	// 各クラスの初期化
	{
		// 感度設定
		sensi = camera->GetSensi();

		// ウェーブの初期化
		//wave = new FlickWave("test");
		//wave = new EasyWave("easy");
		//wave = new ScaleWave("scale");
		wave->Initialize(input, camera, audio);
	}

	// カーソルを消す
	ShowCursor(false);
}

void TestScene::Update()
{
	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN))
	{
		nextScene = new TitleScene();
	}

	// Rでリスタート
	if (input->TriggerKey(DIK_R))
	{
		nextScene = new TestScene();
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

void TestScene::Draw()
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