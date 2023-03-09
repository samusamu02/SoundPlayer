#pragma once
#include <future>
#include <thread>
#include "BaseScene.h"
#include "../PCM/PitchShift/PitchUp.h"

class GenelateEffectScene :
    public BaseScene
{
public:
    GenelateEffectScene();
    ~GenelateEffectScene();
private:
    void Init(void)override;
    uniqueBase Update(uniqueBase ownScene)override;
    void DrawOwnScreen(void)override;

    std::unique_ptr<PitchUp> pitchUp_;

    // �V�[��ID�擾
    SceneID GetSceneID(void)override
    {
        // �T�E���h�Đ��V�[��
        return SceneID::GenelateEffect;
    };
    std::future<bool> fu_;
};

