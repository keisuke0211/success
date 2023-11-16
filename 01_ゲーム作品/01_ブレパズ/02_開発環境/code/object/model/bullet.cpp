//========================================
// 
// �o���b�g����
// 
//========================================
// *** bullet.cpp ***
//========================================
#include "bullet.h"
#include "bullet_cube.h"
#include "enemy.h"
#include "block.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/input.h"
#include "../UI/score.h"
#include "../effect/effectX.h"
#include "../../scene/game.h"
#include "../../scene/pause.h"

// �ÓI�ϐ�
int CBullet::m_nNumAll = 0;

//========================================
// �}�N����`
//========================================
#define BULLET_SPEED		(7.5f)	// �e�̑��x
#define BULLET_DAMAGE		(1)		// �_���[�W��
#define COLLSION_DIAMETER	(1.00f)	// �����蔻��̔{��
#define BULLET_DIAMETER		(0.2f)	// �T�C�Y�̔{��
#define BULLET_LIFE			(60)	// ����

#define CUBE_LIFE1			(60)	// �ǂ⏰�ɔz�u�����ꍇ�̎���
#define CUBE_LIFE2			(60)	// �G�ɓ��Ă��ꍇ�̎���

//========================================
// �R���X�g���N�^
//========================================
CBullet::CBullet(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.fHeight = 0.0f;
	m_Info.fWidth = 0.0f;
	m_Info.bHit = false;
	m_Info.nID = m_nNumAll;

	m_nNumAll++;	// �������Z
}
//========================================
// �f�X�g���N�^
//========================================
CBullet::~CBullet()
{
	m_nNumAll--;	// �������Z
}

//========================================
// ����
//========================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBullet *pBullet = NULL;

	if (pBullet != NULL)
	{
		return pBullet;
	}

	// �o���b�g�̐���
	pBullet = new CBullet;

	pBullet->m_Info.pos = pos;
	pBullet->m_Info.rot = rot;
	pBullet->m_Info.nLife = BULLET_LIFE;
	pBullet->m_Info.size = D3DXVECTOR3(BULLET_DIAMETER, BULLET_DIAMETER, BULLET_DIAMETER);
	pBullet->SetModel(MODEL_BULLET);

	// ����������
	pBullet->Init();

	return pBullet;
}
//========================================
// ������
//========================================
HRESULT CBullet::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BULLET);

	m_Info.move.x = sinf(m_Info.rot.y) * BULLET_SPEED;
	m_Info.move.z = cosf(m_Info.rot.y) * BULLET_SPEED;
	m_Info.col = D3DXCOLOR(0.1f, 0.9f, 0.9f, 1.0f);

	SetPos(m_Info.pos);
	SetScale(m_Info.size);
	SetColor(m_Info.col);
	
	return S_OK;
}

//========================================
// �I��
//========================================
void CBullet::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CBullet::Update(void)
{
	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	bool bPause = CPause::IsPause();
	bool bEnd = CGame::IsEnd();

	if (!bPause && !bEnd)
	{
		// �ߋ��̈ʒu�E�����̍X�V
		m_Info.posOld = m_Info.pos;
		m_Info.rotOld = m_Info.rot;

		// �����̌���
		if (--m_Info.nLife <= 0)
		{// �������s������

			// �e�̔j��
			Uninit();

			return;
		}

		{
			// �ړ��ʂ���
			m_Info.pos.x += m_Info.move.x;

			// X�����̓����蔻��
			if (Collsion(VECTOR_X, m_Info.pos))
			{
				return;
			}
		}

		{
			// �ړ��ʂ���
			m_Info.pos.z += m_Info.move.z;

			// Z�����̓����蔻��
			if (Collsion(VECTOR_Z, m_Info.pos))
			{
				return;
			}
		}

		{
			// �ړ��ʂ���
			m_Info.pos.y += m_Info.move.y;

			// Y�����̓����蔻��
			if (Collsion(VECTOR_Y, m_Info.pos))
			{
				return;
			}
		}

		SetPos(m_Info.pos);
		SetScale(m_Info.size);

		CObjectX::Update();

		CEffectX *pObj = CEffectX::Create();
		pObj->Eff_SetPos(GetPosOld());
		pObj->Eff_SetRot(GetRot());
		pObj->Eff_SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pObj->Eff_SetType(0);
		pObj->Eff_SetLife(10);
		pObj->Eff_SetCol(D3DXCOLOR(0.1f, 0.8f, 0.8f, 1.0f));
		pObj->Eff_SetRadius(0.35f);
	}
}

