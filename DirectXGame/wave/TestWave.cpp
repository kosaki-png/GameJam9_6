/*#include "TestWave.h"

using namespace DirectX;

TestWave::TestWave()
{
}

TestWave::~TestWave()
{
	delete ui;
}

void TestWave::Initialize(Input* input, Camera* camera)
{
	// uiの初期化
	BaseWave::Initialize(input, camera);

	// ここに初期化処理
	{

	}
}

void TestWave::Update()
{
	// ここに更新処理
	{

	}

	// uiの更新
	BaseWave::Update();
}

void TestWave::Draw()
{
	// ここに描画処理
	{

	}
}

void TestWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	BaseWave::DrawUi(cmdList);
}
*/

#include "TestWave.h"

using namespace DirectX;

TestWave::TestWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

TestWave::~TestWave()
{
	for (int i = 0; i < TARGET_AMOUNT; i++)
	{
		delete target[i];
	}
}

void TestWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// uiの初期化
	BaseWave::Initialize(input, camera, audio);

	// ここに初期化処理
	{
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			target[i] = new BaseTarget();
			target[i]->Initialize("sphere");
			target[i]->SetPosition({ (float)(i % 5) - 2.0f, (float)(int)(i / 5) - 1 , 0 });
		}
	}
}

void TestWave::Update()
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
			if (Collision::CheckRay2Sphere(ray, target[i]->GetSphere()))
			{
				if (input->TriggerMouseLeft())
				{
					// 生きているなら殺す
					if (!target[i]->GetIsDead())
					{
						target[i]->SetIsDead(true);
						ui->AddScore(10);
						ui->AddCount();
						//ヒット音を鳴らす
						audio->PlayWave(L"Resources/sound/r7nlp-8pgbr.wav");
					}
					// 死んでいたならミスカウントを増やす
					else
					{
						ui->AddMiss();
					}
				}

				// どれか一つにでも当たっている
				allColl = true;
			}

			// 復活
			if (target[i]->GetIsDead())
			{
				respownCnt[i]++;
				if (respownCnt[i] > 200)
				{
					target[i]->SetIsDead(false);
					respownCnt[i] = 0;
				}
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
			target[i]->Update();
		}

		// クリア条件
		{
			clearFlag = ui->IsTimeUp();
		}
	}

	// uiの更新
	BaseWave::Update();
}

void TestWave::Draw()
{
	// ここに描画処理
	{
		// 的の描画
		for (int i = 0; i < TARGET_AMOUNT; i++)
		{
			target[i]->Draw();
		}
	}
}

void TestWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	BaseWave::DrawUi(cmdList);
}
