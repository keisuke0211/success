//========================================
// 
// �J��������
// 
//========================================
// *** camera.cpp ***
//========================================
#include "camera.h"
#include "../manager.h"
#include "renderer.h"
#include "input.h"
#include "../scene/pause.h"
#include "../scene/title.h"
#include "../scene/game.h"
#include "../object/model/block.h"

//****************************************
// �}�N����`
//****************************************
#define CAMERA_ROT_FORCE_BY_CURSOR	(D3DXVECTOR3(0.0005f,0.00075f,0.0f))	// �J�[�\���̉�]��
#define CAMERA_ROT_FORCE_BY_STICK	(D3DXVECTOR3(0.004f,-0.006f,0.0f))		// �X�e�B�b�N�̉�]��
#define CAMERA_SPIN_DAMP			(0.9f)									// ��]�̌����l
#define CAMERA_SPEED				(50)									// �ړ����x�iX�EZ���W�j
#define ROT_DIAMETER	(0.15f)												// ��]�{��

//========================================
// �R���X�g���N�^
//========================================
CCamera::CCamera()
{
	/* �J������� */
	m_Info.posR = INIT_D3DXVECTOR3;		// ���݂̎��_
	m_Info.posV = INIT_D3DXVECTOR3;		// ���݂̒����_
	m_Info.posOldR = INIT_D3DXVECTOR3;	// �O��̎��_R3;
	m_Info.posOldV = INIT_D3DXVECTOR3;	// �O��̒����_R3;
	m_Info.vecU = INIT_VEC;				// ������x�N�g��
	m_Info.rot = INIT_D3DXVECTOR3;		// ����
	m_Info.targetRot = INIT_D3DXVECTOR3;// �ڕW����
	m_Info.spin = INIT_D3DXVECTOR3;		// ��]��
	m_Info.fDistance = INIT_FLOAT;		// ����
	m_Info.fTargetDistance = INIT_FLOAT;// �ڕW����
	m_Info.fHeight = INIT_FLOAT;		// ����
	m_Info.fTargetHeight = INIT_FLOAT;	// �ڕW����
	m_Info.fVerticalMove = INIT_FLOAT;	// �c�̈ړ���
	m_Info.nScreen = SCREEN_NONE;		// ���e���[�h
	m_Info.bRotMove = false;
	m_Info.nRotType = 0;

	/* �ۑ���� */
	m_Save.posV = INIT_D3DXVECTOR3;		// ���_
	m_Save.posR = INIT_D3DXVECTOR3;		// �����_
	m_Save.rot = INIT_D3DXVECTOR3;		// ����
	m_Save.spin = INIT_D3DXVECTOR3;		// ��]��
	m_Save.fVerticalMove = INIT_FLOAT;	// �c�̈ړ���
	m_Save.fHeight = INIT_FLOAT;		// ����
	m_Save.fDistance = INIT_FLOAT;		// ����
}

//========================================
// �f�X�g���N�^
//========================================
CCamera::~CCamera()
{

}

//========================================
// ������
//========================================
HRESULT CCamera::Init(void)
{
	/* �J������� */
	m_Info.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̈ʒu
	m_Info.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����ꏊ
	m_Info.posOldR = INIT_D3DXVECTOR3;				// �O��̎��_R3;
	m_Info.posOldV = INIT_D3DXVECTOR3;				// �O��̒����_R3;
	m_Info.vecU = INIT_VEC;							// ������x�N�g��
	m_Info.rot = INIT_D3DXVECTOR3;					// ����
	m_Info.targetRot = INIT_D3DXVECTOR3;			// �ڕW����
	m_Info.spin = INIT_D3DXVECTOR3;					// ��]��
	m_Info.fDistance = 300.0f;						// ����
	m_Info.fTargetDistance = 300.0f;				// �ڕW����
	m_Info.fHeight = 0.05f;							// ����
	m_Info.fTargetHeight = 0.05f;					// �ڕW����
	m_Info.fVerticalMove = INIT_FLOAT;				// �c�̈ړ���
	m_Info.nScreen = SCREEN_3D;						// ���e���[�h
	m_Info.bRotMove = false;
	m_Info.nRotType = 0;

	return S_OK;
}

