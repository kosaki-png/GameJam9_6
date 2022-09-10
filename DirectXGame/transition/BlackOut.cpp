#include "BlackOut.h"
#include "SpriteData.h"

BlackOut::BlackOut()
{
}

BlackOut::~BlackOut()
{
	delete black;
}

void BlackOut::Initialize(DirectXCommon* dxCommon, Input* input)
{
	BaseTransition::Initialize(dxCommon, input);

	// スプライト初期設定
	{
		black = Sprite::Create(BLACK, { 0,0 });
		black->SetSize({ 1920.0f, 1080.0f });
		black->SetAlpha(0.0f);
	}
}

void BlackOut::Start()
{
	// スプライト初期化
	black->SetAlpha(0.0f);

	// シーンを変更不可に
	canChange = false;

	// 演出開始
	isMove = true;
}

void BlackOut::Update()
{
	if (isMove)
	{
		// 遷移前
		if (!canChange)
		{
			if (alpha < 1.0f)
			{
				// だんだん濃く
				alpha += 0.01f;
			}
			else
			{
				// シーンを変更可能に
				canChange = true;
			}
		}
		// 遷移後
		else
		{
			if (alpha > 0.0f)
			{
				// だんだん薄く
				alpha -= 0.01f;
			}
			else
			{
				// 演出終了
				isMove = false;
			}
		}

		black->SetAlpha(alpha);
	}
}

void BlackOut::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	{
		black->Draw();
	}
	Sprite::PostDraw();
}
