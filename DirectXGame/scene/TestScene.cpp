#include "TestScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include "FreeCamera.h"
#include "Collision.h"
#include "TestWave.h"
#include "FlickWave.h"

using namespace DirectX;

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
	delete cross;
	delete modelGround;
	delete objGround;
	delete camera;
	delete wave;
	delete lightGroup;
}

void TestScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	audio->Stop();

	// �ėp�I������
	{
		// �J��������
		camera = new FreeCamera(WinApp::window_width, WinApp::window_height);
		camera->SetInput(input);

		// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
		Object3d::SetCamera(camera);

		// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
		if (!Sprite::LoadTexture(texNumber, L"Resources/font_sharp.png")) {
			assert(0);
			return;
		}
		// �f�o�b�O�e�L�X�g������
		text = Text::GetInstance();
		text->Initialize(texNumber);

		// ���C�g����
		lightGroup = LightGroup::Create();
		// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
		Object3d::SetLightGroup(lightGroup);
	}

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			//Sprite::LoadTexture(1, L"Resources/Title1.png");
			Sprite::LoadTexture(10, L"Resources/centerDot.png");
		}

		// �X�v���C�g����
		{
			//title1 = Sprite::Create(1, { 0, 0 });
			cross = Sprite::Create(10, { centerX, centerY });
			cross->SetAnchorPoint({ 0.5f, 0.5f });
			cross->SetSize({ 16, 16 });
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// 3D�I�u�W�F�N�g�����ݒ�
	{
		// ���f���ǂݍ���
		{
			modelGround = Model::CreateFromOBJ("ground");
		}

		// 3D�I�u�W�F�N�g����
		{
			objGround = Object3d::Create(modelGround);
		}

		// 3D�I�u�W�F�N�g�����ݒ�
		{
			objGround->Initialize();
			objGround->SetPosition({0,-5, 0});
		}
	}

	// �e�N���X�̏�����
	{
		// ���x�ݒ�
		sensi = camera->GetSensi();

		// �E�F�[�u�̏�����
		wave = new TestWave();
		wave->Initialize(input, camera);
	}

	// �J�[�\��������
	ShowCursor(false);

}

void TestScene::Update()
{
	// Enter�Ŏw��̃V�[����
	if (input->TriggerKey(DIK_RETURN))
	{
		nextScene = new SelectScene();
	}

	// ESCAPE�ŃQ�[���I��
	if (input->TriggerKey(DIK_ESCAPE))
	{
		option = !option;
		ShowCursor(option);
	}

	// �t���X�N���[���p�i�g�p�֎~�j
	if (input->TriggerKey(DIK_F1))
	{
		dxCommon->ChengeFullScreen();
	}
	
	if (!option)
	{
		// �J�[�\���𒆐S�Œ�
		SetCursorPos(centerX, centerY);

		// �J�������x�؂�ւ�
		{
			if (input->TriggerKey(DIK_UP))
			{
				sensi += 0.001f;
				camera->SetSensi(sensi);
			}
			if (input->TriggerKey(DIK_DOWN))
			{
				sensi -= 0.001f;
				camera->SetSensi(sensi);
			}
			if (input->TriggerKey(DIK_RIGHT))
			{
				sensi += 0.01f;
				camera->SetSensi(sensi);
			}
			if (input->TriggerKey(DIK_LEFT))
			{
				sensi -= 0.01f;
				camera->SetSensi(sensi);
			}
			// ���x��\��
			text->Printf("%d", (int)(sensi * 1000));
		}

		// 3D�I�u�W�F�N�g�X�V
		{
			objGround->Update();
		}

		// �e�N���X�X�V
		{
			lightGroup->Update();
			camera->Update();

			// �E�F�[�u�̍X�V
			wave->Update();
		}
	}
}

void TestScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��
	{
		// �w�i�X�v���C�g
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
			
			wave->Draw();
		}
		Object3d::PostDraw();
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);
		{
			cross->Draw();
			wave->DrawUi(cmdList);

			// �f�o�b�O�e�L�X�g�̕`��
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}
}