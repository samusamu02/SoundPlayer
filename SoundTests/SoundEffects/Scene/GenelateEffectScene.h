#pragma once
#include <functional>
#include <vector>
#include <string>
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

    // 項目選択の初期化
    void Init_Select(void);
    
    // エフェクト名の初期化
    void Init_EffectNames(void);

    // 座標の初期化
    void Init_StringPos(void);

    // 画像の初期化
    void Init_Image(void);

    /// <summary>
    /// 更新処理(次のシーン処理等を行う）
    /// </summary>
    /// <param name="ownScene">シーンの取得</param>
    /// <returns></returns>
    uniqueBase Update(uniqueBase ownScene)override;

    // 描画処理
    void DrawOwnScreen(void)override;

    // セレクターの状態変化
    void ChangeSelect(void);

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

    // キーコードとエフェクトの対応を配列で管理
    std::vector < std::pair<int, Effect>> keyEffects_;

    // それぞれのエフェクト名の保存
    std::vector<std::wstring> effectNames_;

    // サウンドファイル
    SoundFile soundFile_;

    // 現在の選択の状態
    int nowSelect_;

    // それぞれのテキストの位置
    // X座標
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

    // セレクターの位置
    int selecterPosX_;
    int selecterPosY_;

    // 画像描画
    int loadingImg_;

    // 画像の座標
    int imagPosX_;
    int imagPosY_;

    // 画像の拡大率
    double rate_;

    // 画像の回転
    double angele_;

    // 回転スピード
    double angleSpeed_;

    // 時間
    double time_;
};

