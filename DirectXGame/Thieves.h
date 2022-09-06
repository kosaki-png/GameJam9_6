#pragma once

#include <DirectXMath.h>
#include <vector>
#include "SafeDelete.h"
#include "Sprite.h"
#include "Collision.h"
#include <stdlib.h> // rand, srand関数
#include <time.h>   // time関数
#include <random>
#define enemy 3

class Thieves
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

public:

	Thieves();
	~Thieves();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(float speed);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(bool sleep);

	/// <summary>
	/// 描画
	/// </summary>
	void Spawn();

   /// <summary>
   /// 重なりチェック
   /// </summary>
    bool Check(int number);

	std::vector<XMFLOAT2> GetPosition();
	void SetPosition(XMFLOAT2 positions);

private:
	Sprite* thieves[enemy]; //盗賊スプライト
	XMFLOAT2 e_Pos[enemy];
	//各盗賊の座標の乱数生成
	float posX[enemy];
	float posY[enemy];
	float width = 100; //画像の横幅
	float height = 100; //画像の縦幅
	float speed = 0.0f;
	bool Drawflag[enemy]; //描画フラグ
};

