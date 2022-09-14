#pragma once
#include "BaseWave.h"
#include "target/MoveTarget.h"
class TrackWave :
    public BaseWave
{
public:
    TrackWave(std::string key);
    ~TrackWave();
    void Initialize(Input* input, Camera* camera, Audio* audio) override;
    void Update() override;

    void Draw() override;

    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

    XMFLOAT3 ResetPos();
    XMFLOAT3 ResetVel();
    float ResetMoveTime();

public:
    static const int TARGET_AMOUNT = 3;
    std::array<BaseTarget*, TARGET_AMOUNT> targets;
    bool isStart = false;
};

