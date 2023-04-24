#pragma once
#include <functional>
#include "BaseScene.h"
#include "../SoundObj/SoundFile.h"
#include "../PCM/PitchShift/PitchUp.h"
#include "../PCM/PitchShift/PitchDown.h"
#include "../PCM/Wah/Wah.h"
#include "../PCM/Delay/Reverb.h"
#include "../PCM/Equalizer/Equalizer.h"

// �֐��I�u�W�F�N�g�̐錾
using EffectFunc = std::function<void()>;

// �G�t�F�N�g�̎��
enum class Effect
{
    PitchUp,		// �s�b�`�A�b�v
    PitchDown,		// �s�b�`�_�E��
    Wah,            // ���E
    Reverb,			// ���o�[�u
    Equalizer,		// �C�R���C�U�[
    Max				// ���ڐ�
};

class GenelateEffectScene :
    public BaseScene
{
public:
    GenelateEffectScene();
    ~GenelateEffectScene();
private:
    // ����������
    void Init(void)override;

    /// <summary>
    /// �X�V����(���̃V�[�����������s���j
    /// </summary>
    /// <param name="ownScene">�V�[���̎擾</param>
    /// <returns></returns>
    uniqueBase Update(uniqueBase ownScene)override;

    // �`�揈��
    void DrawOwnScreen(void)override;

    // �V�[��ID�擾
    SceneID GetSceneID(void)override
    {
        // �T�E���h�Đ��V�[��
        return SceneID::GenelateEffect;
    };

    // �s�b�`�V�t�g�̃I�u�W�F�N�g
    std::unique_ptr<PitchUp> pitchUp_;
    std::unique_ptr<PitchDown> pitchDown_;

    // ���E�̃I�u�W�F�N�g
    std::unique_ptr<Wah> wah_;

    // ���o�[�u
    std::unique_ptr<Reverb> reverb_;

    // �C�R���C�U
    std::unique_ptr<Equalizer> equalizer_;

    // �T�E���h�t�@�C��
    SoundFile soundFile_;

    // ���݂̑I���̏��
    int nowSelect_;

    // ���ꂼ��̃e�L�X�g�̈ʒu
    int pitchUpY_ = 240;
    int pitchDownY_ = 270;
    int wahY_ = 300;
    int reverbY_ = 330;
    int equalizerY_ = 360;
};

