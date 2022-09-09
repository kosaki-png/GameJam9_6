#pragma once
#include "BaseTarget.h"
class MoveTarget :
    public BaseTarget
{
public:
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMVECTOR = DirectX::XMVECTOR;

public:
    void Initialize(std::string modelName = (" "), XMFLOAT3 pos = { 0.0f,0.0f,0.0f }, XMFLOAT3 vel = { 0.0f,0.0f,0.0f }, float radius = 0.5f) override;
    void Update() override;

    void Draw() override;

    void SetAmplitude(XMFLOAT3 amp) { amplitude = amp; }

protected:
    XMFLOAT3 amplitude = { 0,0,0 };
};

