#pragma once
#include "ParticleManager.h"
#include "BaseScene.h"

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

};