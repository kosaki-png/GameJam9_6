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
	// ui�̏�����
	BaseWave::Initialize(input, camera);

	// �����ɏ���������
	{

	}
}

void EasyWave::Update()
{
	// �����ɍX�V����
	{

	}

	// ui�̍X�V
	BaseWave::Update();
}

void EasyWave::Draw()
{
	// �����ɕ`�揈��
	{

	}
}

void EasyWave::DrawUi(ID3D12GraphicsCommandList* cmdList)
{
	// ui�̕`��
	BaseWave::DrawUi(cmdList);
}