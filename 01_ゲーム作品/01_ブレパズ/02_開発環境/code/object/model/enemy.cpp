//========================================
// 
// �G�l�~�[����
// 
//========================================
// *** enemy.cpp ***
//========================================
#include "enemy.h"
#include "../../scene/pause.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/sound.h"
#include "../UI/score.h"
#include "../EFFECT/particleX.h"
#include "block.h"
#include "bullet_cube.h"
#include "../../system/input.h"

// �ÓI�ϐ�
CEnemy::SetInfo *CEnemy::pSet = NULL;
int CEnemy::m_nNumAll = 0;
bool CEnemy::m_bGravity = true;

//========================================
// �}�N����`
//========================================
#define GRAVITY_MAG		(0.08f)		// �d�͌W�� 0.08
#define GRAVITY_POWER	(1.5f)		// �d�͉����x
#define ROT_DIAMETER	(0.075f)	// ��]�{��

//========================================
// �R���X�g���N�^
//========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.moveRot = INIT_D3DXVECTOR3;
	m_Info.targetRot = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
	m_Info.state = STATE_NORMAL;
	m_Info.stateOld = STATE_NORMAL;
	m_Info.nCntState = 0;
	m_Info.nCntStop = 0;
	m_Info.nCntTime = 0;
	m_Info.nTimeMax = 0;
	m_Info.nStandTime = 0;
	m_Info.bRotMove = false;
	m_Info.bCube = false;
	m_Info.bGravity = false;
	m_Info.nID = m_nNumAll;
	m_nNumAll++;
}

//========================================
// �f�X�g���N�^
//========================================
CEnemy::~CEnemy()
{
	m_nNumAll--;
}

//========================================
// ����
//========================================
CEnemy *CEnemy::Create(int nType, int nMove, D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nCntTime)
{
	CEnemy *pEnemy = new CEnemy;

	pEnemy->SetModel(MODEL_ENEMY_00 + nType);
	pEnemy->m_Info.nType = nType;

	// ����������
	pEnemy->Init();

	pEnemy->m_Info.pos = pos;
	pEnemy->m_Info.rot = rot;
	pEnemy->m_Info.moveRot = rot;
	pEnemy->m_Info.nMove = nMove;
	pEnemy->m_Info.nTimeMax = nCntTime;
	pEnemy->SetPos(pEnemy->m_Info.pos);
	pEnemy->SetRot(pEnemy->m_Info.rot);
	pEnemy->SetColor(pEnemy->m_Info.col);

	if (nMove != 0)
	{
		pEnemy->m_Info.move.x = sinf(pEnemy->m_Info.moveRot.y) * -3;
		pEnemy->m_Info.move.z = cosf(pEnemy->m_Info.moveRot.y) * -3;
	}
	return pEnemy;
}

