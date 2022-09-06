#pragma once
#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "Text.h"

class BackGround
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
	BackGround();
	~BackGround();

	void Initialize();
	void Update();
	void Draw();

	void SetAwake() { mode = false; }
	void SetSleep() { mode = true; }
	void ChangeState() { mode = !mode; }
	bool GetState() { return mode; }

	void SetSpeed(float speed) { this->speed = speed; }

	bool GetOver() { return over; }

	std::vector<XMFLOAT2> GetSignPos();

private: // �����o�ϐ�
	Sprite* ba = nullptr;
	Sprite* back[2] = {};		// �w�i�i���ށj
	Sprite* groundBase0 = nullptr;
	Sprite* groundBase1 = nullptr;
	Sprite* ground0[2] = {};
	Sprite* ground1[2] = {};
	Sprite* mountain0[2] = {};
	Sprite* mountain1[2] = {};
	Sprite* mountain2[2] = {};
	Sprite* mountain3[2] = {};
	Sprite* night = nullptr;
	Sprite* star = nullptr;
	Sprite* sun[2] = {};

	Sprite* fort = nullptr;
	Sprite* sighboard[5] = {};

	// ���̒����ۂ�
	bool mode = false;

	float speed = 0;

	// ���z�_�ŗp
	int sunCount = 0;

	bool over = false;
};