#include "MoveTarget.h"
void MoveTarget::Initialize(std::string modelName, XMFLOAT3 pos, XMFLOAT3 vel, float radius)
{
	//��{������
	BaseTarget::Initialize(modelName, pos, vel, radius);

	//��p�̏�����
	{

	}
}

void MoveTarget::Update()
{
	if (changeTime < 0)
	{
		vel.x = rand() % 6 * 0.01f;
		vel.y = rand() % 6 * 0.01f;
		vel.z = rand() % 6 * 0.01f;
		changeTime = rand() % 400;
	}

	rad.x += vel.x;
	rad.y += vel.y;
	rad.z += vel.z;

	position.x = sinf(rad.x) * 3;
	position.y = cosf(rad.y) * 3;
	position.z = cosf(rad.z) * 3;


	sphere.center = DirectX::XMVectorSet(position.x, position.y, position.z, 0);
	obj->SetPosition(position);

	//Object3D�X�V
	obj->Update();

	changeTime--;
}

void MoveTarget::Draw()
{
	BaseTarget::Draw();
}
