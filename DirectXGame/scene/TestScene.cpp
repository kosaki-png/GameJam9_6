#include "TestScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include "FreeCamera.h"
#include "Collision.h"

using namespace DirectX;

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
	delete cross;
	delete model;
	delete modelGround;
	delete object;
	delete objGround;
	for (int i = 0; i < 20; i++)
	{
		delete target[i];
	}
	delete camera;
	delete ui;
}

void TestScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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
			model = Model::CreateFromOBJ("sphere");
			modelGround = Model::CreateFromOBJ("ground");
		}

		// 3Dオブジェクト生成
		{
			object = Object3d::Create(model);
			objGround = Object3d::Create(modelGround);
		}

		// 3Dオブジェクト初期設定
		{
			object->Initialize();
			objGround->Initialize();
			objGround->SetPosition({0,-5, 0});
		}
	}

	// 視線レイの初期設定
	{
		XMFLOAT3 tmp = camera->GetEye();
		ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		tmp = camera->GetDir();
		ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);

		for (int i = 0; i < 20; i++)
		{
			target[i] = new BaseTarget();
			target[i]->Initialize("sphere");
			target[i]->SetPosition({ (float)(i % 5) - 2.0f, (float)(int)(i / 5) - 1 , 0 });
		}
	}

	// 各クラスの初期化
	{
		// 感度設定
		sensi = camera->GetSensi();

		// UI
		ui = new Ui();
		ui->Initialize();
	}
}

void TestScene::Update()
{
	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN))
	{
		nextScene = new SelectScene();
	}

	// ESCAPEでゲーム終了
	if (input->PushKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// フルスクリーン用（使用禁止）
	if (input->TriggerKey(DIK_F1))
	{
		dxCommon->ChengeFullScreen();
	}
	
	// カーソルを消して中心固定
	ShowCursor(false);
	SetCursorPos(centerX, centerY);

	// カメラ感度切り替え
	{
		if (input->TriggerKey(DIK_UP))
		{
			sensi += 0.005f;
			camera->SetSensi(sensi);
		}
		if (input->TriggerKey(DIK_DOWN))
		{
			sensi -= 0.005f;
			camera->SetSensi(sensi);
		}
		// 感度を表示
		text->Printf("%f", sensi);
	}

	// ターゲット判定
	{
		// 視線レイの更新
		{
			XMFLOAT3 tmp = camera->GetEye();
			ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
			tmp = camera->GetDir();
			ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		}

		for (int i = 0; i < 20; i++)
		{
			// 視線レイと的との当たり判定
			if (Collision::CheckRay2Sphere(ray, target[i]->GetSphere()))
			{
				if (input->TriggerMouseLeft())
				{
					target[i]->SetIsDead(true);
				}
			}

			// 復活
			static int respownCnt[20] = {};
			if (target[i]->GetIsDead())
			{
				respownCnt[i]++;
				if (respownCnt[i] > 200)
				{
					target[i]->SetIsDead(false);
					respownCnt[i] = 0;
				}
			}
		}
	}
	
	// 3Dオブジェクト更新
	{
		object->Update();
		objGround->Update();
	}

	// 各クラス更新
	{
		lightGroup->Update();
		camera->Update();
		particleMan->Update();
		for (int i = 0; i < 20; i++)
		{
			target[i]->Update();
		}
		ui->Update(input);
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
			for (int i = 0; i < 20; i++)
			{
				target[i]->Draw();
			}
		}
		Object3d::PostDraw();

		// パーティクルの描画
		particleMan->Draw(cmdList);
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画前処理
		Sprite::PreDraw(cmdList);
		{
			cross->Draw();
			ui->Draw(cmdList);

			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}
}