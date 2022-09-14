#pragma once
#include "BaseWave.h"
#include "EasyWave.h"
#include "FlickWave.h"
#include "FollowWave.h"
#include "TestWave.h"
#include "AroundWave.h"
#include "EasyWave.h"
#include "TrackWave.h"

enum class WaveMode
{
	traning = 0,
	flick_easy = 1,
	flick_normal = 2,
	flick_hard = 3,
	flick_hell = 4,
	around = 5,
	follow = 6,
	track = 7,
	scale = 8
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

	WaveMode mode = WaveMode::traning;

	BaseWave* wave = nullptr;
};

