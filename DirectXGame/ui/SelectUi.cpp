#include "SelectUi.h"
#include "SpriteData.h"

SelectUi::SelectUi()
{
}

SelectUi::~SelectUi()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			safe_delete(score[i][j]);
		}
	}
}

void SelectUi::Initialize()
{
	//1ˆÊƒXƒRƒA
	ui = new Ui();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			score[i][j] = new Score();
			score[i][j]->Initialize(UI_FONT_1);
			score[i][j]->SetPos(300,400 + (j * 180));
		}
	}
}

void SelectUi::Update()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			score[i][j]->Printf("%d", ui->GetScore());
		}
	}
}

void SelectUi::Draw(ID3D12GraphicsCommandList* cmdList)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			score[i][j]->DrawAll(cmdList);
		}
	}
}
