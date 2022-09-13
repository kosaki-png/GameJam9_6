#include "FlickWave.h"

using namespace DirectX;

FlickWave::FlickWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

FlickWave::~FlickWave()
{
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		delete targets[i];
	}
}

void FlickWave::Initialize(Input* input, Camera* camera, Audio* audio)
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

			// 難易度に応じて大きさ変更
			float scale = 1.0f - 0.3f * 1;//後で直す
			targets[i]->SetScale({ scale, scale , scale });
		}

		// 全て生成してから位置リセット
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			// 初期位置セット
			targets[i]->SetPosition(ResetPos());
		}
	}
}

void FlickWave::Update()
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
		}

		// クリア条件
		{
			clearFlag = ui->IsTimeUp();
		}
	}

	// uiの更新
	BaseWave::Update();
}

void FlickWave::Draw()
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

void FlickWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	BaseWave::DrawUi(cmdList);
}

XMFLOAT3 FlickWave::ResetPos()
{
	XMFLOAT3 result = { (float)(rand() % 5) - 2, (float)(rand() % 4) - 1, 0 };

	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		auto tmp = targets[i]->GetPosition();
		if (tmp.x == result.x && tmp.y == result.y)
		{
			return FlickWave::ResetPos();
		}
	}

	return result;
}
