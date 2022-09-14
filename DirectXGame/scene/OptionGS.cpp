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
	delete fovTex;
	delete sensiTex;

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

		fovTex = new Score();
		fovTex->Initialize(UI_FONT_1);
		fovTex->SetPos(600,450);
		fovTex->SetSize(0.8f);

		sensiTex = new Score();
		sensiTex->Initialize(UI_FONT_1);
		sensiTex->SetPos(600,300);
		fovTex->SetSize(0.8f);

		json.ReadJson("Resources/json/option.json");

		node.name = "option";

		//jsonデータ呼び出し
		auto nog = json.obj.at(node.name).get<picojson::array>();

		for (int i = 0; i < 3; i++)
		{
			node.datas.push_back(nog[i].get<double>());
		}

		// 感度取得
		sensi = node.datas[0];
		bar_ratio[0] = sensi / 3;

		// 視野角取得
		fov = node.datas[1];
		bar_ratio[1] = (fov - 60.0f) / 60;

		// SE音量取得
		bar_ratio[2];

		// 初期の長さ適用
		for (int i = 0; i < 3; i++)
		{
			option_bar[i]->SetSize({ bar_ratio[i] * 800, 10 });
		}
	}
}

void OptionGS::Update()
{
	// マウスの座標取得
	mousePos = input->GetClientMousePos();

	//jsonデータ呼び出し
	auto nog = json.obj.at(node.name).get<picojson::array>();
	
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
		nog[0] = picojson::value(sensi);

		// 視野角セット
		fov = bar_ratio[1] * 60.0f + 60.0f;
		camera->SetFov(fov);
		nog[1] = picojson::value(fov);
		// SE音量セット
		nog[2] = picojson::value(sensi);

	}

	// 値を表示
	{
		// マウス感度	中心約(600 * 400)
		sensi;
		sensiTex->Printf("%.2f", sensi);
		// 視野角		中心約(600 * 550)
		fov;
		fovTex->Printf("%.1f", fov);
		// SE音量		中心約(600 * 700)

	}

	{

		picojson::array arr;
		for (int i = 0; i < nog.size(); i++)
		{
			arr.emplace_back(picojson::value(nog[i]));
		}
		json.obj[node.name] = picojson::value(arr);
	}
}

void OptionGS::Draw(ID3D12GraphicsCommandList* cmdList)
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

	fovTex->DrawAll(cmdList);
	sensiTex->DrawAll(cmdList);
}

void OptionGS::ChangeIsOption()
{
	isOption = !isOption;
	ShowCursor(isOption);
}

void OptionGS::WriteJson()
{
	json.WriteJson("Resources/json/option.json");
}
