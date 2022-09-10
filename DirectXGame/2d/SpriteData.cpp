#include "SpriteData.h"

void SpriteData::LoadTexture()
{
	// �e�L�X�g�p�e�N�X�`���ǂݍ���
	Sprite::LoadTexture(TEXT_FONT,	L"Resources/Texture/font_sharp.png");

	// �^�C�g���ǂݍ���
	Sprite::LoadTexture(TITLE,		L"Resources/Texture/title.png");

	// �Z���N�g�ǂݍ���
	Sprite::LoadTexture(SELECT,		L"Resources/Texture/select.png");

	// �Q�[���ǂݍ���
	Sprite::LoadTexture(GAME,		L"Resources/Texture/game.png");
	Sprite::LoadTexture(CROSS,		L"Resources/Texture/cross.png");
	Sprite::LoadTexture(UI_SCORE,	L"Resources/Texture/ui_01.png");
	Sprite::LoadTexture(UI_FONT_1,	L"Resources/Texture/font_sharp.png");
	Sprite::LoadTexture(UI_FONT_2,	L"Resources/Texture/font_cursive.png");
	Sprite::LoadTexture(OPTION_BASE, L"Resources/Texture/option_base.png");
	Sprite::LoadTexture(OPTION_BAR, L"Resources/Texture/option_bar.png");

	// �G���h�ǂݍ���
	Sprite::LoadTexture(END,		L"Resources/Texture/end.png");
}
