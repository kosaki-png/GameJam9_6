#include "FollowWave.h"

using namespace DirectX;

FollowWave::FollowWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

FollowWave::~FollowWave()
{
	delete target;
	delete ui;
}

void FollowWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// ui�̏�����
	BaseWave::Initialize(input, camera, audio);

	// �����ɏ���������
	{
		target = new MoveTarget();
		target->Initialize("sphere");
		target->SetVelocity({ 0.02f,0.01f,0.0f });
		target->SetAmplitude({ 3.0f,3.0f,0.0f });
	}
}

void FollowWave::Update()
{
	// �����ɍX�V����
	{
		// �������C�̍X�V
		{
			XMFLOAT3 tmp = camera->GetEye();
			ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
			tmp = camera->GetDir();
			ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		}

		// �������C�ƓI�Ƃ̓����蔻��
		if (input->PushMouseLeft())
		{
			if (Collision::CheckRay2Sphere(ray, target->GetSphere()))
			{
				// �����Ă���Ȃ�E��
					ui->AddScore(1);
					ui->AddCount();
					//�q�b�g����炷
					audio->PlayWave(L"Resources/sound/r7nlp-8pgbr.wav");
			}
			else
			{
				// ����ł����Ȃ�~�X�J�E���g�𑝂₷
				ui->AddMiss();
			}
		}

		target->Update();
	}

	// ui�̍X�V
	BaseWave::Update();
}

void FollowWave::Draw()
{
	// �����ɕ`�揈��
	{
		target->Draw();
	}
}

void FollowWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}
