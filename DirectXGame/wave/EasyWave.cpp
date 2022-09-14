#include "EasyWave.h"

EasyWave::EasyWave(std::string key)
	: BaseWave::BaseWave(key)
{
}

EasyWave::~EasyWave()
{
	delete target;
}

void EasyWave::Initialize(Input* input, Camera* camera, Audio* audio)
{
	// uiの初期化
	BaseWave::Initialize(input, camera, audio);

	// ここに初期化処理
	{
		ResetTarget();

		// 初期位置セット
		target->SetPosition(ResetPos());
	}
}

void EasyWave::Update()
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
		//当たり判定
		
		// 視線レイと的との当たり判定
		if (Collision::CheckRay2Sphere(ray, target->GetSphere()))
		{
			if (input->TriggerMouseLeft())
			{
				//スコア追加
				ui->AddScore(10);
				ui->AddCount();
				//ヒット音を鳴らす
				audio->PlayWave(L"Resources/sound/r7nlp-8pgbr.wav");
			
				// 位置リセット
				target->SetPosition(ResetPos());
				delete target;
				target = nullptr;
			}

			// どれか一つにでも当たっている
			allColl = true;
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

		//的を消した時の再生成
		if (target == nullptr)
		{
			ResetTarget();
			// 初期位置セット
			target->SetPosition(ResetPos());
		}

		// 的の更新
		target->Update();
		
		// クリア条件
		{
			clearFlag = ui->IsTimeUp();
		}
	}

	// uiの更新
	BaseWave::Update();
}

void EasyWave::Draw()
{
	// ここに描画処理
	{
		// 的の描画
		target->Draw();
	}
}

void EasyWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	BaseWave::DrawUi(cmdList);
}

void EasyWave::ResetTarget()
{
	// ターゲット生成
	target = new EasyTarget();
	target->Initialize("sphere", ResetPos());
	target->SetVelocity({ 0.01f,0.01f,0.01f });
	target->SetAmplitude({ 3.0f,0.0f,0.0f });

	//スケール
	float scale = 0;
	scale = 1.0f - 0.3f * 0;
	target->SetScale({ scale, scale, scale });
}

DirectX::XMFLOAT3 EasyWave::ResetPos()
{
	XMFLOAT3 result = { (float)(rand() % 5) - 2, (float)(rand() % 4) - 1, 0 };

	auto tmp = target->GetPosition();
	if (tmp.x == result.x && tmp.y == result.y)
	{
		return EasyWave::ResetPos();
	}
	
	return result;
}
