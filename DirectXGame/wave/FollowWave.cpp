#include "FollowWave.h"

using namespace DirectX;

FollowWave::FollowWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

FollowWave::~FollowWave()
{
	delete target;
	delete ui;
}

void FollowWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// uiの初期化
	BaseWave::Initialize(input, camera, audio);

	// ここに初期化処理
	{
		target = new MoveTarget();
		target->Initialize("sphere");
		target->SetVelocity({ 0.02f,0.01f,0.0f });
		target->SetAmplitude({ 3.0f,3.0f,0.0f });
	}
}

void FollowWave::Update()
{
	// ここに更新処理
	{
		// 視線レイの更新
		{
			XMFLOAT3 tmp = camera->GetEye();
			ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
			tmp = camera->GetDir();
			ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		}

		// 視線レイと的との当たり判定
		if (input->PushMouseLeft())
		{
			if (Collision::CheckRay2Sphere(ray, target->GetSphere()))
			{
				// 生きているなら殺す
					ui->AddScore(1);
					ui->AddCount();
					//ヒット音を鳴らす
					audio->PlayWave(L"Resources/sound/r7nlp-8pgbr.wav");
			}
			else
			{
				// 死んでいたならミスカウントを増やす
				ui->AddMiss();
			}
		}

		target->Update();
	}

	// uiの更新
	BaseWave::Update();
}

void FollowWave::Draw()
{
	// ここに描画処理
	{
		target->Draw();
	}
}

void FollowWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	BaseWave::DrawUi(cmdList);
}
