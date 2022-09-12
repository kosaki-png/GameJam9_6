#include "BaseWave.h"
#include "SpriteData.h"

using namespace DirectX;

BaseWave::BaseWave(Level level)
	: level(level)
{
}

BaseWave::~BaseWave()
{
	ranking.WriteJson();
	delete base;
	delete click;
	delete start;
}

void BaseWave::Initialize(Input* input, Camera* camera)
{
	this->input = input;
	this->camera = camera;

	// �������C�̏����ݒ�
	XMFLOAT3 tmp = camera->GetEye();
	ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
	tmp = camera->GetDir();
	ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);

	ui = new Ui();
	ui->Initialize();

	// �J�E���g�_�E���p
	base = Sprite::Create(COUNT_BASE, { 0,0 });
	click = Sprite::Create(CLICK, { 0,0 });
	start = Sprite::Create(START, { 0,0 });

	text = Text::GetInstance();

	ranking.Initialize();
}

void BaseWave::Update()
{
	// ui�̍X�V
	ui->Update();
}

void BaseWave::Draw()
{
}

void BaseWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	ui->Draw(cmdList);
}

void BaseWave::CountDown()
{
	if (!isStart)
	{
		// �N���b�N�ŊJ�n
		if (input->TriggerMouseLeft())
		{
			isStart = true;
		}
	}
	else
	{
		// �J�E���g�_�E��
		time -= 1.0f / 60;
		text->Printf("%f", time);
		text->SetPos(1920.0f / 2 -150, 1080.0f / 2 - 150);

		// �J�E���g�I��
		if (time <= 0)
		{
			isCount = false;
		}
	}
}

void BaseWave::CountDownDraw()
{
	if (isCount)
	{
		base->Draw();
		if (isStart)
		{
			click->Draw();
		}
		else
		{
			start->Draw();
		}
	}
}
