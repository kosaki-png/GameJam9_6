#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "Ui.h"

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
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void SetScore(int num) {
		scoreNum = num;
	}

private:
	Ui* ui;
	Score* score[9][3];

	//Score* firstScore;
	//Score* secondScore;
	//Score* thirdScore;

	int scoreNum;
};

