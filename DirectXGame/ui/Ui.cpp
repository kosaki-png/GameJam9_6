#include "Ui.h"

int   Ui::scoreNum = 0;//�X�R�A�̒l
float Ui::rateNum  = 0;//�����̒l
float Ui::countNum = 1;//���Ă����̒l
float Ui::missNum  = 0;//�O������

Ui::Ui()
{
}

Ui::~Ui()
{
	safe_delete(ui);
	safe_delete(score);
	safe_delete(timeLimit);
	safe_delete(rate);
	safe_delete(parcent);
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
	score->SetPos(700,7);
	score->SetSize(0.7f);

	//����������
	rate = new Score();
	rate->Initialize(2);
	rate->SetPos(1150,7);
	rate->SetSize(0.7f);

	//�p�[�Z���g������
	parcent = new Score();
	parcent->Initialize(2);
	parcent->SetPos(1200, 7);
	parcent->SetSize(0.7f);

	//�������ԏ�����
	Sprite::LoadTexture(3, L"Resources/font_sharp.png");
	timeLimit = new Score();
	timeLimit->Initialize(3);
	timeLimit->SetPos(900, -5);
	timeLimit->SetSize(0.9f);
	time = 59;

	// ���ԑ�����J�n������ԂŃC���X�^���X���쐬
	sw1 = diagnostics::Stopwatch::startNew();
}

void Ui::Update()
{
	float s = sw1->getElapsedSeconds();
	float d = 60 -s;
	timeLimit->Printf("0:%.0f",d);

	Rate();
	score->Printf("%d", scoreNum);
	parcent->Print("%", 1230, 25, 0.5f);
	rate->Printf("%.0f", rateNum);
}

void Ui::Draw(ID3D12GraphicsCommandList* cmdList)
{
	ui->Draw();
	score->DrawAll(cmdList);
	timeLimit->DrawAll(cmdList);
	rate->DrawAll(cmdList);
	parcent->DrawAll(cmdList);
}