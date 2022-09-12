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
	//jsonデータ呼び出し
	auto nog = json.obj.at(key).get<picojson::array>();
	//最後尾にデータを挿入
	nog.emplace_back(picojson::value(data));
	//データを降順にソート
	picojson::value tmp;
	for (int i = 0; i < nog.size(); i++)
	{
		for (int j = i + 1; j < nog.size(); j++)
		{
			if (nog[i].get<double>() < nog[j].get<double>())
			{
				tmp = nog[i];
				nog[i] = nog[j];
				nog[j] = tmp;
			}
		}
	}

	//余計な末尾にデータを削除
	nog.erase(nog.end() - 1);

	picojson::array arr;
	for (int i = 0; i < nog.size(); i++)
	{
		arr.emplace_back(picojson::value(nog[i]));
	}
	json.obj[key] = picojson::value(arr);

}

void Ranking::WriteJson()
{
	json.WriteJson("Resources/json/ranking.json");
}
