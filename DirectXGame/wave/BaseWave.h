#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Ui.h"
#include "Collision.h"
#include "CollisionPrimitive.h"
#include "Camera.h"
#include "DirectXCommon.h"
#include "Sprite.h"

#include <array>
#include "BaseTarget.h"

class BaseWave
{
public:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	BaseWave();
	virtual ~BaseWave();

	virtual void Initialize(Input* input, Camera* camera);
	virtual void Update();
	virtual void Draw();
	virtual void DrawUi(ID3D12GraphicsCommandList* cmdList);
	
	/// <summary>
	/// クリアしたか
	/// </summary>
	/// <returns></returns>
	bool GetClearFlag() { return clearFlag; }

protected:
	// キー入力
	Input* input;

	// 視線レイ用
	Camera* camera = nullptr;
	Ray ray;

	// クリア判定用
	bool clearFlag = false;

	// UI、スコア管轄
	Ui* ui = nullptr;
};