//========================================
// �I��
//========================================
void CCamera::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CCamera::Update(void)
{
	// --- �擾---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	// �ߋ��̈ʒu����
	m_Info.posOldV = m_Info.posV;
	m_Info.posOldR = m_Info.posR;

	// ���_�ړ�
	{
		bool bPause = CPause::IsPause();
		bool bClear = CGame::IsEnd();

		if (!bPause)
		{
			bool bStart = CTitle::IsStart();
			if (bStart && !bClear)
			{
				if (pInputMouse->GetTrigger(CMouse::MOUSE_RIGHT))
				{// �}�E�X�̉E�{�^����������Ă����
					m_Info.nRotType++;
				}
				else if (pInputJoypad->GetTrigger(CJoypad::JOYKEY_LEFT_SHOULDER) || pInputJoypad->GetStick().aAngleTrigger[CJoypad::STICK_TYPE_RIGHT][CJoypad::STICK_ANGLE_LEFT])
				{
					m_Info.nRotType++;
				}
				else if (pInputJoypad->GetTrigger(CJoypad::JOYKEY_RIGHT_SHOULDER) || pInputJoypad->GetStick().aAngleTrigger[CJoypad::STICK_TYPE_RIGHT][CJoypad::STICK_ANGLE_RIGHT])
				{
					m_Info.nRotType--;
				}

				IntLoopControl(&m_Info.nRotType, ROT_MAX, 0);

				switch (m_Info.nRotType)
				{
				case ROT_UP:
					m_Info.spin.y = 0.0f;
					break;
				case ROT_RIGHT:
					m_Info.spin.y = -1.57f;
					break;
				case ROT_DOWN:
					m_Info.spin.y = 3.14f;
					break;
				case ROT_LEFT:
					m_Info.spin.y = 1.57f;
					break;
				}
			}
		}
	}

	if (m_Info.bRotMove)
	{
		m_Info.rot.y += m_Info.spin.y;					// �����Ɉړ���������
		m_Info.spin *= CAMERA_SPIN_DAMP;				// ��]�ʂ�����
	}
	else
	{
		m_Info.targetRot = m_Info.spin;				// �ڕW�����Ɉړ���������
	}
	m_Info.fTargetHeight = m_Info.fVerticalMove;	// �ڕW�����Ɉړ��ʂ���

	// �����𐧌�
	RotControl(&m_Info.rot);

	// �����𐧌�
	FloatControl(&m_Info.fHeight, D3DX_PI * 0.30f, D3DX_PI * 0.01f);

	if (!m_Info.bRotMove)
	{
		// ������ڕW�Ɍ����Đ��ڂ���
		m_Info.rot.y += AngleDifference(m_Info.rot.y, m_Info.targetRot.y) * ROT_DIAMETER;
	}

	// ������ڕW�Ɍ����Đ��ڂ���
	m_Info.fHeight += AngleDifference(m_Info.fHeight, m_Info.fTargetHeight) * ROT_DIAMETER;

	// ������ڕW�����Ɍ����Đ��ڂ���
	m_Info.fDistance += AngleDifference(m_Info.fDistance, m_Info.fTargetDistance) * ROT_DIAMETER;

	if (m_Info.bRotMove)
	{
		m_Info.bRotMove = false;
	}
}

//========================================
// �ݒ�
//========================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	switch (m_Info.nScreen)
	{
	case SCREEN_2D: {	// ���s���e
		D3DXMatrixOrthoLH(&m_Info.mtxProjection,
			SCREEN_WIDTH / 2,						/* ��ʂ̕� */
			SCREEN_HEIGHT / 2,						/* ��ʂ̍��� */
			1.0f,									/* Z�l�̍ŏ��l */
			1500.0f);								/* Z�l�̍ő�l */
	}
		break;

	case SCREEN_3D: {	// �������e
		D3DXMatrixPerspectiveFovLH(&m_Info.mtxProjection,
			D3DXToRadian(45.0f),							/* ����p */
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		/*��ʂ̃A�X�y�N�g��*/
			10.0f,											/*Z�l�̍ŏ��l*/
			2500.0f);										/*Z�l�̍ő�l*/
	}
		break;
	}

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Info.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_Info.mtxView,
		&m_Info.posV,		/*���_*/
		&m_Info.posR,		/*�����_*/
		&m_Info.vecU);		/*������x�N�g��*/

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_Info.mtxView);
}

