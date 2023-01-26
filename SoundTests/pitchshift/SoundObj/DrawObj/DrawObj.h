#pragma once
#include "../SoundObj.h"
class DrawObj :
    public SoundObj
{
public:
    DrawObj();
    ~DrawObj();
protected:
    // Œ»İ‚ÌƒTƒ“ƒvƒ‹‚ÌˆÊ’u
    LONGLONG samplePos_;
private:
};

