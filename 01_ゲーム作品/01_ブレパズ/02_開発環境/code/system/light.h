//========================================
// 
// ���C�g����
// 
//========================================
// *** light.h ***
//========================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../main.h"

#define NUM_LIGHT			(3)		//���C�g�̐�
#define LIGHT_CLOR			(1.0f)	//�S�̂̃��C�g�F
//****************************************
// �N���X
//****************************************
class CLight
{
public:

	// ���C�g���
	typedef struct
	{
		// �ʒu�֘A
		D3DXVECTOR3	rot;	// ����
		D3DXCOLOR	col;	// �F
	}Light;

	// ***** �֐� *****
	CLight();	// �R���X�g���N�^
	~CLight();	// �f�X�g���N�^

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

private:

	// ***** �ϐ� *****
	D3DLIGHT9 m_lihgt;				// ���C�g�̏��
	D3DLIGHT9 m_aLight[NUM_LIGHT];	// ���C�g���

	const Light m_lihgtInformation[NUM_LIGHT] =
	{
		{ D3DXVECTOR3(-0.9f , -0.9f , 0.5f),D3DXCOLOR(LIGHT_CLOR, LIGHT_CLOR, LIGHT_CLOR, 1.0f) },	// ��E�O
		{ D3DXVECTOR3(0.2f , 0.9f , -0.2f)	,D3DXCOLOR(LIGHT_CLOR, LIGHT_CLOR, LIGHT_CLOR, 1.0f) },	// ��
		{ D3DXVECTOR3(0.9f , -0.9f , -0.5f),D3DXCOLOR(LIGHT_CLOR, LIGHT_CLOR, LIGHT_CLOR, 1.0f) },	// �E�E��
	};
};
#endif