#pragma once
#include "ParticleManager.h"

#include "BaseScene.h"
#include "SelectUi.h"
#include "XinputControll.h"
#include <array>
#include "Ranking.h"
#include "Text.h"

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
	void SetSelectMode(int mode);

private:
	Object3d* objField = nullptr;
	Object3d* objSky = nullptr;

	Sprite* menu = nullptr;
	Sprite* score = nullptr;

	SelectUi* selectUi = nullptr;

	bool select = false;
	Text* text = nullptr;

	// 選択用ボタン
	std::array<Button, 9> modeButton;
	Button startButton;

	std::string selectMode = "traning";
	WaveMode mode = WaveMode::traning;
	Ranking* ranking;
};
