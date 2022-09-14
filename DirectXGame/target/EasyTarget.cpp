#include "EasyTarget.h"

DirectX::XMFLOAT3 EasyTarget::ease = { 0,0,0 };

void EasyTarget::Initialize(std::string modelName, XMFLOAT3 pos, XMFLOAT3 vel, float radius)
{
	BaseTarget::Initialize(modelName, pos, vel, radius);

	//ê—p‚Ì‰Šú‰»
	{
		ease = pos;
	}
}

void EasyTarget::Update()
{
	float movetime;
	ease.x += velocity.x;
	position.x = sinf(ease.x) * amplitude.x;
	sphere.center = DirectX::XMVectorSet(position.x, position.y, position.z, 0);

	obj->SetPosition(position);

	//Object3DXV
	obj->Update();
}

void EasyTarget::Draw()
{
	BaseTarget::Draw();
}
