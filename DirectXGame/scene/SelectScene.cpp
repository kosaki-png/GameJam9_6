#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include "OrbitCamera.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
	delete objField;
	delete objSky;
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


			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		// スプライト描画後処理
		Sprite::PostDraw();
	}
}