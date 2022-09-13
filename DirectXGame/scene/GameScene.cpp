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
	delete objGround;
	delete objSky;
	delete option;
	safe_delete(ranking);
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
			objSky = Object3d::Create(modelMng->GetModel(SKYDOME));
		}

		// 3Dオブジェクト初期設定
		{
			//objGround->Initialize();
			objGround->SetPosition({ 0,-5, 0 });

			objSky->SetScale({ 2,2,2 });
		}
	}

	// 各クラスの初期化
	{
        //ランキング初期化
		ranking = new Ranking();
		ranking->Initialize();
		// 感度設定
		sensi = camera->GetSensi();

		// ウェーブの初期化
		waveMng = WaveManager::GetInstance();
		//waveMng->SetWaveMode(WaveMode::flick_easy);
		waveMng->Initialize(input, camera);

		// オプションの初期化
		option = new OptionGS(input, camera, audio);
		option->Initialize();
	}

	// カーソルを消す
	ShowCursor(false);
}

void GameScene::Update()
{
	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN))
	{
		if (!option->GetIsOption())
		{
			ShowCursor(true);
		}
		
		BaseWave* tmpWave = WaveManager::GetInstance()->GetWave();
		ranking->setScore(tmpWave->GetCurrentKey(), (float)tmpWave->GetScore());
		ranking->WriteJson();

		option->WriteJson();
		nextScene = new EndScene();
	}

	// Rでリスタート
	if (input->TriggerKey(DIK_R))
	{
		//nextScene = new TestScene();
	}

	// クリアフラグでゲームクリア
	if (waveMng->GetClearFlag() && nextScene == nullptr)
	{
		if (!option->GetIsOption())
		{
			ShowCursor(true);
		}

		BaseWave* tmpWave = WaveManager::GetInstance()->GetWave();
		ranking->setScore(tmpWave->GetCurrentKey(), (float)tmpWave->GetScore());
		ranking->WriteJson();

		nextScene = new EndScene();
	}

	// ESCAPEでゲーム終了
	if (input->TriggerKey(DIK_ESCAPE))
	{
		option->ChangeIsOption();
	}

	// フルスクリーン用（使用禁止）
	if (input->TriggerKey(DIK_F1))
	{
		dxCommon->ChengeFullScreen();
	}

	if (!option->GetIsOption())
	{
		// ウェーブの更新
		waveMng->Update();
		
		// 3Dオブジェクト更新
		{
			objGround->Update();
			objSky->Update();
		}

		// 各クラス更新
		{
			lightGroup->Update();
			camera->Update();
		}

		// カーソルを中心固定
		SetCursorPos(centerX, centerY);
	}
	else
	{
		option->Update();
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
			objSky->Draw();

			// ウェーブの描画
			waveMng->Draw();
		}
		Object3d::PostDraw();
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画前処理
		Sprite::PreDraw(cmdList);
		{
			cross->Draw();
			// ウェーブUIの描画
			waveMng->DrawUi(cmdList);

			// オプション画面
			option->Draw(cmdList);

			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}
}