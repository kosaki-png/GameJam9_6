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
	// スプライト初期設定
	{
		option_base = Sprite::Create(OPTION_BASE, { 0,0 });
		for (int i = 0; i < 3; i++)
		{
			option_bar[i] = Sprite::Create(OPTION_BAR, { 0,0 });
			option_bar[i]->SetPosition({800.0f, 350.0f + i * 150.0f - 5});
		}

		// 感度取得
		sensi = camera->GetSensi();
		bar_ratio[0] = camera->GetSensi() / 3;

		// 視野角取得
		fov = camera->GetFov();
		bar_ratio[1] = (fov - 60.0f) / 60;

		// SE音量取得
		bar_ratio[2];
	}
}

void OptionGS::Update()
{
	// マウスの座標取得
	mousePos = input->GetClientMousePos();

	// 割合変更
	if (input->PushMouseLeft())
	{
		// それぞれのメーターで当たり判定
		for (int i = 0; i < 3; i++)
		{
			XMFLOAT2 tmpPos = { 800.0f, 350.0f + i * 150.0f - 25 };
			XMFLOAT2 tmpSize = { 800.0f, 40 };
			// 当たっているならその位置でメーターセット
			if (Collision::CheckPoint2Box(mousePos, tmpPos, tmpSize))
			{
				float tmpLen = mousePos.x - 800.0f;
				option_bar[i]->SetSize({ tmpLen, 10 });

				// 割合セット
				bar_ratio[i] = tmpLen / 800.0f;
			}
		}
	}

	// パラメーターセット
	{
		// 感度セット
		sensi = bar_ratio[0] * 3.0f;
		camera->SetSensi(sensi);

		// 視野角セット
		fov = bar_ratio[1] * 60.0f + 60.0f;
		camera->SetFov(fov);

		// SE音量セット

	}

	// 値を表示
	{
		// マウス感度	中心約(600 * 400)
		sensi;

		// 視野角		中心約(600 * 550)
		fov;

		// SE音量		中心約(600 * 700)

	}
}

void OptionGS::Draw()
{
	if (isOption)
	{
		// オプションの描画
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
