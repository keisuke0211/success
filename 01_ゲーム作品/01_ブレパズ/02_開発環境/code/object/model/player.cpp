//========================================
// 
// �v���C���[����
// 
//========================================
// *** player.cpp ***
//========================================
#include "player.h"
#include "../../scene/game.h"
#include "../../scene/title.h"
#include "../../scene/pause.h"
#include "motion.h"
#include "../../manager.h"
#include "../../system/camera.h"
#include "../../system/input.h"
#include "../../system/sound.h"
#include "../../system/physics.h"
#include "bullet.h"
#include "enemy.h"
#include "block.h"
#include "bullet_cube.h"
#include "../EFFECT/particleX.h"
#include "../../scene/pause.h"
#include "../model/model.h"
#include "../../manager.h"
#include "../../system/renderer.h"

//****************************************
// �}�N����`
//****************************************
#define JUMP_POWER		(7.0f)		// �W�����v��
#define GRAVITY_MAG		(0.08f)		// �d�͌W�� 0.08
#define GRAVITY_POWER	(9.5f)		// �d�͉����x
#define POS_DIAMETER	(0.3f)		// �ړ��{��
#define ROT_DIAMETER	(0.3f)		// ��]�{��
#define POS_RANGE_WIDE	(3)			// ����̊g��
#define DUST_MAXCNT		(15)		// �J�E���g�̍ő�l
#define CUBE_LIFE1		(120)		// �ǂ⏰�ɔz�u�����ꍇ�̎���

// ��`
const float CPlayer::PLAYER_SPEED = 1.0f;

//========================================
// �R���X�g���N�^
//========================================
CPlayer::CPlayer(int nPriority) : CMotionModel(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.moveRot = INIT_D3DXVECTOR3;
	m_Info.targetRot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fDepth = INIT_FLOAT;
	m_Info.bMove = false;
	m_Info.bMotion = false;
	m_Info.bAction = false;
}

//========================================
// �f�X�g���N�^
//========================================
CPlayer::~CPlayer()
{

}

//========================================
// ����
//========================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float rotY)
{
	CPlayer *pPlayer  = new CPlayer;

	// ����������
	pPlayer->Init();

	pPlayer->m_Info.pos = pos;
	pPlayer->m_Info.rot = D3DXVECTOR3(0.0f, rotY, 0.0f);
	pPlayer->m_Info.moveRot = D3DXVECTOR3(0.0f, rotY, 0.0f);
	pPlayer->m_Info.targetRot = D3DXVECTOR3(0.0f, rotY, 0.0f);
	return pPlayer;
}

//========================================
// ������
//========================================
HRESULT CPlayer::Init(void)
{
	CCamera *pCamera = CManager::GetCamera();	// �J�����̎擾

	CMotionModel::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	
	// ����
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.col);

	// �J�����̒����_��ݒ�
	pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
	return S_OK;
}

//========================================
// �I��
//========================================
void CPlayer::Uninit(void)
{
	CMotionModel::Uninit();
}

//========================================
// �X�V
//========================================
void CPlayer::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		// �ߋ��̈ʒu�E�����̍X�V
		m_Info.posOld = m_Info.pos;
		m_Info.rotOld = m_Info.rot;

		bool bStart = CTitle::IsStart();
		bool bEnd = CGame::IsEnd();

		if (bStart && !bEnd)
		{
			// �L�[���͏���
			KeyInput();
		}
		// �ʒu�X�V����
		UpdatePos();

		// ����/�ړ�����/�ڕW�����𐧌�
		RotControl(&m_Info.rot);
		RotControl(&m_Info.moveRot);
		RotControl(&m_Info.targetRot);

		// �p�x��ڕW�p�x�Ɍ����Đ��ڂ���
		m_Info.rot.y += AngleDifference(m_Info.rot.y, m_Info.targetRot.y) * ROT_DIAMETER;

		SetRot(m_Info.rot);

		CMotionModel::Update();
	}
}

