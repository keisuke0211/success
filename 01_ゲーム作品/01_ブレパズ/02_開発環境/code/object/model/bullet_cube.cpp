//========================================
// 
// �L���[�u����
// 
//========================================
// *** block.cpp ***
//========================================
#include "model.h"
#include "enemy.h"
#include "block.h"
#include "bullet_cube.h"
#include "../../scene/pause.h"
#include "../EFFECT/particleX.h"
#include "../../system/physics.h"
#include "../../system/sound.h"
#include "../../system/csv_file.h"
#include "../../system/words/text.h"
#include "../../system/words/words.h"
#include "../../system/words/font.h"

// �ÓI�ϐ�
int CCube::m_nNumAll = -1;
int CCube::m_nNumChain = 1;
int CCube::m_nLimitCube = 0;
int CCube::m_nRestCube = 0;
int CCube::m_nUseCube = 0;
bool CCube::bLeadSet = false;
CText *CCube::m_Cube = NULL;

//========================================
// �}�N����`
//========================================
#define RADIUS_TIME			(20)	// ���a�E���ڎ���
#define SIZE_DIAMETER		(2.0f)	// �T�C�Y�̔{��
#define COLLSION_DIAMETER	(1.0f)	// ����̔{��
#define BOM_COLLSION		(2.0f)	// �����̔���
#define DAMAGE_DIAMETER		(2)		// �A�����j�̃_���[�W�̊���		BOM_DAMAGE�@+ (�A���J�E���g / DAMAGE_DIAMETER)
#define BOM_DAMAGE			(1)		// �����_���[�W

//========================================
// �R���X�g���N�^
//========================================
CCube::CCube(int nPriority) : CObjectX(nPriority)
{
	m_nNumAll++;	// ���������Z

	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;		// �ʒu
	m_Info.posOld = INIT_D3DXVECTOR3;	// �ʒu(�ߋ�)
	m_Info.movePos = INIT_D3DXVECTOR3;	// �ړ��ʒu
	m_Info.targetPos = INIT_D3DXVECTOR3;// �ړI�ʒu
	m_Info.rot = INIT_D3DXVECTOR3;		// ����
	m_Info.rotOld = INIT_D3DXVECTOR3;	// ����(�ߋ�)
	m_Info.size = INIT_D3DXVECTOR3;		// �傫��
	m_Info.col = INIT_D3DXCOLOR;		// �F
	m_Info.nShape = -1;					// �`��
	m_Info.nStandTime = 0;				// �ҋ@����
	m_Info.nLife = 0;					// ����
	m_Info.nLifeMax = 0;				// �����̍ő�l
	m_Info.fRadius = 0.0f;				// ���a
	m_Info.nCntRadius = 0;				// ���a����	
	m_Info.fRadiusRate = 0.0f;			// ���a�̊���
	m_Info.bSet = false;				// �z�u�t���O
	m_Info.nChain = 0;					// �A��
	m_Info.bBom = false;				// ����
	m_Info.nID = m_nNumAll;				// �������g��ID
	m_Info.bErase = false;
}

//========================================
// �f�X�g���N�^
//========================================
CCube::~CCube()
{
	m_nNumAll--;	// �������Z
}

