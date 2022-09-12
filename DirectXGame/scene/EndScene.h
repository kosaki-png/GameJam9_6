#pragma once
#include "ParticleManager.h"
#include "BaseScene.h"
#include "ResultUi.h"
#include "object3d.h"

class EndScene :
	public BaseScene
{
public:
	EndScene();
	~EndScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

private:
	// ’n–Ê
	Object3d* objGround = nullptr;
	// “V‹…
	Object3d* objSky = nullptr;
	Model* modelGround = nullptr;
	Model* modelSky = nullptr;
	DirectX::XMFLOAT3 rot = { 0,0,0 };
	ResultUi* resultUi = nullptr;
};