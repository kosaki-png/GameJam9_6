#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
	safe_delete(ba);
	safe_delete(groundBase0);
	safe_delete(groundBase1);
	safe_delete(night);
	safe_delete(star);
	safe_delete(fort);
	for (int i = 0; i < 2; i++)
	{
		safe_delete(back[i]);
		safe_delete(ground0[i]);
		safe_delete(ground1[i]);
		safe_delete(mountain0[i]);
		safe_delete(mountain1[i]);
		safe_delete(mountain2[i]);
		safe_delete(mountain3[i]);
		safe_delete(sun[i]);
	}
	for (auto x : sighboard)
	{
		safe_delete(x);
	}
}

void BackGround::Initialize()
{
	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			Sprite::LoadTexture(1, L"Resources/back00.png");
			Sprite::LoadTexture(2, L"Resources/back03.png");
			Sprite::LoadTexture(3, L"Resources/mountain02.png");
			Sprite::LoadTexture(4, L"Resources/mountain03.png");
			Sprite::LoadTexture(5, L"Resources/night.png");

			Sprite::LoadTexture(10, L"Resources/ground_01.png");
			Sprite::LoadTexture(11, L"Resources/ground_02.png");
			Sprite::LoadTexture(12, L"Resources/groundBase_01.png");
			Sprite::LoadTexture(13, L"Resources/groundBase_02.png");

			Sprite::LoadTexture(15, L"Resources/star.png");
			Sprite::LoadTexture(16, L"Resources/sun01.png");
			Sprite::LoadTexture(17, L"Resources/sun02.png");
			Sprite::LoadTexture(18, L"Resources/mountain04.png");
			Sprite::LoadTexture(19, L"Resources/mountain05.png");

			Sprite::LoadTexture(21, L"Resources/fort.png");
			Sprite::LoadTexture(22, L"Resources/500.png");
			Sprite::LoadTexture(23, L"Resources/1000.png");
			Sprite::LoadTexture(24, L"Resources/2000.png");
			Sprite::LoadTexture(25, L"Resources/3000.png");
			Sprite::LoadTexture(26, L"Resources/4000.png");
		}

		// スプライト生成
		{
			for (int i = 0; i < 2; i++)
			{
				// 背景
				back[i] = Sprite::Create(i + 1, { 0, 0 });

				ground0[i] = Sprite::Create(10, { -1280.0f * i, 0 });
				ground1[i] = Sprite::Create(11, { -1280.0f * i, 0 });

				// 山（スクロール用）
				mountain0[i] = Sprite::Create(3, { -1280.0f * i, 0 });
				mountain1[i] = Sprite::Create(4, { -1280.0f * i, 0 });

				// 山（スクロール用）
				mountain2[i] = Sprite::Create(18, { -1280.0f * i, 0 });
				mountain3[i] = Sprite::Create(19, { -1280.0f * i, 0 });

				// 太陽
				sun[i] = Sprite::Create(i + 16, { 0,0 });
			}

			// 看板
			sighboard[0] = Sprite::Create(26, { -5000,160 });
			sighboard[1] = Sprite::Create(25, { -10000,160 });
			sighboard[2] = Sprite::Create(24, { -15000,160 });
			sighboard[3] = Sprite::Create(23, { -20000,160 });
			sighboard[4] = Sprite::Create(22, { -22500,160 });

			// 砦
			fort = Sprite::Create(21, { -25000, 0 });

			// 地面
			groundBase0 = Sprite::Create(12, { 0, 0 });
			groundBase1 = Sprite::Create(13, { 0, 0 });
			night = Sprite::Create(5, { 0,0 });
			star = Sprite::Create(15, { 0,0 });
		}
	}

	star->SetAlpha(0);

	sunCount = 0;
}

void BackGround::Update()
{
	static XMFLOAT2 position = { 0,0 };

	// 太陽の上下
	{
		position = sun[0]->GetPosition();
		if (speed >= 9 && position.y >= -50)
		{
			position.y -= 0.5f;
		}
		else
		{
			position.y += 0.5f;
		}
		sun[0]->SetPosition(position);
		sun[1]->SetPosition(position);
	}

	star->SetAlpha(position.y / 250);

	// ゲームオーバー
	if (position.y > 250)
	{
		over = true;
	}

	// 背景スクロール
	{
		for (int i = 0; i < 2; i++)
		{
			// 動かして一定ラインで戻す
			{
				// 通常

				{
					// 山1
					position = mountain2[i]->GetPosition();
					position.x += speed * 0.4f;
					if (position.x >= 1280.0f)
					{
						position.x = -1280.0f;
					}
					mountain2[i]->SetPosition(position);
					// 山2
					position = mountain3[i]->GetPosition();
					position.x += speed * 0.5f;
					if (position.x >= 1280.0f)
					{
						position.x = -1280.0f;
					}
					mountain3[i]->SetPosition(position);

					// 地面
					position = ground1[i]->GetPosition();
					position.x += speed;
					if (position.x >= 1280.0f)
					{
						position.x = -1280.0f + speed * 2.5f;
					}
					ground1[i]->SetPosition(position);
				}

				// 悪夢
				{
					// 山1
					position = mountain0[i]->GetPosition();
					position.x += speed * 0.4f;
					if (position.x >= 1280.0f)
					{
						position.x = -1280.0f;
					}
					mountain0[i]->SetPosition(position);
					// 山2
					position = mountain1[i]->GetPosition();
					position.x += speed * 0.5f;
					if (position.x >= 1280.0f)
					{
						position.x = -1280.0f;
					}
					mountain1[i]->SetPosition(position);

					// 地面
					position = ground0[i]->GetPosition();
					position.x += speed;
					if (position.x >= 1280.0f)
					{
						position.x = -1280.0f + speed * 2.5f;
					}
					ground0[i]->SetPosition(position);
				}

				// 看板
				for (int i = 0; i < 5; i++)
				{
					sighboard[i]->MovePosition({ speed / 4, 0 });
				}
				// 砦
				fort->MovePosition({ speed / 4, 0 });
			}
		}
	}

	sunCount++;
}

void BackGround::Draw()
{
	back[mode]->Draw();

	star->Draw();

	if (sun[0]->GetPosition().y > 100)
	{
		if (sunCount % 30 < 15)
		{
			sun[mode]->Draw();
		}
	}
	else
	{
		sun[mode]->Draw();
	}

	if (mode)
	{
		groundBase1->Draw();
		// スクロール用
		for (int i = 0; i < 2; i++)
		{
			// 山
			mountain2[i]->Draw();
			mountain3[i]->Draw();
			// 地面
			ground1[i]->Draw();
		}
		// 弟子
		for (int i = 0; i < 5; i++)
		{
			sighboard[i]->Draw();
		}
		// 砦
		fort->Draw();

		night->Draw();
	}
	else
	{
		groundBase0->Draw();
		// スクロール用
		for (int i = 0; i < 2; i++)
		{
			// 山
			mountain0[i]->Draw();
			mountain1[i]->Draw();
			// 地面
			ground0[i]->Draw();
		}
		// 弟子
		for (int i = 0; i < 5; i++)
		{
			sighboard[i]->Draw();
		}
		// 砦
		fort->Draw();
	}
}

std::vector<DirectX::XMFLOAT2> BackGround::GetSignPos()
{
	std::vector<XMFLOAT2> signPos;
	for (int i = 0; i < 5; i++)
	{
		signPos.push_back(sighboard[i]->GetPosition());
	}
	return signPos;
}
