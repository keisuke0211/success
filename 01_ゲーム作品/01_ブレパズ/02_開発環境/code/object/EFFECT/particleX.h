//========================================
//
// �p�[�e�B�N���y ���f�� �z
//
//========================================
// *** particleX.h ***
//========================================
#ifndef _PARTICLE_X_H_
#define _PARTICLE_X_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CParticleX : public CObjectX
{
public:

	// ***** �\���� *****

	// �J���[
	struct Color
	{
		D3DXCOLOR col;				// �J���[
		D3DXCOLOR colRandamMax;		// �����_���ȐF�͈̔�(�ő�)
		D3DXCOLOR colRandamMin;		// �����_���ȐF�͈̔�(�ŏ�)
		bool bColRandom;			// �����_���ŐF��ύX���邩
	};

	// �p�[�e�B�N��
	struct Info
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 move;	// �ړ���
		D3DXVECTOR3 speed;	// �ړ���
		Color aColor;		// �J���[
		int nForm;			// ������
		int nType;			// ���
		int nLife;			// ����
		float fRadius;		// ���a
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CParticleX(int nPriority = PRIO_EFFECT);
	virtual~CParticleX();

	// *****  �֐� *****

	/* ���C�� */
	HRESULT Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V

	// ����
	static CParticleX *Create(void);

	/* �ݒ� */
	void Par_SetPos(D3DXVECTOR3 pos) { m_Info.pos = pos; }						// �ʒu
	void Par_SetRot(D3DXVECTOR3 rot) { m_Info.rot = rot; }						// ����
	void Par_SetMove(D3DXVECTOR3 move) { m_Info.speed = move; }					// �ړ���
	void Par_SetType(int nType) { m_Info.nType = nType; }						// ���
	void Par_SetForm(int nForm) { m_Info.nForm = nForm;	}						// ������
	void Par_SetLife(int nLife) { m_Info.nLife  = nLife; }						// ����
	void Par_SetCol(D3DXCOLOR col) { m_Info.aColor.col = col; }					// �F
	void Par_SetRadius(float fRadius) { m_Info.fRadius = fRadius; }				// ���a

private:
	// ***** �ϐ� *****
	Info m_Info;		// ���

};
#endif 