#pragma once
#include "BaseWave.h"
class FlickWave :
    public BaseWave
{
public:
    FlickWave();
    ~FlickWave();

    void Initialize(Input* input, Camera* camera) override;
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

