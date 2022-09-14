#include "TrackWave.h"

using namespace DirectX;

TrackWave::TrackWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

TrackWave::~TrackWave()
{
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		delete targets[i];
	}
}

void TrackWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// ui�̏�����
	BaseWave::Initialize(input, camera, audio);

	// �����ɏ���������
	{
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			// �^�[�Q�b�g����
			targets[i] = new BaseTarget();
			targets[i]->Initialize("sphere");
		}
	}

	// �S�Đ������Ă���ʒu���Z�b�g
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		// �����ʒu�Z�b�g
		targets[i]->SetPosition(ResetPos());
		//�����ړ��ʃZ�b�g
		targets[i]->SetVelocity(ResetVel());

		targets[i]->SetMoveTime(ResetMoveTime());
	}
}

void TrackWave::Update()
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

		// �S�Ă̓I�ɓ������Ă��邩
		bool allColl = false;
		// �I���Ƃɓ����蔻��
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			// �������C�ƓI�Ƃ̓����蔻��
			if (Collision::CheckRay2Sphere(ray, targets[i]->GetSphere()))
			{
				float life = targets[i]->GetLife();
				life -= 1;
				targets[i]->SetLife(life);
				targets[i]->SetMode(true);
				// �ǂꂩ��ɂł��������Ă���
				allColl = true;
			}
			else
			{
				targets[i]->SetMode(false);
			}

			if (targets[i]->GetLife() == 0)
			{
				//�X�R�A�ǉ�
				ui->AddScore(50);
				ui->AddCount();
				//�q�b�g����炷
				//audio->PlayWave(L"Resources/sound/r7nlp-8pgbr.wav");

				targets[i]->SetLife(60);

				// �ʒu���Z�b�g
				targets[i]->SetPosition(ResetPos());
				//�ړ��ʃ��Z�b�g
				targets[i]->SetVelocity(ResetVel());
			}

			targets[i]->SetMoveTime(targets[i]->GetMoveTime() - 0.5);

			if (targets[i]->GetMoveTime() == 0)
			{
				XMFLOAT3 tmp = XMFLOAT3(targets[i]->GetVelocity().x * -1, targets[i]->GetVelocity().y, targets[i]->GetVelocity().z);
				targets[i]->SetVelocity(tmp);
				targets[i]->SetMoveTime(ResetMoveTime());
			}


			// �I�̍X�V
			targets[i]->move();
			targets[i]->objUpdata();
		}

		if (ui->IsTimeUp())
		{
			clearFlag = true;
		}

		// ui�̍X�V
		BaseWave::Update();
	}
}

void TrackWave::Draw()
{
	// �����ɕ`�揈��
	{
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			targets[i]->Draw();
		}	}
}

void TrackWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}

XMFLOAT3 TrackWave::ResetPos()
{
	XMFLOAT3 result = { (float)(rand() % 15) - 7, (float)(rand() % 5) - 1, 0 };

	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		auto tmp = targets[i]->GetPosition();
		if (tmp.y == result.y)
		{
			return TrackWave::ResetPos();
		}
	}

	return result;

}

XMFLOAT3 TrackWave::ResetVel()
{
	XMFLOAT3 result = { ((float)(rand() % 5) -2) / 30, 0, 0 };

	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		if (result.x == 0)
		{
			return TrackWave::ResetVel();
		}
	}
	return result;
}

float TrackWave::ResetMoveTime()
{
	float result = (float)(rand() % 40)+1;
	return result;

}
