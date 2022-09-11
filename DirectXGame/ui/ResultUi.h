#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "Ui.h"

class ResultUi
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ResultUi();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultUi();

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
	Score* score;
	Score* accuracy;
	Score* timeToKill;
	Score* targets;
	Score* hits;
	Score* misses;
	Score* parcent;

	int scoreNum;
};