//========================================
// �`��
//========================================
void CBullet::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �����蔻��
//========================================
bool CBullet::Collsion(VECTOR vector, D3DXVECTOR3 pos)
{
	for (int nCntPrio = 0; nCntPrio < PRIO_MAX; nCntPrio++)
	{
		// �擪�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPrio);

		while (pObj != NULL)
		{// �g�p����Ă��鎞�A

			// ���̃I�u�W�F�N�g
			CObject *pObjNext = pObj->GetNext();

			TYPE type;

			// ��ނ��擾
			type = pObj->GetType();

			if (type == TYPE_BLOCK || type == TYPE_CUBE)
			{// ��ނ��u���b�N���L���[�u�̏ꍇ

				// �o���b�g�̎擾
				D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
				float fWidth = GetWidth();			// ��
				float fHeight = GetHeight();		// ����
				float fDepth = GetDepth();			// ���s��

				// �T�C�Y����
				fWidth *= BULLET_DIAMETER;	// ��
				fHeight *= BULLET_DIAMETER;	// ����
				fDepth *= BULLET_DIAMETER;	// ���s��


				// �u���b�N�̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();	// �ʒu
				float fPairWidth = pObj->GetWidth();	// ��
				float fPairHeight = pObj->GetHeight();	// ����
				float fPairDepth = pObj->GetDepth();	// ���s��

				// ����̏C��
				fPairWidth *= COLLSION_DIAMETER;	// ��
				fPairHeight *= COLLSION_DIAMETER;	// ����
				fPairDepth *= COLLSION_DIAMETER;	// ���s��

				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if ((pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// ���ӂƎ�O�ӂ��u���b�N�̕��̓����̎��A

						if ((pos.x + fWidth) >= (PairPos.x - fPairWidth) &&
							(PosOld.x + fWidth) <= (PairPos.x - fPairWidth))
						{// ������߂荞��ł��鎞

							// �_�C�i�~�b�N�L���X�g����
							if (type == TYPE_BLOCK)
							{
								CBlock *pBlock = dynamic_cast<CBlock*>(pObj);
								CBlock::STATE aState = pBlock->GetBlockState();
								if (aState == CBlock::STATE_ALLIE)
								{// ��Ԃ��ђʂȂ�
									return FALSE;
								}
							}
							m_Info.bHit = true;
							pos.x = (PairPos.x - (fPairWidth / COLLSION_DIAMETER)) - (fWidth / BULLET_DIAMETER);
						}
						else if ((pos.x - fWidth) <= (PairPos.x + fPairWidth) &&
							(PosOld.x - fWidth) >= (PairPos.x + fPairWidth))
						{// �E����߂荞��ł��鎞

							// �_�C�i�~�b�N�L���X�g����
							if (type == TYPE_BLOCK)
							{
								CBlock *pBlock = dynamic_cast<CBlock*>(pObj);
								CBlock::STATE aState = pBlock->GetBlockState();
								if (aState == CBlock::STATE_ALLIE)
								{// ��Ԃ��ђʂȂ�
									return FALSE;
								}
							}
							m_Info.bHit = true;
							pos.x = (PairPos.x + (fPairWidth / COLLSION_DIAMETER)) + (fWidth / BULLET_DIAMETER);
						}
					}
				}
							   break;
				case VECTOR_Y: {	/* Y���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.y + fHeight) > (PairPos.y - fPairHeight) &&
							(PosOld.y + fHeight) <= (PairPos.y - fPairHeight))
						{// ������߂荞��ł��鎞

							m_Info.bHit = true;
							pos.y = (PairPos.y - (fPairHeight / COLLSION_DIAMETER)) - (fHeight / BULLET_DIAMETER);
						}
						else if ((pos.y - fHeight) < (PairPos.y + fPairHeight) &&
							(PosOld.y - fHeight) >= (PairPos.y + fPairHeight))
						{// �ォ��߂荞��ł��鎞

							m_Info.bHit = true;
							pos.y = (PairPos.y + (fPairHeight / COLLSION_DIAMETER)) + (fHeight / BULLET_DIAMETER);
						}
					}
				}
							   break;
				case VECTOR_Z: {	/* Z���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.z + fDepth) >= (PairPos.z - fPairDepth) &&
							(PosOld.z + fDepth) <= (PairPos.z - fPairDepth))
						{// �O����߂荞��ł��鎞

							// �_�C�i�~�b�N�L���X�g����
							if (type == TYPE_BLOCK)
							{
								CBlock *pBlock = dynamic_cast<CBlock*>(pObj);
								CBlock::STATE aState = pBlock->GetBlockState();
								if (aState == CBlock::STATE_ALLIE)
								{// ��Ԃ��ђʂȂ�
									return FALSE;
								}
							}
							m_Info.bHit = true;
							pos.z = (PairPos.z - (fPairDepth / COLLSION_DIAMETER)) - (fDepth / BULLET_DIAMETER);
						}
						else if ((pos.z - fDepth) <= (PairPos.z + fPairDepth) &&
							(PosOld.z - fDepth) >= (PairPos.z + fPairDepth))
						{// ������߂荞��ł��鎞

							 // �_�C�i�~�b�N�L���X�g����
							if (type == TYPE_BLOCK)
							{
								CBlock *pBlock = dynamic_cast<CBlock*>(pObj);
								CBlock::STATE aState = pBlock->GetBlockState();
								if (aState == CBlock::STATE_ALLIE)
								{// ��Ԃ��ђʂȂ�
									return FALSE;
								}
							}
							m_Info.bHit = true;
							pos.z = (PairPos.z + (fPairDepth / COLLSION_DIAMETER)) + (fDepth / BULLET_DIAMETER);
						}
					}
				}
				   break;
				}

				if (m_Info.bHit)
				{
					// �L���[�u�̐���
					CCube::Create(m_Info.nType, D3DXVECTOR3(pos.x, pos.y, pos.z), CUBE_LIFE1);

					// �e�̔j��
					Uninit();

					return TRUE;
				}
			}
			else if (type == TYPE_ENEMY)
			{// ��ނ��G��������

				// �o���b�g�̎擾
				D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
				float fWidth = GetWidth();			// ��
				float fHeight = GetHeight();		// ����
				float fDepth = GetDepth();			// ���s��


				// �u���b�N�̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();		// �ʒu
				D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// �ʒu(�ߋ�)
				float fPairWidth = pObj->GetWidth();		// ��
				float fPairHeight = pObj->GetHeight();		// ����
				float fPairDepth = pObj->GetDepth();		// ���s��

				fPairWidth = round(fWidth);
				fPairHeight = round(fHeight);
				fPairDepth = round(fDepth);

				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if ((pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// ���ӂƎ�O�ӂ��u���b�N�̕��̓����̎��A

						if ((pos.x + fWidth) >= (PairPos.x - fPairWidth) &&
							(PosOld.x + fWidth) <= (PairPosOld.x - fPairWidth))
						{// ������߂荞��ł��鎞

							m_Info.bHit = true;
						}
						else if ((pos.x - fWidth) <= (PairPos.x + fPairWidth) &&
							(PosOld.x - fWidth) >= (PairPosOld.x + fPairWidth))
						{// �E����߂荞��ł��鎞

							m_Info.bHit = true;
						}
					}
				}
							   break;
				case VECTOR_Y: {	/* Y���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.y + fHeight) > (PairPos.y - fPairHeight) &&
							(PosOld.y + fHeight) <= (PairPosOld.y - fPairHeight))
						{// ������߂荞��ł��鎞

							m_Info.bHit = true;
						}
						else if ((pos.y - fHeight) < (PairPos.y + fPairHeight) &&
							(PosOld.y - fHeight) >= (PairPosOld.y + fPairHeight))
						{// �ォ��߂荞��ł��鎞

							m_Info.bHit = true;
						}
					}
				}
				   break;
				case VECTOR_Z: {	/* Z���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.z + fDepth) >= (PairPos.z - fPairDepth) &&
							(PosOld.z + fDepth) <= (PairPosOld.z - fPairDepth))
						{// �O����߂荞��ł��鎞

							m_Info.bHit = true;
						}
						else if ((pos.z - fDepth) <= (PairPos.z + fPairDepth) &&
							(PosOld.z - fDepth) >= (PairPosOld.z + fPairDepth))
						{// ������߂荞��ł��鎞

							m_Info.bHit = true;
						}
					}
				}
				   break;
				}

				if (m_Info.bHit)
				{
					// �_�C�i�~�b�N�L���X�g����
					CEnemy *pEnemy = dynamic_cast<CEnemy*>(pObj);
					pEnemy->SetState(CEnemy::STATE_STOP);

					// �L���[�u�̐���
					CCube::Create(m_Info.nType, D3DXVECTOR3(pos.x, pos.y, pos.z), CUBE_LIFE2);

					// �e�̔j��
					Uninit();

					return TRUE;
				}
			}

			pObj = pObjNext;	// ���̃I�u�W�F�N�g����
		}
	}
	return FALSE;
}

//========================================
// ���Z�b�g
//========================================
void CBullet::Reset(void)
{
	m_nNumAll = 0;
}