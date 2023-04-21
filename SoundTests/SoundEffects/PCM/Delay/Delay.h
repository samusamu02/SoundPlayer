#pragma once
#include <memory>
#include "../PCM.h"
#include "../PCMSet.h"
#include "../../Wave/PCMDef.h"

class Delay :
    public PCM
{
public:
    Delay();
    virtual ~Delay();

    // ������
    virtual void Init(void);

    // ���`�����l���̏�����
    virtual void ChannelL_Init(void);

    // �E�`�����l���̏�����
    virtual void ChannelR_Init(void);
    virtual void ChannelL_Delay(void);
    virtual void ChannelR_Delay(void);

    /// <summary>
    /// �V�����f�B���C���K�p���ꂽwav�t�@�C���𐶐�����
    /// </summary>
    /// <param name="fileName">�K�p�O�t�@�C��</param>
    /// <param name="afterFileName">�K�p��t�@�C��</param>
    void GenelateDelayWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

protected:
    struct ChannelL
    {
        // ������
        double attenuation_;

        // �x������
        double delay_;
    };

    struct ChannelR
    {
        // ������
        double attenuation_;

        // �x������
        double delay_;
    };

    // PCM�̏������̃I�u�W�F�N�g
    std::unique_ptr<PCMSet> pcmSet_;

    // PCM
    std::unique_ptr<STEREO_PCM> pcm0_;
    std::unique_ptr<STEREO_PCM> pcm1_;

    // ���`�����l��
    std::unique_ptr<ChannelL> channelL_;

    // �E�`�����l��
    std::unique_ptr<ChannelR> channelR_;

    // �J��Ԃ���
    int repeat_;
private:
};

