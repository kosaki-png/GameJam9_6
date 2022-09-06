#include "EndScene.h"
#include "TitleScene.h"
#include"SelectScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

EndScene::EndScene(bool clear, float time, bool damage, bool sign)
{
	isClear = clear;
	this->time = time;
	this->damage = damage;
	sign1 = sign;
}

EndScene::~EndScene()
{
	safe_delete(clear);
	safe_delete(over);
}

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	audio->Stop();

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

	// �X�v���C�g�p�e�N�X�`���ǂݍ���
	{
		Sprite::LoadTexture(1, L"Resources/GameClear.png");
		Sprite::LoadTexture(2, L"Resources/GaneOver.png");
		Sprite::LoadTexture(3, L"Resources/king.png");
		Sprite::LoadTexture(4, L"Resources/sign.png");
	}

	// �X�v���C�g����
	{
		clear = Sprite::Create(1, { 0,0 });
		over = Sprite::Create(2, { 0,0 });

		king = Sprite::Create(3, { 0,0 });
		sign = Sprite::Create(4, { 0,0 });
	}

	// �X�v���C�g�����ݒ�
	{
	}

	// ���f���ǂݍ���
	{
	}

	// 3D�I�u�W�F�N�g����
	{
	}

	// 3D�I�u�W�F�N�g�����ʒu�ݒ�
	{
	}

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);

	if (clear)
	{
		audio->PlayWave(L"Resources/clear.wav");
	}
	else
	{
		audio->PlayWave(L"Resources/over.wav");
	}
}

void EndScene::Update()
{
	xinput.Update();

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

	// �}�E�X�|�C���g
	{
		static POINT p;
		GetCursorPos(&p);
		WinApp* win = nullptr;
		win = new WinApp();
		ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	text->Print("time...", 480, 380, 1);
	text->Print(std::to_string(time), 500, 490, 1);

	// �p�[�e�B�N������
	//CreateParticles();

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3D�I�u�W�F�N�g�X�V
	{
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

		/// <summary>
		/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ�
		/// </summary>

		if (isClear == true)
		{
			if (damage)
			{
				clear->Draw();
			}
			else
			{
				king->Draw();
			}
			if (sign1)
			{
				sign->Draw();
			}
		}
		else
		{
			over->Draw();
		}

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

		// �f�o�b�O�e�L�X�g�̕`��
		text->DrawAll(cmdList);

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}