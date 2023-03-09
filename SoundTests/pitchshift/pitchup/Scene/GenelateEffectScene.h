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

    // シーンID取得
    SceneID GetSceneID(void)override
    {
        // サウンド再生シーン
        return SceneID::GenelateEffect;
    };
    std::future<bool> fu_;
};

