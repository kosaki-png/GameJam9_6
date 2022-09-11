#pragma once
#include <array>
#include "ParticleManager.h"
#include "CollisionPrimitive.h"

#include "BaseScene.h"
#include "BaseWave.h"

class TestScene :
    public BaseScene
{
public:
	TestScene();
	~TestScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

private:
	bool option = false;

	// �n��
	Object3d* objGround = nullptr;

	// �N���X�w�A
	Sprite* cross = nullptr;
	float sensi = 0;

	// �E�F�[�u
	BaseWave* wave = nullptr;
};

