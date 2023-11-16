//========================================
// 
// csv�t�@�C�����o�͏���
// 
//========================================
// *** csv_file.cpp ***
//========================================
#include "csv_file.h"

//========================================
// �R���X�g���N�^
//========================================
CSVFILE::CSVFILE()
{
	bHeader = false;	// �w�b�_�[
	bIndex = false;		// �C���f�b�N�X
	delim = ',';		// ��؂蕶��
}

//========================================
// �f�X�g���N
//========================================
CSVFILE::~CSVFILE()
{

}

//================================================================================
// �ǂݍ��ݏ���
// �����F�t�@�C���p�X / �w�b�_�[�L�� / �C���f�b�N�X�L�� / ��؂蕶��
//================================================================================
void CSVFILE::FileLood(string filepath, bool bHeader, bool bIndex, char delim)
{
	// �e�v�f��ۑ�
	this->filepath = filepath;
	this->bHeader = bHeader;
	this->bIndex = bIndex;
	this->delim = delim;

	string str_buf;			// �P�s�̃f�[�^���i�[����ϐ�
	string str_comma_buf;	// delim ��؂� �����f�[�^���i�[����ϐ�

	// �t�@�C�����J�� (ifstream�̃R���X�g���N�^�ŊJ��)
	ifstream ifs_csv_file(filepath);

	// �P�s���ǂݍ��� (�ǂݍ��񂾓��e�� str_buf �Ɋi�[)
	for (int nRow = 0; getline(ifs_csv_file, str_buf); nRow++)
	{
		cell.push_back(vector<string>());

		// delim ��؂育�ƂɃf�[�^��ǂݍ��ނ��߂� istringstream �ɂ���
		istringstream i_stream(str_buf);

		for (int nLine = 0; getline(i_stream, str_comma_buf, delim); nLine++)
		{
			// -- �ǂݍ���------------------------
			if (bHeader && bIndex)
			{// �w�b�_�[�ƃC���f�b�N�X�����鎞

				/* �܂�Ԃ�		*/if (nRow == 0 && nLine == 0) continue;
				/* �w�b�_�[		*/if (nRow == 0 && nLine != 0) header.push_back(str_comma_buf);
				/* �C���f�b�N�X */if (nRow != 0 && nLine == 0) index.push_back(str_comma_buf);
				/* �v�f			*/if (nRow != 0 && nLine != 0) cell.at(nRow - 1).push_back(str_comma_buf);
			}
			else if (bHeader)
			{// �w�b�_�[�����鎞
				/* �w�b�_�[		*/if (nRow == 0)				header.push_back(str_comma_buf);
				/* �C���f�b�N�X */if (nRow != 0 && nLine == 0)	index.push_back(string());
				/* �v�f			*/if (nRow != 0)				cell.at(nRow - 1).push_back(str_comma_buf);
			}
			else if (bIndex)
			{// �C���f�b�N�X�����鎞
				/* �w�b�_�[		*/if (nRow == 0 && nLine != 0)	header.push_back(str_comma_buf);
				/* �C���f�b�N�X */if (nLine == 0)				index.push_back(str_comma_buf);
				/* �v�f			*/if (nLine != 0)				cell.at(nRow).push_back(str_comma_buf);
			}
			else
			{// �v�f�̂�
				/* �w�b�_�[		*/if (nRow == 0)	header.push_back(str_comma_buf);
				/* �C���f�b�N�X */if (nLine == 0)	index.push_back(str_comma_buf);
				/* �v�f			*/					cell.at(nRow).push_back(str_comma_buf);
			}
		}
	}
}

//================================================================================
// �����o������
// �����F�t�@�C���p�X / ��؂蕶��
//================================================================================
void CSVFILE::FileSave(string filepath, char delim)
{
	// �������ރt�@�C�����J�� (ofstream�̃R���X�g���N�^�ŊJ��)
	ofstream ofs_csv_file(filepath);

	if (bHeader)
	{
		for (int nRow = 0; nRow < header.size(); nRow++)
		{
			/* ��		*/if (bIndex && nRow == 0)ofs_csv_file << delim;
			/* �w�b�_�[ */ofs_csv_file << header.at(nRow) << delim;
		}
		ofs_csv_file << endl;
	}

	for (int nLine = 0; nLine < index.size(); nLine++)
	{
		if (bIndex)
		{
			/* �C���f�b�N�X */ofs_csv_file << index.at(nLine) << delim;
		}
		for (int nRow = 0; nRow < header.size(); nRow++)
		{
			/* �v�f */ofs_csv_file << cell.at(nLine).at(nRow) << delim;
		}
		ofs_csv_file << endl;
	}
}