//========================================
// ����
//========================================
CCube *CCube::Create(int nShape, D3DXVECTOR3 pos, int nLife)
{
	CCube *pCube = NULL;

	if (pCube != NULL)
	{
		return pCube;
	}

	// �L���[�u�̐���
	pCube = new CCube;

	pCube->m_Info.nCntRadius = RADIUS_TIME;
	pCube->m_Info.fRadiusRate = 0.0f;
	pCube->m_Info.bSet = false;
	pCube->SetModel(MODEL_BULLET + nShape);

	// ����������
	pCube->Init();

	int nCubeLife = nLife;
	
	pCube->m_Info.nShape = nShape;
	pCube->m_Info.nLife = nCubeLife;
	pCube->m_Info.nLifeMax = nCubeLife;
	pCube->SetCubePos(pos);
	pCube->SetPos(pos);

	pCube->m_Info.posOld = pCube->m_Info.pos;

	// �z�u�ꏊ�Ƀv���C���[�����邩
	pCube->ModelCollsion(PRIO_OBJECT, TYPE_PLAYER, VECTOR_NONE, pCube->m_Info.pos);
	pCube->ModelCollsion(PRIO_BLOCK, TYPE_BLOCK, VECTOR_NONE, pCube->m_Info.pos);

	if (pCube->m_Info.bErase)
	{
		pCube->Uninit();
		return NULL;
	}

	// --- �擾 ---------------------------------
	CSound *pSound = CManager::GetSound();

	pSound->PlaySound(CSound::TYPE_SET);

	// �g�p���̉��Z
	m_nUseCube++;

	// �e�L�X�g�̍X�V
	CubeText();

	// �ʒu�␳
	/* X��	*/if (pCube->Correction(VECTOR_X, pCube->m_Info.pos)) { return pCube; }
	/* Y��	*/if (pCube->Correction(VECTOR_Y, pCube->m_Info.pos)) { return pCube;}
	/* Z��	*/if (pCube->Correction(VECTOR_Z, pCube->m_Info.pos)) { return pCube;}

	return pCube;
}

//========================================
// ������
//========================================
HRESULT CCube::Init(void)
{
	CObjectX::Init();

	if (m_nLimitCube - m_nUseCube <= 0)
	{
		Uninit();
		return S_OK;
	}

	// ��ނ̐ݒ�
	SetType(TYPE_CUBE);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Info.col = D3DXCOLOR(0.1f, 0.9f, 0.9f, 1.0f);
	m_Info.nShape = 0;
	m_Info.fRadius = 1.0f;

	// ����
	SetPos(m_Info.pos);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	// �P�ڂ̃L���[�u�Ȃ�
	if (m_Info.nID == 0)
	{
		// �擪�t���O��^�ɂ���
		bLeadSet = true;
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CCube::Uninit(void)
{
	if (m_Info.bSet)
	{
		m_nRestCube--;	// �L���[�u�̎c�萔
	}

	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CCube::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		// �ߋ��̈ʒu�E�����̍X�V
		m_Info.posOld = m_Info.pos;
		m_Info.rotOld = m_Info.rot;

		// ���a����
		if (m_Info.bSet == false)
		{
			m_Info.fRadiusRate = (float)m_Info.nCntRadius / (float)RADIUS_TIME;
			m_Info.fRadius = 1 * (1.0f - m_Info.fRadiusRate);

			if (--m_Info.nCntRadius <= 0)
			{
				m_Info.bSet = true;
			}
		}

		// ��������
		if (m_Info.bSet)
		{
			// ����
			if (--m_Info.nLife <= 0)
			{
				// �P�ڂ̃L���[�u�Ȃ�
				if (m_Info.nID == 0)
				{
					// �擪�t���O���U�ɂ���
					bLeadSet = false;
				}

				// �p�[�e�B�N������
				CParticleX *pObj = CParticleX::Create();
				pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
				pObj->Par_SetRot(INIT_D3DXVECTOR3);
				pObj->Par_SetMove(D3DXVECTOR3(15.0f, 15.0f, 15.0f));
				pObj->Par_SetType(0);
				pObj->Par_SetLife(100);
				pObj->Par_SetCol(D3DXCOLOR(0.3f, 0.8f, 0.8f, 1.0f));
				pObj->Par_SetForm(10);

				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::TYPE_ERASE);

				// ���͂ɃL���[�u�����邩
				Contact(0, VECTOR_X, m_Info.pos);
				Contact(0, VECTOR_Y, m_Info.pos);
				Contact(0, VECTOR_Z, m_Info.pos);

				// �����蔻��
				/* �G		*/ModelCollsion(PRIO_OBJECT, TYPE_ENEMY, VECTOR_X, m_Info.pos);
				/* �G		*/ModelCollsion(PRIO_OBJECT, TYPE_ENEMY, VECTOR_Z, m_Info.pos);
				/* �u���b�N	*/ModelCollsion(PRIO_BLOCK, TYPE_BLOCK, VECTOR_X, m_Info.pos);
				/* �u���b�N	*/ModelCollsion(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.pos);

				// �I�u�W�F�N�g�j��
				Uninit();

				m_nNumChain = 1;

				return;
			}
			else if (m_Info.nLife <= (RADIUS_TIME * 2))
			{
				m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
			}
			else if (m_Info.nLife <= RADIUS_TIME)
			{
				m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
				m_Info.col.a *= ((float)m_Info.nLife / RADIUS_TIME);
			}
		}

		// �T�C�Y�̍X�V
		m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

		SetPos(m_Info.pos);
		SetScale(m_Info.size);
		SetColor(m_Info.col);

		CObjectX::Update();
	}
}

