//========================================
// 
// �Ó]
// 
//========================================
// *** blackout.h ***
//========================================
#ifndef _BLACKOUT_H_	//���̃}�N����`������ĂȂ�������
#define _BLACKOUT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "../../main.h"
#include "../object2D.h"

//****************************************
//�@�N���X
//****************************************
class CBlackout : public CObject2D
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
	CBlackout(int nPriority = PRIO_UI);
	~CBlackout();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CBlackout *Create(void);

private:
	// ***** �ϐ� *****
	Info m_Info;		// ���
};

#endif