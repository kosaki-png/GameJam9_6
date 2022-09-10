#include "OptionGS.h"
#include "SpriteData.h"
#include "Collision.h"

using namespace DirectX;

OptionGS::OptionGS(Input* input, Camera* camera, Audio* audio)
	: input(input), camera(camera), audio(audio)
{
}

OptionGS::~OptionGS()
{
	delete option_base;
	for (int i = 0; i < 3; i++)
	{
		delete option_bar[i];
	}
}

void OptionGS::Initialize()
{
	// �X�v���C�g�����ݒ�
	{
		option_base = Sprite::Create(OPTION_BASE, { 0,0 });
		for (int i = 0; i < 3; i++)
		{
			option_bar[i] = Sprite::Create(OPTION_BAR, { 0,0 });
			option_bar[i]->SetPosition({800.0f, 350.0f + i * 150.0f - 5});
		}

		// ���x�擾
		sensi = camera->GetSensi();
		bar_ratio[0] = camera->GetSensi() / 3;

		// ����p�擾
		fov = camera->GetFov();
		bar_ratio[1] = (fov - 60.0f) / 60;

		// SE���ʎ擾
		bar_ratio[2];
	}
}

void OptionGS::Update()
{
	// �}�E�X�̍��W�擾
	mousePos = input->GetClientMousePos();

	// �����ύX
	if (input->PushMouseLeft())
	{
		// ���ꂼ��̃��[�^�[�œ����蔻��
		for (int i = 0; i < 3; i++)
		{
			XMFLOAT2 tmpPos = { 800.0f, 350.0f + i * 150.0f - 25 };
			XMFLOAT2 tmpSize = { 800.0f, 40 };
			// �������Ă���Ȃ炻�̈ʒu�Ń��[�^�[�Z�b�g
			if (Collision::CheckPoint2Box(mousePos, tmpPos, tmpSize))
			{
				float tmpLen = mousePos.x - 800.0f;
				option_bar[i]->SetSize({ tmpLen, 10 });

				// �����Z�b�g
				bar_ratio[i] = tmpLen / 800.0f;
			}
		}
	}

	// �p�����[�^�[�Z�b�g
	{
		// ���x�Z�b�g
		sensi = bar_ratio[0] * 3.0f;
		camera->SetSensi(sensi);

		// ����p�Z�b�g
		fov = bar_ratio[1] * 60.0f + 60.0f;
		camera->SetFov(fov);

		// SE���ʃZ�b�g

	}

	// �l��\��
	{
		// �}�E�X���x	���S��(600 * 400)
		sensi;

		// ����p		���S��(600 * 550)
		fov;

		// SE����		���S��(600 * 700)

	}
}

void OptionGS::Draw()
{
	if (isOption)
	{
		// �I�v�V�����̕`��
		option_base->Draw();
		for (int i = 0; i < 3; i++)
		{
			option_bar[i]->Draw();
		}
	}
}

void OptionGS::ChangeIsOption()
{
	isOption = !isOption;
	ShowCursor(isOption);
}
