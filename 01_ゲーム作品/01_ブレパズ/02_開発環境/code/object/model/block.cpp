//========================================
// 
// �u���b�N����
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "bullet_cube.h"
#include "enemy.h"
#include "../../scene/game.h"
#include "../../scene/title.h"
#include "../../scene/tutorial.h"
#include "model.h"
#include "../EFFECT/particleX.h"
#include "../../system/sound.h"
#include "../../system/csv_file.h"
#include "../../system/camera.h"
#include "../../system/words/font.h"
#include "../../system/words/text.h"

// �ÓI�ϐ�
CBlock::TypeInfo *CBlock::m_TypeInfo = NULL;
D3DXVECTOR3 CBlock::m_CameraRot = INIT_D3DXVECTOR3;
float CBlock::m_CameraHeigth = 0.0f;
int CBlock::m_nNumAll = 0;

//========================================
// �}�N����`
//========================================
#define GRAVITY_MAG		(0.08f)		// �d�͌W�� 0.08
#define GRAVITY_POWER	(1.5f)		// �d�͉����x
#define TNT_COLLSION	(3.5f)		// TNT�̔����̔���
#define FILE_PATH	("data/GAMEDATA/BLOCK/BLOCK_DATA.txt")	// �t�@�C���p�X

//========================================
// �R���X�g���N�^
//========================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nModelID = 0;
	m_Info.state = STATE_NORMAL;
	m_Info.fRadius = 0.0f;
	m_Info.nCntRadius = 0;
	m_Info.fRadiusRate = 0.0f;
	m_Info.bSet = false;
	m_Info.nEraseTime = 0;
	m_Info.bErase = false;
	m_Info.nID = m_nNumAll;
	m_nNumAll++;
}

//========================================
// �f�X�g���N�^
//========================================
CBlock::~CBlock()
{

}

//========================================
// ����
//========================================
CBlock *CBlock::Create(int nType, D3DXVECTOR3 pos, int nState)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// �I�u�W�F�N�g2D�̐���
	pBlock = new CBlock;

	pBlock->m_Info.state = STATE_MAX;
	pBlock->SetModel(nType);
	pBlock->m_Info.nModelID = nType;

	switch (nState)
	{
	case STATE_NORMAL:
	{
		pBlock->m_Info.state = STATE_NORMAL;
	}
	break;
	case STATE_BREAK:
	{
		pBlock->m_Info.state = STATE_BREAK;
	}
	break;
	case STATE_ALLIE:
	{
		pBlock->m_Info.state = STATE_ALLIE;
	}
	break;
	}

	// ����������
	pBlock->Init();

	pBlock->SetBlockPos(pos);

	return pBlock;
}

//========================================
// ������
//========================================
HRESULT CBlock::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BLOCK);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Info.fRadius = 1.0f;

	if(m_Info.state == STATE_MAX)
	{
	switch (m_TypeInfo[m_Info.nModelID].nState)
	{
	case STATE_NORMAL:
		m_Info.state = STATE_NORMAL;
		break;
	case STATE_BREAK:
		m_Info.state = STATE_BREAK;
		break;
	case STATE_ALLIE:
		m_Info.state = STATE_ALLIE;
		break;
	}
	}

	m_Info.col = INIT_D3DXCOLOR;

	// ����
	SetPos(m_Info.pos);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CBlock::Update(void)
{
	// -- �擾 -------------------------------------------
	CCamera *pCamera = CManager::GetCamera();		// �J����

	// �ߋ��̈ʒu�E�����̍X�V
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	if (m_Info.nID == 154)
	{
		m_Info.nID = 154;
	}

	// �ړ��ʂ̑��
	m_Info.pos.y += m_Info.move.y;

	if (m_Info.state != STATE_NORMAL)
	{
		if (m_Info.pos.y > -40.0f)
		{
			//�x�̈ړ��ʂɏd�͂����Z
			m_Info.move.y -= (GRAVITY_POWER - m_Info.move.y) * GRAVITY_MAG;
			m_Info.pos = Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Y, m_Info.pos);
		}
		else if (m_Info.pos.y <= -40.0f)
		{
			m_Info.move.y = 0.0f;
			m_Info.pos.y = -40.0f;
		}
	}
	
	SetPos(m_Info.pos);
	SetScale(m_Info.size);

	if (m_Info.bErase)
	{// �t���O���^�̎��A

		if (--m_Info.nEraseTime <= 0)
		{
			switch (m_Info.nModelID)
			{
			case MODEL_BOMB:
			{
				Bomb();
			}
				break;
			case MODEL_WOOD_BOX:
			{
				WoodenBox();
			}
				break;
			case MODEL_IRON_BOX:
			{
				WoodenBox();
			}
			break;
			}

			// �j��
			Uninit();

			return;
		}
	}

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// Hit����
//========================================
void CBlock::HitBlock(void)
{
	if (m_Info.state == STATE_BREAK)
	{
		switch (m_Info.nModelID)
		{
		case MODEL_WOOD_BOX:
		{
			m_Info.nEraseTime = 10;
			m_Info.bErase = true;
		}
		break;
		case MODEL_BOMB:
		{
			m_Info.nEraseTime = 10;
			m_Info.bErase = true;
		}
		break;
		case MODEL_IRON_BOX:
		{
			m_Info.nEraseTime = 10;
			m_Info.bErase = true;
		}
		break;
		}
	}
}

