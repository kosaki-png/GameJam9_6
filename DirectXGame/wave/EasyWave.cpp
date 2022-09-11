#include "EasyWave.h"

EasyWave::EasyWave(Level level)
	: BaseWave::BaseWave(level)
{
}

EasyWave::~EasyWave()
{
}

void EasyWave::Initialize(Input* input, Camera* camera)
{
	// uiの初期化
	BaseWave::Initialize(input, camera);

	// ここに初期化処理
	{

	}
}

void EasyWave::Update()
{
	// ここに更新処理
	{

	}

	// uiの更新
	BaseWave::Update();
}

void EasyWave::Draw()
{
	// ここに描画処理
	{

	}
}

void EasyWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	BaseWave::DrawUi(cmdList);
}