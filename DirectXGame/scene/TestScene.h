#pragma once
#include <array>
#include "ParticleManager.h"
#include "Text.h"
#include "DebugCamera.h"
#include "LightGroup.h"
#include "XinputControll.h"
#include "Sprite.h"
#include "Object3d.h"

#include "CollisionPrimitive.h"

#include "BaseScene.h"

#include "BaseTarget.h"
#include "Ui.h"

class TestScene :
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
	TestScene();
	~TestScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

private:
	Text* text;

	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	ParticleManager* particleMan = nullptr;

	float centerX = 1920 / 2;
	float centerY = 1080 / 2;

	XMFLOAT2 mousePos;

	Object3d* object = nullptr;
	Model* model = nullptr;

	// 視線のレイ
	Ray ray;

	std::array<BaseTarget*, 20> target;

	// 地面
	Object3d* objGround = nullptr;
	Model* modelGround = nullptr;

	// クロスヘア
	Sprite* cross = nullptr;
	float sensi = 0;

	// UI
	Ui* ui = nullptr;
};

