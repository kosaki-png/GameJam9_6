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
		}

		// �X�v���C�g����
		{
			//title1 = Sprite::Create(1, { 0, 0 });
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
		}

		// 3D�I�u�W�F�N�g����
		{
			object = Object3d::Create(model);

		}

		// 3D�I�u�W�F�N�g�����ݒ�
		{
			object->Initialize();
		}
	}

	XMFLOAT3 cameraEye = camera->GetEye();
	XMFLOAT3 cameraTarget = camera->GetTarget();
	float cameraDis = camera->GetDistance();
	ray.start = XMVectorSet(cameraEye.x, cameraEye.y, cameraEye.z, 1.0f);
	ray.dir = XMVectorSet((cameraTarget.x - cameraEye.x) / cameraDis, (cameraTarget.y - cameraEye.y) / cameraDis, (cameraTarget.z - cameraEye.z) / cameraDis, 1.0f);

	sphere.center = XMVectorSet(0, 0, 0, 1);
	sphere.radius = 0.5f;

	text = text->GetInstance();

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

	// �}�E�X�|�C���g
	{
		static POINT p;
		GetCursorPos(&p);
		WinApp* win = nullptr;
		win = new WinApp();
		ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	// �p�[�e�B�N������
	//CreateParticles();

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3D�I�u�W�F�N�g�X�V
	{
		object->Update();
	}

	if (input->TriggerKey(DIK_F1))
	{
		dxCommon->ChengeFullScreen();
	}

	//text->Printf("%f", Collision::CheckRay2Sphere(ray, sphere));

	XMFLOAT3 cameraEye = camera->GetEye();
	XMFLOAT3 cameraTarget = camera->GetTarget();
	float cameraDis = camera->GetDistance();
	ray.start = XMVectorSet(cameraEye.x, cameraEye.y, cameraEye.z, 1.0f);
	ray.dir = XMVectorSet((cameraTarget.x - cameraEye.x) / cameraDis, (cameraTarget.y - cameraEye.y) / cameraDis, (cameraTarget.z - cameraEye.z) / cameraDis, 1.0f);

	if (Collision::CheckRay2Sphere(ray, sphere))
	{
		text->Printf("%f", Collision::CheckRay2Sphere(ray, sphere));
	}
	else
	{
		//text->Printf("%f", Collision::CheckRay2Sphere(ray, sphere));
	}


	//text->Printf("%f", (float)input->GetMouseMove().lX);
}

void TestScene::Draw()
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

		object->Draw();

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