//========================================
// �`��
//========================================
void CPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
	D3DVIEWPORT9 pviewport;
	LPDIRECT3DTEXTURE9 pTexture;
	
	//// ���݂̃����_�����O�^�[�Q�b�g���擾�i�ۑ��j
	//pDevice->GetRenderTarget(0, &pRenderDef);

	//// ���݂�Z�o�b�t�@���擾�i�ۑ��j
	//pDevice->GetDepthStencilSurface(&pZBuffDef);

	//// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	//pDevice->SetRenderTarget(0, pRenderDef);

	//// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	//pDevice->SetDepthStencilSurface(pZBuffDef);

	//// �e�N�X�`�������_�����O�p�̃r���[�|�[�g��ݒ�
	//pDevice->SetViewport(&pviewport);

	//CCamera *pCamera = CManager::GetCamera();		// �J�����̎擾
	//D3DXVECTOR3 posV = pCamera->GetInfo().posV;		// ���_
	//D3DXVECTOR3 posR = pCamera->GetInfo().posR;		// �����_
	//D3DXVECTOR3 vecU = pCamera->GetInfo().vecU;		// ������x�N�g��

	//pRenderer->ChangeTarget(posV, posR, vecU);

	//// �����_�����O�^�[�Q�b�g�p�̃e�N�X�`���N���A
	//pDevice->Clear(0, NULL,
	//	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	//	D3DCOLOR_RGBA(0, 255, 0, 255), 1.0f, 0);

	CMotionModel::Draw();

	//// �����_�����O�^�[�Q�b�g�����ɖ߂�
	//pDevice->SetRenderTarget(0, pRenderDef);

	//// Z�o�b�t�@�����ɖ߂�
	//pDevice->SetDepthStencilSurface(pZBuffDef);
}

//========================================
// �L�[���͏���
//========================================
void CPlayer::KeyInput(void)
{
	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g
	CSound *pSound = CManager::GetSound();

	m_Info.bMove = true;

	if (pInputJoypad->GetPress(CJoypad::JOYKEY_LEFT) || pInputJoypad->GetStick(0).aAnglePress[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_LEFT])
	{
		MoveInput(DIRECTION_LEFT);
	}
	else if (pInputJoypad->GetPress(CJoypad::JOYKEY_RIGHT) || pInputJoypad->GetStick(0).aAnglePress[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_RIGHT])
	{
		MoveInput(DIRECTION_RIGHT);
	}
	else if (pInputJoypad->GetPress(CJoypad::JOYKEY_DOWN) || pInputJoypad->GetStick(0).aAnglePress[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_DOWN])
	{
		MoveInput(DIRECTION_FRONT);
	}
	else if (pInputJoypad->GetPress(CJoypad::JOYKEY_UP) || pInputJoypad->GetStick(0).aAnglePress[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_UP])
	{
		MoveInput(DIRECTION_BACK);
	}
	else if (pInputKeyboard->GetPress(DIK_A)) { MoveInput(DIRECTION_LEFT);}		// ���ړ�
	else if (pInputKeyboard->GetPress(DIK_D)) { MoveInput(DIRECTION_RIGHT);}	// �E�ړ�
	else if (pInputKeyboard->GetPress(DIK_W)) { MoveInput(DIRECTION_BACK); }	// ���ړ�
	else if (pInputKeyboard->GetPress(DIK_S)) { MoveInput(DIRECTION_FRONT); }	// ��O�ړ�
	else
	{
		if (m_Info.bAction && (m_Info.move.x < 0.02f && m_Info.move.x > -0.02f) && (m_Info.move.z < 0.02f && m_Info.move.z > -0.02f))
		{
			CMotion *pMotion = CMotionModel::GetMotion();	// ���[�V�������
			pMotion->SetNumMotion(0, true);

			m_Info.bAction = false;
			m_Info.bMotion = false;
		}

		m_Info.bMove = false;
	}


	int nLimit = CCube::GetLimit();
	int nNumUse = CCube::GetUse();
	// �U��
	if (nLimit - nNumUse > 0)
	{
		if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputMouse->GetTrigger(CMouse::MOUSE_LEFT) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
		{
			CBullet::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 15, m_Info.pos.z), m_Info.targetRot);
			//pSound->PlaySound(CSound::TYPE_HIT);
		}
	}
	// �ŏ��̒e���~�߂�
	BulletStop();

	// �ʒu�X�V
	MovePos(PLAYER_SPEED);
}

//========================================
// �L�[�{�[�h�̈ړ�����
//========================================
void CPlayer::MoveInput(DIRECTION drct)
{
	// --- ��� ---------------------------------
	m_Info.moveRot = m_Info.rot;	// �ړ�����

	// --- �ړ� ---------------------------------

	// �ړ������ɉ~��������
	m_Info.moveRot.y = D3DX_PI;

	switch (drct)
	{
	case DIRECTION_LEFT			:m_Info.moveRot.y *= -0.5f; break;	// ��
	case DIRECTION_RIGHT		:m_Info.moveRot.y *= 0.5f;	break;	// �E
	case DIRECTION_BACK			:m_Info.moveRot.y *= 0.0f;	break;	// ��
	case DIRECTION_FRONT		:m_Info.moveRot.y *= 1.0f;	break;	// ��O
	case DIRECTION_LEFT_BACK	:m_Info.moveRot.y *= -0.25f; break;	// ����
	case DIRECTION_LEFT_FRONT	:m_Info.moveRot.y *= -0.75f; break;	// ����O
	case DIRECTION_RIGHT_BACK	:m_Info.moveRot.y *= 0.25f; break;	// �E��
	case DIRECTION_RIGHT_FRONT	:m_Info.moveRot.y *= 0.75f; break;	// �E��O
	}

	if (!m_Info.bRotMove && m_Info.rot.y != m_Info.targetRot.y)
	{
		m_Info.bRotMove = true;
	}
}

