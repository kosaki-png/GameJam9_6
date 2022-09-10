#pragma once
#include "ParticleManager.h"
#include "CollisionPrimitive.h"
#include "object3d.h"

#include "BaseScene.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

private:
	// ’n–Ê
	Object3d* objGround = nullptr;
	Model* modelGround = nullptr;
	// “V‹…
	Object3d* objSky = nullptr;
	Model* modelSky = nullptr;
	DirectX::XMFLOAT3 rot = { 0,0,0 };
};
