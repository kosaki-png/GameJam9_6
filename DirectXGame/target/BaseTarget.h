#pragma once
#include "Object3d.h"
#include "Model.h"
#include "SafeDelete.h"
#include "CollisionPrimitive.h"

class BaseTarget
{
private: // ?G?C???A?X
// Microsoft::WRL::???ȗ?
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::???ȗ?
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	BaseTarget();
	~BaseTarget();

	//??????
	virtual void Initialize(std::string modelName = (" "), XMFLOAT3 pos = { 0.0f,0.0f,0.0f }, XMFLOAT3 vel = { 0.0f,0.0f,0.0f }, float radius = 0.5f);
	//?X?V
	virtual void Update();
	//?`??
	virtual void Draw();

	void objUpdata();

	void move();
	//Set
	void SetPosition(XMFLOAT3 pos) { position = pos; }
	void SetVelocity(XMFLOAT3 vel) { velocity = vel; }
	void SetIsDead(bool setDead) { isDead = setDead; }
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	void SetLife(float targetLife) { life = targetLife; }
	void SetMoveTime(float time) { moveTime = time; }

	//Get
	XMFLOAT3 GetPosition() { return position; }
	XMFLOAT3 GetVelocity() { return velocity; }
	XMFLOAT3 GetScale() { return scale; }
	int GetRadius() { return sphere.radius; }
	Sphere GetSphere() { return sphere; }
	bool GetIsDead() { return isDead; }
	float GetLife() { return life; }
	float GetMoveTime() { return moveTime; }

	void SetMode(bool mode) { this->mode = mode; }

protected:

	Object3d* obj;
	Object3d* sub_obj;

	Sphere sphere;
	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT3 velocity = { 0,0,0 };
	XMFLOAT3 scale = { 1,1,1 };


	bool isDead = false;
	float life = 0;
	float moveTime = 0;

	bool mode = false;
};

