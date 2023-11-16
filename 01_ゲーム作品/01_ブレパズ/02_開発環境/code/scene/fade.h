//========================================
// 
// �t�F�[�h
// 
//========================================
// *** fade.h ***
//========================================
#ifndef _FADE_H_
#define _FADE_H_

#include "../main.h"
#include "../manager.h"
#include "../object/object2D.h"

//****************************************
// �N���X
//****************************************
class CFade : public CObject2D
{

public:
	static const int FADE_TRANSITION = 25;	// �t�F�[�h���ڒl  FADE_TRANSITION / 1000

	// ***** �񋓌^ *****

	// �t�F�[�h�̏��
	enum FADE
	{
		FADE_NONE = 0,	// �������Ă��Ȃ����
		FADE_IN,		// �t�F�[�h�C�����
		FADE_OUT,		// �t�F�[�h�A�E�g���
		FADE_MAX,
	};

	// ***** �֐� *****
	CFade(int nPriority = PRIO_FADE);
	virtual~CFade();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	// -- �ݒ� --------------------------------------------
	/* �t�F�[�h	*/void SetFade(CScene::MODE modeNext);

	// -- �擾 --------------------------------------------
	/* ���	*/static FADE GetFade(void) { return m_fade; }


private:

	// ***** �ϐ� *****
	static FADE m_fade;				// �t�F�[�h���
	static CScene::MODE m_modeNext;	// ���̉��(���[�h)
	D3DXCOLOR m_color;				// �t�F�[�h�J���[
};

#endif