#pragma once
#include "../SoundObj.h"
class DrawObj :
    public SoundObj
{
public:
    DrawObj();
    ~DrawObj();
protected:
    // ���݂̃T���v���̈ʒu
    LONGLONG samplePos_;
private:
};

