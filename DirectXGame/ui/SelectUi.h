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
	void Update(std::string key, picojson::object obj);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// スコアセッター
	/// </summary>
	/// <param name="num">スコア</param>
	void SetScore(int num) {
		scoreNum = num;
	}

private:
	Score* score[3];
	int scoreNum = 0;
	Ranking ranking;
};

