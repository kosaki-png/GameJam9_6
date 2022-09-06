#pragma once

#include <DirectXMath.h>
#include <vector>
#include "SafeDelete.h"
#include "Sprite.h"
#include "Collision.h"
#include <stdlib.h> // rand, srand�֐�
#include <time.h>   // time�֐�
#include <random>
#define enemy 3

class Thieves
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	Thieves();
	~Thieves();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(float speed);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(bool sleep);

	/// <summary>
	/// �`��
	/// </summary>
	void Spawn();

   /// <summary>
   /// �d�Ȃ�`�F�b�N
   /// </summary>
    bool Check(int number);

	std::vector<XMFLOAT2> GetPosition();
	void SetPosition(XMFLOAT2 positions);

private:
	Sprite* thieves[enemy]; //�����X�v���C�g
	XMFLOAT2 e_Pos[enemy];
	//�e�����̍��W�̗�������
	float posX[enemy];
	float posY[enemy];
	float width = 100; //�摜�̉���
	float height = 100; //�摜�̏c��
	float speed = 0.0f;
	bool Drawflag[enemy]; //�`��t���O
};

