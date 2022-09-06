#pragma once
#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "Text.h"
#include "Input.h"

class Player
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
	Player();
	~Player();

	void Initialize(Input* input);
	void Update();
	void Draw();

	XMFLOAT2 GetPosition() { return spritePlayer->GetPosition(); }
	void SetPosition(XMFLOAT2 position) { spritePlayer->SetPosition(position); }

	void Awake() { isSleep = false; sleepCnt = 0; sleepLimit = sleepLimit + 150;}
	bool GetSleep() { return isSleep; }

private: // メンバ変数
	Sprite* spritePlayer = nullptr;
	Input* input = nullptr;

	int sleepCnt = 0;
	int sleepLimit = 200;
	bool isSleep = false;
};