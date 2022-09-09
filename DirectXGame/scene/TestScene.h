#pragma once
#include <array>
#include "ParticleManager.h"
#include "Text.h"
#include "DebugCamera.h"
#include "LightGroup.h"
#include "XinputControll.h"
#include "Sprite.h"
#include "Object3d.h"
#include "CollisionPrimitive.h"

#include "BaseScene.h"
#include "BaseWave.h"

class TestScene :
    public BaseScene
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

public:
	TestScene();
	~TestScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio) override;

	void Update() override;

	void Draw() override;

private:
	bool option = false;

	// �n��
	Object3d* objGround = nullptr;
	Model* modelGround = nullptr;

	// �N���X�w�A
	Sprite* cross = nullptr;
	float sensi = 0;

	// �E�F�[�u
	BaseWave* wave = nullptr;
};

