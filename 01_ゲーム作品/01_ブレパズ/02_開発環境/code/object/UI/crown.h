//========================================
// 
// ����
// 
//========================================
// *** corown.h ***
//========================================
#ifndef _CROWN_H_	//���̃}�N����`������ĂȂ�������
#define _CROWN_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "../../main.h"
#include "../object2D.h"

//****************************************
//�@�N���X
//****************************************
class CCrown : public CObject2D
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
	CCrown(int nPriority = PRIO_UI);
	~CCrown();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CCrown *Create(int nType);

private:
	// ***** �ϐ� *****
	Info m_Info;		// ���
};

#endif