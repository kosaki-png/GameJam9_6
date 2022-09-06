#pragma once

#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "Text.h"
#include "DebugCamera.h"
#include "LightGroup.h"
#include "XinputControll.h"

#include "BaseScene.h"

class TitleScene :
	public BaseScene
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

private: // 静的メンバ変数
	static const int texNumber = 0;

public:
	TitleScene();
	~TitleScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

private:
	Text* text;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	ParticleManager* particleMan = nullptr;

	Xinput xinput;

	float centerX = 1280 / 2;
	float centerY = 720 / 2;

	XMFLOAT2 mousePos;

	Sprite* title1 = nullptr;
	Sprite* title2 = nullptr;
	Sprite* sharp1 = nullptr;
	Sprite* sharp2 = nullptr;
	bool change = true; //切り替え

	// 隠し要素
	int sharpCnt = 0;
	int count = 0;
	bool sharpMode = false;

	Object3d* object = nullptr;
	Model* model = nullptr;
};
