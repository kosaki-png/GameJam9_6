#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include "DebugCamera.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

		// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
		Object3d::SetCamera(camera);

		// �f�o�b�O�e�L�X�g������
		text = Text::GetInstance();

		// ���C�g����
		lightGroup = LightGroup::Create();
		// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
		Object3d::SetLightGroup(lightGroup);
	}

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g����
		{
			tmpSprite = Sprite::Create(SELECT, { 0,0 });
		}

		// �X�v���C�g�̃T�C�Y�ύX
		{
		}
	}

	// 3D�I�u�W�F�N�g�����ݒ�
	{
	}

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(10.0f);

	// �e�N���X�̏�����
	{
	}
}

void SelectScene::Update()
{
	// Enter�Ŏw��̃V�[����
	if (input->TriggerKey(DIK_RETURN))
	{	
		//�Q�[���V�[����
		nextScene = new GameScene();
	}

	// 3D�I�u�W�F�N�g�X�V
	{}
	// �e�N���X�̍X�V
	{
		lightGroup->Update();
		camera->Update();
	}
}

void SelectScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��
	{
		// �w�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);
		{
			tmpSprite->Draw();
		}
		Sprite::PostDraw();
		// �[�x�o�b�t�@�N���A
		dxCommon->ClearDepthBuffer();
	}

	// 3D�`��
	{
		// 3D�I�u�W�F�N�g�̕`��
		Object3d::PreDraw(cmdList);
		{

		}
		Object3d::PostDraw();
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);
		{


			// �f�o�b�O�e�L�X�g�̕`��
			text->DrawAll(cmdList);
		}
		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}