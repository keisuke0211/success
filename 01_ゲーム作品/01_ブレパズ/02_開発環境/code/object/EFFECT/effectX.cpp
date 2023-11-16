//========================================
//
// �G�t�F�N�g�y ���f�� �z
//
//========================================
// *** effectX.cpp ***
//=======================================
#include "effectX.h"
#include "../../manager.h"
#include "../../scene/pause.h"
#include "../../system/renderer.h"

//========================================
// �R���X�g���N�^
//========================================
CEffectX::CEffectX(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
	m_Info.fRadius = INIT_FLOAT;
}

//========================================
// �f�X�g���N�^
//========================================
CEffectX::~CEffectX()
{

}

//========================================
// ����
//========================================
CEffectX *CEffectX::Create(void)
{
	CEffectX *pEnemy = new CEffectX;

	pEnemy->SetModel(MODEL_EFFECT_00);

	// ����������
	pEnemy->Init();

	return pEnemy;
}

//========================================
// ������
//========================================
HRESULT CEffectX::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_EFFECT);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nLife = 10;
	m_Info.fRadius = 0.0f;
	m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);
	m_Info.nType = 0;

	// �ݒ�
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// �I��
//========================================
void CEffectX::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CEffectX::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		// �ʒu�̑��
		m_Info.posOld = m_Info.pos;

		// �ʒu�̑��
		m_Info.pos.x += m_Info.move.x;
		m_Info.move.x += (0.0f - m_Info.move.x) * 0.05f;

		m_Info.pos.y += m_Info.move.y;
		m_Info.move.y += (0.0f - m_Info.move.y) * 0.05f;

		m_Info.pos.z += m_Info.move.z;
		m_Info.move.z += (0.0f - m_Info.move.z) * 0.05f;

		// �ʒu�ƌ����ݒ�
		SetPos(m_Info.pos);
		SetRot(m_Info.rot);

		// �F�E�T�C�Y�̐���
		if (m_Info.nType != 1)
		{
			m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
			m_Info.col.a *= ((float)m_Info.nLife / m_Info.nLifeMax);
		}

		// �T�C�Y�̍X�V
		m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

		// �T�C�Y�ƐF�̐ݒ�
		SetScale(m_Info.size);
		SetColor(m_Info.col);

		if (--m_Info.nLife <= 0)
		{// �������s������

			Uninit();
			return;
		}

		CObjectX::Update();
	}
}

//========================================
// �`��
//========================================
void CEffectX::Draw(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObjectX::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}