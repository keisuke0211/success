//========================================
// 
// �����֘A
// 
//========================================
//  *** physics.cpp ***
//========================================
#include "physics.h"

//========================================
// �R���X�g���N�^
//========================================
CPhysics::CPhysics()
{

}

//========================================
// �f�X�g���N�^
//========================================
CPhysics::~CPhysics()
{

}
//========================================
// int�^�̒l�̐��䏈��
//========================================
void CPhysics::IntControl(int *pData, int nMax, int nMin)
{
	if (*pData > nMax)
	{// �ő�l�������Ă������A
	 // �ő�l����
		*pData = nMax;
	}
	else if (*pData < nMin)
	{// �ŏ��l��������Ă������A
	 // �ŏ��l����
		*pData = nMin;
	}
}

//========================================
// int�^�̒l�̃��[�v���䏈��
//========================================
void CPhysics::IntLoopControl(int *pData, int nMax, int nMin)
{
	if (*pData >= nMax)
	{// �ő�l�ȏ�̎��A
	 // �ŏ��l����
		*pData = nMin;
	}
	else if (*pData < nMin)
	{// �ŏ��l��������Ă������A
	 // �ő�l����
		*pData = nMax - 1;
	}
}

//========================================
// float�^�̒l�̐��䏈��
//========================================
void CPhysics::FloatControl(float *pData, float fMax, float fMin)
{
	if (*pData > fMax)
	{// �ő�l�������Ă������A
	 // �ő�l����
		*pData = fMax;
	}
	else if (*pData < fMin)
	{// �ŏ��l��������Ă������A
	 // �ŏ��l����
		*pData = fMin;
	}
}

//========================================
// float�^�̒l�̃��[�v���䏈��
//========================================
void CPhysics::FloatLoopControl(float *pData, float fMax, float fMin)
{
	if (*pData > fMax)
	{// �ő�l�������Ă������A
	 // �ő�l�����Z
		*pData -= (fMax - fMin);
	}
	else if (*pData < fMin)
	{// �ŏ��l��������Ă������A
	 // �ő�l�����Z
		*pData += (fMax - fMin);
	}
}

//========================================
// 2�_�̊p�x�����߂�
//========================================
float CPhysics::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos)
{
	float fAngle;	// �p�x

	fAngle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);

	fAngle = fAngle;

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1;

	return fAngle;
}

//========================================
// �����̐��䏈��
//========================================
void CPhysics::RotControl(D3DXVECTOR3 *pRot)
{
	FloatLoopControl(&pRot->x, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->y, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->z, D3DX_PI, -D3DX_PI);
}

//========================================
// �p�x�̍������߂�
//========================================
float CPhysics::AngleDifference(float fAngle, float fTargetAngle)
{
	float fAngleDifference = 0.0f;	// �p�x�̍�

	// �p�x�𐧌䂷��
	ControlAngle(&fAngle);

	if ((fAngle >= 0.0f) && (fTargetAngle >= 0.0f))
	{// �ǂ���̊p�x���v���X�̎��A
	 // �p�x�̍���ݒ�
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}
	else if ((fAngle <= 0.0f) && (fTargetAngle <= 0.0f))
	{// �ǂ���̊p�x���}�C�i�X�̎��A
	 // �p�x�̍���ݒ�
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}

	if ((fAngle >= 0.0f) && (fTargetAngle <= 0.0f))
	{// �p�x���v���X�ŁA�ڕW�p�x���}�C�i�X�̎��A
		if (fAngle - D3DX_PI <= fTargetAngle)
		{// �ڕW�p�x�������ɋ߂����A
		 // �p�x�̍���ݒ�
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle - D3DX_PI >= fTargetAngle)
		{// �ڕW�p�x���㑤�ɋ߂����A
		 // �p�x�̍���ݒ�
			fAngleDifference = (D3DX_PI - fAngle) + (D3DX_PI + fTargetAngle);
		}
	}

	if ((fAngle <= 0.0f) && (fTargetAngle >= 0.0f))
	{// �p�x���}�C�i�X�ŁA�ڕW�p�x���v���X�̎��A
		if (fAngle + D3DX_PI >= fTargetAngle)
		{// �ڕW�p�x�������ɋ߂����A
		 // �p�x�̍���ݒ�
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle + D3DX_PI <= fTargetAngle)
		{// �ڕW�p�x���㑤�ɋ߂����A
		 // �p�x�̍���ݒ�
			fAngleDifference = -(D3DX_PI + fAngle) - (D3DX_PI - fTargetAngle);
		}
	}

	return fAngleDifference;
}

//========================================
// �p�x�𐧌䂷��
//========================================
void CPhysics::ControlAngle(float *pAngle)
{
	if (*pAngle > D3DX_PI)
	{// �v���X�̉~�����������Ă��鎞�A
		*pAngle = (D3DX_PI - (*pAngle - D3DX_PI)) * -1;
	}
	else if (*pAngle < -D3DX_PI)
	{// �}�C�i�X�̉~������������Ă��鎞�A
		*pAngle = (D3DX_PI + (*pAngle + D3DX_PI));
	}
}

