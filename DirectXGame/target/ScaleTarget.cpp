#include "ScaleTarget.h"

void ScaleTarget::Initialize(std::string modelName, XMFLOAT3 pos, XMFLOAT3 vel, float radius)
{
	//��{������
	BaseTarget::Initialize(modelName, pos, vel, radius);

	//��p�̏�����
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
	 
	//Object3D�X�V
	obj->Update();
}

void ScaleTarget::Draw()
{
	BaseTarget::Draw();
}
