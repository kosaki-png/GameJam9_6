﻿#pragma once
#include <array>
#include "ParticleManager.h"
#include "CollisionPrimitive.h"

#include "BaseScene.h"
#include "BaseWave.h"

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
	bool option = false;

	// 地面
	Object3d* objGround = nullptr;
	Model* modelGround = nullptr;

	// クロスヘア
	Sprite* cross = nullptr;
	float sensi = 0;

	// ウェーブ
	BaseWave* wave = nullptr;
};

