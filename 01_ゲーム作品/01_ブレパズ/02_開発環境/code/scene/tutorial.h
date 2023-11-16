//========================================
// 
// �`���[�g���A��
// 
//========================================
// *** tutorial.h ***
//========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CText;
class CPlayer;
class CEnemy;

//****************************************
// �N���X
//****************************************
class CTutorial : public CScene
{
	// ***** ��` *****
	static const char* FILE_PATH;		// �ǂݍ��ރt�@�C���p�X
	static const int MAX_TIME = 90;		// ��������
	static const int NUM_TEXT = 10;		// �e�L�X�g��

	static const char* SIDE_FILE;		// ���ʂ̃t�@�C���p�X
	static const char* FLOOR_FILE;		// ���̃t�@�C���p�X
	static const char* BLOCK_FILE1;		// �u���b�N�̃t�@�C���p�X
	static const char* ENEMY_FILE1;		// �G�l�~�[�̃t�@�C���p�X
public:

	// ***** �񋓌^ *****

	// �s��
	enum ACTION
	{
		ACTION_MOVE = 0,	// �ړ�
		ACTION_CAMERA,		// ���_�ړ�
		ACTION_SHOT,		// ����
		ACTION_SET,			// �z�u(����)
		ACTION_SET1,		// �z�u(����)
		ACTION_ENEMY,		// �G
		ACTION_CLEAR,		// �L���[�u����
		ACTION_CLEAR1,		// �L���[�u����
		ACTION_FREE,		// �I��
		ACTION_MAX
	};

	// ***** �֐� *****
	CTutorial();
	~CTutorial();

	// -- ���C�� ------------------------------------------
	/* ������			*/HRESULT Init(void);
	/* �I��				*/void Uninit(void);
	/* �X�V				*/void Update(void);
	/* �`��				*/void Draw(void);
	/* ����				*/static CTutorial *Create(void);
	/* �ǂݍ���			*/void TextLoad(void);

	// -- �ǂݍ��� ----------
	/* �w�i�@�V��	*/static void LoodCeiling(void);
	/* �w�i�@����	*/static void LoodSide(void);
	/* ��			*/static void LoodFloor(void);
	/* �u���b�N		*/static void LoodBlock(void);
	/* �G�l�~�[		*/static void LoodEnemy(void);

	// -- �擾 ------------------------
	/* �v���C���[	*/static CPlayer *GetPlayer() { return m_pPlayer; }
	/* �^�C��		*/static CTime *GetTime() { return m_pTime; }
	/* �X�R�A		*/static CScore *GetScore() { return m_pScore; };
	/* ���݂̍s��	*/static int GetCurAction() { return m_nCurAction; }

private:

	// ***** �\���� *****

	// �e�L�X�g���
	struct LoadTxt
	{
		D3DXVECTOR3 pos;			// �ʒu
		D3DXVECTOR2 size;			// �T�C�Y
		int nType;					// ���
		int nStartTime;				// �J�n����
		int nStandTime;				// �ҋ@����
		int nDisapTime;				// �����鎞��
		int nCreateTime;			// �����ҋ@����
		char *ActionTex[TXT_MAX];	// �s���e�L�X�g
		float nTextSize;			// �e�L�X�g�T�C�Y
		bool bTextBok;				// �e�L�X�g�{�b�N�X�̕\���t���O
	};

	// 
	struct CreateTxt
	{
		int nNumCur;				// ���݂̍s���̐�����
		int nNumCurAll;				// �S�̂Ő�����������
		int nCurAction;				// ���݂̍s��
		int nCreateTime;			// ���̃e�L�X�g�𐶐�����܂ł̎���
		int nCurMax[ACTION_MAX];	// �e�s���̍ő吔
		bool bCreate[ACTION_MAX];	// �����t���O
	};

	// ***** �֐� *****
	/* �e�L�X�g��񏉊���	*/void TxtInit(int nIdx);
	/* �e�L�X�g����			*/void TxtCreate(int nType);
	/* �e�L�X�g�폜			*/void TxtDelete(int nType,int nNextType);
	/* �`���[�g���A��		*/void TutorialTex(void);

	// ***** �ÓI�ϐ� *****
	/* �e�L�X�g���	*/static LoadTxt*m_LoadText;
	/* �v���C���[	*/static CPlayer*m_pPlayer;
	/* �^�C��		*/static CTime	*m_pTime;
	/* �X�R�A		*/static CScore *m_pScore;
	/* ���݂̍s��	*/static int m_nCurAction;

	// ***** �ϐ� *****
	CText *m_Txt[3];			// �e�L�X�g
	ACTION Action;				// �s�����
	CreateTxt m_aCreateText;	// �������

	int m_nStartTime;		// �J�n����
	int m_nEndTime;			// �I������
	bool m_bEnd;			// �I���t���O
};

#endif