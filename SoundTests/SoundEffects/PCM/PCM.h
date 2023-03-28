#pragma once

// �~����
#define M_PI 3.14159265359

class PCM
{
public:
	PCM();
	virtual ~PCM();
protected:
	/// <summary>
	/// �V�����G�t�F�N�g���K�p���ꂽwav�t�@�C���𐶐�����
	/// </summary>
	/// <param name="fileName">�G�t�F�N�g�K�p�O�̃t�@�C��</param>
	/// <param name="afterFileName">�G�t�F�N�g�K�p��̃t�@�C��</param>
	/// <returns></returns>
	virtual bool GenelateEffectWaveFile(const wchar_t* fileName, const wchar_t* afterFileName) = 0;

	/// <summary>
	/// �V�����G�t�F�N�g���K�p���ꂽwav�t�@�C���𐶐�����
	/// </summary>
	/// <param name="rate">�s�b�`�ύX�̔{��</param>
	/// <param name="fileName">�G�t�F�N�g�K�p�O�̃t�@�C��</param>
	/// <param name="afterFileName">�G�t�F�N�g�K�p��̃t�@�C��</param>
	virtual bool GenelateEffectWaveFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) = 0;
private:
};

