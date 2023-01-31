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
    virtual void Update(void);
    virtual void Draw(void) = 0;
protected:
    // �T���v����
    int sampleNum_;
private:
};

