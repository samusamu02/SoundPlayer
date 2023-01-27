#pragma once
#include "../SoundObj.h"

// スクリーンの大きさ
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

class DrawObj :
    public SoundObj
{
public:
    DrawObj();
    ~DrawObj();
protected:

    // サンプル数
    const int sampleNum_ = 32768;

    // 現在のサンプルの位置
    LONGLONG samplePos_;
private:
};

