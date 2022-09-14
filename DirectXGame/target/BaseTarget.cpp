#include "BaseTarget.h"
#include "ModelManager.h"

BaseTarget::BaseTarget()
{
}

BaseTarget::~BaseTarget()
{
	safe_delete(obj);
	safe_delete(sub_obj);
}

//初期化
void BaseTarget::Initialize(std::string modelName, XMFLOAT3 pos,XMFLOAT3 vel, float radius)
{
	//object3D関連初期化
	obj = Object3d::Create(ModelManager::GetInstance()->GetModel(SPHERE));
	sub_obj = Object3d::Create(ModelManager::GetInstance()->GetModel(SPHERE_RED));

	position = pos;
	velocity = vel;
	sphere.center = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
	sphere.radius = radius;

	life = 100;
}

//更新
void BaseTarget::Update()
{
	move();
	objUpdata();
}

//描画
void BaseTarget::Draw()
{
	if(!isDead)
	{
		if (!mode)
		{
			obj->Draw();
		}
		else
		{
			sub_obj->Draw();
		}
	}
}

void BaseTarget::objUpdata()
{
	sphere.center = DirectX::XMVectorSet(position.x, position.y, position.z, 0);

	obj->SetPosition(position);
	obj->SetScale(scale);

	sub_obj->SetPosition(position);
	sub_obj->SetScale(scale);

	sphere.radius = scale.x / 2;

	//Object3D更新
	obj->Update();
	sub_obj->Update();
}

void BaseTarget::move()
{
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;
}
