#pragma once
#include <memory>
#include <array>
#include "../PCM.h"
#include "../PCMSet.h"
#include "../../Wave/PCMDef.h"
class Equalizer :
    public PCM
{
public:
    Equalizer();
    ~Equalizer();

    // 初期化処理
    virtual void Init(void);

    // 左チャンネルのIIRフィルター処理処理
    virtual void ChannelL_IIR(const double coefficient_A, const double coefficient_B, const double coefficient_C);

    // 右チャンネルのIIRフィルター処理処理
    virtual void ChannelR_IIR(const double coefficient_A, const double coefficient_B, const double coefficient_C);

    // 左チャンネルのイコライザー処理処理
    virtual void ChannelL_Equalizer(void);

    // 右チャンネルのイコライザー処理処理
    virtual void ChannelR_Equalizer(void);

    /// <summary>
    /// 新しくイコライザーが適用されたwavファイルを生成する
    /// </summary>
    /// <param name="fileName">適用前のファイル</param>
    /// <param name="afterFileName">適用後のファイル</param>
    void GenelateEquaLizerWaveFile(const double coefficient_A,const double coefficient_B,const double coefficient_C,const wchar_t* fileName, const wchar_t* afterFileName);
private:
    struct ChannelL
    {
        double cf_;          // 中央周波数
        double q_Factor_;    // クオリティファクタ   
        double gain_;        // ゲイン
        std::array<double, 3> coefficients_a_;                      // フィルターの分子係数A
        std::array<double, 3> coefficients_b_;                      // フィルターの分子係数B
        std::array<std::array<double, 3>, 3> coefficients_A_;       // フィルターの分母係数A
        std::array<std::array<double, 3>, 3> coefficients_B_;       // フィルターの分母係数B
    };

    struct ChannelR
    {
        double cf_;          // 中央周波数
        double q_Factor_;    // クオリティファクタ   
        double gain_;        // ゲイン
        std::array<double, 3> coefficients_a_;                      // フィルターの分子係数A
        std::array<double, 3> coefficients_b_;                      // フィルターの分子係数B
        std::array<std::array<double, 3>, 3> coefficients_A_;       // フィルターの分母係数A
        std::array<std::array<double, 3>, 3> coefficients_B_;       // フィルターの分母係数B
    };

    // PCMの初期化のオブジェクト
    std::unique_ptr<PCMSet> pcmSet_;

    // ピッチシフト用のオブジェクト
    std::unique_ptr<STEREO_PCM> pcm0_;
    std::unique_ptr<STEREO_PCM> pcm1_;

    // 左チャンネル
    std::unique_ptr<ChannelL> channelL_;
    // 右チャンネル
    std::unique_ptr<ChannelR> channelR_;

    // 遅延期の数
    long delaylineNum_;
};