//========================================
// ������
//========================================
HRESULT CEnemy::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_ENEMY);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.moveRot = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nLife = m_Info.nType + 1;
	m_Info.nLifeMax = m_Info.nLife;

	// ����
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// �I��
//========================================
void CEnemy::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	pSound->StopSoundType(CSound::SOUND_TYPE_SE);

	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CEnemy::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		// �ߋ��̈ʒu�E�����̍X�V
		m_Info.posOld = m_Info.pos;

		// ��Ԑ���
		StateShift();

		if (m_Info.state != STATE_STOP)
		{

			// �ړ�����
			if (m_Info.state != STATE_STAND && !m_Info.bCube && !m_Info.bRotMove)
			{
				// �����蔻��
				if (!Collision(PRIO_OBJECT, TYPE_PLAYER, VECTOR_X, m_Info.pos) &&
					!Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_X, m_Info.pos) &&
					!Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_X, m_Info.pos) &&
					!Collision(PRIO_OBJECT, TYPE_PLAYER, VECTOR_Z, m_Info.pos) &&
					!Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.pos) &&
					!Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_Z, m_Info.pos))
				{
					if (++m_Info.nCntTime >= m_Info.nTimeMax && m_Info.nMove != 0)
					{
						// �ҋ@��Ԃɂ���
						SetState(STATE_STAND);

						m_Info.nCntTime = 0;
						m_Info.nStandTime = 0;

						switch (m_Info.nMove)
						{
							break;
						case 1:
						{
							if (m_Info.rot.y == 0.0f)
							{
								m_Info.moveRot.y = 3.14f;
							}
							else if (m_Info.rot.y = 3.14f)
							{
								m_Info.moveRot.y = 0.0f;
							}
						}
						break;
						case 2:
						{
							if (m_Info.rot.y == 1.57f)
							{
								m_Info.moveRot.y = -1.57f;
							}
							else if (m_Info.rot.y = -1.57f)
							{
								m_Info.moveRot.y = 1.57f;
							}
						}
						break;
						case 3:
						{
							m_Info.moveRot.y += 1.57f;
							ControlAngle(&m_Info.rot.y);
						}
						break;
						case 4:
						{
							m_Info.moveRot.y -= 1.57f;
							ControlAngle(&m_Info.rot.y);
						}
						break;
						default:
							break;
						}

						// �ڕW�����Ɉړ���������
						m_Info.targetRot = m_Info.moveRot;
						m_Info.bRotMove = true;

						m_Info.move.x = sinf(m_Info.moveRot.y) * -3;
						m_Info.move.z = cosf(m_Info.moveRot.y) * -3;
					}
				}
			}
			else if (m_Info.state == STATE_STAND && m_Info.bRotMove)
			{
				RotControl(&m_Info.rot);
				RotControl(&m_Info.moveRot);
				RotControl(&m_Info.targetRot);

				// �p�x��ڕW�p�x�Ɍ����Đ��ڂ���
				m_Info.rot.y += AngleDifference(m_Info.rot.y, m_Info.targetRot.y) * ROT_DIAMETER;

				// �͈͓��ɓ�������
				if (m_Info.rot.y > m_Info.targetRot.y - 0.05f && m_Info.rot.y < m_Info.targetRot.y + 0.05f)
				{
					m_Info.rot.y = m_Info.targetRot.y;
					m_Info.bRotMove = false;
				}
				SetRot(m_Info.rot);
			}

			if (m_Info.state != STATE_STAND && !m_Info.bCube)
			{
				// �ړ��ʂ̑��
				m_Info.pos.x += m_Info.move.x;
			}

			// �����蔻��
			if (Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_X, m_Info.pos)) {}
			if (Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_X, m_Info.pos)) { m_Info.bCube = true; }
			if (Collision(PRIO_OBJECT, TYPE_PLAYER, VECTOR_X, m_Info.pos)) {}

			if (m_Info.state != STATE_STAND && !m_Info.bCube)
			{
				// �ړ��ʂ̑��
				m_Info.pos.z += m_Info.move.z;
			}
			if (Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.pos)) {}
			if (Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_Z, m_Info.pos)) { m_Info.bCube = true; }
			if (Collision(PRIO_OBJECT, TYPE_PLAYER, VECTOR_Z, m_Info.pos)) {}
		}

		// �d�͂̕ύX
		if (m_bGravity && !m_Info.bGravity)
		{
			m_Info.bGravity = true;
		}
		if (m_Info.nID == (m_nNumAll - 1))
		{
			m_bGravity = false;
		}

		// �ړ��ʂ̑��
		m_Info.pos.y += m_Info.move.y;

		if (m_Info.bGravity)
		{
			//�x�̈ړ��ʂɏd�͂����Z
			m_Info.move.y -= (GRAVITY_POWER - m_Info.move.y) * GRAVITY_MAG;
			Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Y, m_Info.pos);
		}

		SetPos(m_Info.pos);
		SetColor(m_Info.col);

		CObjectX::Update();
	}
}

