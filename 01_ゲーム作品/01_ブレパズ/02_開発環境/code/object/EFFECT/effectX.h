//========================================
//
// �G�t�F�N�g�y ���f�� �z
//
//========================================
// *** effectX.h ***
//========================================
#ifndef _EFFECT_X_H_
#define _EFFECT_X_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CEffectX : public CObjectX
{
public:

	// ***** �\���� *****

	// �G�t�F�N�g���
	struct Info
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 posOld;	// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3	size;	// �T�C�Y
		D3DXVECTOR3 move;	// �ړ���
		D3DXCOLOR col;		// ���_�J���[
		int nType;			// ���
		int nLife;			// ����
		int nLifeMax;		// �����ő�l
		float fRadius;		// ���a
	};

	// ***** �֐� *****
	CEffectX(int nPriority = PRIO_EFFECT);
	virtual~CEffectX();

	/* ���C�� */

	// ����
	static CEffectX *Create(void);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	/* �ݒ� */
	void Eff_SetPos(D3DXVECTOR3 pos) { m_Info.pos = pos; }						// �ʒu
	void Eff_SetRot(D3DXVECTOR3 rot) { m_Info.rot = rot; }						// ����
	void Eff_SetMove(D3DXVECTOR3 move) { m_Info.move = move; }					// �ړ���
	void Eff_SetType(int nType) { m_Info.nType = nType; }						// ���
	void Eff_SetLife(int nLife) { m_Info.nLife = m_Info.nLifeMax = nLife; }		// ����
	void Eff_SetCol(D3DXCOLOR col) { m_Info.col = col; }						// �F
	void Eff_SetRadius(float fRadius) { m_Info.fRadius = fRadius; }				// ���a

	/* �擾 */
	Info GetInfo() { return m_Info; }					// �G�l�~�[���
	D3DXVECTOR3 GetPos() { return m_Info.pos; }			// �ʒu
	D3DXVECTOR3 GetPosOld() { return m_Info.posOld; }	// �ʒu(�ߋ�)

private:

	// ***** �ϐ� *****
	Info m_Info;			// ���

};
#endif