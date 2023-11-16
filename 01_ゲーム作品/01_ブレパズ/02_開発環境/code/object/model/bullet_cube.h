//========================================
// 
// �L���[�u����
// 
//========================================
// *** bullet_cube.h ***
//========================================
#ifndef _BULLET_CUBE_H_
#define _BULLET_CUBE_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �O���錾
//****************************************
class CText;

//****************************************
// �N���X
//****************************************
class CCube : public CObjectX
{
	// ��`
	static const int CUBE_START_DEX = 6;	// �L���[�u�̊J�n�ʒu
public:

	// ***** �񋓌^ *****

	// ���f�����
	enum SHAPE
	{
		SHAPE_LINE = 0,	// ����
		SHAPE_SQUARE,	// �l�p
		SHAPE_MAX
	};

	// ***** �\���� *****

	// �L���[�u���
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 movePos;	// �ړ��ʒu
		D3DXVECTOR3 targetPos;	// �ڕW�ʒu	
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotOld;		// ����(�ߋ�)
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		int nShape;				// �`��
		int nStandTime;			// �ҋ@����
		int nLife;				// ����
		int nLifeMax;			// �����̍ő�l
		float fRadius;			// ���a
		int nCntRadius;			// ���a�E���ڎ���
		float fRadiusRate;		// ���a�̊���
		bool bSet;				// �z�u�t���O
		int nChain;				// �A���J�E���g
		bool bBom;				// �����t���O
		bool bErase;			// ���Ńt���O
		int nID;				// ���g��ID
	};

	// ***** �֐� *****
	/* �R���X�g���N�^	*/CCube(int nPriority = PRIO_CUBE);
	/* �f�X�g���N�^		*/~CCube();

	// -- ���C�� -------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CCube *Create(int nType, D3DXVECTOR3 pos,int nLife);
	/* �e�L�X�g */static void CubeText(void);


	// -- �ݒ� -------------------------------
	/* �ʒu			*/void SetCubePos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	/* ����			*/void SetCubeRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* �F			*/void SetCubeColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* �T�C�Y		*/void SetCubeSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	/* ����			*/void SetCubeLife(const int nLife) { m_Info.nLife = nLife; }
	/* ���			*/void SetCubeType(const int type) { m_Info.nShape = type; }
	/* �擪�t���O	*/static void SetCubeLead(const bool bSet) { bLeadSet = bSet; }
	/* ������		*/static void SetLimit(int nLimit);
	/* ���Z�b�g		*/static void Reset(void);

	// -- �擾 -------------------------------
	/* �ʒu			*/D3DXVECTOR3 GetCubeos(void) { return m_Info.pos; }
	/* ����			*/D3DXVECTOR3 GetCubeRot(void) { return m_Info.rot; }
	/* �F			*/D3DXCOLOR GetCubeColor(void) { return m_Info.col; }
	/* �T�C�Y		*/D3DXVECTOR3 GetCubeSize(void) { return m_Info.size; }
	/* �z�u�t���O	*/bool GetCubeSet(void) { return m_Info.bSet; }
	/* �擪�t���O	*/static bool GetLeadSet(void) { return bLeadSet; }
	/* �A���J�E���g	*/int GetChain(void) { return m_Info.nChain; }
	/* ID			*/int GetID(void) { return m_Info.nID; }
	/* ����			*/static int GetNumAll(void) { return m_nNumAll; }
	/* �c�萔		*/static int GetRest(void) { return m_nRestCube; }
	/* ������		*/static int GetLimit(void) { return m_nLimitCube; }
	/* �g�p��		*/static int GetUse(void) { return m_nUseCube; }

private:

	// ***** �֐� *****
	/* �ʒu�␳				*/bool Correction(VECTOR vector, D3DXVECTOR3 pos);
	/* �ڐG����				*/bool Contact(int mode,VECTOR vector, D3DXVECTOR3 pos);
	/* �����蔻��			*/void ModelCollsion(PRIO nPrio, TYPE nType, VECTOR vector,D3DXVECTOR3 pos);
	/* �L���[�u�̓����蔻��	*/bool CubeCollsion(D3DXVECTOR3 pos,int ID);
	/* �j�󏈗�				*/void Destruction(CCube *pCube);

	// ***** �ϐ� *****
	static int m_nNumAll;		// �L���[�u�̑���
	static int m_nRestCube;		// �L���[�u�̎c�萔
	static int m_nUseCube;		// �L���[�u�̎g�p��
	static int m_nNumChain;		// �A���̑���
	static bool bLeadSet;		// �擪�z�u�t���O
	static int m_nLimitCube;	// �X�e�[�W�Ō��Ă�L���[�u�̐�����
	Info m_Info;				// �v���C���[���
	static CText *m_Cube;		// �e�L�X�g�\��
};
#endif