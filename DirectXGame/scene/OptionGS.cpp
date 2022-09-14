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
	// �X�v���C�g�����ݒ�
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

		//json�f�[�^�Ăяo��
		auto nog = json.obj.at(node.name).get<picojson::array>();

		for (int i = 0; i < 3; i++)
		{
			node.datas.push_back(nog[i].get<double>());
		}

		// ���x�擾
		sensi = node.datas[0];
		bar_ratio[0] = sensi / 3;

		// ����p�擾
		fov = node.datas[1];
		bar_ratio[1] = (fov - 60.0f) / 60;

		// SE���ʎ擾
		bar_ratio[2];

		// �����̒����K�p
		for (int i = 0; i < 3; i++)
		{
			option_bar[i]->SetSize({ bar_ratio[i] * 800, 10 });
		}
	}
}

void OptionGS::Update()
{
	// �}�E�X�̍��W�擾
	mousePos = input->GetClientMousePos();

	//json�f�[�^�Ăяo��
	auto nog = json.obj.at(node.name).get<picojson::array>();
	
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
		nog[0] = picojson::value(sensi);

		// ����p�Z�b�g
		fov = bar_ratio[1] * 60.0f + 60.0f;
		camera->SetFov(fov);
		nog[1] = picojson::value(fov);
		// SE���ʃZ�b�g
		nog[2] = picojson::value(sensi);

	}

	// �l��\��
	{
		// �}�E�X���x	���S��(600 * 400)
		sensi;
		sensiTex->Printf("%.2f", sensi);
		// ����p		���S��(600 * 550)
		fov;
		fovTex->Printf("%.1f", fov);
		// SE����		���S��(600 * 700)

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
		// �I�v�V�����̕`��
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
