#include "BaseTarget.h"

BaseTarget::~BaseTarget()
{
	safe_delete(obj);
	safe_delete(model);
}

//������
void BaseTarget::Initialize(std::string modelName,Vector3 pos,int r)
{
	//object3D�֘A������
	model = Model::CreateFromOBJ(modelName);
	obj = Object3d::Create(model);

	position = pos;
	this->r = r;

}

//�X�V
void BaseTarget::Update()
{

	//Object3D�X�V
	obj->Update();
}

//�`��
void BaseTarget::Draw()
{
	obj->Draw();
}
