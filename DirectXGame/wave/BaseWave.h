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

enum Level
{
	easy	= 0,
	normal	= 1,
	hard	= 2,
	hell	= 3
};

class BaseWave
{
public:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	BaseWave(Level level);
	virtual ~BaseWave();

	virtual void Initialize(Input* input, Camera* camera);
	virtual void Update();
	virtual void Draw();
	virtual void DrawUi(ID3D12GraphicsCommandList* cmdList);
	
	/// <summary>
	/// �J�E���g�_�E���̍X�V
	/// </summary>
	void CountDown();

	/// <summary>
	/// �J�E���g�_�E���p�`��
	/// </summary>
	void CountDownDraw();

	/// <summary>
	/// �J�E���g�_�E������
	/// </summary>
	/// <returns></returns>
	bool GetIsCount() { return isCount; }

	/// <summary>
	/// �N���A������
	/// </summary>
	/// <returns></returns>
	bool GetClearFlag() { return clearFlag; }

protected:
	// ���݂̃��x��
	Level level;

	// �L�[����
	Input* input;

	// �������C�p
	Camera* camera = nullptr;
	Ray ray;

	// �N���A����p
	bool clearFlag = false;

	// UI�A�X�R�A�Ǌ�
	Ui* ui = nullptr;

	// �J�E���g�_�E���p
	Sprite* base = nullptr;
	Sprite* click = nullptr;
	Sprite* start = nullptr;
	Text* text = nullptr;

	bool isCount = true;	// �J�E���g�_�E�������Ă��邩
	bool isStart = false;	// �X�^�[�g���Ă��邩

	float time = 4.0f;		// �J�n�܂ł̎���
};

