#include "BaseTarget.h"

BaseTarget::BaseTarget()
{
}

BaseTarget::~BaseTarget()
{
	safe_delete(obj);
	safe_delete(model);
}

//������
void BaseTarget::Initialize(std::string modelName, XMFLOAT3 pos, int radius)
{
	//object3D�֘A������
	model = Model::CreateFromOBJ(modelName);
	obj = Object3d::Create(model);

	position = pos;
	sphere.center = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
	sphere.radius = 0.5f;
}

//�X�V
void BaseTarget::Update()
{
	sphere.center = DirectX::XMVectorSet(position.x, position.y, position.z, 0);

	//Object3D�X�V
	obj->Update();
}

//�`��
void BaseTarget::Draw()
{
	obj->Draw();
}
