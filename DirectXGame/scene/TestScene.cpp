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

		target = new BaseTarget();
		target->Initialize("sphere");
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

	// ターゲット判定
	{
		// 視線レイの更新
		{
			XMFLOAT3 tmp = camera->GetEye();
			ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
			tmp = camera->GetDir();
			ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		}

		// 視線レイと的との当たり判定
		if (Collision::CheckRay2Sphere(ray, target->GetSphere()))
		{
			if (input->TriggerMouseLeft())
			{
				target->SetIsDead(true);
			}
			text->Printf("%f", 100.0f);
		}

		// 復活
		static int respownCnt = 0;
		if (target->GetIsDead())
		{
			respownCnt++;
			if (respownCnt > 200)
			{
				target->SetIsDead(false);
				respownCnt = 0;
			}
		}
	}
	
	// 3Dオブジェクト更新
	{
		object->Update();
		objGround->Update();
	}

	lightGroup->Update();
	camera->Update();
	particleMan->Update();
	target->Update();
}

void TestScene::Draw()
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
		objGround->Draw();
		target->Draw();

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
		cross->Draw();
		// デバッグテキストの描画
		text->DrawAll(cmdList);

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}