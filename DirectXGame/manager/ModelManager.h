#pragma once
#include "Model.h"
#include <vector>

// モデル指定用変数
static const int FIELD		= 0;	// フィールド
static const int SPHERE		= 1;	// 球
static const int SKYDOME	= 2;	// 天球

class ModelManager
{
public:
	static ModelManager* GetInstance();

	/// <summary>
	/// モデル全ロード
	/// </summary>
	void LoadModel();

	/// <summary>
	/// 指定モデル取得
	/// </summary>
	/// <param name="modelNum"></param>
	/// <returns>モデル</returns>
	Model* GetModel(static const int modelNum);

	/// <summary>
	/// モデル全削除
	/// </summary>
	void Destroy();

private:
	void AddModel(static const int modelNum, const std::string modelName, bool smoothing = false);

private:
	static ModelManager* instance;

	std::vector<Model*> models;
};

