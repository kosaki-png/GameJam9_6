#include "EndScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include "DebugCamera.h"
#include "FreeCamera.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
	delete objGround;
	delete objSky;
	delete modelGround;
	delete modelSky;
}

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	audio->Stop();

	// �ėp�I������
	{
		// �J��������
		camera = new FreeCamera(WinApp::window_width, WinApp::window_height);

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
			tmpSprite = Sprite::Create(END, { 0,0 });
			resultUi = new ResultUi();
			resultUi->Initialize();
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// 3D�I�u�W�F�N�g�����ݒ�
	{
		// ���f���ǂݍ���
		{
			modelGround = Model::CreateFromOBJ("field");
			modelSky = Model::CreateFromOBJ("skydome", true);
		}

		// 3D�I�u�W�F�N�g����
		{
			objGround = Object3d::Create(modelGround);
			objSky = Object3d::Create(modelSky);
		}

		// 3D�I�u�W�F�N�g�����ݒ�
		{
			objGround->Initialize();
			objGround->SetPosition({ 0,-5, 0 });
			objSky->SetScale({ 2,2,2 });
		}
	}

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(300.0f);
}

void EndScene::Update()
{
	// Enter�Ŏw��̃V�[����
	if (input->TriggerKey(DIK_RETURN))
	{
		// �^�C�g���V�[����
		nextScene = new TitleScene();
	}

	// ESCAPE�ŃQ�[���I��
	if (input->PushKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// �p�[�e�B�N������
	//CreateParticles();
	rot.x += 0.1f;
	lightGroup->Update();
	camera->Update();
	camera->SetRotation(rot);
	resultUi->Update();
	// 3D�I�u�W�F�N�g�X�V
	{
		objGround->Update();
		objSky->Update();
	}

}

void EndScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��
	{
		// �w�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);
		{
			
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
			objGround->Draw();
			objSky->Draw();
		}
		Object3d::PostDraw();
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);
		{
			tmpSprite->Draw();
			resultUi->Draw(cmdList);
			// �f�o�b�O�e�L�X�g�̕`��
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}
}