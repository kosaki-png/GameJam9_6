#include "FreeCamera.h"

FreeCamera::FreeCamera(int window_width, int window_height)
			:	Camera(window_width, window_height)
{
	//ビュー行列の計算
	UpdateViewMatrix();

	// 射影行列の計算
	UpdateProjectionMatrix();

	// ビュープロジェクションの合成
	matViewProjection = matView * matProjection;
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::Update()
{
	if (input)
	{
		Input::MouseMove mouseMove = input->GetMouseMove();

		rotation.x += (float)mouseMove.lX * sensi / 10;
		rotation.y += (float)mouseMove.lY * sensi / 10;

		SetRotation(rotation);
	}

	Camera::Update();
}