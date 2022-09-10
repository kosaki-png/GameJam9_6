#pragma once
#include "BaseTransition.h"

class BlackOut :
    public BaseTransition
{
public:
    BlackOut();
    ~BlackOut();

    void Initialize(DirectXCommon* dxCommon, Input* input) override;
    void Start() override;
    void Update() override;
    void Draw() override;

private:
    Sprite* black = nullptr;
    float alpha = 0.0f;

};

