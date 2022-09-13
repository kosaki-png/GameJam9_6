#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"picojson.h"

class JsonFileManager
{
public:
	struct Node
	{
		std::string name;
		std::vector<float> datas;
	};

public:
	//テキストファイル読み込み
	inline std::string ReadTxt(std::string const& filePath);
	//jsonファイル読み込み
	void ReadJson(const std::string& filePath);
	//json書き出し(単体)
	static const void SingleWriteJson(std::vector<float> data, const std::string& key, const std::string& filePath);
	//json書き出し(複数)
	static const void MultipleWriteJson(std::vector<std::vector<float>> data, std::vector<std::string> key, const std::string& filePath);
	//クラス内のjsonオブジェクトを書き出し
	void WriteJson(const std::string& filePath);
	//ノード追加
	static const picojson::object NodeAdd(picojson::object, std::vector<float> data, const std::string& key);
	JsonFileManager();
	~JsonFileManager();

public:
	picojson::object obj;
};

