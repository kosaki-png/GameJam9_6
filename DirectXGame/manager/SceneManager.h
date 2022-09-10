#pragma once
#include "BaseScene.h"
#include "BaseTransition.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();

	/// <summary>
	/// Œ»İ‚ÌƒV[ƒ“æ“¾
	/// </summary>
	/// <returns></returns>
	BaseScene* GetNowScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);
	void Update();
	void Draw();

	void Destroy();

private:
	static SceneManager* instance;

	SceneManager() = default;
	~SceneManager() = default;

	BaseScene* nowScene = nullptr;

	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;

	BaseTransition* transition = nullptr;
};