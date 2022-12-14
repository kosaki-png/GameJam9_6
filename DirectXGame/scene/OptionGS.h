#pragma once
#include "Camera.h"
#include "Input.h"
#include "Audio.h"
#include "Sprite.h"
#include "Score.h"
#include <base/JsonFileManager.h>
#include <array>
#include "BaseScene.h"

class OptionGS
{
public:
	OptionGS(Input* input, Camera* camera, Audio* audio);
	~OptionGS();

	void Initialize();
	void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void ChangeIsOption();
	bool GetIsOption() { return isOption; }

	void WriteJson();

	BaseScene* GetNextScene() { return nextScene; }

private:
	Input* input = nullptr;
	Camera* camera = nullptr;
	Audio* audio = nullptr;

	// 設定用UI
	Sprite* option_base = nullptr;
	std::array<Sprite*, 3> option_bar = { nullptr, nullptr, nullptr };
	std::array<float, 3> bar_ratio = { 0,0,0 };

	// オプション中か
	bool isOption = false;

	// 設定項目
	float fov = 0;
	float sensi = 0;

	Score* fovTex;
	Score* sensiTex;

	// 指定用
	DirectX::XMFLOAT2 mousePos;

	JsonFileManager json;
	JsonFileManager::Node node;

	// シーン選択用
	Sprite* restartBar = nullptr;
	float ratio = 0;
	std::array<DirectX::XMFLOAT2, 2> pos;
	DirectX::XMFLOAT2 restartSize = { 500.0f, 100.0f };
	BaseScene* nextScene = nullptr;
};