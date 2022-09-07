#include "BaseTarget.h"

BaseTarget::~BaseTarget()
{
	safe_delete(obj);
	safe_delete(model);
}

//初期化
void BaseTarget::Initialize(std::string modelName,Vector3 pos,int r)
{
	//object3D関連初期化
	model = Model::CreateFromOBJ(modelName);
	obj = Object3d::Create(model);

	position = pos;
	this->r = r;

}

//更新
void BaseTarget::Update()
{

	//Object3D更新
	obj->Update();
}

//描画
void BaseTarget::Draw()
{
	obj->Draw();
}
