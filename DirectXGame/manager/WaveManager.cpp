#include "WaveManager.h"

WaveManager* WaveManager::instance = nullptr;

WaveManager* WaveManager::GetInstance()
{
    if (!instance)
    {
        instance = new WaveManager();
    }
    return instance;
}

void WaveManager::Initialize(Input* input, Camera* camera)
{
    switch (mode)
    {
    case WaveMode::test:
        wave = new TestWave(easy);
        break;

    case WaveMode::easy:
        wave = new EasyWave(easy);
        break;

    case WaveMode::flick_easy:
        wave = new FlickWave(easy);
        break;

    case WaveMode::filck_normal:
        wave = new FlickWave(normal);
        break;

    case WaveMode::flick_hard:
        wave = new FlickWave(hard);
        break;

    case WaveMode::flick_hell:
        wave = new FlickWave(hell);
        break;

    case WaveMode::follow:
        wave = new FollowWave(easy);
        break;

    default:
        wave = new TestWave(easy);
        break;
    }

    // 初期化
    wave->Initialize(input, camera);
}

void WaveManager::Update()
{
    // カウントダウン開始
    if (wave->GetIsCount())
    {
        wave->CountDown();
    }
    else
    {
        // ウェーブの更新
        wave->Update();
    }
}

void WaveManager::Draw()
{
    wave->Draw();
}

void WaveManager::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
    // カウントダウン開始
    if (wave->GetIsCount())
    {
        wave->CountDownDraw();
    }
    else
    {
        wave->DrawUi(cmdList);
    }
}

bool WaveManager::GetClearFlag()
{
    return wave->GetClearFlag();
}

void WaveManager::DestroyWave()
{
    delete wave;
    wave = nullptr;
    mode = WaveMode::test;
}

void WaveManager::Destroy()
{
    if (wave)
    {
        delete wave;
    }
    delete instance;
}
