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
    // ���f���ǉ�
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
    // �S�Ă̗v�f�ɑ΂���
    for (int i = 0; i < models.size(); i++)
    {
        // �l�������Ă���Ȃ�
        if (models[i])
        {
            // �폜
            delete models[i];
        }
    }
    models.clear();
    delete instance;
}

void ModelManager::AddModel(static const int modelNum, const std::string modelName, bool smoothing)
{
    // �w��ԍ������f���z����傫���Ȃ�
    if (models.size() < modelNum + 1)
    {
        // �z��̑傫�����Đݒ�
        models.resize(modelNum + 1);
    }

    // �z��Ƀ��f����ǉ�
    models[modelNum] = Model::CreateFromOBJ(modelName, smoothing);
}
