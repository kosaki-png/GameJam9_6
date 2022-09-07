#include "BaseTarget.h"

BaseTarget::~BaseTarget()
{
	safe_delete(obj);
	safe_delete(model);
}

//初期化
void BaseTarget::Initialize(std::string modelName, Vector3 pos, int radius)
{
	//object3D関連初期化
	model = Model::CreateFromOBJ(modelName);
	obj = Object3d::Create(model);

	position = pos;
	sphere.center.m128_f32[0] = pos.x;
	sphere.center.m128_f32[1] = pos.y;
	sphere.center.m128_f32[2] = pos.z;
	sphere.radius = radius;
}

//更新
void BaseTarget::Update()
{
	sphere.center.m128_f32[0] = position.x;
	sphere.center.m128_f32[1] = position.y;
	sphere.center.m128_f32[2] = position.z;

	//Object3D更新
	obj->Update();
}

//描画
void BaseTarget::Draw()
{
	obj->Draw();
}
