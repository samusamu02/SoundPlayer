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
    // 初期化処理
    void Init(void)override;

    /// <summary>
    /// 更新処理(次のシーン処理等を行う）
    /// </summary>
    /// <param name="ownScene">シーンの取得</param>
    /// <returns></returns>
    uniqueBase Update(uniqueBase ownScene)override;

    // 描画処理
    void DrawOwnScreen(void)override;

    // シーンID取得
    SceneID GetSceneID(void)override
    {
        // サウンド再生シーン
        return SceneID::SoundPlay;
    };

    // サウンドオブジェクト
    std::unique_ptr<SoundObjMag> soundObjMag_;

    bool viewFlag_;
};

