//========================================
// 
// �t�H���g
// 
//========================================
// *** font.h ***
//========================================
#ifndef _FONT_H_
#define _FONT_H_

#include "../../main.h"

//****************************************
// �N���X
//****************************************
class CFont
{

public:

	static const char* s_FileName[];	// �t�@�C���p�X
	static const char* s_FontName[];	// �t�@�C���p�X

	// ***** �񋓌^ *****

	// �t�H���g
	enum FONT
	{
		FONT_BESTTEN = 0,
		FONT_NOSUTARU,
		FONT_FZGONTA,
		FONT_MEIRIO,
		FONT_MAX,
		FONT_NONE,
	};

	// ***** �֐� *****
	CFont();
	~CFont();

	// -- ���C�� ------------------------------------------
	/* �t�H���g�쐬		*/void FontCreate(FONT nFont);
	/* �e�N�X�`���쐬	*/void TextureCreate(string nWords, FONT nFont);
	/* �S�Ĕj��			*/void ReleaseAll(void);
	/* �w��̔j��		*/void Release(FONT nFont);

	// -- �擾 ------------------------------------------
	/* �e�N�X�`�����̎擾 */LPDIRECT3DTEXTURE9 GetFont(string words, FONT nFont);

private:	

	// ***** �ϐ� *****
	HFONT  m_hFont[FONT_MAX];
	LOGFONT m_logFont[FONT_MAX];
	LPDIRECT3DTEXTURE9 m_texFont[FONT_MAX];	// �e�N�X�`���̏��
};

#endif