#pragma once
#include "Model.h"
#include <vector>

// ���f���w��p�ϐ�
static const int FIELD		= 0;	// �t�B�[���h
static const int SPHERE		= 1;	// ��
static const int SKYDOME	= 2;	// �V��

class ModelManager
{
public:
	static ModelManager* GetInstance();

	/// <summary>
	/// ���f���S���[�h
	/// </summary>
	void LoadModel();

	/// <summary>
	/// �w�胂�f���擾
	/// </summary>
	/// <param name="modelNum"></param>
	/// <returns>���f��</returns>
	Model* GetModel(static const int modelNum);

	/// <summary>
	/// ���f���S�폜
	/// </summary>
	void Destroy();

private:
	void AddModel(static const int modelNum, const std::string modelName, bool smoothing = false);

private:
	static ModelManager* instance;

	std::vector<Model*> models;
};

