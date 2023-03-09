#pragma once
#include "BaseScene.h"
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

    // シーンID取得
    SceneID GetSceneID(void)override
    {
        // サウンド再生シーン
        return SceneID::SoundSelect;
    };
};

