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

    void Init(void);
    void ChannelL_Wah(void);
    void ChannelR_Wah(void);
    void GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:

    struct ChannelL
    {
        double fc;                  // 中心周波数
        double q_;                  // クオリティファクタ
        std::array<double, 3> attenuation_;    // IIRフィルター用係数
        std::array<double, 3> delay_;    // IIRフィルター用係数
    };

    struct ChannelR
    {
        double fc;                  // 中心周波数
        double q_;                  // クオリティファクタ
        std::array<double, 3> attenuation_;    // IIRフィルター用係数
        std::array<double, 3> delay_;    // IIRフィルター用係数
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

