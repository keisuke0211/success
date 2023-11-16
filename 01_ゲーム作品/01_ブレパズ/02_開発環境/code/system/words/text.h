//========================================
// 
// �e�L�X�g�\��
// 
//========================================
// *** text.h ***
//========================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "../../object/object2D.h"
#include "words.h"

//****************************************
// �\����
//****************************************

// �e�L�X�g���(�����p)
struct FormFont
{
	D3DXCOLOR col;		// �����̐F
	float fTextSize;	// �����̃T�C�Y(�����l 20)
	int nAppearTime;	// 1�����ڂ��\�������܂ł̎���(�����l 1)
	int nStandTime;		// �ҋ@����(�����l 10)
	int nEraseTime;		// ������܂ł̎���(�����l 1) �� 0 �͏����Ȃ�
};

// �e���(�����p)
struct FormShadow
{
	D3DXCOLOR col;			// �e�̐F
	bool bShadow;			// �e�t���O
	D3DXVECTOR3 AddPos;		// �����̈ʒu���炸�炷�l (�����l 0,0,0)	(���̕��� + AddPos)
	D3DXVECTOR2 AddSize;	// �����̃T�C�Y�̉��Z�l (�����l 0,0)		(���̕��� + AddSize)
};

//****************************************
// �O���錾
//****************************************
class CFont;

//****************************************
// �N���X
//****************************************
class CText : public CObject2D
{
public:

	// ***** �񋓌^ *****

	// �e�L�X�g�{�b�N�X�̎��
	enum Box
	{
		BOX_NORMAL_RECT = 0,	// �m�[�}��(�����`)
		BOX_NORMAL_SQR,			// �m�[�}��(�����`)
		BOX_MAX
	};

	// ***** �֐� *****
	CText(int nPriority = PRIO_TEXT);
	~CText();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	//--------------------------------------------------
	// �e�L�X�g����
	// ����1  : Box type            / �e�L�X�g�{�b�N�X�̉摜
	// ����2  : D3DXVECTOR3 pos     / �e�L�X�g�{�b�N�X�̈ʒu
	// ����3  : D3DXVECTOR2 size    / �e�L�X�g�{�b�N�X�̃T�C�Y
	// ����4  : const char *Text�@�@/ �e�L�X�g
	// ����5  : CFont::FONT Type�@�@/ �t�H���g���
	// ����6  : FormFont *pFont		/ �t�H���g�֘A�̏��(�F�E���ԂȂ�) �����Ă����v
	// ����7  : bool bTextBok�@�@�@ / ���b�Z�[�W�{�b�N�X�̕\���E��\�� (�����l true)
	// ����8  : FormShadow *Shadow  / �t�H���g�̉e�̏�� �����Ă����v
	//--------------------------------------------------
	static CText *CText::Create(Box type, D3DXVECTOR3 pos, D3DXVECTOR2 size, const char *Text, CFont::FONT FontType, FormFont *pFont = NULL, bool bTextBok = true, FormShadow *Shadow = NULL);

	/* �폜 */void Disap(bool bDisap,int nTime);

	// -- �ݒ� ------------------------------------------
	/* �󔒕\��			*/void SetSpace(bool bSpace) { m_Info.bSpace = bSpace; }
	/* �|�[�Y���̐���	*/void SetTetPause(bool bPause);
	/* �{�b�N�X�̐F		*/void SetBoxColor(D3DXCOLOR col);
	/* �e�L�X�g�̐F		*/bool SetTextColor(D3DXCOLOR col);
	/* �����ύX(�P��)	*/bool ChgWords(char* Text, int nIdx, D3DXCOLOR col);
	/* �����ύX(�S��)	*/bool ChgText(char* Text, D3DXCOLOR col);// �� ���̃e�L�X�g��葽���Ǝg���Ȃ� �܂����p�p���̂�

	// -- �ݒ� ------------------------------------------
	/*�@�T�C�Y	*/float GetTxtSize() { return m_Info.fTextSize; }

private:

	// ***** �\���� *****

	// �e
	struct Shadow
	{
		D3DXCOLOR col;			// �e�̐F
		bool bShadow;			// �e�t���O
		CWords** shadow;		// ����(�e)
		D3DXVECTOR3 AddPos;		// �����̈ʒu���炸�炷�l (�����l 0,0,0)	(���̕��� + AddPos)
		D3DXVECTOR2 AddSize;	// �����̃T�C�Y�̉��Z�l (�����l 0,0)		(���̕��� + AddSize)
	};

	// �e�L�X�g���
	struct Info
	{
		D3DXCOLOR TextBoxCol;	// �e�L�X�g�{�b�N�X�̐F
		D3DXCOLOR FontCol;		// �����̐F
		D3DXCOLOR TextBoxColOld;// �O��̃e�L�X�g�{�b�N�X�̐F
		D3DXCOLOR FontColOld;	// �O��̕����̐F
		bool bCol;				// �F�ύX�t���O(�|�[�Y�ؑ�)

		float fTextSize;		// �����̃T�C�Y
		int nTextLength;		// �����̒���
		int nAppearTime;		// 1�̕��������Z�����܂ł̎���
		int nAddCount;			// ���������Z�����܂ł̃J�E���g
		int nAddLetter;			// �������ړ���邩�w��
		int nLetterPopCount;	// �������o�����ő吔
		int nLetterPopCountX;	// ���ɕ������o������
		int nNiCount;			// ���s�̐�

		int nStandTime;			// �ҋ@����
		bool bStand;			// �ҋ@�t���O

		int nDisapTime;			// �����鎞��
		int nDisapTimeMax;		// ������ő厞��
		bool bRelease;			// �����t���O

		Shadow aShadow;			// �e

		bool bTextBok;			// �e�L�X�g�{�b�N�X�̕\���t���O
		bool bPause;			// �|�[�Y���ł��������ifalse�F�����Ȃ��j
		bool bSpace;			// �󔒕\���t���O(sprintf�p)
		string sText;			// �\������e�L�X�g
		string sALLText;		// �e�L�X�g�̑S��
		CWords** words;			// ����
		CFont::FONT FontType;	// �t�H���g���
	};

	// ***** �֐� *****
	/* ��������	*/void LetterForm(void);
	/* �ҋ@		*/void StandTime(void);
	/* �폜		*/void DisapTime(void);
	/* ��������	*/bool CheckLeadByte(int nLetter);

	// -- �ݒ� ------------------------------------------
	/* �e�L�X�g �T�C�Y	*/void SetTextSize(float TextSize);
	/* �ҋ@����			*/void SetStandTime(int StandTime);
	/* �����̏�������	*/void EraseTime(int time);
	/* �����̏o������	*/void TextLetter(const char *Text, int DispText);

	// ***** �ϐ� *****
	Info m_Info;

};

#endif