//========================================
// �`��
//========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �����蔻��(�����w��)
//========================================
bool CEnemy::Collision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(nPrio);

	bool bHit = false;

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		// ��ނ��擾
		TYPE type = pObj->GetType();

		// �G�l�~�[�̊e�p�[�c�̎擾
		D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
		D3DXVECTOR3 RotOld = GetRotOld();	// ����(�ߋ�)

		float fWidth = 30;		// ��
		float fHeight = 8;		// ����
		float fDepth = 15;		// ���s��

		// �e��ނ̓����蔻��
		if (type == nType)
		{
			// ����̎擾
			D3DXVECTOR3 PairPos = pObj->GetPos();		// �ʒu
			D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// �ʒu(�ߋ�)
			float fPairWidth = pObj->GetWidth();		// ��
			float fPairHeight = pObj->GetHeight();		// ����
			float fPairDepth = pObj->GetDepth();		// ���s��

			fPairWidth = round(fPairWidth);
			fPairHeight = round(fPairHeight);
			fPairDepth = round(fPairDepth);

			if (nType == TYPE_PLAYER)
			{
				fPairWidth = 20;
				fPairHeight = 10;
				fPairDepth = 20;
			}
			else if (nType == TYPE_CUBE)
			{
				fPairWidth = round(fPairWidth);
				fPairHeight = round(fPairHeight);
				fPairDepth = round(fPairDepth);
			}

			switch (vector)
			{
			case VECTOR_X: {	/* X���� */

				if (CollsionX(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_LEFT))
					{// ������߂荞��ł��鎞
						bHit = true;
						pos.x = (PairPos.x - fPairWidth) - fWidth;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_RIGHT))
					{// �E����߂荞��ł��鎞
						bHit = true;
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
						bHit = true;
						pos.y = (PairPos.y - fPairHeight) - fHeight;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_UP))
					{// �ォ��߂荞��ł��鎞
						m_Info.move.y = 0.0f;
						pos.y = (PairPos.y + fPairHeight) + fHeight;
						bHit = true;
						m_Info.bGravity = false;
					}
				}
			}
						   break;
			case VECTOR_Z: {	/* Z���� */

				if (CollsionZ(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_BACK))
					{// ��납��߂荞��ł��鎞
						bHit = true;
						pos.z = (PairPos.z - fPairDepth) - fDepth;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_FRONT))
					{// �O����߂荞��ł��鎞
						bHit = true;
						pos.z = (PairPos.z + fPairDepth) + fDepth;
					}
				}
			}
			   break;
			}

		}

		if (bHit)
		{
			m_Info.pos = pos;
			return TRUE;
		}
		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
	return FALSE;
}

