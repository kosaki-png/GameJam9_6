#pragma once

#include <DirectXMath.h>
#include <vector>
#include "SafeDelete.h"
#include "Sprite.h"
#include "Collision.h"
#include <stdlib.h> // rand, srandΦ
#include <time.h>   // timeΦ
#include <random>
#define enemy 3

class Thieves
{
private: // GCAX
// Microsoft::WRL::πΘͺ
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::πΘͺ
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	Thieves();
	~Thieves();

	/// <summary>
	/// ϊ»
	/// </summary>
	void Initialize();

	/// <summary>
	/// t[
	/// </summary>
	void Update(float speed);

	/// <summary>
	/// `ζ
	/// </summary>
	void Draw(bool sleep);

	/// <summary>
	/// `ζ
	/// </summary>
	void Spawn();

   /// <summary>
   /// dΘθ`FbN
   /// </summary>
    bool Check(int number);

	std::vector<XMFLOAT2> GetPosition();
	void SetPosition(XMFLOAT2 positions);

private:
	Sprite* thieves[enemy]; //―XvCg
	XMFLOAT2 e_Pos[enemy];
	//e―ΜΐWΜΆ¬
	float posX[enemy];
	float posY[enemy];
	float width = 100; //ζΜ‘
	float height = 100; //ζΜc
	float speed = 0.0f;
	bool Drawflag[enemy]; //`ζtO
};

