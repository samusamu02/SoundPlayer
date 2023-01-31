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
    SoundFile soundFile_;
    int loopCount_;
};

