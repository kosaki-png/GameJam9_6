#include "ResultUi.h"
#include "SpriteData.h"

ResultUi::ResultUi()
{
}

ResultUi::~ResultUi()
{
	delete score;
	delete accuracy;
	delete timeToKill;
	delete targets;
	delete hits;
	delete misses;
	delete parcent;
}

void ResultUi::Initialize()
{
	//スコア
	ui = new Ui();
	score = new Score();
	score->Initialize(UI_FONT_1);
	score->SetPos(150,350);
	score->SetSize(1.5f);

	//命中率
	accuracy = new Score();
	accuracy->Initialize(UI_FONT_1);
	accuracy->SetPos(830,350);
	accuracy->SetSize(1.5f);

	//パーセント表記
	parcent = new Score();
	parcent->Initialize(UI_FONT_2);

	//TTK
	timeToKill = new Score();
	timeToKill->Initialize(UI_FONT_1);
	timeToKill->SetPos(1430, 350);
	timeToKill->SetSize(1.5f);
	
	//撃った数
	targets = new Score();
	targets->Initialize(UI_FONT_1);
	targets->SetPos(150, 800);
	targets->SetSize(1.5f);

	//当たった数
	hits = new Score();
	hits->Initialize(UI_FONT_1);
	hits->SetPos(830,800);
	hits->SetSize(1.5f);

	//外した数
	misses = new Score();
	misses->Initialize(UI_FONT_1);
	misses->SetPos(1460, 800);
	misses->SetSize(1.5f);
}

void ResultUi::Update()
{
	auto hitsCount = ui->GetCount() - 1;

	ui->Rate();
	ui->KillTime();

	score->Printf("%d", ui->GetScore());
	accuracy->Printf("%.0f", ui->GetRate());
	parcent->Print("%", 1000, 400, 0.7f);
	timeToKill->Printf("%.2f", ui->GetKillTime());
	targets->Printf("%d", ui->GetTargetCount());
	hits->Printf("%.0f", hitsCount);
	misses->Printf("%.0f", ui->GetMiss());
}

void ResultUi::Draw(ID3D12GraphicsCommandList* cmdList)
{
	score->DrawAll(cmdList);
	accuracy->DrawAll(cmdList);
	parcent->DrawAll(cmdList);
	timeToKill->DrawAll(cmdList);
	targets->DrawAll(cmdList);
	hits->DrawAll(cmdList);
	misses->DrawAll(cmdList);
}
