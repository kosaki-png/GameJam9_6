#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "input/Input.h"

class Ui 
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
private: // �ÓI�����o�ϐ�
	static const int texNumber = 0;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Ui();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Ui();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// ���_�ǉ�
	/// </summary>
	/// <param name="num">�ǉ����_</param>
	void AddScore(int num) {
		scoreNum += num;
	};

	/// <summary>
	/// ���Ă����ǉ�
	/// </summary>
	void AddCount() {
		countNum++;
	};

	/// <summary>
	/// �O�������ǉ�
	/// </summary>
	void AddMiss() {
		missNum++;
	}

	/// <summary>
	/// �����v�Z
	/// </summary>
	/// <returns>�����̒l</returns>
	int Rate() {
		rateNum = countNum / (countNum + missNum) * 100;
		return rateNum;
	};

private:
	Sprite* ui;
	Score* score;
	Score* timeLimit;
	Score* rate;
	float time;

	static float countNum;//���Ă���
	static float missNum; //�O������
	static float rateNum; //�����̒l
	static int scoreNum;//�X�R�A�̒l
};

