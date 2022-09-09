#include "SceneManager.h"

#include "TestScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "EndScene.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (!instance)
	{
		instance = new SceneManager();
	}
	return instance;
}

BaseScene* SceneManager::GetNowScene()
{
	return nowScene;
}

void SceneManager::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	this->input = input;
	this->dxCommon = dxCommon;
	this->audio = audio;

	// 最初のシーン
	nowScene = new TitleScene();
	//nowScene = new SelectScene();
	//nowScene = new GameScene();
	//nowScene = new EndScene();
	//nowScene = new TestScene();

	nowScene->Initialize(dxCommon, input, audio);
}

void SceneManager::Update()
{
	BaseScene* nextScene = nowScene->GetNextScene();

	// 値が入ったら
	if (nextScene)
	{
		// 元のシーンを解放
		delete nowScene;

		// 置き換え
		nowScene = nextScene;
		nowScene->Initialize(dxCommon, input, audio);
	}

	// シーン更新
	nowScene->Update();
}

void SceneManager::Draw()
{
	nowScene->Draw();
}

void SceneManager::Destroy()
{
	delete nowScene;
	delete instance;
}
