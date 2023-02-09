#pragma once
#include "PCM.h"
class PCMSet :
    public PCM
{
public:
    PCMSet();
    ~PCMSet();

    /// <summary>
    /// 変換前ののPCMを変換するPCMに代入する関数
    /// </summary>
    /// <param name="after">代入されるPCM</param>
    /// <param name="before">元データ</param>
    void PCMSetNormal(MONO_PCM& after, MONO_PCM& before);

    /// <summary>
    /// 変換前ののPCMを変換するPCMに代入する関数
    /// </summary>
    /// <param name="after">代入されるPCM</param>
    /// <param name="before">元データ</param>
    void PCMSetNormal(STEREO_PCM& after, STEREO_PCM& before);

private:
};

