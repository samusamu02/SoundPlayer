#pragma once
#include "BaseScene.h"
#include "../SoundObj/SoundFile.h"

class SoundSelectScene :
    public BaseScene
{
public:
    SoundSelectScene();
    ~SoundSelectScene();
private:
    // ����������
    void Init(void)override;

    /// <summary>
    /// �X�V����(���̃V�[�����������s���j
    /// </summary>
    /// <param name="ownScene">�V�[���̎擾</param>
    /// <returns></returns>
    uniqueBase Update(uniqueBase ownScene)override;

    // �`�揈��
    void DrawOwnScreen(void)override;

    // �V�[��ID�擾
    SceneID GetSceneID(void)override
    {
        // �T�E���h�Đ��V�[��
        return SceneID::SoundSelect;
    };

    // �T�E���h�t�@�C����
    SoundFile soundFile_;
};

