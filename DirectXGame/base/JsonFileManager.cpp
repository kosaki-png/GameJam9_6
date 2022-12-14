#include "JsonFileManager.h"
inline std::string JsonFileManager::ReadTxt(std::string const& filePath)
{
	//ファイル読み込み
	std::ifstream ifs(filePath);
	std::stringstream buffer;

	buffer << ifs.rdbuf();
	std::string str = buffer.str();

	if (str.size() >= 3 && str[0] == -17 && str[1] == -69 && str[2] == -65)return str.substr(3);
	else return str;
}

void JsonFileManager::ReadJson(const std::string& filePath)
{
	std::ifstream ifs(filePath);
	if (!ifs)
	{
		throw std::exception("File cannot be opened.");
	}

	std::string json = ReadTxt(filePath);
	picojson::value val;
	std::string err;
	picojson::parse(val, json.c_str(), json.c_str() + strlen(json.c_str()), &err);

	if (!err.empty())
	{
		throw std::exception("json format error in");
	}

	obj = val.get<picojson::object>();
}
const void JsonFileManager::SingleWriteJson(std::vector<float> nodeData, const std::string& key,const std::string& filePath)
{
	picojson::object obj;
	obj = NodeAdd(obj, nodeData, key);
	std::ofstream ofs(filePath);

	ofs << picojson::value(obj).serialize(true) << std::endl;

}
const void JsonFileManager::MultipleWriteJson(std::vector<std::vector<float>> data, const std::vector<std::string> key, const std::string& filePath)
{
	picojson::object obj;
	for (int i = 0; i<key.size(); i++)
	{
		obj = NodeAdd(obj, data[i], key[i]);
	}
	std::ofstream ofs(filePath);

	ofs << picojson::value(obj).serialize(true) << std::endl;
}
void JsonFileManager::WriteJson(const std::string& filePath)
{
	std::ofstream ofs(filePath);

	ofs << picojson::value(obj).serialize(true) << std::endl;
	
}
const picojson::object JsonFileManager::NodeAdd(picojson::object obj, std::vector<float> data, const std::string& key)
{
	picojson::array arr;
	for (int i = 0; i<data.size(); i++)
	{
		arr.emplace_back(picojson::value(data[i]));
	}
	obj[key] = picojson::value(arr);
	return obj;
}

JsonFileManager::JsonFileManager()
{
}

JsonFileManager::~JsonFileManager()
{
}