//========================================
// �����蔻��(�S��)
//========================================
void CEnemy::ModelCollsion(PRIO nPrio, TYPE nType, D3DXVECTOR3 pos)
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
			float fWidth = GetWidth();			// ��
			float fHeight = GetHeight();		// ����
			float fDepth = GetDepth();			// ���s��

			// �T�C�Y����
			fWidth *= 3.5f;	// ��
			fHeight *= 3.5f;// ����
			fDepth *= 3.5f;	// ���s��

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
				case TYPE_ENEMY:
				{
					// �_�C�i�~�b�N�L���X�g����
					CEnemy *pEnemy = dynamic_cast<CEnemy*>(pObj);

					// ID���擾
					int nID = pEnemy->GetID();

					if (m_Info.nID != nID)
					{
						// Hit����
						pEnemy->HitLife(1);
					}
				}
				break;
				case TYPE_BLOCK:
				{
					// �_�C�i�~�b�N�L���X�g����
					CBlock *pBlock = dynamic_cast<CBlock*>(pObj);

					// ID���擾
					int nID = pBlock->GetID();

					int nBlockType = pBlock->GetBlockType();
					if (nBlockType == MODEL_BOMB || nBlockType == MODEL_WOOD_BOX)
					{
						// Hit����
						pBlock->HitBlock();
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
// �q�b�g����
//========================================
void CEnemy::HitLife(int nDamage)
{
	CSound *pSound = CManager::GetSound();

	m_Info.nLife -= nDamage;
	m_Info.bCube = false;

	if (m_Info.nLife <= 0)
	{
		/*ModelCollsion(PRIO_BLOCK, TYPE_BLOCK, m_Info.pos);
		ModelCollsion(PRIO_OBJECT, TYPE_ENEMY, m_Info.pos);*/

		// �p�[�e�B�N������
		CParticleX *pObj = CParticleX::Create();
		pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 20, m_Info.pos.z));
		pObj->Par_SetRot(INIT_D3DXVECTOR3);
		pObj->Par_SetMove(D3DXVECTOR3(10.0f, 3.0f, 10.0f));
		pObj->Par_SetType(0);
		pObj->Par_SetLife(100);
		pObj->Par_SetCol(D3DXCOLOR(0.3f, 0.8f, 0.8f, 1.0f));
		pObj->Par_SetForm(15);

		// �G�̔j��
		Uninit();

		int nScore = (100 * m_Info.nLifeMax) * nDamage;

		// �X�R�A�ݒ�
		CScore::SetScore(nScore);

		// ������SE�Đ�
		pSound->PlaySound(CSound::TYPE_HIT);

		return;
	}
	else
	{
		// �q�b�gSE�̍Đ�
		pSound->PlaySound(CSound::TYPE_HIT);

		// �_���[�W���
		SetState(STATE_DAMAGE);

		// �p�[�e�B�N������
		CParticleX *pObj = CParticleX::Create();
		pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 20, m_Info.pos.z));
		pObj->Par_SetRot(INIT_D3DXVECTOR3);
		pObj->Par_SetMove(D3DXVECTOR3(10.0f, 3.0f, 10.0f));
		pObj->Par_SetType(0);
		pObj->Par_SetLife(50);
		pObj->Par_SetCol(D3DXCOLOR(0.3, 0.8f, 0.8f, 1.0f));
		pObj->Par_SetForm(15);
	}
}

//========================================
// ��Ԑݒ�
//========================================
void CEnemy::SetState(STATE state)
{
	// ���
	switch (state)
	{
	case STATE_NORMAL: { /* �ʏ� */

		 // ��Ԃ̐ݒ�
		m_Info.state = STATE_NORMAL;

		// �_���[�W�F�̐ݒ�
		m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.1f, 1.0f);
	}
	   break;

	case STATE_DAMAGE: { /* �_���[�W */

		m_Info.state = STATE_DAMAGE;	// ��Ԑݒ�
		m_Info.nCntState = 10;			// ����

		// �_���[�W�F�̐ݒ�
		m_Info.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	}
	   break;
	case STATE_STAND: {/* �ҋ@ */
		m_Info.state = STATE_STAND;
		m_Info.nCntState = STAND_TIME;
	}
	   break;
	case STATE_STOP: {/* ��~ */
		m_Info.stateOld = m_Info.state;
		m_Info.state = STATE_STOP;
		m_Info.nCntStop = STOP_TIME;
	}
	   break;
	}
}

//========================================
// ��Ԑ���
//========================================
void CEnemy::StateShift(void)
{
	// ���
	switch (m_Info.state)
	{
	case STATE_NORMAL: { /* �ʏ��� */

	}
	   break;
	case STATE_DAMAGE: { /* �_���[�W��� */

		 // ��Ԃ�ؑւ���
		if (--m_Info.nCntState <= 0)
		{
			// �ʏ��Ԃɂ���
			SetState(STATE_NORMAL);
		}
	}
	   break;
	case STATE_STAND: { /* �ҋ@ */
		if (--m_Info.nCntState <= 0)
		{
			if (!m_Info.bRotMove)
			{
				// �ʏ��Ԃɂ���
				SetState(STATE_NORMAL);
			}
		}
	}
	   break;
	case STATE_STOP: {/* ��~ */
		if (--m_Info.nCntStop <= 0)
		{
			if (!m_Info.bRotMove)
			{
				// �ʏ��Ԃɂ���
				SetState(m_Info.stateOld);
				m_Info.stateOld = STATE_NORMAL;
			}
		}
	}
	}
}

//========================================
// ���Z�b�g
//========================================
void CEnemy::Reset(void)
{
	m_nNumAll = 0;
	m_bGravity = true;
}