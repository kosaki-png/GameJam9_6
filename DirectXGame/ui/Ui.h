#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "input/Input.h"
#include "SafeDelete.h"
#include "Stopwatch.h"

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
	void AddScore(int num = 10) {
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

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="targetNum">値を変えたい対象</param>
	/// <param name="setNum">変更する数字</param>
	void SetNum(int& targetNum, int setNum = 0) {
		targetNum = setNum;
	};

	//getter
	const float& GetOnePlace() { return onePlace; }//タイムの１の位
	const float& GetTnePlace() { return tenPlace; }//タイムの10の位
	const float& GetHundredPlace() { return hundredPlace; }//タイムの100の位
	const float& GetRate() { return rateNum; }
	const int& GetScore() {return scoreNum; }

	void TimerManage();
private:
	Sprite* ui;
	Score* score;
	Score* timeLimit;
	Score* rate;
	Score* parcent;
	std::unique_ptr<diagnostics::Stopwatch> timer;
	
	float onePlace;  //1の位
	int tenPlace;    //10の位
	int hundredPlace;//100の位
	int initialValue;//初期値
	float countNum;  //当てた数
	float missNum;   //外した数
	float rateNum;   //割合の値
	static int scoreNum;    //スコアの値
};

