#pragma once
#include "Delay.h"
class Reverb :
    public Delay
{
public:
    Reverb();
    ~Reverb();

    virtual void Init(void);
    virtual void ChannelL_Init(void);
    virtual void ChannelR_Init(void);
    void GenelateReverbWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:
    struct ChannelL
    {
        double a;
        double d;
    };

    struct ChannelR
    {
        double a;
        double d;
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
};

