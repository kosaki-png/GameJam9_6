#include "SpriteData.h"

void SpriteData::LoadTexture()
{
	// �e�L�X�g�p�e�N�X�`���ǂݍ���
	Sprite::LoadTexture(TEXT_FONT,	L"Resources/Texture/font_sharp.png");

	// �^�C�g���ǂݍ���
	Sprite::LoadTexture(TITLE,		L"Resources/Texture/title_01.png");

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
	Sprite::LoadTexture(COUNT_BASE,	L"Resources/Texture/count_base.png");
	Sprite::LoadTexture(CLICK,		L"Resources/Texture/count_click.png");
	Sprite::LoadTexture(START,		 L"Resources/Texture/count_start.png");

	// �G���h�ǂݍ���
	Sprite::LoadTexture(END,		L"Resources/Texture/result_01.png");

	// �g�����W�V�����ǂݍ���
	Sprite::LoadTexture(BLACK,		L"Resources/Texture/black_64x64.png");
}
