/*
public:
    �N���X��();
    ~�N���X��();

    void Initialize(Input* input, Camera* camera) override;
    void Update() override;
    void Draw() override;
    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

private:
*/

#pragma once
#include "BaseWave.h"

class TestWave :
    public BaseWave
{
public:
    TestWave(Level level);
    ~TestWave();

    void Initialize(Input* input, Camera* camera) override;
    void Update() override;
    void Draw() override;
    void DrawUi(ID3D12GraphicsCommandList* cmdList) override;

private:
    // �^�[�Q�b�g
    static const int TARGET_AMOUNT = 20;
    std::array<BaseTarget*, TARGET_AMOUNT> target;

    std::array<int, TARGET_AMOUNT> respownCnt = {};
};