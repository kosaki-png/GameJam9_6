#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "Ui.h"

class ResultUi
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ResultUi();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ResultUi();

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
	Score* score;
	Score* accuracy;
	Score* timeToKill;
	Score* targets;
	Score* hits;
	Score* misses;
	Score* parcent;

	int scoreNum;
};

