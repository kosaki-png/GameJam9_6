#pragma once
#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "Text.h"
#include "Define.h"

using namespace DirectX;

class Dog
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::���ȗ�
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMVECTOR = DirectX::XMVECTOR;
    using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
    static const int texNumber = 0;
public:// �����o�֐�
    Dog();
    ~Dog();

    /// <summary>
    /// ������
    /// </summary>
    /// <returns>����</returns>
    bool Initialize();

    /// <summary>
    /// ���t���[������
    /// </summary>
    void Update();

    /// <summary>
    /// �ǐ�
    /// </summary>
    void Traking();

    /// <summary>
    /// ��������
    /// </summary>
    /// <returns></returns>
    XMFLOAT2 Rand();

    /// <summary>
    /// ���x�ύX
    /// </summary>
    /// <param name="Speed">���x</param>
    void SetSpeed(float speed) {this->speed = speed;}

    /// <summary>
    /// ���Z�b�g
    /// </summary>
    void ReStart();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw(bool sleep);

    //setter getter
    XMFLOAT2 GetPosition() { return position; }
    void SetPosition(XMFLOAT2 position) { this->position = position; }

    XMFLOAT2 GetSize() { return size; }
    void SetSize(XMFLOAT2 size) { this->size = size; }
private:
    //���|�C���^
    Sprite* dog = nullptr;
    //�|�W�V����
    XMFLOAT2 position{-300,0};
    //�T�C�Y
    XMFLOAT2 size{100,100 };
    //���x
    float speed = 0;
    //���S�t���O
    bool dead_flag = false;
    //�ǐՃt���O
    bool track_flag = true;
    //�`��t���O
    bool Drawflag[D_DOG]; 
    //�ǐՃ|�C���g
    XMFLOAT2 trackPoint = { 0,0 };
};

