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

    // 初期化
    virtual void Init(void);

    // 左チャンネルの初期化
    virtual void ChannelL_Init(void);

    // 右チャンネルの初期化
    virtual void ChannelR_Init(void);
    virtual void ChannelL_Delay(void);
    virtual void ChannelR_Delay(void);

    /// <summary>
    /// 新しくディレイが適用されたwavファイルを生成する
    /// </summary>
    /// <param name="fileName">適用前ファイル</param>
    /// <param name="afterFileName">適用後ファイル</param>
    void GenelateDelayWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

protected:
    struct ChannelL
    {
        // 減衰率
        double attenuation_;

        // 遅延時間
        double delay_;
    };

    struct ChannelR
    {
        // 減衰率
        double attenuation_;

        // 遅延時間
        double delay_;
    };

    // PCMの初期化のオブジェクト
    std::unique_ptr<PCMSet> pcmSet_;

    // PCM
    std::unique_ptr<STEREO_PCM> pcm0_;
    std::unique_ptr<STEREO_PCM> pcm1_;

    // 左チャンネル
    std::unique_ptr<ChannelL> channelL_;

    // 右チャンネル
    std::unique_ptr<ChannelR> channelR_;

    // 繰り返し回数
    int repeat_;
private:
};

