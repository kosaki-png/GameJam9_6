#pragma once
#include "Sprite.h"

// テキスト用
static const int TEXT_FONT = 0;

// タイトル用
static const int TITLE = 1;

// セレクト用
static const int SELECT = 11;

// ゲーム用
static const int GAME = 21;
static const int CROSS = 22;
static const int UI_SCORE = 23;
static const int UI_FONT_1 = 24;
static const int UI_FONT_2 = 25;

// エンド用
static const int END = 31;

class SpriteData
{
public:
	static void LoadTexture();

};

