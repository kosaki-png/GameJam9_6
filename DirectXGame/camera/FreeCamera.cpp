#include "FreeCamera.h"

FreeCamera::FreeCamera(int window_width, int window_height)
			:	Camera(window_width, window_height)
{
	//�r���[�s��̌v�Z
	UpdateViewMatrix();

	// �ˉe�s��̌v�Z
	UpdateProjectionMatrix();

	// �r���[�v���W�F�N�V�����̍���
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