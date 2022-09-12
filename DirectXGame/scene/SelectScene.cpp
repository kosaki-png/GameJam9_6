#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

#include "OrbitCamera.h"

#include <cassert>
#include <sstream>
#include <iomanip>

#include "Collision.h"

using namespace DirectX;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
	delete objField;
	delete objSky;
	delete menu;
	delete score;
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height, {75, 50}, 0.002f);
		camera->SetInput(input);

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
			menu = Sprite::Create(MENU, { 0,0 });
			score = Sprite::Create(SCORE, { 0,0 });
		}

		// �X�v���C�g�̏����ݒ�
		{
		}
	}

	// 3D�I�u�W�F�N�g�����ݒ�
	{
		// �I�u�W�F�N�g����
		{
			objField = Object3d::Create(modelMng->GetModel(FIELD));
			objSky = Object3d::Create(modelMng->GetModel(SKYDOME));
		}
		// �I�u�W�F�N�g�����ݒ�
		{
			objField->SetPosition({ 0, -5, 0 });
			objSky->SetScale({ 2,2,2 });
		}
	}

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(10.0f);

	// �{�^���̏�����
	{
		// ���[�h�w��p
		for (int i = 0; i < modeButton.size(); i++)
		{
			if (i % 3 == 0)
			{
				modeButton[i].position = {(float)100, (float)(225 * (i / 3) + 200)};
			}
			if (i % 3 == 1)
			{
				modeButton[i].position = { (float)(1920 / 2 - 275), (float)(225 * (i / 3) + 200) };
			}
			if (i % 3 == 2)
			{
				modeButton[i].position = { (float)(1920 - 650), (float)(225 * (i / 3) + 200) };
			}

			// �T�C�Y�ݒ�
			modeButton[i].size = { 550.0f, 150.0f };
		}

		// �J�n�p
		startButton.position = { 1250.0f, 400.0f };
		startButton.size = { 400.0f, 400.0f };
	}

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

	// ���[�h��I�сA�N���b�N�����Ƃ�
	if (select && input->TriggerMouseLeft())
	{
		// ���݂̃}�E�X���W���擾
		DirectX::XMFLOAT2 mousePos = input->GetClientMousePos();

		// �}�E�X���W�ƃ{�^���Ƃ̓����蔻��
		if (Collision::CheckPoint2Box(mousePos, startButton.position, startButton.size))
		{
			// �E�F�[�u���[�h�Z�b�g
			WaveManager::GetInstance()->SetWaveMode(selectMode);
			//�Q�[���V�[����
			nextScene = new GameScene();
		}
	}

	// ���[�h�I��
	if (!select)
	{
		if (input->TriggerMouseLeft())
		{
			// ���݂̃}�E�X���W���擾
			DirectX::XMFLOAT2 mousePos = input->GetClientMousePos();

			// �}�E�X���W�ƃ{�^���Ƃ̓����蔻��
			for (int i = 0; i < modeButton.size(); i++)
			{
				if (Collision::CheckPoint2Box(mousePos, modeButton[i].position, modeButton[i].size))
				{
					// ���[�h�Z�b�g
					SetSelectMode(i);

					// �I��
					select = true;
				}
			}
		}
	}
	if (input->TriggerMouseRight())
	{
		select = false;
	}

	// 3D�I�u�W�F�N�g�X�V
	{
		objField->Update();
		objSky->Update();
	}
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
			//tmpSprite->Draw();
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
			objField->Draw();
			objSky->Draw();
		}
		Object3d::PostDraw();
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);
		{
			if (!select)
			{
				menu->Draw();
			}
			else
			{
				score->Draw();
			}

			// �f�o�b�O�e�L�X�g�̕`��
			text->DrawAll(cmdList);
		}
		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}

void SelectScene::SetSelectMode(int mode)
{
	switch (mode)
	{
	case 0:
		selectMode = WaveMode::test;
		break;
	case 1:
		selectMode = WaveMode::easy;
		break;
	case 2:
		selectMode = WaveMode::flick_easy;
		break;
	case 3:
		selectMode = WaveMode::filck_normal;
		break;
	case 4:
		selectMode = WaveMode::flick_hard;
		break;
	case 5:
		selectMode = WaveMode::flick_hell;
		break;
	case 6:
		selectMode = WaveMode::follow;
		break;
	case 7:
		selectMode = WaveMode::test;
		break;
	case 8:
		selectMode = WaveMode::test;
		break;
	case 9:
		selectMode = WaveMode::test;
		break;
	}
}
