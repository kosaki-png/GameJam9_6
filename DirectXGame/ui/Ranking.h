#pragma once
#include "base/JsonFileManager.h"

class Ranking
{
public:
	Ranking();
	~Ranking();
	void Initialize();

	void setScore(static const std::string key, float data);

	void WriteJson();
public:
	JsonFileManager json;
};

