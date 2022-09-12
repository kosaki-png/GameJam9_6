#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Ui.h"
#include "Collision.h"
#include "CollisionPrimitive.h"
#include "Camera.h"
#include "DirectXCommon.h"
#include "Sprite.h"

#include <array>
#include "BaseTarget.h"
#include <ui/Ranking.h>



class BaseWave
{
public:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	BaseWave(std::string key);
	virtual ~BaseWave();

	virtual void Initialize(Input* input, Camera* camera);
	virtual void Update();
	virtual void Draw();
	virtual void DrawUi(ID3D12GraphicsCommandList* cmdList);
	
	/// <summary>
	/// カウントダウンの更新
	/// </summary>
	void CountDown();

	/// <summary>
	/// カウントダウン用描画
	/// </summary>
	void CountDownDraw();

	/// <summary>
	/// カウントダウン中か
	/// </summary>
	/// <returns></returns>
	bool GetIsCount() { return isCount; }

	/// <summary>
	/// クリアしたか
	/// </summary>
	/// <returns></returns>
	bool GetClearFlag() { return clearFlag; }

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns>現在のキー</returns>
	std::string GetCurrentKey() {return currentKey;}

	/// <summary>
	/// スコア取得
	/// </summary>
	/// <returns></returns>
	int GetScore() { return ui->GetScore(); }

protected:
	// キー入力
	Input* input;

	//現在のキー
	std::string currentKey;

	// 視線レイ用
	Camera* camera = nullptr;
	Ray ray;

	// クリア判定用
	bool clearFlag = false;

	// UI、スコア管轄
	Ui* ui = nullptr;

	// カウントダウン用
	Sprite* base = nullptr;
	Sprite* click = nullptr;
	Sprite* start = nullptr;
	Text* text = nullptr;

	bool isCount = true;	// カウントダウンをしているか
	bool isStart = false;	// スタートしているか

	float time = 4.0f;		// 開始までの時間
};

