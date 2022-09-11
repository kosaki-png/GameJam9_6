#pragma once
#include "Object3d.h"
#include "Model.h"
#include "SafeDelete.h"
#include "CollisionPrimitive.h"

class BaseTarget
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	BaseTarget();
	~BaseTarget();

	//初期化
	virtual void Initialize(std::string modelName = (" "), XMFLOAT3 pos = { 0.0f,0.0f,0.0f }, XMFLOAT3 vel = { 0.0f,0.0f,0.0f }, float radius = 0.5f);
	//更新
	virtual void Update();
	//描画
	virtual void Draw();

	//Set
	void SetPosition(XMFLOAT3 pos) { position = pos; }
	void SetVelocity(XMFLOAT3 vel) { velocity = vel; }
	void SetIsDead(bool setDead) { isDead = setDead; }
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	//Get
	XMFLOAT3 GetPosition() { return position; }
	XMFLOAT3 GetVelocity() { return velocity; }
	XMFLOAT3 GetScale() { return scale; }
	int GetRadius() { return sphere.radius; }
	Sphere GetSphere() { return sphere; }
	bool GetIsDead() { return isDead; }

protected:

	Object3d* obj;

	Sphere sphere;
	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT3 velocity = { 0,0,0 };
	XMFLOAT3 scale = { 1,1,1 };

	bool isDead = false;
};

