//========================================
// 
// �e�L�X�g(2D)
// 
//========================================
// *** text2D.h ***
//========================================
#ifndef _TEXT2D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _TEXT2D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "../object.h"
#include "../../main.h"

//****************************************
// �O���錾
//****************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//****************************************
// �N���X
//****************************************
class CText2D :public CObject 
{
	static const int START_CHAR = (int)'!';				// �J�n�����ԍ�
	static const int PTN_WIDTH = 8;						// �p�^�[����
	static const int PTN_HEIGHT = 8;					// �p�^�[������
	static const int PTN_MAX = PTN_WIDTH * PTN_HEIGHT;	// �p�^�[���ő�l

public:
	// ***** �񋓌^ *****

	// �\���`��
	enum DISPLAY
	{
		DISPLAY_CENTER,	// ��������
		DISPLAY_LEFT,	// ������
		DISPLAY_RIGHT,	// �E����
		DISPLAY_MAX,
	};

	// ***** �֐� *****
	CText2D(int nPriority = PRIO_UI);
	virtual~CText2D();
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	/* �ݒ� */
	void SetString(char *pString);					// ������
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu
	void SetDisp(DISPLAY disp) { m_disp = disp; }	// �\���`��

	// �T�C�Y
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }

	// *** �ÓI�֐� ***
	static CText2D *Create(void);		// ��������

private:
	// ***** �ϐ� *****
	CObject2D *m_apObject2D[TXT_MAX];	// �I�u�W�F�N�g2D�̃|�C���^�z��
	char m_aString[TXT_MAX];			// ������̃|�C���^
	DISPLAY m_disp;		// �\���`��
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	float m_fWidth;		// ��
	float m_fHeight;	// ����
};

#endif