//========================================
// �ؔ�
//========================================
void CBlock::WoodenBox(void)
{
	bool bGravity = CEnemy::IsmGravity();

	if (!bGravity)
	{
		CEnemy::SetGravity(true);
	}

	// �p�[�e�B�N������
	CParticleX *pObj = CParticleX::Create();
	pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
	pObj->Par_SetRot(INIT_D3DXVECTOR3);
	pObj->Par_SetMove(D3DXVECTOR3(35.0f, 15.0f, 35.0f));
	pObj->Par_SetType(0);
	pObj->Par_SetLife(100);
	pObj->Par_SetCol(D3DXCOLOR(0.6f, 0.337f, 0.086f, 1.0f));
	pObj->Par_SetForm(20);
}

//========================================
// ���e
//========================================
void CBlock::Bomb(void)
{
	// �L���[�u�Ƃ̓����蔻��
	BombCollsion(PRIO_BLOCK, TYPE_BLOCK, VECTOR_NONE, m_Info.pos);
	BombCollsion(PRIO_BLOCK, TYPE_BLOCK, VECTOR_X, m_Info.pos);
	BombCollsion(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Y, m_Info.pos);
	BombCollsion(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.pos);

	BombCollsion(PRIO_OBJECT, TYPE_ENEMY, VECTOR_NONE, m_Info.pos);
	BombCollsion(PRIO_OBJECT, TYPE_ENEMY, VECTOR_X,m_Info.pos);
	BombCollsion(PRIO_OBJECT, TYPE_ENEMY, VECTOR_Y, m_Info.pos);
	BombCollsion(PRIO_OBJECT, TYPE_ENEMY, VECTOR_Z, m_Info.pos);

	// �p�[�e�B�N������
	CParticleX *pObj = CParticleX::Create();
	pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
	pObj->Par_SetRot(INIT_D3DXVECTOR3);
	pObj->Par_SetMove(D3DXVECTOR3(25.0f, 15.0f, 25.0f));
	pObj->Par_SetType(0);
	pObj->Par_SetLife(100);
	pObj->Par_SetCol(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	pObj->Par_SetForm(15);

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::TYPE_HIT);
}

//========================================
// �S��
//========================================
void CBlock::IronBox(void)
{
	bool bGravity = CEnemy::IsmGravity();

	if (!bGravity)
	{
		CEnemy::SetGravity(true);
	}

	// �p�[�e�B�N������
	CParticleX *pObj = CParticleX::Create();
	pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
	pObj->Par_SetRot(INIT_D3DXVECTOR3);
	pObj->Par_SetMove(D3DXVECTOR3(35.0f, 15.0f, 35.0f));
	pObj->Par_SetType(0);
	pObj->Par_SetLife(100);
	pObj->Par_SetCol(D3DXCOLOR(0.6f, 0.337f, 0.086f, 1.0f));
	pObj->Par_SetForm(20);
}

//========================================
// �����̓����蔻��
//========================================
void CBlock::BombCollsion(PRIO nPrio, TYPE nType, VECTOR vector,D3DXVECTOR3 pos)
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

			 // �u���b�N�̎擾
			int nBlockType = GetBlockType();	// ���
			float fWidth = GetWidth();			// ��
			float fHeight = GetHeight();		// ����
			float fDepth = GetDepth();			// ���s��

			if (nBlockType == MODEL_BOMB)
			{
				if (vector != VECTOR_NONE)
				{
					fHeight *= 1.5f;
				}

				switch (vector)
				{
				case CPhysics::VECTOR_X:
					fWidth *= TNT_COLLSION;
					break;
				case CPhysics::VECTOR_Y:
					fHeight *= TNT_COLLSION;
					break;
				case CPhysics::VECTOR_Z:
					fDepth *= TNT_COLLSION;
					break;
				case CPhysics::VECTOR_NONE:
					fWidth *= (TNT_COLLSION - 1.5f);
					fHeight *= 0.5f;
					fDepth *= (TNT_COLLSION - 1.5f);
					break;
				default:
					fWidth *= TNT_COLLSION;
					fDepth *= TNT_COLLSION;
					break;
				}
			}

			// ����̎擾
			D3DXVECTOR3 PairPos = pObj->GetPos();		// �ʒu
			D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// �ʒu(�ߋ�)
			float fPairWidth = pObj->GetWidth();		// ��
			float fPairHeight = pObj->GetHeight();		// ����
			float fPairDepth = pObj->GetDepth();		// ���s��

			// �����蔻��
			if (Collsion(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
			{// ����������

				switch (nType)
				{
				case TYPE_BLOCK:
				{
					// �_�C�i�~�b�N�L���X�g����
					CBlock *pBlock = dynamic_cast<CBlock*>(pObj);

					// ID���擾
					int nID = pBlock->GetID();

					CBlock::STATE state = pBlock->GetBlockState();

					if (state == STATE_BREAK)
					{
						if (m_Info.nID != nID)
						{
							// Hit����
							pBlock->HitBlock();
						}
					}
				}
				break;
				case TYPE_CUBE:
				{
					// �_�C�i�~�b�N�L���X�g����
					CCube *pCube = dynamic_cast<CCube*>(pObj);

					// HIT����
					pCube->SetCubeLife(20);
				}
				break;
				case TYPE_ENEMY:
				{
					// �_�C�i�~�b�N�L���X�g����
					CEnemy *pEnemy = dynamic_cast<CEnemy*>(pObj);

					// HIT����
					pEnemy->HitLife(1);
				}
				break;
				}
			}
		}

		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
}

