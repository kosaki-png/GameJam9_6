#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "Ui.h"
#include <ui/Ranking.h>
#include<base/JsonFileManager.h>
class SelectUi
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SelectUi();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SelectUi();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(std::string key, picojson::object obj);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void SetScore(int num) {
		scoreNum = num;
	}

private:
	Score* score[3];

	//Score* firstScore;
	//Score* secondScore;
	//Score* thirdScore;

	int scoreNum;
	Ranking ranking;
};