//========================================
// �`��
//========================================
void CCube::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �ʒu�␳
//========================================
bool CCube::Correction(VECTOR vector, D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(PRIO_CUBE);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		//�@����t���O
		bool bHit = false;

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		TYPE type;

		// ��ނ��擾
		type = pObj->GetType();

		if (type == TYPE_CUBE)
		{// ��ނ��L���[�u�̏ꍇ

			// �_�C�i�~�b�N�L���X�g����
			CCube *pCube = dynamic_cast<CCube*>(pObj);

			// ID���擾
			int ID = pCube->GetID();

			if (m_Info.nID != ID)
			{// �����ȊO�̃L���[�u��������A

				// �������g�̎擾
				float fWidth = GetWidth();		// ��
				float fHeight = GetHeight();	// ����
				float fDepth = GetDepth();		// ���s��

				// ����̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();	// �ʒu
				float fPairWidth = pObj->GetWidth();	// ��
				float fPairHeight = pObj->GetHeight();	// ����
				float fPairDepth = pObj->GetDepth();	// ���s��

				//�@���S�_����̋���
				float fCubeWidth = fPairWidth * SIZE_DIAMETER;		// ��
				float fCubeHeight = fPairHeight * SIZE_DIAMETER;	// ����
				float fCubeDepth = fPairDepth * SIZE_DIAMETER;		// ���s��

				// �T�C�Y����
				fPairWidth *= COLLSION_DIAMETER;	// ��
				fPairHeight *= COLLSION_DIAMETER;	// ����
				fPairDepth *= COLLSION_DIAMETER;	// ���s��

				// �e�����̓����蔻��
				D3DXVECTOR3 PairUpPos = D3DXVECTOR3(PairPos.x, PairPos.y + fCubeHeight, PairPos.z);		// ��
				D3DXVECTOR3 PairDownPos = D3DXVECTOR3(PairPos.x, PairPos.y - fCubeHeight, PairPos.z);	// ��
				D3DXVECTOR3 PairLeftPos = D3DXVECTOR3(PairPos.x + fCubeWidth, PairPos.y, PairPos.z);	// ��
				D3DXVECTOR3 PairRightPos = D3DXVECTOR3(PairPos.x - fCubeWidth, PairPos.y, PairPos.z);	// �E
				D3DXVECTOR3 PairBackPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z + fCubeDepth);	// ��
				D3DXVECTOR3 PairFrontPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z - fCubeDepth);	// ��O

				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if (Collsion(pos, PairLeftPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ����
						m_Info.pos = PairLeftPos;
						bHit = true;
						break;
					}

					if (Collsion(pos, PairRightPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// �E��
						m_Info.pos = PairRightPos;
						bHit = true;
						break;
					}
				}
							   break;
				case VECTOR_Y: {	/* Y���� */

					if (Collsion(pos, PairUpPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// �㑤
						m_Info.pos = PairUpPos;
						bHit = true;
						break;
					}

					if (Collsion(pos, PairDownPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ����
						m_Info.pos = PairDownPos;
						bHit = true;
						break;
					}
				}
							   break;
				case VECTOR_Z: {	/* Z���� */

					if (Collsion(pos, PairBackPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ����
						m_Info.pos = PairBackPos;
						bHit = true;
						break;
					}

					if (Collsion(pos, PairFrontPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ��O��
						m_Info.pos = PairFrontPos;
						bHit = true;
						break;
					}
				}
						   break;
				}

				// ���肪�^�Ȃ� TRUE ��Ԃ�
				if (bHit)
				{	
					if (CubeCollsion(m_Info.pos, m_Info.nID))
					{
						m_Info.bErase = true;
					}

					return TRUE;
				}
			}
		}

		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
	return FALSE;
}

//========================================
// �L���[�u�̓����蔻��
//========================================
bool CCube::CubeCollsion(D3DXVECTOR3 pos, int ID)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(PRIO_CUBE);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		TYPE type;

		// ��ނ��擾
		type = pObj->GetType();

		if (type == TYPE_CUBE)
		{// ��ނ��L���[�u�̏ꍇ

			// �_�C�i�~�b�N�L���X�g����
			CCube *pCube = dynamic_cast<CCube*>(pObj);

			// ID���擾
			int nID = pCube->GetID();

			if (ID != nID)
			{// �����ȊO�̃L���[�u��������A

				// �������g�̎擾
				float fWidth = GetWidth();		// ��
				float fHeight = GetHeight();	// ����
				float fDepth = GetDepth();		// ���s��

				// ����̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();	// �ʒu
				float fPairWidth = pObj->GetWidth();	// ��
				float fPairHeight = pObj->GetHeight();	// ����
				float fPairDepth = pObj->GetDepth();	// ���s��

				// �T�C�Y����
				fWidth *= 0.1f;
				fHeight *= 0.1f;
				fDepth *= 0.1f;
				fPairWidth *= 0.5f;
				fPairHeight *= 0.5f;
				fPairDepth *= 0.5f;

				if (Collsion(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{
					return TRUE;
				}
			}
		}

		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
	return FALSE;
}

//========================================
// �ڐG����
//========================================
bool CCube::Contact(int mode, VECTOR vector, D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(PRIO_CUBE);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		bool bHit = false;

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		int ID;
		TYPE type;

		// ��ނ��擾
		type = pObj->GetType();

		if (type == TYPE_CUBE)
		{// ��ނ��L���[�u�̏ꍇ

			// �_�C�i�~�b�N�L���X�g����
			CCube *pCube = dynamic_cast<CCube*>(pObj);

			// ID���擾
			ID = pCube->GetID();

			// �z�u�t���O���擾
			bool bSet = pCube->GetCubeSet();

			if(!pCube->m_Info.bBom)
			{
				if (m_Info.nID != ID && bSet)
				{// �����ȊO�̃L���[�u��������A

					// �������g�̎擾
					float fWidth = GetWidth();		// ��
					float fHeight = GetHeight();	// ����
					float fDepth = GetDepth();		// ���s��

					// ����̎擾
					D3DXVECTOR3 PairPos = pCube->GetPos();	// �ʒu
					float fPairWidth = pCube->GetWidth();	// ��
					float fPairHeight = pCube->GetHeight();	// ����
					float fPairDepth = pCube->GetDepth();	// ���s��

					//�@���S�_����̋���
					float fCubeWidth = fPairWidth * SIZE_DIAMETER;		// ��
					float fCubeHeight = fPairHeight * SIZE_DIAMETER;	// ����
					float fCubeDepth = fPairDepth * SIZE_DIAMETER;		// ���s��

					// �T�C�Y����
					fPairWidth *= COLLSION_DIAMETER;	// ��
					fPairHeight *= COLLSION_DIAMETER;	// ����
					fPairDepth *= COLLSION_DIAMETER;	// ���s��

					// �e�����̓����蔻��
					D3DXVECTOR3 PairUpPos = D3DXVECTOR3(PairPos.x, PairPos.y + fCubeHeight, PairPos.z);		// ��
					D3DXVECTOR3 PairDownPos = D3DXVECTOR3(PairPos.x, PairPos.y - fCubeHeight, PairPos.z);	// ��
					D3DXVECTOR3 PairLeftPos = D3DXVECTOR3(PairPos.x + fCubeWidth, PairPos.y, PairPos.z);	// ��
					D3DXVECTOR3 PairRightPos = D3DXVECTOR3(PairPos.x - fCubeWidth, PairPos.y, PairPos.z);	// �E
					D3DXVECTOR3 PairBackPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z + fCubeDepth);	// ��
					D3DXVECTOR3 PairFrontPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z - fCubeDepth);	// ��O

					switch (vector)
					{
					case VECTOR_X: {	/* X���� */

						if (Collsion(pos, PairLeftPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// ����

							bHit = true;
							break;
						}

						if (Collsion(pos, PairRightPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// �E��

							bHit = true;
							break;
						}
					}
					   break;
					case VECTOR_Y: {	/* Y���� */

						if (Collsion(pos, PairUpPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// �㑤

							bHit = true;
							break;
						}

						if (Collsion(pos, PairDownPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// ����

							bHit = true;
							break;
						}
					}
					   break;
					case VECTOR_Z: {	/* Z���� */

						if (Collsion(pos, PairBackPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// ����

							bHit = true;
							break;
						}

						if (Collsion(pos, PairFrontPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// ��O��

							bHit = true;
							break;
						}
					}
					   break;
					}

					// ���肪�^�Ȃ� TRUE ��Ԃ�
					if (bHit)
					{
						// �A������
						if (mode == 0)
						{
							pCube->Destruction(pCube);
						}
						return TRUE;
					}
				}
			}
		}

		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
	return FALSE;
}

//========================================
// �I�u�W�F�N�g�̓����蔻��
//========================================
void CCube::ModelCollsion(PRIO nPrio, TYPE nType, VECTOR vector,D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(nPrio);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		TYPE type;

		// ��ނ��擾
		type = pObj->GetType();

		if (type == nType)
		{// �I��������ނ̎��A

			// �L���[�u�̎擾
			float fWidth = GetWidth();			// ��
			float fHeight = GetHeight();		// ����
			float fDepth = GetDepth();			// ���s��

			// �T�C�Y����
			if (m_Info.bSet)
			{
				if (vector != VECTOR_Y)
				{
					fHeight *= 0.05f;
				}

				switch (vector)
				{
				case CPhysics::VECTOR_X:
					fWidth *= BOM_COLLSION;
					break;
				case CPhysics::VECTOR_Y:
					fHeight *= BOM_COLLSION;
					break;
				case CPhysics::VECTOR_Z:
					fDepth *= BOM_COLLSION;
					break;
				case CPhysics::VECTOR_NONE:
					fWidth *= BOM_COLLSION;
					fDepth *= BOM_COLLSION;
					break;
				default:
					fWidth *= BOM_COLLSION;
					fDepth *= BOM_COLLSION;
					break;
				}
			}

			// ����̎擾
			D3DXVECTOR3 PairPos = pObj->GetPos();		// �ʒu
			D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// �ʒu(�ߋ�)
			float fPairWidth = pObj->GetWidth();		// ��
			float fPairHeight = pObj->GetHeight();		// ����
			float fPairDepth = pObj->GetDepth();		// ���s��

			if (nType == TYPE_ENEMY)
			{// �I��������ނ̎��A
				fPairHeight = 24.0f;
			}

			// �����蔻��
			if (Collsion(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
			{// ����������

				switch (nType)
				{
				case TYPE_ENEMY:
				{
					// �_�C�i�~�b�N�L���X�g����
					CEnemy *pEnemy = dynamic_cast<CEnemy*>(pObj);

					// HIT����
					pEnemy->HitLife(BOM_DAMAGE + (m_Info.nChain / DAMAGE_DIAMETER));
				}
					break;
				case TYPE_PLAYER:
				{
					m_Info.bErase = true;
				}
				break;

				case TYPE_BLOCK:
				{
					// �_�C�i�~�b�N�L���X�g����
					CBlock *pBlock = dynamic_cast<CBlock*>(pObj);

					if (m_Info.bSet)
					{
						CBlock::STATE state = pBlock->GetBlockState();
						int nBlockType = pBlock->GetBlockType();

						if (state == CBlock::STATE_BREAK && nBlockType != MODEL_IRON_BOX)
						{
							// Hit����
							pBlock->HitBlock();
						}
					}
					else if (!m_Info.bSet)
					{
						CBlock::STATE aState = pBlock->GetBlockState();
						if (aState == CBlock::STATE_ALLIE)
						{// ��Ԃ��ђʂȂ�
							m_Info.bErase = true;
						}
					}
				}
				break;
				}
				
			}
		}

		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
}

//========================================
// �j�󏈗�
//========================================
void CCube::Destruction(CCube *pCube)
{
	// �I�u�W�F�N�g�j��
	pCube->m_Info.nLife = 10 + m_nNumChain;
	pCube->m_Info.bBom = true;

	m_nNumChain++;	// �A���J�E���g�����Z

	// �A���J�E���g����
	pCube->m_Info.nChain = m_nNumChain;

	// ���͂ɃL���[�u�����邩
	pCube->Contact(0, VECTOR_X, pCube->m_Info.pos);
	pCube->Contact(0, VECTOR_Y, pCube->m_Info.pos);
	pCube->Contact(0, VECTOR_Z, pCube->m_Info.pos);
}

//========================================
// �g�p���̐ݒ�
//========================================
void CCube::SetLimit(int nLimit)
{
	m_nRestCube = nLimit;
	m_nUseCube = 0;
	m_nLimitCube = nLimit;

	// �������𕶎���ɐݒ�
	char aString[TXT_MAX];
	sprintf(aString, "CUBE �F%02d", m_nRestCube);

	FormFont pFont = {
		INIT_D3DXCOLOR,
		11.0f,
		1,
		10,
		-1
	};

	FormShadow pShadow = {
		D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),
		true,
		D3DXVECTOR3(2.0f,2.0f,0.0f),
		D3DXVECTOR2(1.0f,1.0f)
	};

	m_Cube = CText::Create(CText::BOX_NORMAL_RECT,
		D3DXVECTOR3(SCREEN_WIDTH - 290.0f, 42.0f, 0.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		aString,
		CFont::FONT_BESTTEN,
		&pFont, false, &pShadow);
}

//========================================
// ���Z�b�g
//========================================
void CCube::Reset(void)
{
	m_nNumAll = -1;
	m_nRestCube = 0;
	m_nUseCube = 0;
	m_nNumChain = 1;
	m_nLimitCube = 0;
	bLeadSet = false;

	if (m_Cube != NULL)
	{
		m_Cube = NULL;
	}
}

//========================================
// �e�L�X�g
//========================================
void CCube::CubeText(void)
{
	int nNumSet = 0;
	D3DXCOLOR col;
	int nRest = m_nLimitCube - m_nUseCube;
	char aString[TXT_MAX];

	if (nRest <= 0)
	{
		nRest = 0;
	}
	sprintf(aString, "%02d", nRest);

	// �������擾
	int m_Digit = strlen(aString);

	if (nRest <= 0)
	{
		col = D3DXCOLOR(0.45f, 0.45f, 0.45f, 1.0f);
	}
	else if (nRest <= m_nLimitCube / 3)
	{
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (nRest <= m_nLimitCube * 2/3)
	{
		col = D3DXCOLOR(0.8f,0.8f,0.0f,1.0f);
	}
	else if (nRest <= m_nLimitCube)
	{
		col = INIT_D3DXCOLOR;
	}


	for (int nTime = 0; nTime < m_Digit; nTime++)
	{
		m_Cube->ChgWords(&aString[nTime], CUBE_START_DEX + nTime, col);
	}
}