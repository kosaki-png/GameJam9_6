#pragma once
#include "BaseWave.h"

class EasyWave :
    public BaseWave
{
public:
    EasyWave(std::string key);
    ~EasyWave();

    void Initialize(Input* input, Camera* camera, Audio* audio) override;
    void Update() override;
    void Draw() override;
    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

private:
    XMFLOAT3 ResetPos();

private:
    // “I
    static const int TARGET_AMOUNT = 4;
    std::array<BaseTarget*, TARGET_AMOUNT> targets;

    std::array<std::array<bool, 4>, 5> isPos;
};