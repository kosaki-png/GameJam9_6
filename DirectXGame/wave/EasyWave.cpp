#include "EasyWave.h"

EasyWave::EasyWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

EasyWave::~EasyWave()
{
	delete target;
}

void EasyWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// ui�̏�����
	BaseWave::Initialize(input, camera, audio);

	// �����ɏ���������
	{
		ResetTarget();

		// �����ʒu�Z�b�g
		target->SetPosition(ResetPos());
	}
}

void EasyWave::Update()
{
	// �����ɍX�V����
	{
		// �������C�̍X�V
		{
			XMFLOAT3 tmp = camera->GetEye();
			ray.start = DirectX::XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
			tmp = camera->GetDir();
			ray.dir = DirectX::XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		}

		if (input->TriggerMouseLeft())
		{
			ui->AddTargets();
		}

		// �S�Ă̓I�ɓ������Ă��邩
		bool allColl = false;
		//�����蔻��
		
		// �������C�ƓI�Ƃ̓����蔻��
		if (Collision::CheckRay2Sphere(ray, target->GetSphere()))
		{
			if (input->TriggerMouseLeft())
			{
				//�X�R�A�ǉ�
				ui->AddScore(10);
				ui->AddCount();
				//�q�b�g����炷
				audio->PlayWave(L"Resources/sound/r7nlp-8pgbr.wav");
			
				// �ʒu���Z�b�g
				target->SetPosition(ResetPos());
				delete target;
				target = nullptr;
			}

			// �ǂꂩ��ɂł��������Ă���
			allColl = true;
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

		//�I�����������̍Đ���
		if (target == nullptr)
		{
			ResetTarget();
			// �����ʒu�Z�b�g
			target->SetPosition(ResetPos());
		}

		// �I�̍X�V
		target->Update();
		
		// �N���A����
		{
			clearFlag = ui->IsTimeUp();
		}
	}

	// ui�̍X�V
	BaseWave::Update();
}

void EasyWave::Draw()
{
	// �����ɕ`�揈��
	{
		// �I�̕`��
		target->Draw();
	}
}

void EasyWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}

void EasyWave::ResetTarget()
{
	// �^�[�Q�b�g����
	target = new EasyTarget();
	target->Initialize("sphere", ResetPos());
	target->SetVelocity({ 0.01f,0.01f,0.01f });
	target->SetAmplitude({ 3.0f,0.0f,0.0f });

	//�X�P�[��
	float scale = 0;
	scale = 1.0f - 0.3f * 0;
	target->SetScale({ scale, scale, scale });
}

DirectX::XMFLOAT3 EasyWave::ResetPos()
{
	XMFLOAT3 result = { (float)(rand() % 5) - 2, (float)(rand() % 4) - 1, 0 };

	auto tmp = target->GetPosition();
	if (tmp.x == result.x && tmp.y == result.y)
	{
		return EasyWave::ResetPos();
	}
	
	return result;
}
