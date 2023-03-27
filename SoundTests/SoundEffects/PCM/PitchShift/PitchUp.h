#pragma once
#include <memory>
#include "PitchShift.h"

class PitchUp
	: public PitchShift
{
public:
	PitchUp();
	~PitchUp();

	// �s�b�`�V�t�g
	bool GenelatePitchShiftFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) override;

private:
	// ������
	void Init(void) override;

	// ���`�����l���̕ϐ�������
	void ChannelL_Init(void) override;

	// �E�`�����l���̕ϐ�������
	void ChannelR_Init(void) override;

	// ���`�����l���̃^�C���X�g���b�`
	void ChannelL_Timestretching(void) override;

	// �E�`�����l���̃^�C���X�g���b�`
	void ChannelR_Timestretching(void) override;

	// ���`�����l���̃��T���v�����O
	void ChannelL_Resampling(void) override;

	// �E�`�����l���̃��T���v�����O
	void ChannelR_Resampling(void) override;
};

