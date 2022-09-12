#pragma once
#include <DirectXMath.h>
#include "Sprite.h"
#include "Input.h"
#include "DirectXCommon.h"

class BaseTransition
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

public:
	BaseTransition();
	virtual ~BaseTransition();

	virtual void Initialize(DirectXCommon* dxCommon, Input* input);
	virtual void Start();
	virtual void Update();
	virtual void Draw();

	bool GetCanChange() { return canChange; }
	bool GetIsMove() { return isMove; }

protected:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	bool canChange = false;
	bool isMove = false;
	bool isHalf = false;
};

