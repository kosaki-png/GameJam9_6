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
		//number番号の盗賊の位置と j番の盗賊の位置が当たっていたら
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
	/* 乱数の種を初期化 */
	srand((unsigned)time(NULL));

	for (int i = 0, size = enemy; i < size; i++)
	{
		do {
			// 座標抽選
			posX[i] = rand() % 300 + 1;
			posY[i] = rand() % 500 + 300;

		} while (Check(i));
	}

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			Sprite::LoadTexture(14, L"Resources/盗賊A.png");
			Sprite::LoadTexture(20, L"Resources/盗賊.png");
		}

		// スプライト生成
		{
			for (int i = 0, size = enemy; i < size; i++)
			{
				e_Pos[i] = { -1200,0 };
				e_Pos[i] = { e_Pos[i].x + posX[i],posY[i] };
				thieves[i] = Sprite::Create(14, { e_Pos[i].x ,e_Pos[i].y });
				Drawflag[i] = true;
			}
		}

		//スプライトサイズ変更
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
			// 座標抽選
			posX[i] = rand() % 300 + 1;
			posY[i] = rand() % 500 + 300;
		} while (Check(i));
		e_Pos[i] = { -1200,0 };
		e_Pos[i] = { e_Pos[i].x + posX[i],posY[i] };
		thieves[i]->SetPosition(e_Pos[i]);
		Drawflag[i] = true;
	}

}
