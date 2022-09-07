#pragma once
#include "Camera.h"

class FreeCamera
	: public Camera
{
public:
	FreeCamera(int window_width, int window_height);
	~FreeCamera();

	void Update() override;

private:

};

