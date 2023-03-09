#pragma once
#include <vector>
struct ChannelL
{
	double pmin;		// �s�[�N�̉���
	double pmax;		// �s�[�N�̏��
	double p;			// �g�`�̎���
	double q;			// ������̍X�V
	double offset0;		// ���͉����̊J�n�ʒu
	double offset1;		// ���������̊J�n�ʒu
	double ta;			// �s�b�`�ύX�O�̃T���v���f�[�^	
	double tb;			// �s�b�`�ύX��̃T���v���f�[�^

	std::vector<double> x;		// ���̉��f�[�^���i�[
	std::vector<double> y;		// m�T���v�����炵�����f�[�^���i�[
	std::vector<double> r;		// x��y�̑��֊֐������߂�
};

struct ChannelR
{
	double pmin;		// �s�[�N�̉���
	double pmax;		// �s�[�N�̏��
	double p;			// �g�`�̎���
	double q;			// ������̍X�V
	double offset0;		// ���͉����̊J�n�ʒu
	double offset1;		// ���������̊J�n�ʒu
	double ta;			// �s�b�`�ύX�O�̃T���v���f�[�^	
	double tb;			// �s�b�`�ύX��̃T���v���f�[�^

	std::vector<double> x;		// ���̉��f�[�^���i�[
	std::vector<double> y;		// m�T���v�����炵�����f�[�^���i�[
	std::vector<double> r;		// x��y�̑��֊֐������߂�
};