#include "BaseTarget.h"

BaseTarget::BaseTarget()
{
}

BaseTarget::~BaseTarget()
{
	safe_delete(obj);
	safe_delete(model);
}

//初期化
void BaseTarget::Initialize(std::string modelName, XMFLOAT3 pos, int radius)
{
	//object3D関連初期化
	model = Model::CreateFromOBJ(modelName);
	obj = Object3d::Create(model);

	position = pos;
	sphere.center = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
	sphere.radius = 0.5f;
}

//更新
void BaseTarget::Update()
{
	sphere.center = DirectX::XMVectorSet(position.x, position.y, position.z, 0);

	//Object3D更新
	obj->Update();
}

//描画
void BaseTarget::Draw()
{
	obj->Draw();
}
