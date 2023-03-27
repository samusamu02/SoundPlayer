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
    void Init(void)override;
    uniqueBase Update(uniqueBase ownScene)override;
    void DrawOwnScreen(void)override;
    
    SoundFile soundFile_;

    // �V�[��ID�擾
    SceneID GetSceneID(void)override
    {
        // �T�E���h�Đ��V�[��
        return SceneID::SoundSelect;
    };
};

