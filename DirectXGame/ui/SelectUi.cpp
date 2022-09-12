#include "SelectUi.h"
#include "SpriteData.h"

SelectUi::SelectUi()
{
}

SelectUi::~SelectUi()
{
	for (int j = 0; j < 3; j++)
	{
		safe_delete(score[j]);
	}
}

void SelectUi::Initialize()
{
	ranking.Initialize();

	for (int j = 0; j < 3; j++)
	{
		score[j] = new Score();
		score[j]->Initialize(UI_FONT_1);
		score[j]->SetPos(300,400 + (j * 180));
	}
}

void SelectUi::Update(std::string key, picojson::object obj)
{
	//jsonデータ呼び出し
	auto nog = obj.at(key).get<picojson::array>();

	for (int j = 0; j < 3; j++)
	{
		score[j]->Printf("%d", nog[j].get<float>());
	}
}

void SelectUi::Draw(ID3D12GraphicsCommandList* cmdList)
{
	for (int j = 0; j < 3; j++)
	{
		score[j]->DrawAll(cmdList);
	}
}