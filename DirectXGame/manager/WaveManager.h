#pragma once
#include "BaseWave.h"
#include "EasyWave.h"
#include "FlickWave.h"
#include "FollowWave.h"
#include "TestWave.h"
#include "AroundWave.h"

enum class WaveMode
{
	test = 0,
	easy = 1,
	flick_easy = 2,
	flick_normal = 3,
	flick_hard = 4,
	flick_hell = 5,
	follow = 6,
	around = 7
};

class WaveManager
{
public:
	static WaveManager* GetInstance();

	void SetWaveMode(WaveMode mode) { this->mode = mode; }
	WaveMode GetWaveMode() { return mode; }

	void Initialize(Input* input, Camera* camera, Audio* audio);
	void Update();
	void Draw();
	void DrawUi(ID3D12GraphicsCommandList* cmdList);

	bool GetClearFlag();

	bool GetIsCount();

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

