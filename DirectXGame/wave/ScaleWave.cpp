#include "ScaleWave.h"

ScaleWave::ScaleWave(std::string key)
    :  BaseWave::BaseWave(key)
{
}

ScaleWave::~ScaleWave()
{
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		delete targets[i];
	}
}

void ScaleWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// uiの初期化
	BaseWave::Initialize(input, camera, audio);

	// ここに初期化処理
	{
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			// ターゲット生成
			targets[i] = new ScaleTarget();
			targets[i]->Initialize("sphere");
			targets[i]->SetVelocity({ 0.003f,0.003f,0.003f });
		}

		// 全て生成してから位置リセット
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			// 初期位置セット
			targets[i]->SetPosition(ResetPos());
		}
	}
}

void ScaleWave::Update()
{
	// ここに更新処理
	{
		// 視線レイの更新
		{
			XMFLOAT3 tmp = camera->GetEye();
			ray.start = DirectX::XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
			tmp = camera->GetDir();
			ray.dir = DirectX::XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		}

		if (input->TriggerMouseLeft())
		{
			ui->AddTargets();
		}

		// 全ての的に当たっているか
		bool allColl = false;
		// 的ごとに当たり判定
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			// 視線レイと的との当たり判定
			if (Collision::CheckRay2Sphere(ray, targets[i]->GetSphere()))
			{
				if (input->TriggerMouseLeft())
				{
					//スコア追加
					ui->AddScore(10);
					ui->AddCount();
					//ヒット音を鳴らす
					audio->PlayWave(L"Resources/sound/r7nlp-8pgbr.wav");
					//スケールを初期値に戻す
					targets[i]->SetScale({ 1.0f,1.0f,1.0f });
					// 位置リセット
					targets[i]->SetPosition(ResetPos());
				}

				// どれか一つにでも当たっている
				allColl = true;
			}
		}

		// 全てに当たっていなかったら
		if (!allColl)
		{
			if (input->TriggerMouseLeft())
			{
				// ミスを増やす
				ui->AddMiss();
			}
		}

		// 的の更新
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			targets[i]->Update();

			if (targets[i]->GetScale().x < 0)
			{
				// ミスを増やす
				ui->AddMiss();
				//スケールを初期値に戻す
				targets[i]->SetScale({ 1.0f,1.0f,1.0f });
				// 位置リセット
				targets[i]->SetPosition(ResetPos());
			}
		}

		// クリア条件
		{
			clearFlag = ui->IsTimeUp();
		}
	}

	// uiの更新
	BaseWave::Update();
}

void ScaleWave::Draw()
{
	// ここに描画処理
	{
		// 的の描画
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			targets[i]->Draw();
		}
	}
}

void ScaleWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	BaseWave::DrawUi(cmdList);
}

DirectX::XMFLOAT3 ScaleWave::ResetPos()
{
	XMFLOAT3 result = { (float)(rand() % 5) - 2, (float)(rand() % 4) - 1, 0 };

	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		auto tmp = targets[i]->GetPosition();
		if (tmp.x == result.x && tmp.y == result.y)
		{
			return ScaleWave ::ResetPos();
		}
	}

	return result;
}
