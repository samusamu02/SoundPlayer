#pragma once
#include "Delay.h"
class Reverb :
    public Delay
{
public:
    Reverb();
    ~Reverb();

    // 初期化処理
    virtual void Init(void);
    virtual void ChannelL_Init(void);
    virtual void ChannelR_Init(void);
    void GenelateReverbWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:
};

