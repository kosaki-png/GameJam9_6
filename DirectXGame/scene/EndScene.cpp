#include "EndScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include "DebugCamera.h"
#include "FreeCamera.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
	delete objGround;
	delete objSky;
	delete modelGround;
	delete modelSky;
	safe_delete(resultUi);
}

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	audio->Stop();

	// 汎用的初期化
	{
		// カメラ生成
		camera = new FreeCamera(WinApp::window_width, WinApp::window_height);

		// 3Dオブジェクトにカメラをセット
		Object3d::SetCamera(camera);

		// デバッグテキスト初期化
		text = Text::GetInstance();

		//ライト生成
		lightGroup = LightGroup::Create();
		// 3Dオブジェクトにライトを生成
		Object3d::SetLightGroup(lightGroup);

		audio->PlayLoop(L"Resources/sound/title.wav");
	}

	// スプライト初期設定
	{
		// スプライト生成
		{
			tmpSprite = Sprite::Create(END, { 0,0 });
			resultUi = new ResultUi();
			resultUi->Initialize();
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

	// カメラ中視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(300.0f);
}

void EndScene::Update()
{
	// Enterで指定のシーンへ
	if (input->TriggerKey(DIK_RETURN))
	{
		// ウェーブを削除
		WaveManager::GetInstance()->DestroyWave();
		// タイトルシーンへ
		nextScene = new SelectScene();
	}
	if (input->TriggerMouseLeft())
	{
		// ウェーブを削除
		WaveManager::GetInstance()->DestroyWave();
		// タイトルシーンへ
		nextScene = new SelectScene();
	}

	// ESCAPEでゲーム終了
	if (input->PushKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	rot.x += 0.1f;
	lightGroup->Update();
	camera->Update();
	camera->SetRotation(rot);
	resultUi->Update();
	// 3Dオブジェクトの更新
	{
		objGround->Update();
		objSky->Update();
	}
	//その他更新
	{
		//クリック音を鳴らす
		if (input->TriggerMouseLeft())
		{
			audio->PlayWave(L"Resources/sound/w0cz1-hiuw9.wav");
		}
	}

}

void EndScene::Draw()
{
	//コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライトの描画
	{
		// 背景スプライトの描画前処理
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
		//  前景スプライト描画前処理
		Sprite::PreDraw(cmdList);
		{
			tmpSprite->Draw();
			resultUi->Draw(cmdList);
			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}
}