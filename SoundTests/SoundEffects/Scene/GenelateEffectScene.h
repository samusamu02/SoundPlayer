#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "../SoundObj/SoundFile.h"
#include "../PCM/PitchShift/PitchUp.h"
#include "../PCM/PitchShift/PitchDown.h"
#include "../PCM/Wah/Wah.h"
#include "../PCM/Delay/Reverb.h"
#include "../PCM/Equalizer/Equalizer.h"

// 関数オブジェクトの宣言
using EffectFunc = std::function<void()>;

// エフェクトの種類
enum class Effect
{
    PitchUp,		    // ピッチアップ
    PitchDown,		    // ピッチダウン
    Wah,                // ワウ
    Reverb,			    // リバーブ
    Equalizer_Base,		// イコライザー(低音)
    Equalizer_Middle,   // イコライザー(中音)
    Equalizer_Treble,   // イコライザー(高音)
    Max				    // 項目数
};

class GenelateEffectScene :
    public BaseScene
{
public:
    GenelateEffectScene();
    ~GenelateEffectScene();
private:
    // 初期化処理
    void Init(void)override;

    // 座標の初期化
    void Init_Pos(void);

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
        return SceneID::GenelateEffect;
    };

    // ピッチシフトのオブジェクト
    std::unique_ptr<PitchUp> pitchUp_;
    std::unique_ptr<PitchDown> pitchDown_;

    // ワウのオブジェクト
    std::unique_ptr<Wah> wah_;

    // リバーブのオブジェクト
    std::unique_ptr<Reverb> reverb_;

    // イコライザのオブジェクト
    std::unique_ptr<Equalizer> equalizer_;

    // サウンドファイル
    SoundFile soundFile_;

    // 現在の選択の状態
    int nowSelect_;

    // それぞれのテキストの位置
    // X座標
    int selecterPosX_;
    int stringPosX_;

    // Y座標
    std::vector<int> y_Coordinates_;
    int pitchUpPosY_;
    int pitchDownPosY_;
    int wahPosY_;
    int reverbPosY_;
    int equalizerPosY_Bass_;
    int equalizerPosY_Middle_;
    int equalizerPosY_Treble_;
};

