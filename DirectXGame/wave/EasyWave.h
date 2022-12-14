#pragma once
#include "BaseWave.h"
#include "EasyTarget.h"

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
    
    void ResetTarget();

    XMFLOAT3 ResetPos();

private:
    // ?I
    EasyTarget* target = nullptr;
    std::array<std::array<bool, 4>, 5> isPos;
};