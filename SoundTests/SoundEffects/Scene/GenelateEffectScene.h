#pragma once
#include <thread>
#include "BaseScene.h"
#include "../SoundObj/SoundFile.h"
#include "../PCM/PitchShift/PitchUp.h"
#include "../PCM/PitchShift/PitchDown.h"
#include "../PCM/Wah/Wah.h"
#include "../PCM/Delay/Delay.h"
#include "../PCM/Delay/Reverb.h"
#include "../PCM/Equalizer/Equalizer.h"

// それぞれのテキストの位置
constexpr int PITCHUP_Y = 240;
constexpr int PITCHDOWN_Y = 270;
constexpr int REVERB_Y = 300;
constexpr int EQUALIZER_Y = 330;

// エフェクトの種類
enum class Effect
{
    PitchUp,		// ピッチアップ
    PitchDown,		// ピッチダウン
    Reverb,			// リバーブ
    Equalizer,		// イコライザー
    Max				// 項目数
};

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

    // ピッチシフトのオブジェクト
    std::unique_ptr<PitchUp> pitchUp_;
    std::unique_ptr<PitchDown> pitchDown_;

    // ワウのオブジェクト
    std::unique_ptr<Wah> wah_;

    // ディレイ
    std::unique_ptr<Delay> delay_;

    // リバーブ
    std::unique_ptr<Reverb> reverb_;
    
    // イコライザ
    std::unique_ptr<Equalizer> equalizer_;

    // サウンドファイル
    SoundFile soundFile_;

    // シーンID取得
    SceneID GetSceneID(void)override
    {
        // サウンド再生シーン
        return SceneID::GenelateEffect;
    };

    // 現在の選択の状態
    int nowSelect;
};

