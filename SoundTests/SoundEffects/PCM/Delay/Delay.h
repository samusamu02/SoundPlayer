#pragma once
#include <memory>
#include "../PCM.h"
#include "../PCMSet.h"
#include "../../Wave/PCMDef.h"

class Delay :
    public PCM
{
public:
    Delay();
    virtual ~Delay();

    virtual void Init(void);
    virtual void ChannelL_Init(void);
    virtual void ChannelR_Init(void);
    virtual void ChannelL_Delay(void);
    virtual void ChannelR_Delay(void);
    void GenelateDelayWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

protected:
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

    // 繰り返し回数
    int repeat_;
public:
};

