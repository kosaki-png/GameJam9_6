#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include "OrbitCamera.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include "Collision.h"

using namespace DirectX;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
	delete objField;
	delete objSky;
	delete menu;
	delete score;
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height, {75, 50}, 0.002f);
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
			tmpSprite = Sprite::Create(SELECT, { 0,0 });
			menu = Sprite::Create(MENU, { 0,0 });
			score = Sprite::Create(SCORE, { 0,0 });
		}

		// スプライトの初期設定
		{
		}
	}

	// 3Dオブジェクト初期設定
	{
		// オブジェクト生成
		{
			objField = Object3d::Create(modelMng->GetModel(FIELD));
			objSky = Object3d::Create(modelMng->GetModel(SKYDOME));
		}
		// オブジェクト初期設定
		{
			objField->SetPosition({ 0, -5, 0 });
			objSky->SetScale({ 2,2,2 });
		}
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(10.0f);

	// ボタンの初期化
	{
		// モード指定用
		for (int i = 0; i < modeButton.size(); i++)
		{
			if (i % 3 == 0)
			{
				modeButton[i].position = {(float)100, (float)(225 * (i / 3) + 200)};
			}
			if (i % 3 == 1)
			{
				modeButton[i].position = { (float)(1920 / 2 - 275), (float)(225 * (i / 3) + 200) };
			}
			if (i % 3 == 2)
			{
				modeButton[i].position = { (float)(1920 - 650), (float)(225 * (i / 3) + 200) };
			}

			// サイズ設定
			modeButton[i].size = { 550.0f, 150.0f };
		}

		// 開始用
		startButton.position = { 1250.0f, 400.0f };
		startButton.size = { 400.0f, 400.0f };
	}

	// 各クラスの初期化
	{
	}
}

void SelectScene::Update()
{
	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN))
	{	
		//ゲームシーンへ
		nextScene = new GameScene();
	}

	// モードを選び、クリックしたとき
	if (select && input->TriggerMouseLeft())
	{
		// 現在のマウス座標を取得
		DirectX::XMFLOAT2 mousePos = input->GetClientMousePos();

		// マウス座標とボタンとの当たり判定
		if (Collision::CheckPoint2Box(mousePos, startButton.position, startButton.size))
		{
			// ウェーブモードセット
			WaveManager::GetInstance()->SetWaveMode(selectMode);
			//ゲームシーンへ
			nextScene = new GameScene();
		}
	}

	// モード選択
	if (!select)
	{
		if (input->TriggerMouseLeft())
		{
			// 現在のマウス座標を取得
			DirectX::XMFLOAT2 mousePos = input->GetClientMousePos();

			// マウス座標とボタンとの当たり判定
			for (int i = 0; i < modeButton.size(); i++)
			{
				if (Collision::CheckPoint2Box(mousePos, modeButton[i].position, modeButton[i].size))
				{
					// モードセット
					SetSelectMode(i);

					// 選ぶ
					select = true;
				}
			}
		}
	}
	if (input->TriggerMouseRight())
	{
		select = false;
	}

	// 3Dオブジェクト更新
	{
		objField->Update();
		objSky->Update();
	}
	// 各クラスの更新
	{
		lightGroup->Update();
		camera->Update();
	}
}

void SelectScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライト描画
	{
		// 背景スプライト描画前処理
		Sprite::PreDraw(cmdList);
		{
			//tmpSprite->Draw();
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
			objField->Draw();
			objSky->Draw();
		}
		Object3d::PostDraw();
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画前処理
		Sprite::PreDraw(cmdList);
		{
			if (!select)
			{
				menu->Draw();
			}
			else
			{
				score->Draw();
			}

			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		// スプライト描画後処理
		Sprite::PostDraw();
	}
}

void SelectScene::SetSelectMode(int mode)
{
	switch (mode)
	{
	case 0:
		selectMode = WaveMode::test;
		break;
	case 1:
		selectMode = WaveMode::easy;
		break;
	case 2:
		selectMode = WaveMode::flick_easy;
		break;
	case 3:
		selectMode = WaveMode::filck_normal;
		break;
	case 4:
		selectMode = WaveMode::flick_hard;
		break;
	case 5:
		selectMode = WaveMode::flick_hell;
		break;
	case 6:
		selectMode = WaveMode::follow;
		break;
	case 7:
		selectMode = WaveMode::test;
		break;
	case 8:
		selectMode = WaveMode::test;
		break;
	case 9:
		selectMode = WaveMode::test;
		break;
	}
}
