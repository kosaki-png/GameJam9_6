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

void WaveManager::Initialize(Input* input, Camera* camera, Audio* audio)
{
    if (wave)
    {
        delete wave;
    }

    switch (mode)
    {
    case WaveMode::test:
        wave = new TestWave("test");
        break;

    case WaveMode::easy:
        wave = new EasyWave("easy");
        break;

    case WaveMode::flick_easy:
        wave = new FlickWave("flick_easy");
        break;

    case WaveMode::filck_normal:
        wave = new FlickWave("filck_normal");
        break;

    case WaveMode::flick_hard:
        wave = new FlickWave("flick_hard");
        break;

    case WaveMode::flick_hell:
        wave = new FlickWave("flick_hell");
        break;

    case WaveMode::follow:
        wave = new FollowWave("follow");
        break;

    case WaveMode::around:
        wave = new AroundWave("around");
        break;

    default:
        wave = new TestWave("test");
        break;
    }

    // 初期化
    wave->Initialize(input, camera,audio);
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

bool WaveManager::GetIsCount()
{
    return wave->GetIsCount();
}

void WaveManager::DestroyWave()
{
    //delete wave;
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
