#pragma once
#include "BaseWave.h"
#include "MoveTarget.h"
class FollowWave :
    public BaseWave
{
public:
    FollowWave();
    ~FollowWave();

    void Initialize(Input* input, Camera* camera) override;
    void Update() override;

    void Draw() override;

    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

public:
    MoveTarget* target = nullptr;

    bool isStart = false;

};
