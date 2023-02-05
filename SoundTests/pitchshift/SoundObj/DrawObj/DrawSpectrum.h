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
    // バッファーサイズ
    std::vector<float> paramList;

    // FFTに使うサンプル数
    int fftSampleNum_;

    int screen_w_;
    int screen_h_;
};