//========================================
// �ʒu�̍������߂�
//========================================
float CPhysics::PosDifference(float fPos, float fTargetPos)
{
	float fPosDifference = 0.0f;	// �ʒu�̍�

	if ((fPos >= 0.0f) && (fTargetPos >= 0.0f))
	{// �ǂ���̊p�x���v���X�̎��A
	 // �p�x�̍���ݒ�
		fPosDifference = fTargetPos - fPos;

		return fPosDifference;
	}
	else if ((fPos <= 0.0f) && (fTargetPos <= 0.0f))
	{// �ǂ���̊p�x���}�C�i�X�̎��A
	 // �p�x�̍���ݒ�
		fPosDifference = fTargetPos - fPos;

		return fPosDifference;
	}

	return fPosDifference;
}

//========================================
// �Q�_�̋��������߂�
//========================================
D3DXVECTOR3 Length(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos)
{
	D3DXVECTOR3 PosDifference = INIT_D3DXVECTOR3;

	return PosDifference;
}

//========================================
// �����蔻��(�S����)
//========================================
bool CPhysics::Collsion(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize)
{
	// ����t���O
	bool bHit = false;

	if ((pos.x + size.x) > (PairPos.x - PairSize.x) &&
		(pos.x - size.x) < (PairPos.x + PairSize.x) &&
		(pos.y + size.y) > (PairPos.y - PairSize.y) &&
		(pos.y - size.y) < (PairPos.y + PairSize.y) &&
		(pos.z + size.z) > (PairPos.z - PairSize.z) &&
		(pos.z - size.z) < (PairPos.z + PairSize.z))
	{// �u���b�N��������ɂ��鎞�A

		return TRUE;
	}

	return FALSE;
}

//========================================
// �����蔻��(��)
//========================================
bool CPhysics::CollsionX(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize)
{
	if ((pos.z + size.z) > (PairPos.z - PairSize.z) &&
		(pos.z - size.z) < (PairPos.z + PairSize.z) &&
		(pos.y + size.y) > (PairPos.y - PairSize.y) &&
		(pos.y - size.y) < (PairPos.y + PairSize.y))
	{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

		return TRUE;
	}
	return FALSE;
}

//========================================
// �����蔻��(��)
//========================================
bool CPhysics::CollsionY(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize)
{
	if ((pos.x + size.x) > (PairPos.x - PairSize.x) &&
		(pos.x - size.x) < (PairPos.x + PairSize.x) &&
		(pos.z + size.z) > (PairPos.z - PairSize.z) &&
		(pos.z - size.z) < (PairPos.z + PairSize.z))
	{// ���ӂƉE�ӂ�����̕��̓����̎��A

		return TRUE;
	}
	return FALSE;
}

//========================================
// �����蔻��(��)
//========================================
bool CPhysics::CollsionZ(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize)
{
	if ((pos.x + size.x) > (PairPos.x - PairSize.x) &&
		(pos.x - size.x) < (PairPos.x + PairSize.x) &&
		(pos.y + size.y) > (PairPos.y - PairSize.y) &&
		(pos.y - size.y) < (PairPos.y + PairSize.y))
	{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

		return TRUE;
	}
	return FALSE;
}

//========================================
// �����蔻��(�w�����)
//========================================
bool CPhysics::CollsionDirection(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 PosOld, D3DXVECTOR3 PairPosOld, D3DXVECTOR3 size, D3DXVECTOR3 PairSize, DIRECTION nDirection)
{
	switch (nDirection)
	{
	case CPhysics::DIRECTION_UP:
	{
		if ((pos.y - size.y) < (PairPos.y + PairSize.y) &&
			(PosOld.y - size.y) >= (PairPosOld.y + PairSize.y))
		{// �ォ��߂荞��ł��鎞
			return TRUE;
		}
	}
		break;
	case CPhysics::DIRECTION_DOWN:
	{
		if ((pos.y + size.y) > (PairPos.y - PairSize.y) &&
			(PosOld.y + size.y) <= (PairPosOld.y - PairSize.y))
		{// ������߂荞��ł��鎞
			return TRUE;
		}
	}
		break;
	case CPhysics::DIRECTION_LEFT:
	{
		if ((pos.x + size.x) > (PairPos.x - PairSize.x) &&
			(PosOld.x + size.x) <= (PairPosOld.x - PairSize.x))
		{// ������߂荞��ł��鎞
			return TRUE;
		}
	}
		break;
	case CPhysics::DIRECTION_RIGHT:
	{
		if ((pos.x - size.x) < (PairPos.x + PairSize.x) &&
			(PosOld.x - size.x) >= (PairPosOld.x + PairSize.x))
		{// �E����߂荞��ł��鎞
			return TRUE;
		}
	}
		break;
	case CPhysics::DIRECTION_BACK:
	{
		if ((pos.z + size.z) > (PairPos.z - PairSize.z) &&
			(PosOld.z + size.z) <= (PairPosOld.z - PairSize.z))
		{// ��납��߂荞��ł��鎞
			return TRUE;
		}
	}
		break;
	case CPhysics::DIRECTION_FRONT:
	{
		if ((pos.z - size.z) < (PairPos.z + PairSize.z) &&
			(PosOld.z - size.z) >= (PairPosOld.z + PairSize.z))
		{// �O����߂荞��ł��鎞
			return TRUE;
		}
	}
		break;
	}

	return FALSE;
}
