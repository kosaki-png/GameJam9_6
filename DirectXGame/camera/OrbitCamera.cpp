#include "OrbitCamera.h"

OrbitCamera::OrbitCamera(int window_width, int window_height, DirectX::XMFLOAT2 distance, float speed)
	: Camera(window_width, window_height), dis(distance), speed(speed)
{
}

OrbitCamera::~OrbitCamera()
{
}

void OrbitCamera::Update()
{
	rad += speed;

	SetEye({ sinf(rad) * dis.x , dis.y, cosf(rad) * dis.x});

	Camera::Update();
}
