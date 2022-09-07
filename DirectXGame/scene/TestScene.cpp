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
		}

		// スプライト生成
		{
			//title1 = Sprite::Create(1, { 0, 0 });
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
		}

		// 3Dオブジェクト生成
		{
			object = Object3d::Create(model);

		}

		// 3Dオブジェクト初期設定
		{
			object->Initialize();
		}
	}

	XMFLOAT3 cameraEye = camera->GetEye();
	XMFLOAT3 cameraTarget = camera->GetTarget();
	float cameraDis = camera->GetDistance();
	ray.start = XMVectorSet(cameraEye.x, cameraEye.y, cameraEye.z, 1.0f);
	ray.dir = XMVectorSet((cameraTarget.x - cameraEye.x) / cameraDis, (cameraTarget.y - cameraEye.y) / cameraDis, (cameraTarget.z - cameraEye.z) / cameraDis, 1.0f);

	sphere.center = XMVectorSet(0, 0, 0, 1);
	sphere.radius = 0.5f;

	text = text->GetInstance();

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
		object->Update();
	}

	if (input->TriggerKey(DIK_F1))
	{
		dxCommon->ChengeFullScreen();
	}

	//text->Printf("%f", Collision::CheckRay2Sphere(ray, sphere));

	XMFLOAT3 cameraEye = camera->GetEye();
	XMFLOAT3 cameraTarget = camera->GetTarget();
	float cameraDis = camera->GetDistance();
	ray.start = XMVectorSet(cameraEye.x, cameraEye.y, cameraEye.z, 1.0f);
	ray.dir = XMVectorSet((cameraTarget.x - cameraEye.x) / cameraDis, (cameraTarget.y - cameraEye.y) / cameraDis, (cameraTarget.z - cameraEye.z) / cameraDis, 1.0f);

	if (Collision::CheckRay2Sphere(ray, sphere))
	{
		text->Printf("%f", Collision::CheckRay2Sphere(ray, sphere));
	}
	else
	{
		//text->Printf("%f", Collision::CheckRay2Sphere(ray, sphere));
	}


	//text->Printf("%f", (float)input->GetMouseMove().lX);
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

		object->Draw();

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