//========================================
// �ړ�����
//========================================
void CPlayer::MovePos(float fMove)
{
	// --- �擾 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();		// �J����
	D3DXVECTOR3 posV = pCamera->GetInfo().posV;		// ���_
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;		// �����_
	CMotion *pMotion = CMotionModel::GetMotion();	// ���[�V�������
	bool pPlayMotion = pMotion->GetMotion();		// ���[�V�������s���Ă��邩

	if (!m_Info.bMove)
	{
		fMove = 0.0f;
	}

	if (m_Info.bMove)
	{
		// ���_���璍���_�܂ł̊p�x
		float fAngle
			= FindAngle(D3DXVECTOR3(posV.x, posV.z, 0.0f), D3DXVECTOR3(posR.x, posR.z, 0.0f));

		ControlAngle(&fAngle);

		// �p�x�̂��S�����ɂ���
		{
			if (fAngle < D3DX_PI * -0.75 ||
				fAngle > D3DX_PI * 0.75)
			{
				fAngle = 3.14f;
			}
			else if (fAngle > D3DX_PI * -0.25 &&
				fAngle < D3DX_PI * 0.25)
			{
				fAngle = 0.0f;
			}
			else if (fAngle > D3DX_PI * -0.75 &&
				fAngle < D3DX_PI * -0.25)
			{
				fAngle = -1.57f;
			}
			else if (fAngle > D3DX_PI * 0.25 &&
				fAngle < D3DX_PI * 0.75)
			{
				fAngle = 1.57f;
			}
		}
		m_Info.moveRot.y += fAngle;

		// �ړ����[�V����
		if (pMotion != NULL && !m_Info.bMotion)
		{
			pMotion->SetNumMotion(1,true);

			m_Info.bMotion = true;
			m_Info.bAction = true;
		}
	}
	else
	{
		if (pMotion != NULL && !m_Info.bMotion && !pPlayMotion)
		{
			pMotion->SetNumMotion(0,false);
		}
	}

	if (!pPlayMotion)
	{
		m_Info.bMotion = false;
	}

	m_Info.move.x += sinf(m_Info.moveRot.y) * fMove;
	m_Info.move.z += cosf(m_Info.moveRot.y) * fMove;
}

//========================================
// �ʒu�X�V
//========================================
void CPlayer::UpdatePos(void)
{
	// --- �擾 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();		// �J����

	{
		// �ړ��ʂ̑��
		m_Info.pos.x += m_Info.move.x;

		// �ړ��ʂ̌���
		m_Info.move.x *= 0.75f;

		// X�����̓����蔻��
		m_Info.pos = Collision(PRIO_BLOCK,TYPE_BLOCK,VECTOR_X, m_Info.pos);
		m_Info.pos = Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_X, m_Info.pos);
		m_Info.pos = Collision(PRIO_OBJECT, TYPE_ENEMY, VECTOR_X, m_Info.pos);
	}

	{
		// �ړ��ʂ̑��
		m_Info.pos.z += m_Info.move.z;

		// �ړ��ʂ̌���
		m_Info.move.z *= 0.75f;

		// Z�����̓����蔻��
		m_Info.pos = Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.pos);
		m_Info.pos = Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_Z, m_Info.pos);
		m_Info.pos = Collision(PRIO_OBJECT, TYPE_ENEMY, VECTOR_Z, m_Info.pos);


	}

	{
		// �ړ��ʂ̑��
		m_Info.pos.y += m_Info.move.y;

		//�x�̈ړ��ʂɏd�͂����Z
		m_Info.move.y -= (GRAVITY_POWER - m_Info.move.y) * GRAVITY_MAG;

		// Y�����̓����蔻��
		m_Info.pos = Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Y, m_Info.pos);

		float fSize = 10.0f;
		// �����蔻��i�������p�j
		if ((m_Info.pos.y - fSize) < (-120) &&
			(m_Info.posOld.y - fSize) >= (-120))
		{// ����������
			m_Info.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);

			CModel::SetPlayerShadow(true);
		}

		if (m_Info.pos.y <= -12.5)
		{
			CModel::SetPlayerShadow(false);
		}
	}

	// �ʒu�̐ݒ�
	SetPos(m_Info.pos);

	// �ڕW�����Ɉړ���������
	m_Info.targetRot = m_Info.moveRot;


	bool bStart = CTitle::IsStart();

	if (bStart)
	{
		// �J�����̒����_��ݒ�
		pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
	}
}

