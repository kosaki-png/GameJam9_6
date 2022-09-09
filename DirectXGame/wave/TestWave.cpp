/*#include "TestWave.h"

using namespace DirectX;

TestWave::TestWave()
{
}

TestWave::~TestWave()
{
	delete ui;
}

void TestWave::Initialize(Input* input, Camera* camera)
{
	// ui�̏�����
	BaseWave::Initialize(input, camera);

	// �����ɏ���������
	{

	}
}

void TestWave::Update()
{
	// �����ɍX�V����
	{

	}

	// ui�̍X�V
	BaseWave::Update();
}

void TestWave::Draw()
{
	// �����ɕ`�揈��
	{

	}
}

void TestWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}
*/

#include "TestWave.h"

using namespace DirectX;

TestWave::TestWave()
{
}

TestWave::~TestWave()
{
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		delete target[i];
	}
	delete ui;
}

void TestWave::Initialize(Input* input, Camera* camera)
{
	// ui�̏�����
	BaseWave::Initialize(input, camera);

	// �����ɏ���������
	{
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			target[i] = new BaseTarget();
			target[i]->Initialize("sphere");
			target[i]->SetPosition({ (float)(i % 5) - 2.0f, (float)(int)(i / 5) - 1 , 0 });
		}
	}
}

void TestWave::Update()
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
			if (Collision::CheckRay2Sphere(ray, target[i]->GetSphere()))
			{
				if (input->TriggerMouseLeft())
				{
					// �����Ă���Ȃ�E��
					if (!target[i]->GetIsDead())
					{
						target[i]->SetIsDead(true);
						ui->AddScore(10);
						ui->AddCount();
					}
					// ����ł����Ȃ�~�X�J�E���g�𑝂₷
					else
					{
						ui->AddMiss();
					}
				}

				// �ǂꂩ��ɂł��������Ă���
				allColl = true;
			}

			// ����
			if (target[i]->GetIsDead())
			{
				respownCnt[i]++;
				if (respownCnt[i] > 200)
				{
					target[i]->SetIsDead(false);
					respownCnt[i] = 0;
				}
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
			target[i]->Update();
		}
	}

	// ui�̍X�V
	BaseWave::Update();
}

void TestWave::Draw()
{
	// �����ɕ`�揈��
	{
		// �I�̕`��
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			target[i]->Draw();
		}
	}
}

void TestWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}
