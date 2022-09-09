#include "FollowWave.h"

using namespace DirectX;

FollowWave::FollowWave()
{
}

FollowWave::~FollowWave()
{
	delete target;
	delete ui;
}

void FollowWave::Initialize(Input* input, Camera* camera)
{
	// ui‚Ì‰Šú‰»
	BaseWave::Initialize(input, camera);

	// ‚±‚±‚É‰Šú‰»ˆ—
	{
		target = new BaseTarget();
		target->Initialize("sphere");
	}
}

void FollowWave::Update()
{
	// ‚±‚±‚ÉXVˆ—
	{


		target->Update();
	}

	// ui‚ÌXV
	BaseWave::Update();
}

void FollowWave::Draw()
{
	// ‚±‚±‚É•`‰æˆ—
	{
		target->Draw();
	}
}

void FollowWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui‚Ì•`‰æ
	BaseWave::DrawUi(cmdList);
}
