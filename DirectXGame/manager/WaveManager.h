#pragma once
#include "BaseWave.h"
#include "EasyWave.h"
#include "FlickWave.h"
#include "FollowWave.h"
#include "TestWave.h"

enum class WaveMode
{
	test = 0,
	easy = 1,
	flick_easy = 2,
	filck_normal = 3,
	flick_hard = 4,
	flick_hell = 5,
	follow = 6
};

class WaveManager
{
public:
	static WaveManager* GetInstance();

	void SetWaveMode(WaveMode mode) { this->mode = mode; }
	WaveMode GetWaveMode() { return mode; }

	void Initialize(Input* input, Camera* camera);
	void Update();
	void Draw();
	void DrawUi(ID3D12GraphicsCommandList* cmdList);

	bool GetClearFlag();

	void DestroyWave();
	void Destroy();

	BaseWave* GetWave() { return wave; }

private:
	WaveManager() = default;
	~WaveManager() = default;;

	static WaveManager* instance;

	WaveMode mode = WaveMode::test;

	BaseWave* wave = nullptr;
};

