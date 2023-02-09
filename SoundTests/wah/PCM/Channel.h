#pragma once
#include <vector>
struct ChannelL
{
	int pmin;		// �s�[�N�̉���
	int pmax;		// �s�[�N�̏��
	int p;			// �g�`�̎���
	int q;			// ������̍X�V
	int offset0;	// ���͉����̊J�n�ʒu
	int offset1;	// ���������̊J�n�ʒu
	int ta;			// �s�b�`�ύX�O�̃T���v���f�[�^	
	int tb;			// �s�b�`�ύX��̃T���v���f�[�^

	std::vector<double> x;		// ���̉��f�[�^���i�[
	std::vector<double> y;		// m�T���v�����炵�����f�[�^���i�[
	std::vector<double> r;		// x��y�̑��֊֐������߂�
};

struct ChannelR
{
	int pmin;		// �s�[�N�̉���
	int pmax;		// �s�[�N�̏��
	int p;			// �g�`�̎���
	int q;			// ������̍X�V
	int offset0;	// ���͉����̊J�n�ʒu
	int offset1;	// ���������̊J�n�ʒu
	int ta;			// �s�b�`�ύX�O�̃T���v���f�[�^	
	int tb;			// �s�b�`�ύX��̃T���v���f�[�^

	std::vector<double> x;		// ���̉��f�[�^���i�[
	std::vector<double> y;		// m�T���v�����炵�����f�[�^���i�[
	std::vector<double> r;		// x��y�̑��֊֐������߂�
};