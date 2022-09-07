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

		/*rotation.x += (float)mouseMove.lX / 10;
		rotation.y += (float)mouseMove.lY / 10;*/
		if (input->TriggerKey(DIK_RIGHT))
		{
			rotation.x += 0.4f;
		}
		if (input->TriggerKey(DIK_LEFT))
		{
			rotation.x -= 0.4f;
		}

		SetRotation(rotation);
	}

	Camera::Update();
}