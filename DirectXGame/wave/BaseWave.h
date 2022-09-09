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
	BaseWave();
	virtual ~BaseWave();

	virtual void Initialize(Input* input, Camera* camera);
	virtual void Update();
	virtual void Draw();
	virtual void DrawUi(ID3D12GraphicsCommandList* cmdList);
	
	/// <summary>
	/// �N���A������
	/// </summary>
	/// <returns></returns>
	bool GetClearFlag() { return clearFlag; }

protected:
	// �L�[����
	Input* input;

	// �������C�p
	Camera* camera = nullptr;
	Ray ray;

	// �N���A����p
	bool clearFlag = false;

	// UI�A�X�R�A�Ǌ�
	Ui* ui = nullptr;
};

