#include "BlackOut.h"
#include "SpriteData.h"

BlackOut::BlackOut()
{
}

BlackOut::~BlackOut()
{
	delete black;
}

void BlackOut::Initialize(DirectXCommon* dxCommon, Input* input)
{
	BaseTransition::Initialize(dxCommon, input);

	// �X�v���C�g�����ݒ�
	{
		black = Sprite::Create(BLACK, { 0,0 });
		black->SetSize({ 1920.0f, 1080.0f });
		black->SetAlpha(0.0f);
	}
}

void BlackOut::Start()
{
	// �X�v���C�g������
	black->SetAlpha(0.0f);

	// �V�[����ύX�s��
	canChange = false;

	// ���o�J�n
	isMove = true;
}

void BlackOut::Update()
{
	if (isMove)
	{
		// �J�ڑO
		if (!canChange)
		{
			if (alpha < 1.0f)
			{
				// ���񂾂�Z��
				alpha += 0.01f;
			}
			else
			{
				// �V�[����ύX�\��
				canChange = true;
			}
		}
		// �J�ڌ�
		else
		{
			if (alpha > 0.0f)
			{
				// ���񂾂񔖂�
				alpha -= 0.01f;
			}
			else
			{
				// ���o�I��
				isMove = false;
			}
		}

		black->SetAlpha(alpha);
	}
}

void BlackOut::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	{
		black->Draw();
	}
	Sprite::PostDraw();
}
