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
#include "ModelManager.h"
#include "WaveManager.h"

class BaseScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	struct Button
	{
		XMFLOAT2 position = { 0,0 };
		XMFLOAT2 size = { 1,1 };
	};

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

	ModelManager* modelMng = nullptr;
	WaveManager* waveMng = nullptr;

	Camera* camera = nullptr;

	Text* text = nullptr;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };
	float ambientColor1[3] = { 1,1,1 };
	float ambientColor2[3] = { 1,1,1 };

	float centerX = 1920 / 2;
	float centerY = 1080 / 2;

	Sprite* tmpSprite = nullptr;
};
