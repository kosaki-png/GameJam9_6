#include "FlickWave.h"

using namespace DirectX;

FlickWave::FlickWave()
{
}

FlickWave::~FlickWave()
{
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		delete targets[i];
	}

	delete ui;
}

void FlickWave::Initialize(Input* input, Camera* camera)
{
	// ui�̏�����
	BaseWave::Initialize(input, camera);

	// �����ɏ���������
	{
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			targets[i] = new BaseTarget();
			targets[i]->Initialize("sphere");
		}

		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			targets[i]->SetPosition(ResetPos());
		}
	}
}

void FlickWave::Update()
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
				if (input->TriggerMouseLeft())
				{
					ui->AddScore(10);
					ui->AddCount();

					// �ʒu���Z�b�g
					targets[i]->SetPosition(ResetPos());
				}

				// �ǂꂩ��ɂł��������Ă���
				allColl = true;
			}
		}

		// �S�Ăɓ������Ă��Ȃ�������
		if (!allColl)
		{
			if (input->TriggerMouseLeft())
			{
				// �~�X�𑝂₷
				ui->AddMiss();
			}
		}

		// �I�̍X�V
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			targets[i]->Update();
		}
	}

	// ui�̍X�V
	BaseWave::Update();
}

void FlickWave::Draw()
{
	// �����ɕ`�揈��
	{
		// �I�̕`��
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			targets[i]->Draw();
		}
	}
}

void FlickWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}

XMFLOAT3 FlickWave::ResetPos()
{
	XMFLOAT3 result = { (float)(rand() % 5) - 2, (float)(rand() % 4) - 1, 0 };

	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		auto tmp = targets[i]->GetPosition();
		if (tmp.x == result.x && tmp.y == result.y)
		{
			return FlickWave::ResetPos();
		}
	}

	return result;
}