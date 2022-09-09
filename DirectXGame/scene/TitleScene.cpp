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
			
		}

		// 3Dオブジェクト生成
		{
			
		}

		// 3Dオブジェクト初期設定
		{
			
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

	// ESCAPEでゲーム終了
	if (input->PushKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// パーティクル生成
	//CreateParticles();

	lightGroup->Update();
	camera->Update();

	// 3Dオブジェクト更新
	{

	}

	// フルスクリーン変更(使用禁止)
	if (input->TriggerKey(DIK_F1))
	{
		dxCommon->ChengeFullScreen();
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
		Sprite::PostDraw();
	}
}