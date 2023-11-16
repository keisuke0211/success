//========================================
// 
// �e����
// 
//========================================
// *** bullet.h ***
//========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CBullet : public CObjectX
{
public:

	// ***** �\���� *****

	// �e���
	struct Info
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 posOld;	// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 rotOld;	// ����(�ߋ�)
		D3DXVECTOR3 move;	// �ړ���
		D3DXVECTOR3	size;	// �T�C�Y
		D3DCOLOR col;		// ���_�J���[
		int nType;			// ���
		int nLife;			// ����

		float fWidth;		// ��
		float fHeight;		// ����
		bool bHit;			// �q�b�g�t���O
		int nID;			// ���g��ID
	};

	// ***** �֐� *****
	CBullet(int nPriority = PRIO_OBJECT);
	~CBullet();

	/* ���C�� */

	// ����
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ���Z�b�g	*/static void Reset(void);

	/* �擾 */
	/* �e���		*/Info GetInfo() { return m_Info; }
	/* �ʒu			*/D3DXVECTOR3 GetPos() { return m_Info.pos; }
	/* �ʒu(�ߋ�)	*/D3DXVECTOR3 GetPosOld() { return m_Info.posOld; }
	/* ����			*/D3DXVECTOR3 GetRot() { return m_Info.rot; }
	/* �ړ���		*/D3DXVECTOR3 GetMove() { return m_Info.move; }
	/* ���			*/int GetType(void) { return m_Info.nType; }
	/* ID			*/int GetID(void) { return m_Info.nID; }
	/* ����			*/static int GetNumAll(void) { return m_nNumAll; }

private:

	// ***** �֐� *****
	bool Collsion(VECTOR vector, D3DXVECTOR3 pos);	// �����蔻��

	// ***** �ϐ� *****
	static int m_nNumAll;	// �o���b�g�̑���
	Info m_Info;			// ���
};
#endif