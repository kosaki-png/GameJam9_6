#include "Ui.h"

int   Ui::scoreNum = 0;//�X�R�A�̒l
float Ui::rateNum  = 0;//�����̒l
float Ui::countNum = 0;//���Ă����̒l
float Ui::missNum  = 0;//�O������

Ui::Ui()
{
}

Ui::~Ui()
{
}

void Ui::Initialize()
{
	//Ui������
	Sprite::LoadTexture(1, L"Resources/ui_01.png");
	ui = Sprite::Create(1,{ 640,0 });

	//�X�R�A������
	Sprite::LoadTexture(2, L"Resources/font_cursive.png");
	score = new Score();
	score->Initialize(2);
	score->SetPos(700,9);
	score->SetSize(0.7f);

	//����������
	rate = new Score();
	rate->Initialize(2);
	rate->SetPos(1150,7);
	rate->SetSize(0.7f);

	//�������ԏ�����
	Sprite::LoadTexture(3, L"Resources/font_sharp.png");
	timeLimit = new Score();
	timeLimit->Initialize(3);
	timeLimit->SetPos(870, -5);
	timeLimit->SetSize(0.9f);
	time = 9999;
}

void Ui::Update(Input* input)
{
	timeLimit->Printf("%.2f", time);
	time--;
    		
	if (countNum != 0 || missNum != 0)
	{
		Rate();
	}

	score->Printf("%d", scoreNum);

	rate->Printf("%.0f", rateNum);
}

void Ui::Draw(ID3D12GraphicsCommandList* cmdList)
{
	ui->Draw();
	score->DrawAll(cmdList);
	timeLimit->DrawAll(cmdList);
	rate->DrawAll(cmdList);
}