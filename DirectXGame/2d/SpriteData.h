#pragma once
#include "Sprite.h"

class SpriteData
{
public:
	static void LoadTexture();

public:
	// テキスト用
	const int TEXT_FONT = 0;

	// タイトル用
	const int TITLE = 1;

	// セレクト用
	const int SELECT = 11;

	// ゲーム用
	const int GAME = 21;

	// エンド用
	const int END = 31;

};

