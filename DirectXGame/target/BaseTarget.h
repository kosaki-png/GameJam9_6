#pragma once
#include "Object3d.h"
#include "Model.h"
#include "SafeDelete.h"
#include "CollisionPrimitive.h"

class BaseTarget
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	BaseTarget();
	~BaseTarget();

	//������
	virtual void Initialize(std::string modelName = (" "), XMFLOAT3 pos = { 0,0,0 }, float radius = 0.5f);
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();

	//Set
	void SetPosition(XMFLOAT3 pos) { position = pos; }
	void SetIsDead(bool setDead) { isDead = setDead; }

	//Get
	XMFLOAT3 GetPosition() { return position; }
	XMFLOAT3 GetVelocity() { return velocity; }
	int GetRadius() { return sphere.radius; }
	Sphere GetSphere() { return sphere; }
	bool GetIsDead() { return isDead; }

private:

	Object3d* obj;
	Model* model;

	Sphere sphere;
	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT3 velocity = { 0,0,0 };

	bool isDead = false;
};

