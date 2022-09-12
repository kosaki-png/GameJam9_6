#include "Ui.h"
#include "SpriteData.h"

int Ui::scoreNum = 0;
float Ui::countNum = 1;
float Ui::missNum = 0;
float Ui::rateNum = 0;
float Ui::targetsNum = 0;
float Ui::timeToKill = 0; //キル速

Ui::Ui()
{
}

Ui::~Ui()
{
	safe_delete(ui);
	//delete score;
	safe_delete(score);
	safe_delete(timeLimit);
	safe_delete(rate);
	safe_delete(parcent);
}

void Ui::Initialize()
{
	rateNum = 100;     //割合の値
	scoreNum = 0;    //スコアの値
	initialValue = 0;//初期値
	onePlace = 0;    //1の位
	tenPlace = 0;    //10の位
	hundredPlace = 1;//100の位
	countNum = 1;    //当てた数の値
	missNum = 0;     //外した数
	targetsNum = 0;  //撃った数
	timeToKill = 0;  //キル速

	//Ui初期化
	ui = Sprite::Create(UI_SCORE,{ 640,0 });

	//スコア初期化
	score = new Score();
	score->Initialize(UI_FONT_2);
	score->SetPos(700,7);
	score->SetSize(0.7f);

	//割合初期化
	rate = new Score();
	rate->Initialize(UI_FONT_2);
	rate->SetPos(1150,7);
	rate->SetSize(0.7f);

	//パーセント初期化
	parcent = new Score();
	parcent->Initialize(UI_FONT_2);
	parcent->SetPos(1200, 7);
	parcent->SetSize(0.7f);

	//制限時間初期化
	timeLimit = new Score();
	timeLimit->Initialize(UI_FONT_1);
	timeLimit->SetPos(900, -5);
	timeLimit->SetSize(0.9f);

	// 時間測定を開始した状態でインスタンスを作成
	timer = diagnostics::Stopwatch::startNew();
}

void Ui::Update(std::string key,picojson::object obj)
{
	if (!IsTimeUp())
	{
		TimerManage();
	}

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
		//SetNum(initialValue, 9);
		onePlace = 9;
		//timer->restart();
		tenPlace--;
	}

	if (tenPlace < 0)
	{
		SetNum(tenPlace, 5);

		if (!IsTimeUp())
		{
			hundredPlace--;
		}
	}

	//onePlace = initialValue - timer->getElapsedSeconds();
	//onePlace = initialValue;
	onePlace -= 0.016f;
}
