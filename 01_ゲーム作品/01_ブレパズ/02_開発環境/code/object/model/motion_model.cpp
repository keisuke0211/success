//========================================
// 
// ���[�V�������f������
// 
//========================================
// *** motion_model.cpp ***
//========================================
#include "motion.h"
#include "motion_model.h"
#include "../../manager.h"
#include "../../system/renderer.h"


//========================================
// �R���X�g���N�^
//========================================
CMotionModel::CMotionModel(int nPriority) : CObject(nPriority)
{
	m_pMotion = NULL;
	m_pos = INIT_D3DXVECTOR3;
	m_posOld = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
	m_size = INIT_D3DXVECTOR3;
}

//========================================
// �f�X�g���N�^
//========================================
CMotionModel::~CMotionModel()
{

}

//========================================
// ����
//========================================
CMotionModel * CMotionModel::Create(void)
{
	CMotionModel *pMotionModel = NULL;

	pMotionModel = new CMotionModel;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMotionModel != NULL);

	// ���l�̏�����
	pMotionModel->Init();

	// �C���X�^���X��Ԃ�
	return pMotionModel;
}

//========================================
// ������
//========================================
HRESULT CMotionModel::Init(void)
{
	// �ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				// �X�P�[��
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// �����蔻��
	m_quat = { 0.0f,0.0f,0.0f,1.0f };						// �N�I�[�^�j�I��
	SetIsColor(false);										// �F�̕ύX
	SetColor({ 1.0f,1.0f,1.0f,1.0f });						// �F

	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXQuaternionRotationAxis(&m_quat, &vecY, D3DX_PI);	// �N�I�[�^�j�I���ɂ���]
	return S_OK;
}

//========================================
// �I��
//========================================
void CMotionModel::Uninit(void)
{
	if (m_pMotion != NULL)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//========================================
// �X�V
//========================================
void CMotionModel::Update(void)
{
	if (m_pMotion != NULL)
	{// ���[�V�����ԍ��̐ݒ�
		m_pMotion->Update();
	}
}

//========================================
// �`��
//========================================
void CMotionModel::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxRotQuat, mtxScale;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);									// �s�񏉊����֐�

	// �N�H�[�^�j�I���̎g�p�����p���̐ݒ�
	D3DXMatrixRotationQuaternion(&mtxRotQuat, &m_quat);					// �N�I�[�^�j�I���ɂ��s���]

	D3DXMatrixScaling(&mtxScale, m_scale.y, m_scale.x, m_scale.z);		// �X�P�[���g�k�s��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);			// �s��|���Z�֐� 

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// �s���]�֐�

	D3DXMatrixMultiply(&mtxRot, &mtxRot, &mtxRotQuat);					// �s��|���Z�֐� 
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_pMotion != NULL)
	{// �p�[�c�̕`��ݒ�
		m_pMotion->SetParts(m_mtxWorld, m_bcolor, m_color);
	}
}


//========================================
// ���[�V�����̐ݒ�
//========================================
void CMotionModel::SetMotion(const char * pName)
{
	if (m_pMotion != NULL)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(0);

	// ���[�V�����ԍ��̐ݒ�
	m_pMotion->SetNumMotion(0,false);
}

//========================================
// �F�ݒ�
//========================================
void CMotionModel::ChangeColar(D3DXCOLOR color)
{
	SetColor(color);
	SetIsColor(true);
}