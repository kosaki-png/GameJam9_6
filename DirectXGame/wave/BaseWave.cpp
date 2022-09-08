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

	// �������C�̏����ݒ�
	XMFLOAT3 tmp = camera->GetEye();
	ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
	tmp = camera->GetDir();
	ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);

	ui = new Ui();
	ui->Initialize();
}

void BaseWave::Update()
{
	// ui�̍X�V
	ui->Update();
}

void BaseWave::Draw()
{
}

void BaseWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	ui->Draw(cmdList);
}
