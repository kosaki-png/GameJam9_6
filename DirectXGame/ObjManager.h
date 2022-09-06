#pragma once
#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "Text.h"
#include "Input.h"
#include <vector>

#include "Define.h"
#include "BackGround.h"
#include "Player.h"
#include "Dog.h"
#include "River.h"
#include "Thieves.h"

class ObjManager
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int texNumber = 0;

public: // メンバ関数

	ObjManager();
	~ObjManager();

	void Initialize(Input* input);
	void Update();
	void SpeedDown();
	inline bool InvincibleTime(bool hit_Flag);
	inline int RandomStart(int count);
	inline float MinElement(Dog* array, float position);
	void Draw();
	bool GetClear() { return clear; }
	bool GetOver() { return over; }

	bool GetDamage() { return damage; }

	bool GetSign() { return signClear; }

private:	// メンバ変数
	Input* input = nullptr;
	BackGround* back = nullptr;
	Player* player = nullptr;
	Dog* dog[DOG] = {};
	Dog* dream_dog[D_DOG] = {};
	River* river = nullptr;
	Thieves* thieves = nullptr;

	float speed = 0;
	bool hit_Flag;
	int invincibleCount;
	int limit;
	bool life_Flag;
	bool second_Flag;
	float min;
	int doglimit;
	int doglimit1;
	int riverlimit;
	int thievelimit;

	bool dog_Flag;
	bool river_Flag;
	bool thieves_Flag;
	int startTime;;
	float goal = 50000;

	bool clear = false;
	bool over = false;

	// ノーダメ用
	bool damage = false;

	// 看板用
	bool sign[5] = {false, false, false, false, false, };
	bool signClear = false;
};