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
	//�e�L�X�g�t�@�C���ǂݍ���
	inline std::string ReadTxt(std::string const& filePath);
	//json�t�@�C���ǂݍ���
	void ReadJson(const std::string& filePath);
	//json�����o��(�P��)
	static const void SingleWriteJson(std::vector<float> data, const std::string& key, const std::string& filePath);
	//json�����o��(����)
	static const void MultipleWriteJson(std::vector<std::vector<float>> data, std::vector<std::string> key, const std::string& filePath);
	//�N���X����json�I�u�W�F�N�g�������o��
	void WriteJson(const std::string& filePath);
	//�m�[�h�ǉ�
	static const picojson::object NodeAdd(picojson::object, std::vector<float> data, const std::string& key);
	JsonFileManager();
	~JsonFileManager();

public:
	picojson::object obj;
};

