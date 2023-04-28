#pragma once
#include <functional>
#include <vector>
#include <string>
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
    PitchUp,		    // �s�b�`�A�b�v
    PitchDown,		    // �s�b�`�_�E��
    Wah,                // ���E
    Reverb,			    // ���o�[�u
    Equalizer_Base,		// �C�R���C�U�[(�ቹ)
    Equalizer_Middle,   // �C�R���C�U�[(����)
    Equalizer_Treble,   // �C�R���C�U�[(����)
    Max				    // ���ڐ�
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

    // ���ڑI���̏�����
    void Init_Select(void);
    
    // �G�t�F�N�g���̏�����
    void Init_EffectNames(void);

    // ���W�̏�����
    void Init_StringPos(void);

    // �摜�̏�����
    void Init_Image(void);

    /// <summary>
    /// �X�V����(���̃V�[�����������s���j
    /// </summary>
    /// <param name="ownScene">�V�[���̎擾</param>
    /// <returns></returns>
    uniqueBase Update(uniqueBase ownScene)override;

    // �`�揈��
    void DrawOwnScreen(void)override;

    // �Z���N�^�[�̏�ԕω�
    void ChangeSelect(void);

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

    // ���o�[�u�̃I�u�W�F�N�g
    std::unique_ptr<Reverb> reverb_;

    // �C�R���C�U�̃I�u�W�F�N�g
    std::unique_ptr<Equalizer> equalizer_;

    // �L�[�R�[�h�ƃG�t�F�N�g�̑Ή���z��ŊǗ�
    std::vector < std::pair<int, Effect>> keyEffects_;

    // ���ꂼ��̃G�t�F�N�g���̕ۑ�
    std::vector<std::wstring> effectNames_;

    // �T�E���h�t�@�C��
    SoundFile soundFile_;

    // ���݂̑I���̏��
    int nowSelect_;

    // ���ꂼ��̃e�L�X�g�̈ʒu
    // X���W
    int stringPosX_;

    // Y���W
    std::vector<int> y_Coordinates_;
    int pitchUpPosY_;
    int pitchDownPosY_;
    int wahPosY_;
    int reverbPosY_;
    int equalizerPosY_Bass_;
    int equalizerPosY_Middle_;
    int equalizerPosY_Treble_;

    // �Z���N�^�[�̈ʒu
    int selecterPosX_;
    int selecterPosY_;

    // �摜�`��
    int loadingImg_;

    // �摜�̍��W
    int imagPosX_;
    int imagPosY_;

    // �摜�̊g�嗦
    double rate_;

    // �摜�̉�]
    double angele_;

    // ��]�X�s�[�h
    double angleSpeed_;

    // ����
    double time_;
};

