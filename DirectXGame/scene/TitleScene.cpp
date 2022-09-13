#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include "FreeCamera.h"
#include "Collision.h"

using namespace DirectX;

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete objGround;
	delete objSky;
}

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	audio->Stop();

	// 汎用的初期化
	{
		// カメラ生成
		camera = new FreeCamera(WinApp::window_width, WinApp::window_height);
		//camera->SetInput(input);

		// 3Dオブジェクトにカメラをセット
		Object3d::SetCamera(camera);

		// デバッグテキスト初期化
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
			tmpSprite = Sprite::Create(TITLE, { 0,0 });
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
			objGround->Initialize();
			objGround->SetPosition({ 0,-5, 0 });
			objSky->SetScale({ 2,2,2 });
		}
	}

	text = text->GetInstance();

}

void TitleScene::Update()
{
	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN))
	{
		nextScene = new SelectScene();
	}
	if (input->TriggerMouseLeft())
	{
		nextScene = new SelectScene();
	}

	// 3Dオブジェクト更新
	{
		objGround->Update();
		objSky->Update();
	}

	// 各クラス更新
	{
		//クリック音
		if (input->TriggerMouseLeft())
		{
			audio->PlayWave(L"Resources/sound/w0cz1-hiuw9.wav");
		}

		lightGroup->Update();
		rot.x += 0.1f;
		camera->SetRotation(rot);
		camera->Update();
	}
}

void TitleScene::Draw()
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
		}
		Object3d::PostDraw();
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画前処理
		Sprite::PreDraw(cmdList);
		{
			tmpSprite->Draw();

			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}
}