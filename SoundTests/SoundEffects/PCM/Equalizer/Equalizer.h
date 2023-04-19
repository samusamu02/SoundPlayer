#pragma once
#include <memory>
#include <array>
#include "../PCM.h"
#include "../PCMSet.h"
#include "../../Wave/PCMDef.h"
class Equalizer :
    public PCM
{
public:
    Equalizer();
    ~Equalizer();

    virtual void Init(void);
    virtual void ChannelL_Init(void);
    virtual void ChannelR_Init(void);
    virtual void ChannelL_Equalizer(void);
    virtual void ChannelR_Equalizer(void);
    void GenelateEquaLizerWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:
    struct ChannelL
    {
        double fc;
        double Q;
        double g;
        std::array<double, 3> attenuation;
        std::array<double, 3> b;
        std::array<std::array<double, 3>, 3> A;
        std::array<std::array<double, 3>, 3> B;
    };

    struct ChannelR
    {
        double fc;
        double Q;
        double g;
        std::array<double, 3> attenuation;
        std::array<double, 3> b;
        std::array<std::array<double, 3>, 3> A;
        std::array<std::array<double, 3>, 3> B;
    };

    // PCM�̏������̃I�u�W�F�N�g
    std::unique_ptr<PCMSet> pcmSet_;

    // �s�b�`�V�t�g�p�̃I�u�W�F�N�g
    std::unique_ptr<STEREO_PCM> pcm0_;
    std::unique_ptr<STEREO_PCM> pcm1_;

    // ���`�����l��
    std::unique_ptr<ChannelL> channelL_;
    // �E�`�����l��
    std::unique_ptr<ChannelR> channelR_;

    // �x�����̐�
    long delaylineNum_;
};

