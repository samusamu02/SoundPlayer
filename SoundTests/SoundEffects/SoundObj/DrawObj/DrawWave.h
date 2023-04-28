#pragma once
#include "DrawObj.h"
#include "../SoundFile.h"
#include <memory>

class DrawWave :
    public DrawObj
{
public:
    DrawWave();
    ~DrawWave();

    void Init(void);
    void Update(void);
    void Draw(void);
private:
    // サウンドのファイル場所
    SoundFile soundFile_;

    // スクリーンサイズ
    int screen_w_;
    int screen_h_;

    // サンプル数
    LONGLONG drawStartSampleCount_;
    LONGLONG totalSampleCount_;
};

