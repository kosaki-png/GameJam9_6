#include "Thieves.h"

Thieves::Thieves()
{
}

Thieves::~Thieves()
{
	for (auto x : thieves)
	{
		safe_delete(x);
	}
}

bool Thieves::Check(int number)
{
	for (int i = 0, size = number; i < size; i++)
	{
		//number�ԍ��̓����̈ʒu�� j�Ԃ̓����̈ʒu���������Ă�����
		if (Collision::IsCollidingDistance({posX[number],posY[number],width,height}, { posX[i],posY[i],width,height }))
		{
			return true;
		}
	}

	return false;
}

std::vector<DirectX::XMFLOAT2> Thieves::GetPosition()
{
	std::vector<XMFLOAT2> positions;
	for (int i = 0, size = enemy; i < size; i++)
	{
		{
		   positions.push_back(thieves[i]->GetPosition());
		}
	}
	return positions;
}

void Thieves::SetPosition(XMFLOAT2 positions)
{
	for (int i = 0, size = enemy; i < size; i++)
	{
		{
			thieves[i]->SetPosition(positions);
		}
	}
}

void Thieves::Initialize()
{
	/* �����̎�������� */
	srand((unsigned)time(NULL));

	for (int i = 0, size = enemy; i < size; i++)
	{
		do {
			// ���W���I
			posX[i] = rand() % 300 + 1;
			posY[i] = rand() % 500 + 300;

		} while (Check(i));
	}

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			Sprite::LoadTexture(14, L"Resources/����A.png");
			Sprite::LoadTexture(20, L"Resources/����.png");
		}

		// �X�v���C�g����
		{
			for (int i = 0, size = enemy; i < size; i++)
			{
				e_Pos[i] = { -1200,0 };
				e_Pos[i] = { e_Pos[i].x + posX[i],posY[i] };
				thieves[i] = Sprite::Create(14, { e_Pos[i].x ,e_Pos[i].y });
				Drawflag[i] = true;
			}
		}

		//�X�v���C�g�T�C�Y�ύX
		{
			for (int i = 0, size = enemy; i < size; i++)
			{
				thieves[i]->SetSize({ width,height });
			}
		}
	}
}

void Thieves::Update(float speed)
{
	this->speed = speed;

	for (int i = 0, size = enemy; i < size; i++)
	{
	    if(Drawflag[i])
	    e_Pos[i].x += speed;
	    thieves[i]->SetPosition(e_Pos[i]);
	    if (e_Pos[i].x >= 2560)
	    {
	    	Drawflag[i] = false;
	    }
	}
}

void Thieves::Draw(bool sleep)
{
	for (int i = 0, size = enemy; i < size; i++)
	{
		if (Drawflag[i] && sleep == false)
		{
			thieves[i] = Sprite::Create(14, { e_Pos[i].x ,e_Pos[i].y });
			thieves[i]->SetIsFlipX(true);
			thieves[i]->Draw();
		}
		else if (Drawflag[i] && sleep == true)
		{
			thieves[i] = Sprite::Create(20, { e_Pos[i].x ,e_Pos[i].y });
			thieves[i]->SetIsFlipX(true);
			thieves[i]->Draw();
		}
	}
}

void Thieves::Spawn()
{
	for (int i = 0, size = enemy; i < size; i++)
	{
		do {
			// ���W���I
			posX[i] = rand() % 300 + 1;
			posY[i] = rand() % 500 + 300;
		} while (Check(i));
		e_Pos[i] = { -1200,0 };
		e_Pos[i] = { e_Pos[i].x + posX[i],posY[i] };
		thieves[i]->SetPosition(e_Pos[i]);
		Drawflag[i] = true;
	}

}
