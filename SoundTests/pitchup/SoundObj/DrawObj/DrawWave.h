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
    // �T�E���h�̃t�@�C���ꏊ
    SoundFile soundFile_;


    int screen_w_;
    int screen_h_;
    int drawStartSampleCount_;
    int totalSampleCount_;


};

