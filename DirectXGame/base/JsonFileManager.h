#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"picojson.h"

class JsonFileManager
{
public:
	//テキストファイル読み込み
	inline std::string readTxt(std::string const& filePath);
	//jsonファイル読み込み
	void readJson(const std::string& filePath);
	//json書き出し(単体)
	static const void singleWriteJson(std::vector<float>data, const std::string& key, const std::string& filePath);
	//json書き出し(複数)
	static const void multipleWriteJson(std::vector < std::vector<float>>data, std::vector<std::string> key, const std::string& filePath);

	//ノード追加
	static const picojson::object nodeAdd(picojson::object, std::vector<float>data, const std::string& key);
protected:
	JsonFileManager();
	~JsonFileManager();

private:
	picojson::object obj;
};

