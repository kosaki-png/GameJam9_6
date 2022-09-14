#include "SceneManager.h"

#include "TestScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "EndScene.h"

#include "BlackOut.h"

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
	//nowScene = new TitleScene();
	//nowScene = new SelectScene();
	//nowScene = new GameScene();
	//nowScene = new EndScene();
	nowScene = new TestScene();

	nowScene->Initialize(dxCommon, input, audio);

	transition = new BlackOut();
	transition->Initialize(dxCommon, input);
}

void SceneManager::Update()
{
	BaseScene* nextScene = nowScene->GetNextScene();

	// �l���������Ƃ�
	if (nextScene)
	{
		// ���o�������Ă��Ȃ��Ȃ�
		if (!transition->GetIsMove())
		{
			transition->Start();
		}

		// ���o��
		if (transition->GetIsMove())
		{
			// �V�[�����~�߂�

		}

		// �܂�Ԃ�
		if (transition->GetCanChange())
		{
			// ���̃V�[�������
			delete nowScene;

			// �u������
			nowScene = nextScene;
			nowScene->Initialize(dxCommon, input, audio);
		}
	}

	// �V�[���X�V
	nowScene->Update();
	transition->Update();
}

void SceneManager::Draw()
{
	nowScene->Draw();
	transition->Draw();
}

void SceneManager::Destroy()
{
	delete nowScene;
	delete transition;
	delete instance;
}
