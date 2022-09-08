#include "BaseWave.h"
using namespace DirectX;

BaseWave::BaseWave()
{
}

BaseWave::~BaseWave()
{
}

void BaseWave::Initialize(Input* input, Camera* camera)
{
	this->input = input;
	this->camera = camera;

	// 視線レイの初期設定
	XMFLOAT3 tmp = camera->GetEye();
	ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
	tmp = camera->GetDir();
	ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);

	ui = new Ui();
	ui->Initialize();
}

void BaseWave::Update()
{
	// uiの更新
	ui->Update();
}

void BaseWave::Draw()
{
}

void BaseWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// uiの描画
	ui->Draw(cmdList);
}
