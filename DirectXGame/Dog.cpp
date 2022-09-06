#include "Dog.h"

Dog::Dog()
{
}

Dog::~Dog()
{
	safe_delete(dog);
}

bool Dog::Initialize()
{
	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			Sprite::LoadTexture(7, L"Resources/dog2.png");
			Sprite::LoadTexture(27, L"Resources/dog.png");
		}

		// スプライト生成
		{
			// 背景
			dog = Sprite::Create(7, { Rand().x,Rand().y });
		}
	}

	trackPoint = { 600,500};

	return true;
}

void Dog::Update()
{
	position = dog->GetPosition();

	position.x += speed;
	
	Traking();

	if (position.x > trackPoint.x)
	{
		track_flag = false;
	}

	dog->SetPosition(position);
}

void Dog::Traking()
{
	//速度
	float move = 2.0f;

	XMFLOAT2 dir;
	dir.y = trackPoint.y - position.y;

	float length = sqrtf(dir.y * dir.y);
	XMFLOAT2 normalize;
	normalize.y = dir.y / length;
	position.y += normalize.y / move;
}

XMFLOAT2 Dog::Rand()
{
	const float rnd_posX = -3840.0f;
	const float rnd_posY = 1400.0f;

	XMFLOAT2 pos{};
	pos.x = (float)rand() / RAND_MAX * rnd_posX / 2.0f;
	pos.y = (float)rand() / RAND_MAX * rnd_posY / 2.0f;

	if (pos.x < 0)
	{
		pos.x -= 320;
	}

	if (pos.y <= 300)
	{
		pos.y += 230;
	}

	return pos;
}

void Dog::ReStart()
{
	position = { Rand().x, Rand().y };

	dog->SetPosition(position);
}

void Dog::Draw(bool sleep)
{
	if (sleep)
	{
		// 背景
		dog = Sprite::Create(27, { position.x ,position.y });
		dog->Draw();
	}
	else
	{
		// 背景
		dog = Sprite::Create(7, { position.x ,position.y });
		dog->Draw();
	}
}