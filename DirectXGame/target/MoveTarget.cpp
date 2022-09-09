#include "MoveTarget.h"
void MoveTarget::Initialize(std::string modelName, XMFLOAT3 pos, XMFLOAT3 vel, float radius)
{
	//基本初期化
	BaseTarget::Initialize(modelName, pos, vel, radius);

	//専用の初期化
	{

	}
}

void MoveTarget::Update()
{
	static XMFLOAT3 ease;
	ease.x += velocity.x;
	ease.y += velocity.y;
	ease.z += velocity.z;

	position.x = sinf(ease.x) * amplitude.x;
	position.y = sinf(ease.y) * amplitude.y;
	position.z = sinf(ease.z) * amplitude.z;

	sphere.center = DirectX::XMVectorSet(position.x, position.y, position.z, 0);

	obj->SetPosition(position);

	//Object3D更新
	obj->Update();

}

void MoveTarget::Draw()
{
	BaseTarget::Draw();
}
