#include "Ui.h"

int   Ui::scoreNum = 0;//スコアの値
float Ui::rateNum  = 0;//割合の値
float Ui::countNum = 1;//当てた数の値
float Ui::missNum  = 0;//外した数

Ui::Ui()
{
}

Ui::~Ui()
{
}

void Ui::Initialize()
{
	//Ui初期化
	Sprite::LoadTexture(1, L"Resources/ui_01.png");
	ui = Sprite::Create(1,{ 640,0 });

	//スコア初期化
	Sprite::LoadTexture(2, L"Resources/font_cursive.png");
	score = new Score();
	score->Initialize(2);
	score->SetPos(700,7);
	score->SetSize(0.7f);

	//割合初期化
	rate = new Score();
	rate->Initialize(2);
	rate->SetPos(1150,7);
	rate->SetSize(0.7f);

	//パーセント初期化
	parcent = new Score();
	parcent->Initialize(2);
	parcent->SetPos(1200, 7);
	parcent->SetSize(0.7f);

	//制限時間初期化
	Sprite::LoadTexture(3, L"Resources/font_sharp.png");
	timeLimit = new Score();
	timeLimit->Initialize(3);
	timeLimit->SetPos(870, -5);
	timeLimit->SetSize(0.9f);
	time = 99999;
}

void Ui::Update()
{
	timeLimit->Printf("%.0f", time);
	time--;

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