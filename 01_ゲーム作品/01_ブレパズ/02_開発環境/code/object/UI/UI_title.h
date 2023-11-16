//========================================
// 
// �^�C�g���w�i
// 
//========================================
// *** UI_title.h ***
//========================================
#ifndef _UI_TITLE_H_	//���̃}�N����`������ĂȂ�������
#define _UI_TITLE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "../../main.h"
#include "../object2D.h"

//****************************************
//�@�N���X
//****************************************
class CUiTitle : public CObject2D
{
public:

	// ***** �\���� *****

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR2 size;		// �傫��
		D3DXCOLOR col;			// �F
		int nType;				// ���
	};

	// ***** �֐� *****
	CUiTitle(int nPriority = PRIO_OBJECT);
	~CUiTitle();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CUiTitle *Create(void);

private:
	// ***** �ϐ� *****
	Info m_Info;		// ���
};

#endif

