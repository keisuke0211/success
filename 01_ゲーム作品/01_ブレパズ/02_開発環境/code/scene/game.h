//========================================
// 
// �Q�[��
// 
//========================================
// *** game.h ***
//========================================
#ifndef _GAME_H_
#define _GAME_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CTime;	// �^�C��
class CScore;	// �X�R�A
class CPlayer;	// �v���C���[
class CText;	// �e�L�X�g

//****************************************
// �N���X
//****************************************
class CGame : public CScene
{
	static const int ADDTIME_MAX = 90;		// �{�[�i�X���X�R�A�ɉ��Z���鎞��
	static const int MAX_CUBE = 30;			// �X�e�[�W�Ŕz�u�o����L���[�u�̐���
	static const char* STAGE_INFO_FILE;		// �X�e�[�W���̃t�@�C���p�X
	static const char* SIDE_STAGE_FILE;		// ���ʂ̃t�@�C��
	static const char* FLOOR_STAGE_FILE;	// ���̃t�@�C��

	static const int TIME_SCORE = 50;		// �P�b�̃X�R�A�̉��Z�l
	static const int CUBE_SCORE = 200;		// �P�̃X�R�A�̉��Z�l

public:

	// ***** �񋓌^ *****

	// �X�e�[�W
	enum Stage
	{
		STAGE_00 = 0,
		STAGE_01,
		STAGE_02,
		STAGE_03,
		STAGE_04,
		STAGE_MAX
	};

	// ***** �֐� *****
	CGame();
	virtual~CGame();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CGame *Create(void);
	
	// -- �ǂݍ��� ------------------------------------------
	/* �X�e�[�W���	*/static void LoodStage(void);
	/* �w�i�@�V��	*/static void LoodCeiling(void);
	/* �w�i�@����	*/static void LoodSide(void);
	/* ��			*/static void LoodFloor(void);
	/* �u���b�N		*/static void LoodBlock(void);
	/* �G�l�~�[		*/static void LoodEnemy(void);

	// -- �ݒ� ------------------------------------------
	/* �X�e�[�W�I��	*/static void SetStage(int nStage);
	/* ���Z�b�g		*/static void Reset(void);

	// -- �擾 ------------------------------------------
	/* �v���C���[	*/static CPlayer *GetPlayer() { return m_pPlayer; }
	/* �^�C��		*/static CTime *GetTime() { return m_pTime; }
	/* �X�R�A		*/static CScore *GetScore() { return m_pScore; };
	/* ����			*/static bool IsTime() { return m_bTime; }
	/* �I��			*/static bool IsEnd() { return m_bEnd; }
	
	// �X�e�[�W���
	struct StageInfo
	{
		int nTime[STAGE_MAX];
		int nCube[STAGE_MAX];
		int nClearBonus[STAGE_MAX];
		char aBlockFile[STAGE_MAX][TXT_MAX];
		char aEnemyFile[TXT_MAX];
		D3DXVECTOR3 PlayerPos[STAGE_MAX];
		float PlayerRot[STAGE_MAX];
	};

	static StageInfo m_aStageInfo;

private:

	// ***** �񋓌^ *****

	// ���U���g���o
	enum Rst
	{
		RST_TEXT = 0,	// �N���A�{�[�i�X�I
		RST_TIME,		// �^�C���{�[�i�X(�e�L�X�g)
		RST_TIME_CALC,	// �^�C���{�[�i�X(�v�Z)
		RST_CLEAR,		// �N���A�{�[�i�X(�e�L�X�g)
		RST_CLEAR_CALC,	// �N���A�{�[�i�X(���l)
		RST_BONUS,		// �{�[�i�X�̍��v(�e�L�X�g)
		RST_BONUS_CALC,	// �{�[�i�X�̍��v(�v�Z)
		RST_ADD_SCORE,	// �X�R�A���Z
		RST_STAND,		// �ҋ@
		RST_END,		// �����L���O��ʂɈړ�
		RST_MAX
	};

	// �Q�[���]��
	enum Eve
	{
		EVE_PERFECT = 0,	// �p�[�t�F�N�g Perfect
		EVE_GREAT,			// �O���C�g�@great
		EVE_USUALLY,		//�@���[�W���A���[ usually
		EVE_MAX
	};

	// ***** �֐� *****
	/* ���U���g	*/void  Result(void);

	// ***** �ϐ� *****
	/* �v���C���[	*/static CPlayer *m_pPlayer;
	/* �^�C��		*/static CTime *m_pTime;
	/* �X�R�A		*/static CScore *m_pScore;

	D3DXVECTOR3 m_rot;					// ����
	float m_nMoveRot;					// �����̉����x
	int m_nStartTime;					// �J�n����
	int m_nEndTime;						// �I������
	int m_nRstStgType;					// ���U���g���o�̎��
	int m_nTextCreate;					// ���̃e�L�X�g�̐�������܂ł̎���

	int m_nTimeTotal;					// �^�C���{�[�i�X�̍��v�l
	int m_nClearTotal;					// �N���A�{�[�i�X�̍��v�l
	int m_nTotal;						// �S�Ă̍��v�l
	int m_nAddTime;						// �X�R�A�̉��Z����
	int m_nStandTime;					// �ҋ@����(���U���g���o�I����)
	int m_nEveGame;						// �Q�[���]��
	CText *m_RstText[RST_ADD_SCORE];	// �e�L�X�g�\��
	bool m_bAddScore;					// �X�R�A�̉��Z�t���O
	bool m_bSpecial;					// ����N���A
	static bool m_bTime;				// ���ԃt���O
	static int m_nScore;				// �X�R�A�̕ۑ��p
	static int m_nStage;				// ���݂̃X�e�[�W 
	static int m_nSelectStage;			// ���ݑI�����Ă���X�e�[�W 
	static bool m_bEnd;					// �I���t���O
	static bool m_bGemeOver;			// �Q�[���I�[�o�[

	int nCntTest;
	int nCntTime;
};

#endif