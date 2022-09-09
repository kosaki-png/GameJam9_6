#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Score.h"
#include "input/Input.h"
#include "SafeDelete.h"
#include "Stopwatch.h"

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
	void AddScore(int num = 10) {
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

	/// <summary>
	/// �Z�b�^�[
	/// </summary>
	/// <param name="targetNum">�l��ς������Ώ�</param>
	/// <param name="setNum">�ύX���鐔��</param>
	void SetNum(int& targetNum, int setNum = 0) {
		targetNum = setNum;
	};

	//getter
	const float& GetOnePlace() { return onePlace; }//�^�C���̂P�̈�
	const float& GetTnePlace() { return tenPlace; }//�^�C����10�̈�
	const float& GetHundredPlace() { return hundredPlace; }//�^�C����100�̈�
	const float& GetRate() { return rateNum; }
	const int& GetScore() {return scoreNum; }

	void TimerManage();
private:
	Sprite* ui;
	Score* score;
	Score* timeLimit;
	Score* rate;
	Score* parcent;
	std::unique_ptr<diagnostics::Stopwatch> timer;
	
	float onePlace;  //1�̈�
	int tenPlace;    //10�̈�
	int hundredPlace;//100�̈�
	int initialValue;//�����l
	float countNum;  //���Ă���
	float missNum;   //�O������
	float rateNum;   //�����̒l
	static int scoreNum;    //�X�R�A�̒l
};

