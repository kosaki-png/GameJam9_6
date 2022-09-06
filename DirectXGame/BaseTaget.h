#pragma once
#include "base/Vector3.h"
#include "3d/Object3d.h"
#include "3d/Model.h"
#include "base/SafeDelete.h"

class BaseTaget
{
private:
	BaseTaget();
	~BaseTaget();

	//初期化
	virtual void Initialize(std::string modelName);
	//更新
	virtual void Update();
	//描画
	virtual void Draw();

	//Set
	void SetPosition(Vector3 pos) { position = pos; }

	//Get
	Vector3 GetPosition() { return position; }
	Vector3 GetVelocity() { return velocity; }


private:

	Object3d* obj;
	Model* model;
	
	Vector3 position = { 0,0,0 };
	Vector3 velocity = { 0,0,0 };
	int r = 1;
};

