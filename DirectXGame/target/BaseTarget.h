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
	virtual void Initialize(std::string modelName = (" "), XMFLOAT3 pos = { 0,0,0 }, float radius = 0.5f);
	//更新
	virtual void Update();
	//描画
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

