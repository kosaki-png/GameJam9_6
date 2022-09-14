#include "ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager* ModelManager::GetInstance()
{
    if (!instance)
    {
        instance = new ModelManager();
    }
    return instance;
}

void ModelManager::LoadModel()
{
    // モデル追加
    AddModel(FIELD, "field");
    AddModel(SPHERE, "sphere", true);
    AddModel(SKYDOME, "skydome", true);
    AddModel(SPHERE_RED, "sphere_red", true);
}

Model* ModelManager::GetModel(const int modelNum)
{
    return models[modelNum];
}

void ModelManager::Destroy()
{
    // 全ての要素に対して
    for (int i = 0; i < models.size(); i++)
    {
        // 値が入っているなら
        if (models[i])
        {
            // 削除
            delete models[i];
        }
    }
    models.clear();
    delete instance;
}

void ModelManager::AddModel(static const int modelNum, const std::string modelName, bool smoothing)
{
    // 指定番号がモデル配列より大きいなら
    if (models.size() < modelNum + 1)
    {
        // 配列の大きさを再設定
        models.resize(modelNum + 1);
    }

    // 配列にモデルを追加
    models[modelNum] = Model::CreateFromOBJ(modelName, smoothing);
}
