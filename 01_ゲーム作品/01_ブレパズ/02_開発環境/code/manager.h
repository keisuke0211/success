//========================================
// 
// �}�l�[�W���[����
// 
//========================================
// *** manager.h ***
//========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "object\object.h"

//****************************************
// �O���錾
//****************************************
class CRenderer;		// �����_���[
class CCamera;			// �J����
class CLight;			// ���C�g
class CSound;			// �T�E���h
class CTexture;			// �e�N�X�`��
class CKeyboard;		// �L�[�{�[�h
class CMouse;			// �}�E�X
class CJoypad;			// �W���C�p�b�g
class CFont;			// �t�H���g
class CTitle;			// �^�C�g��
class CTutorial;		// �`���[�g���A��
class CGame;			// �Q�[��
class CResult;			// ���U���g
class CRanking;			// �����L���O
class CPause;			// �|�[�Y
class CFade;			// �t�F�[�h

//****************************************
// �N���X
//****************************************

// ��ʃN���X
class CScene : public CPhysics
{
public:

	// ***** �񋓌^ *****

	// ���[�h
	enum MODE
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_RANKING,	// �����L���O
		MODE_MAX
	};

	// ***** �֐� *****
	CScene();
	virtual~CScene();

	// -- ���C�� ------------------------------------------
	/* ����			*/static CScene *Create(MODE mode);
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);

	// -- �擾 ------------------------------------------
	/* ���[�h�擾		*/static CScene::MODE GetMode(void);
	/* �^�C�g��			*/static CTitle *GetTitle() { return m_pTitle; }
	/* �`���[�g���A��	*/static CTutorial *GetTutorial() { return m_pTutorial; }
	/* �Q�[��			*/static CGame *GetGame() { return m_pGame; }
	/* �����L���O		*/static CRanking *GetRanking() { return m_pRanking; }
	/* �|�[�Y			*/static CPause *GetPause() { return m_pPause; }

private:

	// ***** �ϐ� *****
	/* �^�C�g��			*/static CTitle *m_pTitle;
	/* �`���[�g���A��	*/static CTutorial *m_pTutorial;
	/* �Q�[��			*/static CGame *m_pGame;
	/* �����L���O		*/static CRanking *m_pRanking;
	/* �|�[�Y			*/static CPause	*m_pPause;

	static MODE m_mode;		// ���[�h���
};

// �}�l�[�W���[�N���X
class CManager
{
public:

	// ***** �֐� *****
	CManager();
	virtual~CManager();

	/* ������	*/HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	// -- �ݒ� ----------
	/* ���[�h */static void SetMode(CScene::MODE mode);

	// -- �擾 --------------------------------------
	/* �����_���[	*/static CRenderer *GetRenderer() { return m_pRenderer; }
	/* �J����		*/static CCamera *GetCamera() { return m_pCamera; }
	/* ���C�g		*/static CLight *GetLight() { return m_pLight; }
	/* �T�E���h		*/static CSound *GetSound() { return m_pSound; }
	/* �e�N�X�`��	*/static CTexture* GetTexture(){ return m_pTexture; }
	/* �L�[�{�[�h	*/static CKeyboard* GetInputKeyboard() { return m_InputKeyboard; }
	/* �}�E�X		*/static CMouse* GetInputMouse() { return m_InputMouse; }
	/* �W���C�p�b�g	*/static CJoypad* GetInputJoypad() { return m_InputJoypad; }
	/* �t�H���g		*/static CFont*	GetFont() { return m_pFont; }
	/* �t�F�[�h		*/static CFade *GetFade() { return m_pFade; }

private:
	/* �����_���[	*/static CRenderer *m_pRenderer;
	/* �J����		*/static CCamera *m_pCamera;
	/* ���C�g		*/static CLight *m_pLight;
	/* �T�E���h		*/static CSound *m_pSound;
	/* �e�N�X�`��	*/static CTexture *m_pTexture;
	/* �L�[�{�[�h	*/static CKeyboard *m_InputKeyboard;
	/* �t�H���g		*/static CFont *m_pFont;
	/* �}�E�X		*/static CMouse* m_InputMouse;
	/* �W���C�p�b�g	*/static CJoypad* m_InputJoypad;
	/* �V�[��		*/static CScene *m_pScene;
	/* �t�F�[�h		*/static CFade *m_pFade;

};

#endif