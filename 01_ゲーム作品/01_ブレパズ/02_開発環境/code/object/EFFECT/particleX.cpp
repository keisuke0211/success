//========================================
//
// �G�t�F�N�g�y ���f�� �z
//
//========================================
// *** effectX.cpp ***
//=======================================
#include "particleX.h"
#include "effectX.h"

//========================================
// �R���X�g���N�^
//========================================
CParticleX::CParticleX(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.speed = INIT_D3DXVECTOR3;
	m_Info.nForm = 0;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.fRadius = 0.0;

	m_Info.aColor.col = INIT_D3DXCOLOR;
	m_Info.aColor.colRandamMax = INIT_D3DXCOLOR;
	m_Info.aColor.colRandamMin = INIT_D3DXCOLOR;
	m_Info.aColor.bColRandom = false;
}

//========================================
// �f�X�g���N�^
//========================================
CParticleX::~CParticleX()
{

}

//========================================
// ����
//========================================
CParticleX *CParticleX::Create(void)
{
	CParticleX *pParticle = new CParticleX;

	// ����������
	pParticle->Init();

	return pParticle;
}

//========================================
// ������
//========================================
HRESULT CParticleX::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_PARTICLE);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.aColor.col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_Info.nLife = 10;
	m_Info.fRadius = 0.0f;
	m_Info.nType = 0;

	// �ݒ�
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.aColor.col);

	return S_OK;
}

//========================================
// �I��
//========================================
void CParticleX::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CParticleX::Update(void)
{
	for (int nForm = 0; nForm < m_Info.nForm; nForm++)
	{
		//�p�x�̐ݒ�
		float fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;

		if (m_Info.speed.x >= 0.1f)
		{
			float fSpeedX = (float)(rand() % (2 * (int)m_Info.speed.x)) / (int)m_Info.speed.x + 1;
			m_Info.move.x = sinf(fRot) * fSpeedX;
		}

		if (m_Info.speed.x >= 0.1f)
		{
			float fSpeedY = (float)(rand() % (2 * (int)m_Info.speed.y)) / (int)m_Info.speed.y + 1;
			m_Info.move.y = fSpeedY;
		}

		if (m_Info.speed.x >= 0.1f)
		{
			float fSpeedZ = (float)(rand() % (2 * (int)m_Info.speed.z)) / (int)m_Info.speed.z + 1;
			m_Info.move.z = cosf(fRot) * fSpeedZ;
		}
		
		// �T�C�Y
		switch (m_Info.nType)
		{
		case 0:
			m_Info.fRadius = (float)(rand() % ((int)4) + (int)2) / (float)10;
			break;

		case 1:
			m_Info.fRadius = (float)(rand() % ((int)7) + (int)2) / (float)10;
			break;

		case 2:
			m_Info.fRadius = (float)(rand() % ((int)2) + (int)1) / (float)10;
			break;
		}


		// �G�t�F�N�g�̐���
		CEffectX *pObj = CEffectX::Create();
		pObj->Eff_SetPos(m_Info.pos);
		pObj->Eff_SetRot(m_Info.rot);
		pObj->Eff_SetMove(m_Info.move);
		pObj->Eff_SetType(m_Info.nType);
		pObj->Eff_SetLife(m_Info.nLife);
		pObj->Eff_SetCol(m_Info.aColor.col);
		pObj->Eff_SetRadius(m_Info.fRadius);
		pObj->SetPos(m_Info.pos);
		pObj->SetRot(m_Info.rot);
		pObj->SetColor(m_Info.aColor.col);
	}

	Uninit();
	return;
}