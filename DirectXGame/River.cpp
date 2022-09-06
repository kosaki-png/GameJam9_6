#include "River.h"

#include "Define.h"

River::River()
{
}

River::~River()
{
	safe_delete(base);
	for (auto x : fall01)
	{
		safe_delete(x);
	}
}				

void River::Initialize()
{
	//�����ʒu
	F_position = { -700,0 };

	Sprite::LoadTexture(8, L"Resources/river.png");
	Sprite::LoadTexture(9,L"Resources/river1.png");

	base = Sprite::Create(8, F_position);
	base->SetSize({ 1280,720 });

	for (int i = 0; i < RIVER; ++i)
	{
		fall01[i] = Sprite::Create(9, F_position);
	}

	Speed = 5.0f;
}

void River::Update()
{

	Flow(UpDown_Flag);

	//�X�N���[��(������E��)
	{
		position1 = base->GetPosition();
		position1.x += Speed;
		base->SetPosition(position1);
	}
}

void River::Draw()
{
	base->Draw();

	for (int i = 0; i < RIVER; ++i)
	{
		fall01[i]->Draw();
	}
}

void River::ReStart()
{
	base->SetPosition(F_position);
	for (int i = 0; i < RIVER; ++i)
	{
		fall01[i]->SetPosition(F_position);
	}
}

void River::Flow(bool UpDown_Flag)
{
	float ki = 0.08f;
	float scrol = 0.59f;
	float min = 720.0f;

	//�����
	if (UpDown_Flag)
	{
		for (int i = 0; i < RIVER; i++)
		{
			size = fall01[i]->GetSize();
			size.x += ki;
			// �������Ĉ�胉�C���Ŗ߂�
			{
				//��
				position = fall01[i]->GetPosition();
				position.y -= scrol * (i + 3);
				position.x += Speed;

				if (position.y <= 0)
				{
					position.y = 360.0f;
					size.x = 1280.0f;
					size.y = 720.0f;
				}

				fall01[i]->SetPosition(position);
			}
		}
	}//������
	else
	{
		for (int i = 0; i < RIVER; i++)
		{
			size.x += ki;

			// �������Ĉ�胉�C���Ŗ߂�
			{
				//��
				position = fall01[i]->GetPosition();
				position.y += scrol * (i + 3);
				position.x += Speed;

				if (position.y >= min)
				{
					position.y = 0.0f;
					size.x = 1280.0f;
					size.y = 720.0f;
				}
				fall01[i]->SetPosition(position);
			}
		}
	}
}