#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include <DirectXMath.h>
#include "Camera.h"
#include "Text.h"
#include "LightGroup.h"
#include "SpriteData.h"
#include "SafeDelete.h"

struct SceneButton
{
	DirectX::XMFLOAT2 position = { 0,0 };
	DirectX::XMFLOAT2 scale = { 0,0 };
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	virtual void Update() = 0;

	virtual void Draw() = 0;

	BaseScene* GetNextScene() { return nextScene; }

protected:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;

	BaseScene* nextScene = nullptr;

	Camera* camera = nullptr;

	Text* text = nullptr;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	float centerX = 1920 / 2;
	float centerY = 1080 / 2;
};
