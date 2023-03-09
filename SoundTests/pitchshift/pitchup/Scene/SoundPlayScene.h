#pragma once
#include <memory>
#include "BaseScene.h"
#include "../SoundObj/SoundObjMag.h"

class SoundPlayScene :
    public BaseScene
{
public:
    SoundPlayScene();
    ~SoundPlayScene();
private:
    void Init(void)override;
    uniqueBase Update(uniqueBase ownScene)override;
    void DrawOwnScreen(void)override;

    // �V�[��ID�擾
    SceneID GetSceneID(void)override
    {
        // �T�E���h�Đ��V�[��
        return SceneID::SoundPlay;
    };

    // �T�E���h�I�u�W�F�N�g
    std::unique_ptr<SoundObjMag> soundObjMag_;
};

