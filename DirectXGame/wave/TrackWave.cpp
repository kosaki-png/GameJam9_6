#include "TrackWave.h"

using namespace DirectX;

TrackWave::TrackWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

TrackWave::~TrackWave()
{
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		delete targets[i];
	}
}

void TrackWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// uiの初期化
	BaseWave::Initialize(input, camera, audio);

	// ここに初期化処理
	{
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			// ターゲット生成
			targets[i] = new BaseTarget();
			targets[i]->Initialize("sphere");
		}
	}

	// 全て生成してから位置リセット
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		// 初期位置セット
		targets[i]->SetPosition(ResetPos());
		//初期移動量セット
		targets[i]->SetVelocity(ResetVel());

		targets[i]->SetMoveTime(ResetMoveTime());
	}
}

void TrackWave::Update()
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

		// 全ての的に当たっているか
		bool allColl = false;
		// 的ごとに当たり判定
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			// 視線レイと的との当たり判定
			if (Collision::CheckRay2Sphere(ray, targets[i]->GetSphere()))
			{
				float life = targets[i]->GetLife();
				life -= 1;
				targets[i]->SetLife(life);
				targets[i]->SetMode(true);
				// どれか一つにでも当たっている
				allColl = true;
			}
			else
			{
				targets[i]->SetMode(false);
			}

			if (targets[i]->GetLife() == 0)
			{
				//スコア追加
				ui->AddScore(50);
				ui->AddCount();
				//ヒット音を鳴らす
				//audio->PlayWave(L"Resources/sound/r7nlp-8pgbr.wav");

				targets[i]->SetLife(60);

				// 位置リセット
				targets[i]->SetPosition(ResetPos());
				//移動量リセット
				targets[i]->SetVelocity(ResetVel());
			}

			targets[i]->SetMoveTime(targets[i]->GetMoveTime() - 0.5);

			if (targets[i]->GetMoveTime() == 0)
			{
				XMFLOAT3 tmp = XMFLOAT3(targets[i]->GetVelocity().x * -1, targets[i]->GetVelocity().y, targets[i]->GetVelocity().z);
				targets[i]->SetVelocity(tmp);
				targets[i]->SetMoveTime(ResetMoveTime());
			}


			// 的の更新
			targets[i]->move();
			targets[i]->objUpdata();
		}

		if (ui->IsTimeUp())
		{
			clearFlag = true;
		}

		// uiの更新
		BaseWave::Update();
	}
}

void TrackWave::Draw()
{
	// ここに描画処理
	{
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			targets[i]->Draw();
		}	}
}

void TrackWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	BaseWave::DrawUi(cmdList);
}

XMFLOAT3 TrackWave::ResetPos()
{
	XMFLOAT3 result = { (float)(rand() % 15) - 7, (float)(rand() % 5) - 1, 0 };

	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		auto tmp = targets[i]->GetPosition();
		if (tmp.y == result.y)
		{
			return TrackWave::ResetPos();
		}
	}

	return result;

}

XMFLOAT3 TrackWave::ResetVel()
{
	XMFLOAT3 result = { ((float)(rand() % 5) -2) / 30, 0, 0 };

	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		if (result.x == 0)
		{
			return TrackWave::ResetVel();
		}
	}
	return result;
}

float TrackWave::ResetMoveTime()
{
	float result = (float)(rand() % 40)+1;
	return result;

}
