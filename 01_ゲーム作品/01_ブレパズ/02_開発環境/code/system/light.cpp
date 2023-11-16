//========================================
// 
// ���C�g����
// 
//========================================
// *** light.cpp ***
//========================================
#include "light.h"
#include "../manager.h"
#include "renderer.h"

//========================================
// �R���X�g���N�^
//========================================
CLight::CLight()
{

}

//========================================
// �f�X�g���N�^
//========================================
CLight::~CLight()
{

}

//========================================
// ������
//========================================
HRESULT CLight::Init(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;//�ݒ�p�����x�N�g��

	//���C�g�̏����N���A����
	ZeroMemory(&m_lihgt, sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_lihgt.Type = D3DLIGHT_DIRECTIONAL;

	for (int nCntLight = 0; nCntLight < NUM_LIGHT; nCntLight++)
	{
		//���C�g�̊g�U����ݒ�
		m_lihgt.Diffuse = m_lihgtInformation[nCntLight].col;

		//���C�g�̕�����ݒ�
		vecDir = m_lihgtInformation[nCntLight].rot;

		//�x�N�g���𐳋K��
		D3DXVec3Normalize(&vecDir, &vecDir);

		m_lihgt.Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_lihgt);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
	return S_OK;
}

//========================================
// �I��
//========================================
void CLight::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CLight::Update(void)
{

}