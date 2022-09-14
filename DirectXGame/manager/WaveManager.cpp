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
    case WaveMode::traning:
        wave = new EasyWave("traning");
        break;

    case WaveMode::flick_easy:
        wave = new FlickWave("flick1");
        break;

    case WaveMode::flick_normal:
        wave = new FlickWave("flick2");
        break;

    case WaveMode::flick_hard:
        wave = new FlickWave("grid1");
        break;

    case WaveMode::flick_hell:
        wave = new FlickWave("grid2");
        break;

    case WaveMode::follow:
        wave = new FollowWave("track1");
        break;

    case WaveMode::track:
        wave = new TrackWave("track2");
        break;

    case WaveMode::around:
        wave = new AroundWave("360");
        break;

    case WaveMode::scale:
        wave = new AroundWave("shrink");
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
    mode = WaveMode::traning;
}

void WaveManager::Destroy()
{
    if (wave)
    {
        delete wave;
    }
    delete instance;
}
