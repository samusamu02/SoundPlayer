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
    // �T���v����
    const int fftsampleNam_ = 4096;

    // �o�b�t�@�[�T�C�Y
    const int buffuerlength_ = 800;

    // �t�[���G�ϊ����s�������ʂ���
    std::vector<float> paramList_;
};

