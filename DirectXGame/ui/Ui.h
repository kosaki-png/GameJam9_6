#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "input/Input.h"

class Ui 
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private: // 静的メンバ変数
	static const int texNumber = 0;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Ui();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Ui();

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

	/// <summary>
	/// 得点追加
	/// </summary>
	/// <param name="num">追加得点</param>
	void AddScore(int num) {
		scoreNum += num;
	};

	/// <summary>
	/// 当てた数追加
	/// </summary>
	void AddCount() {
		countNum++;
	};

	/// <summary>
	/// 外した数追加
	/// </summary>
	void AddMiss() {
		missNum++;
	}

	/// <summary>
	/// 割合計算
	/// </summary>
	/// <returns>割合の値</returns>
	int Rate() {
		rateNum = countNum / (countNum + missNum) * 100;
		return rateNum;
	};

private:
	Sprite* ui;
	Score* score;
	Score* timeLimit;
	Score* rate;
	float time;

	static float countNum;//当てた数
	static float missNum; //外した数
	static float rateNum; //割合の値
	static int scoreNum;//スコアの値
};

