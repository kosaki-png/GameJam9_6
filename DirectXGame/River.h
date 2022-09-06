#pragma once
#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "Text.h"
#include "input.h"
#include "Define.h"

class River
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
public: // メンバ関数

	River();
	~River();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input"></param>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 速度変更
	/// </summary>
	/// <param name="Speed">速度</param>
	void SetSpeed(float Speed) { this->Speed = Speed; }

	/// <summary>
	/// セットフラグ
	/// </summary>
	void SetUpDown() { UpDown_Flag = !UpDown_Flag;}

	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="input">インプットインスタンス</param>
	void ReStart();

	/// <summary>
	/// 流れる
	/// </summary>
	/// <param name="UpDown_Flag">流れる方向</param>
	void Flow(bool UpDown_Flag);

	//setter getter
	XMFLOAT2 GetPosition() { return base->GetPosition(); }
	bool GetUpdown() { return UpDown_Flag; }
	void SetPosition(XMFLOAT2 position) { base->SetPosition(position); }

private://メンバ変数
	Sprite* base = nullptr;
	Sprite* fall01[RIVER] = {};
	float Speed;
	bool UpDown_Flag = true;
	XMFLOAT2 size{ 100,100 };
	XMFLOAT2 F_position{};
	XMFLOAT2 position = { 0,0 };
	XMFLOAT2 position1 = { 0,0 };
};