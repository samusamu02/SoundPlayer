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

    // ����������
    virtual void Init(void);

    // ���`�����l����IIR�t�B���^�[��������
    virtual void ChannelL_IIR(const double coefficient_A, const double coefficient_B, const double coefficient_C);

    // �E�`�����l����IIR�t�B���^�[��������
    virtual void ChannelR_IIR(const double coefficient_A, const double coefficient_B, const double coefficient_C);

    // ���`�����l���̃C�R���C�U�[��������
    virtual void ChannelL_Equalizer(void);

    // �E�`�����l���̃C�R���C�U�[��������
    virtual void ChannelR_Equalizer(void);

    /// <summary>
    /// �V�����C�R���C�U�[���K�p���ꂽwav�t�@�C���𐶐�����
    /// </summary>
    /// <param name="fileName">�K�p�O�̃t�@�C��</param>
    /// <param name="afterFileName">�K�p��̃t�@�C��</param>
    void GenelateEquaLizerWaveFile(const double coefficient_A,const double coefficient_B,const double coefficient_C,const wchar_t* fileName, const wchar_t* afterFileName);
private:
    struct ChannelL
    {
        double cf_;          // �������g��
        double q_Factor_;    // �N�I���e�B�t�@�N�^   
        double gain_;        // �Q�C��
        std::array<double, 3> coefficients_a_;                      // �t�B���^�[�̕��q�W��A
        std::array<double, 3> coefficients_b_;                      // �t�B���^�[�̕��q�W��B
        std::array<std::array<double, 3>, 3> coefficients_A_;       // �t�B���^�[�̕���W��A
        std::array<std::array<double, 3>, 3> coefficients_B_;       // �t�B���^�[�̕���W��B
    };

    struct ChannelR
    {
        double cf_;          // �������g��
        double q_Factor_;    // �N�I���e�B�t�@�N�^   
        double gain_;        // �Q�C��
        std::array<double, 3> coefficients_a_;                      // �t�B���^�[�̕��q�W��A
        std::array<double, 3> coefficients_b_;                      // �t�B���^�[�̕��q�W��B
        std::array<std::array<double, 3>, 3> coefficients_A_;       // �t�B���^�[�̕���W��A
        std::array<std::array<double, 3>, 3> coefficients_B_;       // �t�B���^�[�̕���W��B
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

