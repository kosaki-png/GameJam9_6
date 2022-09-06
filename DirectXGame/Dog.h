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
private: // エイリアス
// Microsoft::WRL::を省略
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::を省略
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMVECTOR = DirectX::XMVECTOR;
    using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
    static const int texNumber = 0;
public:// メンバ関数
    Dog();
    ~Dog();

    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns>成否</returns>
    bool Initialize();

    /// <summary>
    /// 毎フレーム処理
    /// </summary>
    void Update();

    /// <summary>
    /// 追跡
    /// </summary>
    void Traking();

    /// <summary>
    /// 乱数生成
    /// </summary>
    /// <returns></returns>
    XMFLOAT2 Rand();

    /// <summary>
    /// 速度変更
    /// </summary>
    /// <param name="Speed">速度</param>
    void SetSpeed(float speed) {this->speed = speed;}

    /// <summary>
    /// リセット
    /// </summary>
    void ReStart();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(bool sleep);

    //setter getter
    XMFLOAT2 GetPosition() { return position; }
    void SetPosition(XMFLOAT2 position) { this->position = position; }

    XMFLOAT2 GetSize() { return size; }
    void SetSize(XMFLOAT2 size) { this->size = size; }
private:
    //犬ポインタ
    Sprite* dog = nullptr;
    //ポジション
    XMFLOAT2 position{-300,0};
    //サイズ
    XMFLOAT2 size{100,100 };
    //速度
    float speed = 0;
    //死亡フラグ
    bool dead_flag = false;
    //追跡フラグ
    bool track_flag = true;
    //描画フラグ
    bool Drawflag[D_DOG]; 
    //追跡ポイント
    XMFLOAT2 trackPoint = { 0,0 };
};

