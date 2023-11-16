//========================================
//
// ����
//
//========================================
// *** time.h ***
//========================================
#ifndef _TIME_H_
#define _TIME_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// �O���錾
//****************************************
class CText;

//****************************************
// �N���X
//****************************************
class CTime : public CObject
{
	// ��`
	static const int TIME_START_DEX = 6;	// ���Ԃ̊J�n�ʒu

public:

	CTime(int nPriority = PRIO_UI);
	~CTime();

	// *****  �֐� *****

	/* ���C�� */
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CTime *Create(int nTime = 0);
	/* �^�C���ݒ�	*/void SetTime(int nTime = 0);
	/* �^�C������	*/int GetTime(void) { return m_nTime; }
private:
	// ***** �ϐ� *****
	int m_nTime;		// ����
	int m_nTimeMax;		// ���Ԃ̍ő�l
	int m_nCounter;		// �J�E���^�[
	int m_Digit;		// ����
	int m_nNumWarn;		// ���������x����
	bool m_bSetTime;	// ���Ԃ̐ݒ��������
	bool m_bUpdateTime;	// ���Ԃ̍X�V�t���O
	CText *m_Time;		// �e�L�X�g�\��

};
#endif 