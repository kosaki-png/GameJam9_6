#include "WinApp.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "EndScene.h"
#include "LightGroup.h"
#include "ParticleManager.h"
#include "FlameRate.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 汎用機能
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	FlameRate* flamerate = nullptr;
	//GameScene* gameScene = nullptr;
	BaseScene* scene = nullptr;

	// ゲームウィンドウの作成
	win = new WinApp();
	win->CreateGameWindow();
	 
	//フレームレート固定の初期化
	flamerate = new FlameRate();

	// 追加
	//WinApp* window2 = nullptr;
	//window2 = new WinApp();
	//window2->CreateGameWindow();

	//DirectX初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化

	// 入力の初期化
	input = Input::GetInstance();
	if (!input->Initialize(win->GetInstance(), win->GetHwnd())) {
		assert(0);
		return 1;
	}
	// オーディオの初期化
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}
	// スプライト静的初期化
	if (!Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice());
	// ライト静的初期化
	LightGroup::StaticInitialize(dxCommon->GetDevice());
	// パーティクルマネージャ初期化
	ParticleManager::GetInstance()->Initialize(dxCommon->GetDevice());

#pragma endregion

	// 最初のシーン
	scene = new TitleScene();
	//scene = new SelectScene();
	//scene = new GameScene();
	//scene = new EndScene();

	// 最初のシーンの初期化
	scene->Initialize(dxCommon, input, audio);

	//ShowCursor(FALSE);
	// メインループ
	while (true)
	{
		//フレームレート固定の更新処理
		flamerate->Update();
		// メッセージ処理
		if (win->ProcessMessage()) { break; }

		// 追加
		//if (window2->ProcessMessage()) { break; }

		// 入力関連の毎フレーム処理
		input->Update();

		// シーン切り替え
		{
			// シーンクラスで指定した次のシーンを受け取る
			BaseScene* nextScene = scene->GetNextScene();

			if (nextScene)	// nextSceneがnullでないとき
			{
				// 元のシーンを削除
				delete scene;

				// 次に指定したシーンを初期化
				nextScene->Initialize(dxCommon, input, audio);

				// 現在のシーンに適用
				scene = nextScene;
			}
		}

		scene->Update();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		scene->Draw();
		// 描画終了
		dxCommon->PostDraw();
        //フレームレート待機処理
		flamerate->Wait();
	}

	// 各種解放
	safe_delete(scene);
	safe_delete(audio);
	safe_delete(dxCommon);
	safe_delete(flamerate);
	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	safe_delete(win);

	// 追加
	//window2->TerminateGameWindow();
	//safe_delete(window2);

	return 0;
}