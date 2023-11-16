//========================================
//
// �X�R�A
//
//========================================
// *** score.h ***
//========================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// �O���錾
//****************************************
class CText;

//****************************************
// �N���X
//****************************************
class CScore : public CObject
{
	// ��`
	static const int SCORE_START_DEX = 6;	// �X�R�A�̊J�n�ʒu

public:

	CScore(int nPriority = PRIO_UI);
	~CScore();

	// *****  �֐� *****

	// -- ���C�� ---------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CScore *Create(void);

	// -- �ݒ� ---------------------------------
	/* �X�R�A	*/static void SetScore(int nScore = 0);

	// -- �擾 ---------------------------------
	/* �X�R�A	*/int GetScore(void) { return m_nScore; }

private:
	// ***** �ϐ� *****
	static int m_nScore;
	static bool m_bUpdateText;	// �X�R�A�̍X�V�t���O
	int m_Digit;				// ����
	CText *m_Score;				// �e�L�X�g�\��
};
#endif 