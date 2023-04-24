#pragma once
#include <memory>
#include <array>
#include "../PCM.h"
#include "../PCMSet.h"
#include "../../Wave/PCMDef.h"


class Wah :
    public PCM
{
public:
    Wah();
    ~Wah();

    // 初期化処理
    void Init(void);

    // 左チャンネルのワウ処理
    void ChannelL_Wah(void);

    // 右チャンネルのワウ処理
    void ChannelR_Wah(void);

    /// <summary>
    /// 新しくワウが適用されたサウンドファイルを生成する
    /// </summary>
    /// <param name="fileName">適用前のファイル</param>
    /// <param name="afterFileName">適用後のファイル</param>
    void GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:

    struct ChannelL
    {
        double cf_;                                 // 中心周波数
        double q_Factor_;                           // クオリティファクタ
        std::array<double, 3> coefficients_a_;      // IIRフィルター用係数
        std::array<double, 3> coefficients_b_;      // IIRフィルター用係数
    };

    struct ChannelR
    {
        double fc;                                  // 中心周波数
        double q_;                                  // クオリティファクタ
        std::array<double, 3> coefficients_a_;      // IIRフィルター用係数
        std::array<double, 3> coefficients_b_;      // IIRフィルター用係数
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
    int delaylineNum_;

    // ワウの深さ
    double depth_;

    // ワウの周波数
    double rate_;
};

