#pragma once
#include "../SoundObj.h"
class DrawObj :
    public SoundObj
{
public:
    DrawObj();
    ~DrawObj();
protected:
    // 現在のサンプルの位置
    LONGLONG samplePos_;
private:
};

