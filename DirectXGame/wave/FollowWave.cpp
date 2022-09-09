#include "FollowWave.h"

using namespace DirectX;

FollowWave::FollowWave()
{
}

FollowWave::~FollowWave()
{
	delete target;
	delete ui;
}

void FollowWave::Initialize(Input* input, Camera* camera)
{
	// ui�̏�����
	BaseWave::Initialize(input, camera);

	// �����ɏ���������
	{
		target = new BaseTarget();
		target->Initialize("sphere");
	}
}

void FollowWave::Update()
{
	// �����ɍX�V����
	{


		target->Update();
	}

	// ui�̍X�V
	BaseWave::Update();
}

void FollowWave::Draw()
{
	// �����ɕ`�揈��
	{
		target->Draw();
	}
}

void FollowWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}
