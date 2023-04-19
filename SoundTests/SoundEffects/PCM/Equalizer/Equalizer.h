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

    virtual void Init(void);
    virtual void ChannelL_Init(void);
    virtual void ChannelR_Init(void);
    virtual void ChannelL_Equalizer(void);
    virtual void ChannelR_Equalizer(void);
    void GenelateEquaLizerWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:
    struct ChannelL
    {
        double fc;
        double Q;
        double g;
        std::array<double, 3> attenuation;
        std::array<double, 3> b;
        std::array<std::array<double, 3>, 3> A;
        std::array<std::array<double, 3>, 3> B;
    };

    struct ChannelR
    {
        double fc;
        double Q;
        double g;
        std::array<double, 3> attenuation;
        std::array<double, 3> b;
        std::array<std::array<double, 3>, 3> A;
        std::array<std::array<double, 3>, 3> B;
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

