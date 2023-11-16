//========================================
// 
// �I�u�W�F�N�g�y X�t�@�C�� �z����
// 
//========================================
// *** objectX.cpp ***
//========================================
#include "objectX.h"
#include "../manager.h"
#include "../system/renderer.h"
#include "../system/texture.h"
#include "model\model.h"

//========================================
// �R���X�g���N�^
//========================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	// �l���N���A����
	m_pos = INIT_D3DXVECTOR3;		// �ʒu
	m_posOld = INIT_D3DXVECTOR3;	// �ʒu(�ߋ�)
	m_rot = INIT_D3DXVECTOR3;		// ����
	m_scale = INIT_D3DXVECTOR3;		// �X�P�[��
	m_color = INIT_D3DXCOLOR;		// �F
	m_nModelID = 0;					// ���f��ID
	m_bColor = false;
}

//========================================
// �f�X�g���N�^
//========================================
CObjectX::~CObjectX()
{

}

//========================================
// ����
//========================================
CObjectX *CObjectX::Create(void)
{
	CObjectX *pObj3D = NULL;

	if (pObj3D != NULL)
	{
		return pObj3D;
	}

	// �I�u�W�F�N�g3D�̐���
	pObj3D = new CObjectX;

	// ����������
	pObj3D->Init();

	return pObj3D;
}
//========================================
// ������
//========================================
HRESULT CObjectX::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �X�P�[��
	SetColor({ 1.0f,1.0f,1.0f,1.0f });			// �F

	m_pModel = CModel::Create();

	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(m_rot);
	m_pModel->SetScale(m_scale);
	m_pModel->SetColor(m_color);
	m_pModel->SetModelID(0);

	// ���f���̍X�V
	m_pModel->SetModelID(m_nModelID);
	m_size = m_pModel->GetSize(m_nModelID);
	m_Width = m_pModel->GetWidth(m_nModelID);
	m_Height = m_pModel->GetHeight(m_nModelID);
	m_Depth = m_pModel->GetDepth(m_nModelID);

	return S_OK;
}

//========================================
// �I��
//========================================
void CObjectX::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;	//�������J��
		m_pModel = NULL;	//�|�C���^��NULL�ɂ���
	}

	// �I�u�W�F�N�g�̉��
	this->Release();
}

//========================================
// �X�V
//========================================
void CObjectX::Update(void)
{
	// �F�̍X�V
	m_pModel->SetColor(m_color);
}

//========================================
// �`��
//========================================
void CObjectX::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.y, m_scale.x, m_scale.z);		// �X�P�[���g�k�s��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);			// �s��|���Z�֐� 

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��ݒ�
	m_pModel->Draw(m_mtxWorld, true);

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
