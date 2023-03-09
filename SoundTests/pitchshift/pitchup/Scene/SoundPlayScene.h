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

    // シーンID取得
    SceneID GetSceneID(void)override
    {
        // サウンド再生シーン
        return SceneID::SoundPlay;
    };

    // サウンドオブジェクト
    std::unique_ptr<SoundObjMag> soundObjMag_;
};

