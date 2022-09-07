#include "Ui.h"

Ui::Ui()
{
}

Ui::~Ui()
{
}

void Ui::Initialize()
{
	Sprite::LoadTexture(1, L"Resources/ui_01.png");
	ui = Sprite::Create(1,{ 300,0 });
}

void Ui::Update()
{
}

void Ui::Draw(ID3D12GraphicsCommandList* cmdList)
{
	ui->Draw();
	//score->DrawAll(cmdList);
	//timeLimit->DrawAll(cmdList);
}
