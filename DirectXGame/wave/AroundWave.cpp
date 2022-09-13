#include "AroundWave.h"

using namespace DirectX;

AroundWave::AroundWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

AroundWave::~AroundWave()
{
	delete target;
}

void AroundWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// ui�̏�����
	BaseWave::Initialize(input, camera, audio);

	target = new BaseTarget();
	target->Initialize();
}

void AroundWave::Update()
{
	// �������C�̍X�V
	XMFLOAT3 tmp = camera->GetEye();
	ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
	tmp = camera->GetDir();
	ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);

	if (input->TriggerMouseLeft())
	{
		if (Collision::CheckRay2Sphere(ray, target->GetSphere()))
		{
			ui->AddScore();
			ResetPos();
		}
	}

	if (ui->IsTimeUp())
	{
		clearFlag = true;
	}

	target->Update();

	// ui�̍X�V
	BaseWave::Update();
}

void AroundWave::Draw()
{
	target->Draw();
}

void AroundWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}

void AroundWave::ResetPos()
{
	// �p�x�Z�b�g
	rad = (float)(rand() % 360);
	//rad = rad * PI / 180;

	height = rand() % 5 - 2;

	target->SetPosition({ sinf(rad) * 5, (float)height, cosf(rad) * 5 - 5 });
}
