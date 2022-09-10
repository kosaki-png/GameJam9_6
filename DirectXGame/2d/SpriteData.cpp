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

	// エンド読み込み
	Sprite::LoadTexture(END,		L"Resources/Texture/end.png");
}