//========================================
// �J�����̉�ʐݒ�
//========================================
void CCamera::SetScreen(void)
{
	// ���e���[�h�̐؂�ւ�

	switch (m_Info.nScreen)
	{
	case SCREEN_2D: {	// ���s���e
		
		// �ۑ�����������
		m_Info.posV = m_Save.posV;						// ���_
		m_Info.posR = m_Save.posR;						// �����_
		m_Info.rot  = m_Save.rot;						// ����
		m_Info.spin = m_Save.spin;						// ��]��
		m_Info.fTargetHeight = m_Save.fHeight;			// ����
		m_Info.fDistance = m_Save.fDistance;			// ����
		m_Info.fVerticalMove = m_Save.fHeight;			// �c�̈ړ���

		m_Info.nScreen = SCREEN_3D;
	}
	 break;

	case SCREEN_3D: {	// �������e
		
		// ����ۑ�����
		m_Save.posV = m_Info.posV;						// ���_
		m_Save.posR = m_Info.posR;						// �����_
		m_Save.rot	= m_Info.rot;						// ����
		m_Save.spin	= m_Info.spin;						// ��]��
		m_Save.fHeight = m_Info.fHeight;				// ����
		m_Save.fDistance = m_Info.fDistance;			// ����
		m_Save.fVerticalMove = m_Info.fVerticalMove;	// �c�̈ړ���

		// ������������
		m_Info.rot.y = 0.0f;

		m_Info.fVerticalMove = 0.05f;

		m_Info.nScreen = SCREEN_2D;
	}
	 break;
	}
}

//========================================
// �J�����̉�]����
//========================================
void CCamera::AxisRotationCamera(DIRECTION drct, float fRot, int nIdx)
{
	// �����ɉ����Č����̈ړ��ʂ��X�V
	switch (drct)
	{
	case DIRECTION_UP:m_Info.fVerticalMove += fRot; break;
	case DIRECTION_DOWN:m_Info.fVerticalMove -= fRot; break;
	case DIRECTION_LEFT:m_Info.spin.y -= fRot; break;
	case DIRECTION_RIGHT:m_Info.spin.y += fRot; break;
	}
}

//========================================
// �J�����̎��_�ݒ�
//========================================
void CCamera::SetPosV(D3DXVECTOR3 pos, int nIdx)
{
	// ���_�̈ʒu����
	m_Info.posV = pos;

	// �����_�̈ʒu��ݒ�
	m_Info.posR.x = m_Info.posV.x + (sinf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
	m_Info.posR.y = m_Info.posV.y + (m_Info.fDistance * m_Info.fHeight);
	m_Info.posR.z = m_Info.posV.z + (cosf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
}

//========================================
// �J�����̒����_�ݒ�
//========================================
void CCamera::SetPosR(D3DXVECTOR3 pos, int nIdx)
{
	// �����_�̈ʒu����
	m_Info.posR = pos;

	// ���_�̈ʒu��ݒ�
	m_Info.posV.x = m_Info.posR.x + (sinf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
	m_Info.posV.y = m_Info.posR.y + (m_Info.fDistance * m_Info.fHeight);
	m_Info.posV.z = m_Info.posR.z + (cosf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
}

//========================================
// �J�����̌����ݒ�
//========================================
void CCamera::SetRot(D3DXVECTOR3 rot, int nIdx)
{
	m_Info.rot = rot;
	m_Info.targetRot = rot;
	m_Info.bRotMove = true;
}

//========================================
// �J�����̍���
//========================================
void CCamera::SetHeigth(float Heigth)
{
	m_Info.fVerticalMove = Heigth;
}

//========================================
// �J�����̋���
//========================================
void CCamera::SetDistance(float fDistance)
{
	m_Info.fTargetDistance = fDistance;
}
