//========================================
// 
// �^�C�g��
// 
//========================================
// *** title.h ***
//========================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CWords;
class CText;
class CStage;

//****************************************
// �N���X
//****************************************
class CTitle : public CScene
{
	// ***** ��` *****
	static const char* TEXT_FILE_PATH;	// �ǂݍ��ރt�@�C���p�X
	static const int STAND_MAX = 20;	// �e�L�X�g�̑ҋ@����
	static const int TEXT_TIME = 150;	// �e�L�X�g�̕\������
	static const int WORDS_MAX = 4;		// �����̍ő吔
	static const int STAGE_MAX = 6;		// �X�e�[�W�摜�̍ő吔

public:

	// ***** �񋓌^ *****

	// �^�C�g�����[�h
	enum TITLE
	{
		TITLE_OUTSET = 0,	// �^�C�g��
		TITLE_MENU,			// ���j���[
		TITLE_NEXT,			// ���̉�ʂɈړ� 
		TITLE_MAX
	};

	// ���j���[
	enum MENU
	{
		MENU_GAME = 0,	// �Q�[��
		MENU_TUTORIAL,	// �`���[�g���A��
		MENU_RANKING,	// �����L���O
		MENU_END,		// �I��
		MENU_MAX
	};

	// ***** �֐� *****
	CTitle();
	~CTitle();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CTitle *Create(void);
	/* �^�C�g��		*/void TitleAnime(void);
	/* ���j���[���� */void MenuCreate(void);
	/* ���j���[		*/void Menu(void);
	/* �e�L�X�g�폜 */void TextClear(int nWords,int nText, TITLE aTitle);

	// -- �ݒ� ------------------------------------------
	/* �J�n		*/static void SetStart(bool bStart) { m_bStart = bStart; }
	/* �N���A	*/static void SetClear(bool bClear) { m_bClear = bClear; }

	// -- �擾 ------------------------------------------
	/* �J�n			*/static bool IsStart() { return m_bStart; }
	/* �N���A		*/static bool IsClear() { return m_bClear; }

private:

	// ***** �֐� *****
	/* �e�L�X�g�ǂݍ���	*/void TextLoad(void);

	// ***** �ÓI�ϐ� *****
	static bool m_bStart;	// �J�n�t���O
	static bool m_bClear;	// �N���A�t���O

	// ***** �ϐ� *****
	TITLE Title;				// ���݂̃��[�h
	CWords *m_Words[4];			// �^�C�g��
	CWords *m_WordsShadow[4];	// �^�C�g���E�e
	bool m_bMove[4];			// �^�C�g���ړ��t���O
	CText *m_Menu[MENU_MAX];	// ���j���[�e�L�X�g
	int m_nTextTime;			// �e�L�X�g�̕\������
	int m_nStandTime;			// �ҋ@����
	int m_nSelectMenu;			// ���ݑI�����Ă��郁�j���[
};

#endif