//================================================================================
// �R���\�[���o�͏���
//================================================================================
void CSVFILE::FileShow(void)
{
	/* �t�@�C���p�X			*/cout << "filepath = " << filepath << ", ";
	/* �w�b�_�[				*/cout << "bHeader = " << int(bHeader) << ", ";
	/* �C���f�b�N�X			*/cout << "bIndex = " << int(bIndex) << ", ";
	/* �v�f					*/cout << "delim = " << delim << endl;
	/* �w�b�_�[ �T�C�Y		*/cout << "header size = " << header.size() << ", ";
	/* �C���f�b�N�X �T�C�Y	*/cout << "index size = " << index.size() << endl;

	if (bHeader)
	{
		for (int nRow = 0; nRow < header.size(); nRow++)
		{
			if (bIndex && nRow == 0) cout << "\t";
			cout << header.at(nRow) << "(h)" << "\t";
		}
		cout << endl;
	}
	for (int nLine = 0; nLine < index.size(); nLine++)
	{
		if (bIndex)
		{
			cout << index.at(nLine) << "(i)" << "\t";
		}
		for (int j = 0; j < header.size(); j++)
		{
			cout << cell.at(nLine).at(j) << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

//================================================================================
// �w�b�_�[�̐ݒ�
// �����F�w�b�_�[�� / ��؂蕶��
//================================================================================
void CSVFILE::SetHeader(string str, char delim)
{
	string str_comma_buf;	// delim ��؂� �����f�[�^���i�[����ϐ�

	// delim ��؂育�ƂɃf�[�^��ǂݍ��ނ��߂� istringstream �ɂ���
	istringstream i_stream(str);

	for (int nLine = 0; getline(i_stream, str_comma_buf, delim); nLine++)
	{
		header.push_back(str_comma_buf);
	}

	bHeader = true;
}

//================================================================================
// �C���f�b�N�X�̐ݒ� (�ꊇ)
// �����F�C���f�b�N�X�� / ��؂蕶��
//================================================================================
void CSVFILE::SetIndex(string str, char delim)
{
	string str_comma_buf;	// delim ��؂� �����f�[�^���i�[����ϐ�

	// delim ��؂育�ƂɃf�[�^��ǂݍ��ނ��߂� istringstream �ɂ���
	istringstream i_stream(str);

	for (int nLine = 0; getline(i_stream, str_comma_buf, delim); nLine++)
	{
		index.push_back(str_comma_buf);
	}

	bIndex = true;
}

//================================================================================
// �f�[�^(�v�f)�̐ݒ�E�ǉ�
// �����F�f�[�^ / �s�ԍ� / ��ԍ�
//================================================================================
void CSVFILE::SetCell(string str, int row,int line)
{
	cell.push_back(vector<string>());

	if (!bIndex && line == 0)
	{
		index.push_back(string());
	}

	cell.at(row).push_back(str);
}

//================================================================================
// �����𐧌� (float�^)
// �����F�f�[�^ / ���� / ����
// �Ԓl�F�f�[�^(�ϊ���)
//================================================================================
float CSVFILE::Format(float val, int nLen, FORMAT format)
{	
	float fRet;

	fRet = val * powf(10.0, nLen);

	switch (format)
	{
	case FORMAT_ROUNF: { /* �l�̌ܓ� */
		fRet = (int)(fRet + 0.5);
	}
	  break;
	case FORMAT_CEIL: { /* �؂�グ */
		fRet = (int)(fRet + 0.9);
	}
	  break;
	case FORMAT_FLOOR: { /* �؂�̂� */
		fRet = (int)(fRet);
	}
	  break;
	}

	return fRet * powf(10.0, -nLen);
}

//================================================================================
// �����𐧌� (float�^)
// �����F�f�[�^ / ���� / ����
// �Ԓl�F�f�[�^(�ϊ���)
//================================================================================
double CSVFILE::Format(double val, int nLen, FORMAT format)
{
	float fRet;

	fRet = val * pow(10.0, nLen);

	switch (format)
	{
	case FORMAT_ROUNF: { /* �l�̌ܓ� */
		fRet = (double)(int)(fRet + 0.5);
	}
	  break;
	case FORMAT_CEIL: { /* �؂�グ */
		fRet = (double)(int)(fRet + 0.9);
	}
	  break;
	case FORMAT_FLOOR: { /* �؂�̂� */
		fRet = (double)(int)(fRet);
	}
	  break;
	}

	return fRet * pow(10.0, -nLen);
}

//================================================================================
// ������ �� int�^
// �����F�f�[�^(�ϊ���) / �f�[�^(�ϊ���)
// �Ԓl�F�ϊ��o������
//================================================================================
bool CSVFILE::ToValue(int &val, const string &str)
{
	try 
	{
		val = stoi(str);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

//================================================================================
// ������ �� float�^
// �����F�f�[�^(�ϊ���) / �f�[�^(�ϊ���)
// �Ԓl�F�ϊ��o������
//================================================================================
bool CSVFILE::ToValue(float &val, const string &str)
{
	try 
	{
		val = stof(str);
		return true;
	}
	catch (...) 
	{
		return false;
	}
}

//================================================================================
// ������ �� double�^
// �����F�f�[�^(�ϊ���) / �f�[�^(�ϊ���)
// �Ԓl�F�ϊ��o������
//================================================================================
bool CSVFILE::ToValue(double &val, const string &str)
{
	try
	{
		val = stod(str);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

//================================================================================
// ������ �� char�^
// �����F�f�[�^(�ϊ���) / �f�[�^(�ϊ���)
// �Ԓl�F�ϊ��o������
//================================================================================
bool CSVFILE::ToValue(char* &val, const string &str)
{
	try
	{
		char* cstr = new char[str.size() + 1]; // �������m��

		char_traits<char>::copy(cstr, str.c_str(), str.size() + 1);

		val = cstr;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

//================================================================================
// ������ �� bool�^
// �����F�f�[�^(�ϊ���) / �f�[�^(�ϊ���)
// �Ԓl�F�ϊ��o������
//================================================================================
bool CSVFILE::ToValue(bool &val, const string &str)
{
	try
	{
		val = stoi(str);
		return true;
	}
	catch (...)
	{
		return false;
	}
}