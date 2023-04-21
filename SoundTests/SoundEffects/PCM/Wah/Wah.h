#pragma once
#include <memory>
#include <array>
#include "../PCM.h"
#include "../PCMSet.h"
#include "../../Wave/PCMDef.h"


class Wah :
    public PCM
{
public:
    Wah();
    ~Wah();

    void Init(void);
    void ChannelL_Wah(void);
    void ChannelR_Wah(void);
    void GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:

    struct ChannelL
    {
        double fc;                  // ���S���g��
        double q_;                  // �N�I���e�B�t�@�N�^
        std::array<double, 3> attenuation_;    // IIR�t�B���^�[�p�W��
        std::array<double, 3> delay_;    // IIR�t�B���^�[�p�W��
    };

    struct ChannelR
    {
        double fc;                  // ���S���g��
        double q_;                  // �N�I���e�B�t�@�N�^
        std::array<double, 3> attenuation_;    // IIR�t�B���^�[�p�W��
        std::array<double, 3> delay_;    // IIR�t�B���^�[�p�W��
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
    int delaylineNum_;

    // ���E�̐[��
    double depth_;

    // ���E�̎��g��
    double rate_;
};

