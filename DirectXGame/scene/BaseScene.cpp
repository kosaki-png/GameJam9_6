#include "BaseScene.h"
#include <cassert>


BaseScene::BaseScene()
{
}


BaseScene::~BaseScene()
{
	delete lightGroup;
	delete camera;
	delete tmpSprite;
}

void BaseScene::Initialize(DirectXCommon * dxCommon, Input * input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// モデル一覧所得
	modelMng = ModelManager::GetInstance();

	int a = 0;
	a++;
}