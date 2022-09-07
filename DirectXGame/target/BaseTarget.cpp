#include "BaseTarget.h"

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
	sphere.center = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0);
	sphere.radius = radius;
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
