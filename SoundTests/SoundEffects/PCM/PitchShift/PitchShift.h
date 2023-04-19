#pragma once
#include <memory>
#include "../PCM.h"
#include "../PCMSet.h"
#include "../../Wave/PCMDef.h"

class PitchShift
	: public PCM
{
public:
	PitchShift();
	virtual ~PitchShift();

protected:

	struct ChannelL
	{
		double search_min;					// �T���͈͂̉���
		double search_max;					// �T���͈͂̏��
		double in_pos;						// ���̓f�[�^�̌��݂̈ʒu
		double out_pos;						// �o�̓f�[�^�̌��݂̈ʒu
		double currentIndex;				// ���݂̃T���v���̃C���f�b�N�X
		double nextIndex;					// ���̃T���v���̃C���f�b�N�X

		std::vector<double> soundData;				// ���̉����f�[�^���i�[���邽�߂̕ϐ�
		std::vector<double> shiftData;				// �T���v�������炷���߂̕ϐ�
		std::vector<double> correlation;			// originalSoundData_��shiftedSoundData_�̑��֊֐������߂邽�߂̕ϐ�
	};

	struct ChannelR
	{
		double search_min;					// �T���͈͂̉���
		double search_max;					// �T���͈͂̏��
		double in_pos;						// ���̓f�[�^�̌��݂̈ʒu
		double out_pos;						// �o�̓f�[�^�̌��݂̈ʒu
		double currentIndex;				// ���݂̃T���v���̃C���f�b�N�X
		double nextIndex;					// ���̃T���v���̃C���f�b�N�X

		std::vector<double> soundData;			// ���̉����f�[�^���i�[���邽�߂̕ϐ�
		std::vector<double> shiftData;			// �T���v�������炷���߂̕ϐ�
		std::vector<double> correlation;		// originalSoundData_��shiftedSoundData_�̑��֊֐������߂邽�߂̕ϐ�
	};

	// ����������
	virtual void Init(void) = 0;

	// ���`�����l���̕ϐ�����������
	virtual void ChannelL_Init(void) = 0;

	// �E�`�����l���̕ϐ�����������
	virtual void ChannelR_Init(void) = 0;

	// ���`�����l���̃^�C���X�g���b�`����
	virtual void ChannelL_Timestretching(void) = 0;

	// �E�`�����l���̃^�C���X�g���b�`����
	virtual void ChannelR_Timestretching(void) = 0;

	// ���`�����l���̃��T���v�����O����
	virtual void ChannelL_Resampling(void) = 0;

	// �E�`�����l���̃��T���v�����O����
	virtual void ChannelR_Resampling(void) = 0;

	/// <summary>
	/// �V�����s�b�`�V�t�g���K�p���ꂽwav�t�@�C���𐶐�����
	/// </summary>
	/// <param name="rate">�s�b�`�ύX�̔{��</param>
	/// <param name="fileName">�K�p�O�̃t�@�C��</param>
	/// <param name="afterFileName">�K�p��̃t�@�C��</param>
	virtual void GenelatePitchShiftWaveFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) = 0;

	// PCM�̏������̃I�u�W�F�N�g
	std::unique_ptr<PCMSet> pcmSet_;

	// �s�b�`�V�t�g�p�̃I�u�W�F�N�g
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;
	std::unique_ptr<STEREO_PCM> pcm2_;

	// ���`�����l��
	std::unique_ptr<ChannelL> channelL_;
	// �E�`�����l��
	std::unique_ptr<ChannelR> channelR_;

	// ���֊֐��̃s�[�N
	double peak_;

	// �T���v���̎��Ԏ��̃C���f�b�N�X
	double timeIndex_;

	// �^�C���X�g���b�`�̐L�k�������߂�
	double rate_;

	// �s�b�`�̒l
	double pitch_;

	// �n�j���O���̃T�C�Y
	int hanningSize_;

	// ���֊֐��̃T�C�Y
	int correlationSize_;
private:
};

