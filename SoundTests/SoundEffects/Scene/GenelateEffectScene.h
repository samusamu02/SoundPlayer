#pragma once
#include <thread>
#include "BaseScene.h"
#include "../SoundObj/SoundFile.h"
#include "../PCM/PitchShift/PitchUp.h"
#include "../PCM/PitchShift/PitchDown.h"
#include "../PCM/Wah/Wah.h"
#include "../PCM/Delay/Delay.h"
#include "../PCM/Delay/Reverb.h"
#include "../PCM/Equalizer/Equalizer.h"

// ���ꂼ��̃e�L�X�g�̈ʒu
constexpr int PITCHUP_Y = 240;
constexpr int PITCHDOWN_Y = 270;
constexpr int REVERB_Y = 300;
constexpr int EQUALIZER_Y = 330;

// �G�t�F�N�g�̎��
enum class Effect
{
    PitchUp,		// �s�b�`�A�b�v
    PitchDown,		// �s�b�`�_�E��
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
    void Init(void)override;
    uniqueBase Update(uniqueBase ownScene)override;
    void DrawOwnScreen(void)override;

    // �s�b�`�V�t�g�̃I�u�W�F�N�g
    std::unique_ptr<PitchUp> pitchUp_;
    std::unique_ptr<PitchDown> pitchDown_;

    // ���E�̃I�u�W�F�N�g
    std::unique_ptr<Wah> wah_;

    // �f�B���C
    std::unique_ptr<Delay> delay_;

    // ���o�[�u
    std::unique_ptr<Reverb> reverb_;
    
    // �C�R���C�U
    std::unique_ptr<Equalizer> equalizer_;

    // �T�E���h�t�@�C��
    SoundFile soundFile_;

    // �V�[��ID�擾
    SceneID GetSceneID(void)override
    {
        // �T�E���h�Đ��V�[��
        return SceneID::GenelateEffect;
    };

    // ���݂̑I���̏��
    int nowSelect;
};

