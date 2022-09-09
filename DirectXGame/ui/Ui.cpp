#include "Ui.h"

int Ui::scoreNum = 0;

Ui::Ui()
{
}

Ui::~Ui()
{
	safe_delete(ui);
	delete score;
	safe_delete(timeLimit);
	safe_delete(rate);
	safe_delete(parcent);
}

void Ui::Initialize()
{
	rateNum = 0;     //�����̒l
	scoreNum = 0;    //�X�R�A�̒l
	initialValue = 0;//�����l
	onePlace = 0;    //1�̈�
	tenPlace = 0;    //10�̈�
	hundredPlace = 1;//100�̈�
	countNum = 1;    //���Ă����̒l
	missNum = 0;     //�O������
	
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

	// ���ԑ�����J�n������ԂŃC���X�^���X���쐬
	timer = diagnostics::Stopwatch::startNew();
	onePlace = 0;
}

void Ui::Update()
{
	TimerManage();
	timeLimit->Printf("%d:%d%.0f",hundredPlace,tenPlace,onePlace);

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

void Ui::TimerManage()
{
	if (onePlace < 0)
	{
		SetNum(initialValue, 9);
		timer->restart();
		tenPlace--;
	}

	if (tenPlace < 0)
	{
		SetNum(tenPlace, 5);
		hundredPlace--;
	}

	onePlace = initialValue - timer->getElapsedSeconds();
}
