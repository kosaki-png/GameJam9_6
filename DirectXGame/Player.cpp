#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	safe_delete(spritePlayer);
}

void Player::Initialize(Input* input)
{
	this->input = input;

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			Sprite::LoadTexture(6, L"Resources/メロス.png");
		}

		// スプライト生成
		{
			// プレイヤー
			spritePlayer = Sprite::Create(6, { 1000, 300 });
		}
	}
}

void Player::Update()
{
	// 悪夢切り替え
	sleepCnt++;
	if (sleepCnt > sleepLimit)
	{
		isSleep = true;
	}

	// 上下移動
	if (input->PushKey(DIK_W))
	{
		spritePlayer->MovePosition({ 0, -6});
	}
	if (input->PushKey(DIK_S))
	{
		spritePlayer->MovePosition({ 0, 6});
	}
}

void Player::Draw()
{
	spritePlayer->Draw();
}