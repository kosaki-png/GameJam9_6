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
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	static const int texNumber = 0;

public: // �����o�֐�
	Player();
	~Player();

	void Initialize(Input* input);
	void Update();
	void Draw();

	XMFLOAT2 GetPosition() { return spritePlayer->GetPosition(); }
	void SetPosition(XMFLOAT2 position) { spritePlayer->SetPosition(position); }

	void Awake() { isSleep = false; sleepCnt = 0; sleepLimit = sleepLimit + 150;}
	bool GetSleep() { return isSleep; }

private: // �����o�ϐ�
	Sprite* spritePlayer = nullptr;
	Input* input = nullptr;

	int sleepCnt = 0;
	int sleepLimit = 200;
	bool isSleep = false;
};