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

	River();
	~River();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input"></param>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���x�ύX
	/// </summary>
	/// <param name="Speed">���x</param>
	void SetSpeed(float Speed) { this->Speed = Speed; }

	/// <summary>
	/// �Z�b�g�t���O
	/// </summary>
	void SetUpDown() { UpDown_Flag = !UpDown_Flag;}

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	/// <param name="input">�C���v�b�g�C���X�^���X</param>
	void ReStart();

	/// <summary>
	/// �����
	/// </summary>
	/// <param name="UpDown_Flag">��������</param>
	void Flow(bool UpDown_Flag);

	//setter getter
	XMFLOAT2 GetPosition() { return base->GetPosition(); }
	bool GetUpdown() { return UpDown_Flag; }
	void SetPosition(XMFLOAT2 position) { base->SetPosition(position); }

private://�����o�ϐ�
	Sprite* base = nullptr;
	Sprite* fall01[RIVER] = {};
	float Speed;
	bool UpDown_Flag = true;
	XMFLOAT2 size{ 100,100 };
	XMFLOAT2 F_position{};
	XMFLOAT2 position = { 0,0 };
	XMFLOAT2 position1 = { 0,0 };
};