#include "BaseTarget.h"

BaseTarget::~BaseTarget()
{
	safe_delete(obj);
	safe_delete(model);
}

//������
void BaseTarget::Initialize(std::string modelName, Vector3 pos, int radius)
{
	//object3D�֘A������
	model = Model::CreateFromOBJ(modelName);
	obj = Object3d::Create(model);

	position = pos;
	sphere.center.m128_f32[0] = pos.x;
	sphere.center.m128_f32[1] = pos.y;
	sphere.center.m128_f32[2] = pos.z;
	sphere.radius = radius;
}

//�X�V
void BaseTarget::Update()
{
	sphere.center.m128_f32[0] = position.x;
	sphere.center.m128_f32[1] = position.y;
	sphere.center.m128_f32[2] = position.z;

	//Object3D�X�V
	obj->Update();
}

//�`��
void BaseTarget::Draw()
{
	obj->Draw();
}
