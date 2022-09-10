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
void BaseTarget::Initialize(std::string modelName, XMFLOAT3 pos,XMFLOAT3 vel, float radius)
{
	//object3D関連初期化
	model = Model::CreateFromOBJ(modelName, true);
	obj = Object3d::Create(model);
	obj->SetPosition(pos);

	position = pos;
	velocity = vel;
	sphere.center = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
	sphere.radius = radius;
}

//更新
void BaseTarget::Update()
{
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	sphere.center = DirectX::XMVectorSet(position.x, position.y, position.z, 0);

	obj->SetPosition(position);
	//obj->SetRotation(rotation);
	
	//Object3D更新
	obj->Update();
}

//描画
void BaseTarget::Draw()
{
	if(!isDead)
	{
		obj->Draw();
	}
}
