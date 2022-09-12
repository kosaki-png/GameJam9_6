#include "Ranking.h"

Ranking::Ranking()
{
}

Ranking::~Ranking()
{
}

void Ranking::Initialize()
{
	std::string key;
	json.ReadJson("Resources/json/ranking.json");
}

void Ranking::setScore(std::string key, float data)
{
	//json�f�[�^�Ăяo��
	auto nog = json.obj.at(key).get<picojson::array>();
	//�Ō���Ƀf�[�^��}��
	nog.emplace_back(picojson::value(data));
	//�f�[�^���~���Ƀ\�[�g
	picojson::value tmp;
	for (int i = 0; i < nog.size(); i++)
	{
		for (int j = i + 1; j < nog.size(); j++)
		{
			if (nog[i].get<float>() < nog[j].get<float>())
			{
				tmp = nog[i];
				nog[i] = nog[j];
				nog[j] = tmp;
			}
		}
	}

	//�]�v�Ȗ����Ƀf�[�^���폜
	nog.erase(nog.end() - 1);
}

void Ranking::WriteJson()
{
	json.WriteJson("Resources/json/ranking.json");
}
