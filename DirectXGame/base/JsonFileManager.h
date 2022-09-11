#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"picojson.h"

class JsonFileManager
{
public:
	//�e�L�X�g�t�@�C���ǂݍ���
	inline std::string ReadTxt(std::string const& filePath);
	//json�t�@�C���ǂݍ���
	void ReadJson(const std::string& filePath);
	//json�����o��(�P��)
	static const void SingleWriteJson(std::vector<float> data, const std::string& key, const std::string& filePath);
	//json�����o��(����)
	static const void MultipleWriteJson(std::vector<std::vector<float>> data, std::vector<std::string> key, const std::string& filePath);

	//�m�[�h�ǉ�
	static const picojson::object NodeAdd(picojson::object, std::vector<float> data, const std::string& key);
protected:
	JsonFileManager();
	~JsonFileManager();

private:
	picojson::object obj;
};
