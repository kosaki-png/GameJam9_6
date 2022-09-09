#include "WinApp.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "LightGroup.h"
#include "ParticleManager.h"
#include "FlameRate.h"
#include "3d/Object3d.h"

#include "SceneManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 汎用機能
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	FlameRate* flamerate = nullptr;
	SceneManager* sceneMng = nullptr;

	// ゲームウィンドウの作成
	win = new WinApp();
	win->CreateGameWindow();

#pragma region 汎用機能初期化

	//フレームレート固定の初期化
	flamerate = new FlameRate();

	//DirectX初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

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

	// デバッグテキスト用テクスチャ読み込み
	SpriteData::LoadTexture();
	// デバッグテキスト初期化
	Text::GetInstance()->Initialize(TEXT_FONT);

#pragma endregion

	// シーンの初期化
	sceneMng = SceneManager::GetInstance();
	sceneMng->Initialize(dxCommon, input, audio);

	// メインループ
	while (true)
	{
		//フレームレート固定の更新処理
		flamerate->Update();
		// メッセージ処理
		if (win->ProcessMessage()) { break; }

		// 入力関連の毎フレーム処理
		input->Update();

		// シーンの更新
		sceneMng->Update();

		// 描画開始
		dxCommon->PreDraw();
		// シーンの描画
		sceneMng->Draw();
		// 描画終了
		dxCommon->PostDraw();
        //フレームレート待機処理
		flamerate->Wait();
	}

	// 各種解放
	sceneMng->Destroy();
	safe_delete(audio);
	safe_delete(dxCommon);
	safe_delete(flamerate);
	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	safe_delete(win);

	return 0;
}