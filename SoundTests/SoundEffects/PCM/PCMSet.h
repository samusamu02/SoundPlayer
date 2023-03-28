#pragma once
#include "PCM.h"
#include "../Wave/PCMDef.h"
class PCMSet :
    public PCM
{
public:
    PCMSet();
    ~PCMSet();

    /// <summary>
    /// ピッチシフト用のエフェクト適用前のサウンドファイルのデータをコピーする関数
    /// </summary>
    /// <param name="after">コピーする変数</param>
    /// <param name="before">元データ</param>
    void PCMSetPitchShift(MONO_PCM& after, MONO_PCM& before,double rate);

    /// <summary>
    /// ピッチシフト用のエフェクト適用前のサウンドファイルのデータをコピーする関数
    /// </summary>
    /// <param name="after">代入されるPCM</param>
    /// <param name="before">元データ</param>
    void PCMSetPitchShift(STEREO_PCM& after, STEREO_PCM& before,double rate);

    /// <summary>
    /// エフェクト適用前のサウンドファイルのデータをコピーする関数
    /// </summary>
    /// <param name="after">代入されるPCM</param>
    /// <param name="before">元データ</param>
    void PCMSetNormal(MONO_PCM& after, MONO_PCM& before);

    /// <summary>
    /// エフェクト適用前のサウンドファイルのデータをコピーする関数
    /// </summary>
    /// <param name="after">コピーする変数</param>
    /// <param name="before">元データ</param>
    void PCMSetNormal(STEREO_PCM& after, STEREO_PCM& before);

private:
};

