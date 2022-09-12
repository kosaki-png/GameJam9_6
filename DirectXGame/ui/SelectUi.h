#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "Ui.h"

class SelectUi
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectUi();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectUi();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
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

