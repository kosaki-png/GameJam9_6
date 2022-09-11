#pragma once
#include "Camera.h"
class OrbitCamera
    : public Camera
{
public:
    OrbitCamera(int window_width, int window_height, DirectX::XMFLOAT2 distance = {10.0f, 10.0f}, float speed = 0.01f);
    ~OrbitCamera();

    void Update() override;

private:
    float rad = 90.0f;
    float speed = 0.0f;
    DirectX::XMFLOAT2 dis = {1,1};

};