//========================================
// ���f���Ƃ̓����蔻��
//========================================
D3DXVECTOR3 CPlayer::Collision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(nPrio);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		// ��ނ��擾
		TYPE type = pObj->GetType();

		// �v���C���[�̊e�p�[�c�̎擾
		D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
		D3DXVECTOR3 RotOld = GetRotOld();	// ����(�ߋ�)
		D3DXVECTOR3 Scale = GetSize();
		float fSizeXZ = 20.0f;
		float fSizeY = 10.0f;

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

			if (type == TYPE_BLOCK)
			{
				CBlock *pBlock = dynamic_cast<CBlock*>(pObj);
				int nBlockType = pBlock->GetBlockType();

				if (nBlockType = MODEL_BOMB)
				{
					// ����̏C��
					fPairWidth *= 0.8f;		// ��
					fPairHeight *= 0.8f;	// ����
					fPairDepth *= 0.8f;		// ���s��
				}
			}

			fPairWidth = round(fPairWidth);
			fPairHeight = round(fPairHeight);
			fPairDepth = round(fPairDepth);

			// --- �����蔻�� ----------------------------------------------
			switch (vector)
			{
			case VECTOR_X: {	/* X���� */

				if (CollsionX(pos, PairPos, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_LEFT))
					{// ������߂荞��ł��鎞
						pos.x = (PairPos.x - fPairWidth) - fSizeXZ;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_RIGHT))
					{// �E����߂荞��ł��鎞
						pos.x = (PairPos.x + fPairWidth) + fSizeXZ;
					}
				}
			}
						   break;
			case VECTOR_Y: {	/* Y���� */

				if (CollsionY(pos, PairPos, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// ���ӂƉE�ӂ�����̕��̓����̎��A

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_DOWN))
					{// ������߂荞��ł��鎞
						pos.y = (PairPos.y - fPairHeight) - fSizeY;

						if (nType != TYPE_ENEMY)
						{
							//�v���C���[���㏸��
							if (m_Info.move.y > 0.0f)
							{
								//�x�̈ړ��ʂ�0��
								m_Info.move.y = 0.0f;
							}
						}
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_UP))
					{// �ォ��߂荞��ł��鎞

						if (nType != TYPE_CUBE)
						{
							pos.y = (PairPos.y + fPairHeight) + fSizeY;
						}
						else
						{
							pos.y = (PairPos.y + fPairHeight) + fSizeY;
						}

						m_Info.move.y = 0.0f;
					}
				}
			}
						   break;
			case VECTOR_Z: {	/* Z���� */

				if (CollsionZ(pos, PairPos, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_BACK))
					{// ��납��߂荞��ł��鎞
						pos.z = (PairPos.z - fPairDepth) - fSizeXZ;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_FRONT))
					{// �O����߂荞��ł��鎞
						pos.z = (PairPos.z + fPairDepth) + fSizeXZ;
					}
				}
			}
						   break;
			}
		}
		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
	return pos;
}

//========================================
// �e��~
//========================================
void CPlayer::BulletStop(void)
{
	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(PRIO_OBJECT);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		 // ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		TYPE type = pObj->GetType();	// ��ނ��擾

		if (type == TYPE_BULLET)
		{// ��ނ��o���b�g�̎��A

			// �_�C�i�~�b�N�L���X�g����
			CBullet *pBullet = dynamic_cast<CBullet*>(pObj);


			if (pInputKeyboard->GetTrigger(DIK_E) || pInputMouse->GetTrigger(CMouse::MOUSE_4) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_X) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_B))
			{
				// ID�擾
				int nID = pBullet->GetID();
				bool nCubeSet = false;

				// �擪�t���O�̎擾
				nCubeSet = CCube::GetLeadSet();

				if (!nCubeSet)
				{
					int nType = pBullet->GetType();
					D3DXVECTOR3 pos = pBullet->GetPos();

					// �L���[�u�̐���
					CCube::Create(nType, pos, CUBE_LIFE1);
					CCube::SetCubeLead(true);

					// �I�u�W�F�N�g�j��
					pObj->Uninit();
				}
			}
		}
		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
}