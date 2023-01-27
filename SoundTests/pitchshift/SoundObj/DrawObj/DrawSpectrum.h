#pragma once
#include "DrawObj.h"
class DrawSpectrum :
    public DrawObj
{
public:
    DrawSpectrum();
    ~DrawSpectrum();

    void Init(void);
    void Draw(void);
private:
    // サンプル数
    const int fftsampleNam_ = 4096;

    // バッファーサイズ
    const int buffuerlength_ = 800;

    // フーリエ変換を行った結果を代入
    std::vector<float> paramList_;
};

