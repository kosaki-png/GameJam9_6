#pragma once
#include "BaseWave.h"
#include "MoveTarget.h"
class FollowWave :
    public BaseWave
{
public:
    FollowWave(std::string key);
    ~FollowWave();

    void Initialize(Input* input, Camera* camera, Audio* audio) override;
    void Update() override;

    void Draw() override;

    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

public:
    MoveTarget* target = nullptr;

    bool isStart = false;

};

