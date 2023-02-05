#pragma once
#include <DxLib.h>
#include "../SoundObj.h"

class DrawObj :
    public SoundObj
{
public:
    DrawObj();
    ~DrawObj();

    virtual void Init(void);
    virtual void Draw(void) = 0;
protected:
    // ƒTƒ“ƒvƒ‹”
    int sampleNum_;
private:
};

