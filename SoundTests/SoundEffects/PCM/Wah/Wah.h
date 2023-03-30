#pragma once
#include "../PCM.h"
class Wah :
    public PCM
{
public:
    Wah();
    ~Wah();

    void Init(void);
    void GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:
};

