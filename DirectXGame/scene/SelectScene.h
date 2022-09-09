#pragma once
#include "ParticleManager.h"

#include "BaseScene.h"
#include "XinputControll.h"

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

private:

};
