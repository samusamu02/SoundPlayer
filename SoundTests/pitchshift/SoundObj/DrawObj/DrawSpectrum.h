#pragma once
#include "DrawObj.h"
#include <vector>
class DrawSpectrum :
    public DrawObj
{
public:
    DrawSpectrum();
    ~DrawSpectrum();

    void Init(void);
    void Draw(void);
private:
    // �o�b�t�@�[�T�C�Y
    std::vector<float> paramList;

    // FFT�Ɏg���T���v����
    int fftSampleNum_;

    int screen_w_;
    int screen_h_;
};

