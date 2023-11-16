//========================================
// 
// �u���b�N����
// 
//========================================
// *** block.h ***
//========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CBlock : public CObjectX
{
public:

	// ���
	enum STATE
	{
		STATE_NORMAL = 0,	// �ʏ�
		STATE_BREAK,		// �j���
		STATE_ALLIE,		// �ђ�
		STATE_MAX,
	};

	// ***** �\���� *****

	// ��ޏ��
	struct TypeInfo
	{
		int nModelID;	// ���f��ID
		int nState;		// ���
	};

	// �u���b�N���
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotOld;		// ����(�ߋ�)
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		int nModelID;			// ���
		STATE state;			// ���
		float fRadius;			// ���a
		int nCntRadius;			// ���a�E���ڎ���
		float fRadiusRate;		// ���a�̊���
		bool bSet;				// �z�u�t���O
		int nID;				// ���g��ID

		int nEraseTime;			// �����܂ł̎���
		bool bErase;			// �����t���O
	};

	// ***** �֐� *****
	CBlock(int nPriority = PRIO_BLOCK);
	~CBlock();

	// ����
	static CBlock *Create(int nType,D3DXVECTOR3 pos,int nState);

	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* �ǂݍ���		*/static void Load(void);
	/* HIT			*/void HitBlock(void);
	
	// -- �ݒ� ---------------------------------------------
	/* �ʒu		*/virtual void SetBlockPos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	/* ����		*/void SetBlockRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* �F		*/void SetBlockColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* �傫��	*/void SetBlockSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	/* ���Z�b�g	*/static void Reset(void);

	// -- ���� ---------------------------------------------
	/* �ʒu		*/D3DXVECTOR3 GetBlockPos(void) { return m_Info.pos; }
	/* ����		*/D3DXVECTOR3 GetBlockRot(void) { return m_Info.rot; }
	/* �F		*/D3DXCOLOR GetBlockColor(void) { return m_Info.col; }
	/* �傫��	*/D3DXVECTOR3 GetBlockSize(void) { return m_Info.size; }
	/* ���		*/STATE GetBlockState(void) { return m_Info.state; }
	/* ���		*/int GetBlockType(void) { return m_Info.nModelID; }
	/* ID		*/int GetID(void) { return m_Info.nID; }

private:	

	// ***** �֐� *****
	/* ��������		*/void BombCollsion(PRIO nPrio, TYPE nType, VECTOR vector,D3DXVECTOR3 pos);
	/* �����蔻��	*/D3DXVECTOR3 Collision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos);
	/* ���e			*/void Bomb(void);
	/* �ؔ�			*/void WoodenBox(void);
	/* �S��			*/void IronBox(void);

	// ***** �ϐ� *****
	static int m_nNumAll;			// �L���[�u�̑���
	static D3DXVECTOR3 m_CameraRot;	// �����̕ۑ�
	static float m_CameraHeigth;	// �����̕ۑ�

	Info m_Info;					// �u���b�N���
	static TypeInfo *m_TypeInfo;	// ��ޏ��

};
#endif