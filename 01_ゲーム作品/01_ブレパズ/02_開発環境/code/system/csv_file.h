//========================================
// 
// csv�t�@�C�����o�͏���
// 
//========================================
// *** csv_file.h ***
//========================================
#ifndef _CSV_FILE_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _CSV_FILE_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#pragma once
#include <iostream>	// �O���̑��u�Ɠ��o��
#include <fstream>	// �t�@�C�� �̓��o��
#include <vector>
#include <string>
#include <sstream>	// �J���}�ŋ�؂邽�߂ɕK�v

using namespace std;

//****************************************
// �N���X
//****************************************
class CSVFILE
{
public:
	
	// ***** �񋓌^ *****

	// �[������
	enum FORMAT
	{
		FORMAT_ROUNF,	// �l�̌ܓ�
		FORMAT_CEIL,	// �؂�グ
		FORMAT_FLOOR,	// �؂�̂�
		FORMAT_MAX,
	};

	// ***** �R���X�g���N�^�E�f�X�g���N�^ *****
	CSVFILE();
	virtual~CSVFILE();

	// ***** �֐� *****

	//--------------------------------------------------
	// �ǂݍ��ݏ���
	// ����1  : string filepath / �t�@�C���p�X
	// ����2  : bool bHeader	/ �w�b�_�[�̗L��
	// ����3  : bool bIndex		/ �C���f�b�N�X�̗L��
	// ����4  : char delim		/ ��؂蕶��
	//--------------------------------------------------
	void FileLood(string filepath, bool bHeader, bool bIndex, char delim);

	//--------------------------------------------------
	// �����o������
	// ����1  : string filepath / �t�@�C���p�X
	// ����2  : char delim		/ ��؂蕶��
	//--------------------------------------------------
	void FileSave(string filepath, char delim);

	//--------------------------------------------------
	// �R���\�[���o�͏���
	//--------------------------------------------------
	void FileShow(void);

	// -- �\�� -------------------------------------------------------------------

	//--------------------------------------------------
	// �[������ (float�^)
	// ����1  : float &val		/ �f�[�^
	// ����2  : ing nLen		/ ����
	// ����3  : FORMAT format	/ ����
	// �Ԓl   : float			/ �f�[�^(�ϊ���)
	//--------------------------------------------------
	float Format(float val, int nLen, FORMAT format);

	//--------------------------------------------------
	// �[������ (double�^)
	// ����1  : double &val		/ �f�[�^
	// ����2  : ing nLen		/ ����
	// ����3  : FORMAT format	/ ����
	// �Ԓl   : double			/ �f�[�^(�ϊ���)
	//--------------------------------------------------
	double Format(double val, int nLen, FORMAT format);

	// -- �ϊ� -------------------------------------------------------------------

	//--------------------------------------------------
	// ������ �� int�^
	// ����1  : int &val    / �f�[�^(�ϊ���)
	// ����2  : string &str / �f�[�^(�ϊ���)
	// �Ԓl   : bool        / �ϊ��ł�����
	//--------------------------------------------------
	bool ToValue(int &val, const string &str);

	//--------------------------------------------------
	// ������ �� float�^
	// ����1  : float &val  / �f�[�^(�ϊ���)
	// ����2  : string &str / �f�[�^(�ϊ���)
	// �Ԓl   : bool        / �ϊ��ł�����
	//--------------------------------------------------
	bool ToValue(float &val, const string &str);

	//--------------------------------------------------
	// ������ �� double�^
	// ����1  : double &val / �f�[�^(�ϊ���)
	// ����2  : string &str / �f�[�^(�ϊ���)
	// �Ԓl   : bool        / �ϊ��ł�����
	//--------------------------------------------------
	bool ToValue(double &val, const string &str);

	//--------------------------------------------------
	// ������ �� char�^
	// ����1  : char &val	/ �f�[�^(�ϊ���)
	// ����2  : string &str / �f�[�^(�ϊ���)
	// �Ԓl   : bool        / �ϊ��ł�����
	//--------------------------------------------------
	bool ToValue(char* &val, const string &str);

	//--------------------------------------------------
	// ������ �� bool�^
	// ����1  : bool &val	/ �f�[�^(�ϊ���)
	// ����2  : string &str / �f�[�^(�ϊ���)
	// �Ԓl   : bool        / �ϊ��ł�����
	//--------------------------------------------------
	bool ToValue(bool &val, const string &str);

	//--------------------------------------------------
	// int�^ �� ������
	// ����1  : int &val / �f�[�^
	// �Ԓl   : string	/ �f�[�^(string)
	//--------------------------------------------------
	string CastCell(int &val) { return to_string(val); }

	//--------------------------------------------------
	// float�^ �� ������
	// ����1  : float &val  / �f�[�^
	// �Ԓl   : string	   / �f�[�^(string)
	//--------------------------------------------------
	string CastCell(float &val){ return to_string(Format(val, 2, FORMAT_FLOOR)); }

	//--------------------------------------------------
	// double�^ �� ������
	// ����1  : double &val / �f�[�^
	// �Ԓl   : string	   / �f�[�^(string)
	//--------------------------------------------------
	string CastCell(double &val) { return to_string(val); }

	//--------------------------------------------------
	// char�^ �� ������
	// ����1  : char &val / �f�[�^
	// �Ԓl   : string	   / �f�[�^(string)
	//--------------------------------------------------
	string CastCell(char &val) { return &val; }

	//--------------------------------------------------
	// char�^ �� ������
	// ����1  : char* &val / �f�[�^
	// �Ԓl   : string	   / �f�[�^(string)
	//--------------------------------------------------
	string CastCell(char* &val) { return * &val; }

	// -- �ݒ� -----------------------------------------
	/* �w�b�_�[		*/void SetHeader(string str, char delim);
	/* �C���f�b�N�X	*/void SetIndex(string str, char delim);

	// -- �ݒ�E�ǉ� ------------------------------------------
	/* �v�f	*/void SetCell(string str, int row, int line);

	// -- �擾 ------------------------------------------
	/* �s��	*/int GetRowSize(void) { return cell.size(); }
	/* ��	*/int GetLineSize(int row) { return cell.at(row).size(); }
	/* �v�f */string GetData(int row, int line) { return cell.at(row).at(line); }

private:

	// ***** �ϐ� *****
	string filepath;	// �t�@�C���p�X
	bool bHeader;		// �w�b�_�[�̗L��
	bool bIndex;		// �C���f�b�N�X�̗L��
	char delim;			// ��؂蕶��

	/* �ۊ� */
	vector<string> header;			// �w�b�_�[��
	vector<string> index;			// �C���f�b�N�X��
	vector<vector<string>> cell;	// �v�f
};

#endif