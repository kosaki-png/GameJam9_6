#pragma once
#include <array>
#include "ParticleManager.h"
#include "CollisionPrimitive.h"

#include "BaseScene.h"
#include "BaseWave.h"

#include "OptionGS.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

private:
	// 地面
	Object3d* objGround = nullptr;
	Model* modelGround = nullptr;

	// 天球
	Object3d* objSky = nullptr;
	Model* modelSky = nullptr;

	// クロスヘア
	Sprite* cross = nullptr;
	float sensi = 0;

	// オプション用
	OptionGS* option = nullptr;

	// ウェーブ
	BaseWave* wave = nullptr;
};

