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
        return SceneID::SoundSelect;
    };

    // サウンドファイル名
    SoundFile soundFile_;
};

