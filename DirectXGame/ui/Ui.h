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
	void Update(Input* input);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

private:
	Sprite* ui;
	Score* score;
	Score* timeLimit;
	Score* rate;
	float time;
	static int num;
};

