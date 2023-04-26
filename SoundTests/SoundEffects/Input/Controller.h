#pragma once
#include <array>
#include <map>
#include <list>
#include <vector>
#include <chrono>

#include "InputID.h"

// ���͂̏��
enum class Trg
{
	Now,	// ���݂̒l
	Old,	// �O��̒l
	Max	
};

// Trg�̒l���C���f�b�N�X�ɂ��āA�e�v�f�̐^�U�l��array�̃G�C���A�X
using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;

// ����ID���L�[�Ƃ��āATrgBool��l�Ƃ���map�̃G�C���A�X
using CntData = std::map<InputID, TrgBool>;

class Controller
{
public:

	// �����O�o�b�t�@�̍\����
	struct RingBuf
	{
		int value = 0;								// �f�[�^�̒l
		double time = 0.0;							// �f�[�^�̎���
		RingBuf* before = nullptr;					// �O�̗v�f
		RingBuf* next = nullptr;					// ���̗v�f
		static RingBuf* Create(int no);				// �����O�o�b�t�@�𐶐�����ÓI���\�b�h
		static void Destroy(RingBuf* beginBuf);		// �����O�o�b�t�@��j������ÓI���\�b�h
	};

	Controller() {};
	virtual ~Controller() {};

	// �X�V����
	virtual void Update(void) = 0;

	// CntData���擾���郁�\�b�h
	const CntData& GetCntData(void)
	{
		return cntData_;
	}

protected:
	// ���͏�Ԃ̃f�[�^
	CntData cntData_;
	// �����O�o�b�t�@�̌��݂̗v�f�ւ̃|�C���^
	RingBuf* ringBuf_ = nullptr;
	// �����O�o�b�t�@�̐擪�̗v�f�ւ̃|�C���^
	RingBuf* startBuf_ = nullptr;

private:
};

