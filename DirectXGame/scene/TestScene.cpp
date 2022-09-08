#include "TestScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include "FreeCamera.h"
#include "Collision.h"

using namespace DirectX;

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
	delete cross;
	delete model;
	delete modelGround;
	delete object;
	delete objGround;
	for (int i = 0; i < 20; i++)
	{
		delete target[i];
	}
	delete camera;
	delete ui;
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

		// �p�[�e�B�N���}�l�[�W������
		particleMan = ParticleManager::GetInstance();
		particleMan->SetCamera(camera);
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
			model = Model::CreateFromOBJ("sphere");
			modelGround = Model::CreateFromOBJ("ground");
		}

		// 3D�I�u�W�F�N�g����
		{
			object = Object3d::Create(model);
			objGround = Object3d::Create(modelGround);
		}

		// 3D�I�u�W�F�N�g�����ݒ�
		{
			object->Initialize();
			objGround->Initialize();
			objGround->SetPosition({0,-5, 0});
		}
	}

	// �������C�̏����ݒ�
	{
		XMFLOAT3 tmp = camera->GetEye();
		ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		tmp = camera->GetDir();
		ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);

		for (int i = 0; i < 20; i++)
		{
			target[i] = new BaseTarget();
			target[i]->Initialize("sphere");
			target[i]->SetPosition({ (float)(i % 5) - 2.0f, (float)(int)(i / 5) - 1 , 0 });
		}
	}

	// �e�N���X�̏�����
	{
		// ���x�ݒ�
		sensi = camera->GetSensi();

		// UI
		ui = new Ui();
		ui->Initialize();
	}
}

void TestScene::Update()
{
	// Enter�Ŏw��̃V�[����
	if (input->TriggerKey(DIK_RETURN))
	{
		nextScene = new SelectScene();
	}

	// ESCAPE�ŃQ�[���I��
	if (input->PushKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// �t���X�N���[���p�i�g�p�֎~�j
	if (input->TriggerKey(DIK_F1))
	{
		dxCommon->ChengeFullScreen();
	}
	
	// �J�[�\���������Ē��S�Œ�
	ShowCursor(false);
	SetCursorPos(centerX, centerY);

	// �J�������x�؂�ւ�
	{
		if (input->TriggerKey(DIK_UP))
		{
			sensi += 0.005f;
			camera->SetSensi(sensi);
		}
		if (input->TriggerKey(DIK_DOWN))
		{
			sensi -= 0.005f;
			camera->SetSensi(sensi);
		}
		// ���x��\��
		text->Printf("%f", sensi);
	}

	// �^�[�Q�b�g����
	{
		// �������C�̍X�V
		{
			XMFLOAT3 tmp = camera->GetEye();
			ray.start = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
			tmp = camera->GetDir();
			ray.dir = XMVectorSet(tmp.x, tmp.y, tmp.z, 1.0f);
		}

		for (int i = 0; i < 20; i++)
		{
			// �������C�ƓI�Ƃ̓����蔻��
			if (Collision::CheckRay2Sphere(ray, target[i]->GetSphere()))
			{
				if (input->TriggerMouseLeft())
				{
					target[i]->SetIsDead(true);
				}
			}

			// ����
			static int respownCnt[20] = {};
			if (target[i]->GetIsDead())
			{
				respownCnt[i]++;
				if (respownCnt[i] > 200)
				{
					target[i]->SetIsDead(false);
					respownCnt[i] = 0;
				}
			}
		}
	}
	
	// 3D�I�u�W�F�N�g�X�V
	{
		object->Update();
		objGround->Update();
	}

	// �e�N���X�X�V
	{
		lightGroup->Update();
		camera->Update();
		particleMan->Update();
		for (int i = 0; i < 20; i++)
		{
			target[i]->Update();
		}
		ui->Update(input);
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
			for (int i = 0; i < 20; i++)
			{
				target[i]->Draw();
			}
		}
		Object3d::PostDraw();

		// �p�[�e�B�N���̕`��
		particleMan->Draw(cmdList);
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);
		{
			cross->Draw();
			ui->Draw(cmdList);

			// �f�o�b�O�e�L�X�g�̕`��
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}
}