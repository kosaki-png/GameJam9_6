#include "SpriteData.h"

void SpriteData::LoadTexture()
{
	// テキスト用テクスチャ読み込み
	Sprite::LoadTexture(TEXT_FONT,	L"Resources/Texture/font_sharp.png");

	// タイトル読み込み
	Sprite::LoadTexture(TITLE,		L"Resources/Texture/title_01.png");

	// セレクト読み込み
	Sprite::LoadTexture(SELECT,		L"Resources/Texture/select.png");

	// ゲーム読み込み
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

	// エンド読み込み
	Sprite::LoadTexture(END,		L"Resources/Texture/result_01.png");

	// トランジション読み込み
	Sprite::LoadTexture(BLACK,		L"Resources/Texture/black_64x64.png");
}
