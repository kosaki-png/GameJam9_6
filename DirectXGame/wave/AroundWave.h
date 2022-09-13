#pragma once
#include "BaseWave.h"
class AroundWave :
    public BaseWave
{
public:
    AroundWave(std::string key);
    ~AroundWave();

    void Initialize(Input* input, Camera* camera, Audio* audio) override;
    void Update() override;
    void Draw() override;
    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

private:
    void ResetPos();

private:
    BaseTarget* target = nullptr;

    float rad = 0;
    float height = 0;

    const float PI = 3.141592;
};

