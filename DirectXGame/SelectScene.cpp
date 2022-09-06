#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"

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
			Sprite::LoadTexture(1, L"Resources/Tutorial1.png");
			Sprite::LoadTexture(2, L"Resources/Tutorial2.png");
		}

		// �X�v���C�g����
		{
			Tutorial1 = Sprite::Create(1, { 0,0 });
			Tutorial2 = Sprite::Create(2, { 0,0 });
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
	// �R���g���[���̍X�V
	xinput.Update();

	// �V�[���ڍs
	// Enter�Ŏw��̃V�[����
	if (input->TriggerKey(DIK_RETURN) && page == true)
	{
		change = true;
		page = false;
	}
	else if (input->TriggerKey(DIK_RETURN) && page == false)
	{
		//�Q�[���V�[����
		nextScene = new GameScene();
	}
	else if (input->TriggerKey(DIK_LEFTARROW) && page == false)
	{
		change = false;
		page = true;
	}

	// ESCAPE�ŃQ�[���I��
	if (input->PushKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// �}�E�X�|�C���g
	{
		static POINT p;
		GetCursorPos(&p);
		WinApp* win = nullptr;
		win = new WinApp();
		ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3D�I�u�W�F�N�g�X�V
	{}
	// �e�N���X�̍X�V
	{}
}

void SelectScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��
	{
		// �w�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);

		/// <summary>
		/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ�
		/// </summary>

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
		// �[�x�o�b�t�@�N���A
		dxCommon->ClearDepthBuffer();
	}

	// 3D�`��
	{
		// 3D�I�u�W�F�N�g�̕`��
		Object3d::PreDraw(cmdList);

		/// <summary>
		/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ�
		/// </summary>

		Object3d::PostDraw();
		// �p�[�e�B�N���̕`��
		particleMan->Draw(cmdList);
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);

		/// <summary>
		/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ�
		/// </summary>

		if (page == true)
		{
		Tutorial1->Draw();
		}
		else
		{
		Tutorial2->Draw();
		}

		// �f�o�b�O�e�L�X�g�̕`��
		text->DrawAll(cmdList);

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}