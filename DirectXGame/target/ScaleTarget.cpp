#include "ScaleTarget.h"

void ScaleTarget::Initialize(std::string modelName, XMFLOAT3 pos, XMFLOAT3 vel, float radius)
{
	//基本初期化
	BaseTarget::Initialize(modelName, pos, vel, radius);

	//専用の初期化
	{
		this->pos = pos;
	}
}

void ScaleTarget::Update()
{
	scale.x -= velocity.x;
	scale.y -= velocity.y;
	scale.z -= velocity.z;

	sphere.center = DirectX::XMVectorSet(position.x, position.y, position.z, 0);
	sphere.radius = scale.x / 2;

	obj->SetPosition(position);
	obj->SetScale(scale);
	 
	//Object3D更新
	obj->Update();
}

void ScaleTarget::Draw()
{
	BaseTarget::Draw();
}