//========================================
// �I�u�W�F�N�g�̓����蔻��
//========================================
D3DXVECTOR3 CBlock::Collision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(nPrio);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		// ��ނ��擾
		TYPE type = pObj->GetType();

		// �_�C�i�~�b�N�L���X�g����
		CBlock *pBlock = dynamic_cast<CBlock*>(pObj);
		int nID = pBlock->GetID();

		if (m_Info.nID != nID)
		{
			// �u���b�N�̎擾
			D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
			D3DXVECTOR3 RotOld = GetRotOld();	// ����(�ߋ�)
			D3DXVECTOR3 Scale = GetSize();
			float fWidth = GetWidth();		// ��
			float fHeight = GetHeight();	// ����
			float fDepth = GetDepth();		// ���s��

			if (m_Info.nModelID == MODEL_BOMB)
			{
				fHeight = 20.0f;
			}

			fWidth = round(fWidth);
			fHeight = round(fHeight);
			fDepth = round(fDepth);

			if (type == nType)
			{// ��ނ��u���b�N�̎��A

				// �u���b�N�̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();		// �ʒu
				D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// �ʒu(�ߋ�)
				D3DXVECTOR3 PairRot = pObj->GetRot();		// ����
				D3DXVECTOR3 PairRotOld = pObj->GetRotOld();	// ����(�ߋ�)

				float fPairWidth = pObj->GetWidth();	// ��
				float fPairHeight = pObj->GetHeight();	// ����
				float fPairDepth = pObj->GetDepth();	// ���s��

				int nModelId = pBlock->GetBlockType();
				if (nModelId == MODEL_BOMB)
				{
					fPairHeight = 20.0f;
				}

				fPairWidth = round(fPairWidth);
				fPairHeight = round(fPairHeight);
				fPairDepth = round(fPairDepth);

				// --- �����蔻�� ----------------------------------------------
				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if (CollsionX(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

						if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_LEFT))
						{// ������߂荞��ł��鎞
							pos.x = (PairPos.x - fPairWidth) - fWidth;
						}
						else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_RIGHT))
						{// �E����߂荞��ł��鎞
							pos.x = (PairPos.x + fPairWidth) + fWidth;
						}
					}
				}
							   break;
				case VECTOR_Y: {	/* Y���� */

					if (CollsionY(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_DOWN))
						{// ������߂荞��ł��鎞

						}
						else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_UP))
						{// �ォ��߂荞��ł��鎞

							m_Info.move.y = 0.0f;

							pos.y = (PairPos.y + fPairHeight) + fHeight;
						}
					}
				}
							   break;
				case VECTOR_Z: {	/* Z���� */

					if (CollsionZ(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

						if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_BACK))
						{// ��납��߂荞��ł��鎞
							pos.z = (PairPos.z - fPairDepth) - fDepth;
						}
						else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_FRONT))
						{// �O����߂荞��ł��鎞
							pos.z = (PairPos.z + fPairDepth) + fDepth;
						}
					}
				}
							   break;
				}
			}
		}
		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
	return pos;
}

//========================================
// �ǂݍ���
//========================================
void CBlock::Load(void)
{
	int nCntModel = 0;
	char aDataSearch[TXT_MAX];	// �f�[�^�����p
	m_TypeInfo = NULL;

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END"))
		{// �ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{// �܂�Ԃ�
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{
			int nMaxBlock = 0;

			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &nMaxBlock);			// �ő吔
			m_TypeInfo = new CBlock::TypeInfo[nMaxBlock];
			assert(m_TypeInfo != NULL);
		}
		else if (!strcmp(aDataSearch, "BLOCK"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			m_TypeInfo[nCntModel].nModelID = nCntModel;			// ���f��ID
			fscanf(pFile, "%d", &m_TypeInfo[nCntModel].nState);	// ���
			nCntModel++;
		}
	}
}

//========================================
// ���Z�b�g
//========================================
void CBlock::Reset(void)
{
	if (m_TypeInfo != NULL)
	{
		delete[] m_TypeInfo;
		m_TypeInfo = NULL;
	}

	m_CameraRot = INIT_D3DXVECTOR3;
	m_CameraHeigth = 0.0f;
	m_nNumAll = 0;
}