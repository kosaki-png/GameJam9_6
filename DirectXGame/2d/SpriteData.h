#pragma once
#include "Sprite.h"

// テキスト用
static const int TEXT_FONT = 0;

// タイトル用
static const int TITLE = 1;

// セレクト用
static const int SELECT = 11;
static const int SCORE = 12;
static const int MENU = 13;

// ゲーム用
static const int GAME = 21;
static const int CROSS = 22;
static const int UI_SCORE = 23;
static const int UI_FONT_1 = 24;
static const int UI_FONT_2 = 25;
static const int OPTION_BASE = 26;
static const int OPTION_BAR = 27;
static const int COUNT_BASE = 28;
static const int CLICK = 29;
static const int START = 30;

// エンド用
static const int END = 41;

// トランジション用
static const int BLACK = 51;

class SpriteData
{
public:
	static void LoadTexture();

};

