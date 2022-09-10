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

	// �ŏ��̃V�[��
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

	// �l����������
	if (nextScene)
	{
		// ���̃V�[�������
		delete nowScene;

		// �u������
		nowScene = nextScene;
		nowScene->Initialize(dxCommon, input, audio);
	}

	// �V�[���X�V
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
