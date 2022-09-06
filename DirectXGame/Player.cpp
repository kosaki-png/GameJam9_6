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

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			Sprite::LoadTexture(6, L"Resources/�����X.png");
		}

		// �X�v���C�g����
		{
			// �v���C���[
			spritePlayer = Sprite::Create(6, { 1000, 300 });
		}
	}
}

void Player::Update()
{
	// �����؂�ւ�
	sleepCnt++;
	if (sleepCnt > sleepLimit)
	{
		isSleep = true;
	}

	// �㉺�ړ�
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