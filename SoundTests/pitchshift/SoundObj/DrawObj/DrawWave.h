#pragma once
#include "DrawObj.h"

class DrawWave :
    public DrawObj
{
public:
    DrawWave();
    ~DrawWave();
    void Init();
    void DrawSoundWave();
private:

    // 再生位置
    LONGLONG totalSampleCount_;     // サンプルの総数
    LONGLONG drawStartSampleCount_; // 現在のサンプル位置
};
    


