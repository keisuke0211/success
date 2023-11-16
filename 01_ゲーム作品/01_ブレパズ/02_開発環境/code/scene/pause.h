//========================================
// 
// �|�[�Y
// 
//========================================
// *** pause.h ***
//========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CWords;
class CText;
class CBlackout;

//****************************************
// �N���X
//****************************************
class CPause : public CScene
{
	// ***** ��` *****
	static const int TEXT_MAX = 4;	// �e�L�X�g�̍ő吔

public:

	// ***** �񋓌^ *****

	// ���j���[
	enum MENU
	{
		MENU_RESUME = 0,// �ĊJ
		MENU_RESET,		// ��蒼��
		MENU_TITLE,		// �^�C�g���ɖ߂�
		MENU_MAX
	};

	// ***** �֐� *****
	CPause();
	~CPause();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CPause *Create(void);
	/* ���j���[���� */void MenuCreate(void);
	/* ���j���[		*/void Menu(void);

	// -- �ݒ� --------------------------------------------
	/* �|�[�Y */static void SetPause(bool bPause) { m_bPause = bPause; }

	// -- �擾 --------------------------------------------
	/* �|�[�Y	*/static bool IsPause(void) { return m_bPause; }

private:

	// ***** �ϐ� *****
	static bool m_bPause;
	bool m_Menu;
	int m_nSelectMenu;	// ���ݑI�����Ă��郁�j���[
	CText *m_Text[TEXT_MAX];
	CBlackout *m_Blackout;

};

#endif