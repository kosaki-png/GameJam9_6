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
	/// ���������ǉ�
	/// </summary>
	void AddTargets() {
		targetsNum++;
	};

	/// <summary>
	/// �����v�Z
	/// </summary>
	/// <returns>�����̒l</returns>
	int Rate() {
		rateNum = GetCount() / (GetCount() + GetMiss()) * 100;
		return rateNum;
	};

	/// <summary>
	/// �L���^�C���v�Z
	/// </summary>
	/// <returns></returns>
	float KillTime()
	{
		timeToKill = GetCount() - 1;
		timeToKill = timeToKill / 60;
		return timeToKill;
	}

	/// <summary>
	/// �Z�b�^�[
	/// </summary>
	/// <param name="targetNum">�l��ς������Ώ�</param>
	/// <param name="setNum">�ύX���鐔��</param>
	void SetNum(int& targetNum, int setNum = 0) {
		targetNum = setNum;
	};

	/// <summary>
	/// �^�C���A�b�v�Ȃ�
	/// </summary>
	/// <returns></returns>
	bool IsTimeUp(){
		return GetHundredPlace() < 0;
	}

	//getter
	const float& GetOnePlace() { return onePlace; }//�^�C���̂P�̈�
	const float& GetTnePlace() { return tenPlace; }//�^�C����10�̈�
	const float& GetHundredPlace() { return hundredPlace; }//�^�C����100�̈�
	const float& GetRate() { return rateNum; }
	const float& GetMiss() { return missNum; }
	const float& GetCount() { 	return countNum;}
	const float& GetKillTime() { return timeToKill; }
	const int& GetScore() {return scoreNum; }
	const int& GetTargetCount() { return targetsNum; }


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
	static float targetsNum;
	static float countNum;  //���Ă���
	static float missNum;   //�O������
	static float rateNum;   //�����̒l
	static int scoreNum;    //�X�R�A�̒l
	static float timeToKill; //�L����
};

