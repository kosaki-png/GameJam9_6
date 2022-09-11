#pragma once
#include "BaseWave.h"

class EasyWave :
    public BaseWave
{
public:
    EasyWave(Level level);
    ~EasyWave();

    void Initialize(Input* input, Camera* camera) override;
    void Update() override;
    void Draw() override;
    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

private:

};