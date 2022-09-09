#pragma once
#include "BaseWave.h"
class FollowWave :
    public BaseWave
{
public:
    void Initialize(Input* input, Camera* camera) override;
    void Update() override;

    void Draw() override;

    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

public:
    BaseTarget* target = nullptr;

    bool isStart = false;

    XMFLOAT4 position = { 0.0f,0.0f,0.0f,0.0f };
};

