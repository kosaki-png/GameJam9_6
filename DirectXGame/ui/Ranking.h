#pragma once
#include "base/JsonFileManager.h"

class Ranking
{
public:
public:
	Ranking();
	~Ranking();
	void Initialize();

	void setScore(std::string key, float data);

	void WriteJson();
public:
	JsonFileManager json;
};

