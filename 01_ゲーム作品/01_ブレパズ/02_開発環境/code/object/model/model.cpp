//========================================
// 
// ���f������
// 
//========================================
// *** objectX.cpp ***
//========================================
#include "model.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"

//========================================
// �ÓI�ϐ�
//========================================
CModel::MODEL_MATERIAL *CModel::m_material = NULL;	// �}�e���A�����
int CModel::m_nMaxModel = 0;						// ���f����		
float CModel::m_Width = NULL;
float CModel::m_Height = NULL;
float CModel::m_Depth = NULL;
bool CModel::m_bPlayerShadow = true;

//========================================
//�}�N����`
//========================================
#define SHADOW_MINPOS (D3DXVECTOR3(0.0f,-12.5f,0.0f))	// �e�̍Œ�ʒu

//========================================
// �R���X�g���N�^
//========================================
CModel::CModel()
{
	// �l���N���A����
	m_pTexture = NULL;
	m_pParent = NULL;				// �e���f���̏��
	m_mtxWorld = {};				// ���[���h�}�g���b�N�X
	m_pos = INIT_D3DXVECTOR3;		// �ʒu
	m_posOld = INIT_D3DXVECTOR3;	// �ʒu(�ߋ�)
	m_rot = INIT_D3DXVECTOR3;		// ����
	m_size = INIT_D3DXVECTOR3;
	m_scale = INIT_D3DXVECTOR3;		// �傫��
	m_color = INIT_D3DXCOLOR;		// �F
	m_nModelID = -1;				// ���f��ID
}

//========================================
// �f�X�g���N�^
//========================================
CModel::~CModel()
{

}

//========================================
// ����
//========================================
CModel *CModel::Create(void)
{
	CModel *pModel = new CModel;

	//�|�C���^���m�ۂ��ꂽ
	if (pModel != NULL)
	{
		// ����������
		pModel->Init();

		return pModel;
	}

	//�|�C���^���m�ۂ���Ă��Ȃ���΁ANULL��Ԃ�
	return NULL;
}

//========================================
// ���f�����̏�����
//========================================
void CModel::InitModel(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �t�@�C���ǂݍ���
	LoadModel("data\\GAMEDATA\\MODEL\\MODEL_DATA.txt");

	for (int nCntModel = 0; nCntModel < m_nMaxModel; nCntModel++)
	{// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(&m_material[nCntModel].aFileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_material[nCntModel].pBuffer,
			NULL,
			&m_material[nCntModel].nNumMat,
			&m_material[nCntModel].pMesh);

		// �}�e���A���̃e�N�X�`�����̃������m��
		m_material[nCntModel].pIdxTex = new int[m_material[nCntModel].nNumMat];

		// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_material[nCntModel].pBuffer->GetBufferPointer();

		CTexture* pTexture = CManager::GetTexture();

		for (int nCntMat = 0; nCntMat < (int)m_material[nCntModel].nNumMat; nCntMat++)
		{
			// �}�e���A���̃e�N�X�`�����̏�����
			m_material[nCntModel].pIdxTex[nCntMat] = -1;

			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �e�N�X�`���t�@�C�������݂���

				// �e�N�X�`���̓ǂݍ���
				m_material[nCntModel].pIdxTex[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
			}
		}
		// ���_���W�̍ŏ��l�E�ő�l�̎Z�o
		CalcSize(nCntModel);
	}
}

//========================================
// ���f�����̏I��
//========================================
void CModel::UninitModel(void)
{
	for (int nCnt = 0; nCnt < m_nMaxModel; nCnt++)
	{
		// ���b�V���̔j��
		if (m_material[nCnt].pMesh != NULL)
		{
			m_material[nCnt].pMesh->Release();
			m_material[nCnt].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (m_material[nCnt].pBuffer != NULL)
		{
			m_material[nCnt].pBuffer->Release();
			m_material[nCnt].pBuffer = NULL;
		}

		// �������̉��
		delete[] m_material[nCnt].pIdxTex;
		m_material[nCnt].pIdxTex = NULL;
	}

	// �������̉��
	delete[] m_material;
	m_material = NULL;
}

//========================================
// X�t�@�C���̓ǂݍ���
//========================================
void CModel::LoadModel(const char *pFileName)
{
	int nCntModel = 0;
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(pFileName, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END"))
		{// �ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{// �܂�Ԃ�
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_MODEL"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &m_nMaxModel);		// �ő吔
			m_material = new CModel::MODEL_MATERIAL[m_nMaxModel];
			assert(m_material != NULL);
		}
		else if (!strcmp(aDataSearch, "MODEL"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%s", &m_material[nCntModel].aFileName[0]);	// �t�@�C����
			fscanf(pFile, "%d", &m_material[nCntModel].bShadow);		// �e�̗L��
			nCntModel++;
		}
	}
}

//========================================
// ������
//========================================
HRESULT CModel::Init()
{
	// �����o�ϐ��̏�����
	m_pos = INIT_D3DXVECTOR3;					// �ʒu
	m_rot = INIT_D3DXVECTOR3;					// ����
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �傫��
	m_nModelID = -1;							// ���f��ID

	return S_OK;
}

//========================================
// �I��
//========================================
void CModel::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CModel::Update(void)
{

}

//================================================================================
// �`�� 
// �e���f�����w�肳��Ă�ꍇ�A�e�̃��[���h�}�g���b�N�X���ɕ`�悷��
//================================================================================
void CModel::Draw(bool Color)
{
	if (m_nModelID >= 0 && m_nModelID < m_nMaxModel)
	{
		// �e�̃��[���h�}�g���b�N�X
		D3DXMATRIX mtxParent = {};

		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

		// ���݂̃}�e���A���ۑ��p
		D3DMATERIAL9 matDef;

		// �}�e���A���f�[�^�ւ̃|�C���^
		D3DXMATERIAL *pMat;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// �T�C�Y�̔��f
		D3DXMatrixScaling(&mtxScaling, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScaling);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		if (m_pParent != NULL)
		{
			mtxParent = m_pParent->GetMtxWorld();

			// �s��|���Z�֐�
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		if (m_material[m_nModelID].pBuffer != NULL)
		{// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)m_material[m_nModelID].pBuffer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)m_material[m_nModelID].nNumMat; nCntMat++)
			{
				if (Color)
				{// �}�e���A�����̐ݒ�
					D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;

					// ������F�ɐݒ�
					matD3D.Diffuse = m_color;

					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&matD3D);
				}
				else
				{// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				}

				CTexture *pTexture = CManager::GetTexture();
				m_pTexture = pTexture->GetAddress(m_material[m_nModelID].pIdxTex[nCntMat]);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, m_pTexture);

				// ���f���p�[�c�̕`��
				m_material[m_nModelID].pMesh->DrawSubset(nCntMat);
			}

			// �e�̕`��
			SetShadow(pDevice, pMat, m_nModelID);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//========================================
// �`��
//========================================
void CModel::Draw(D3DXMATRIX mtxParent, bool Color)
{
	if (m_nModelID >= 0 && m_nModelID < m_nMaxModel)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

		// ���݂̃}�e���A���ۑ��p
		D3DMATERIAL9 matDef;

		// �}�e���A���f�[�^�ւ̃|�C���^
		D3DXMATERIAL *pMat;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// �T�C�Y�̔��f
		D3DXMatrixScaling(&mtxScaling, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScaling);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// �s��|���Z�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		if (m_material[m_nModelID].pBuffer != NULL)
		{// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)m_material[m_nModelID].pBuffer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)m_material[m_nModelID].nNumMat; nCntMat++)
			{
				if (Color)
				{// �}�e���A�����̐ݒ�
					D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;

					// ������F�ɐݒ�
					matD3D.Diffuse = m_color;

					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&matD3D);
				}
				else
				{// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				}

				CTexture *pTexture = CManager::GetTexture();
				m_pTexture = pTexture->GetAddress(m_material[m_nModelID].pIdxTex[nCntMat]);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, m_pTexture);

				// ���f���p�[�c�̕`��
				m_material[m_nModelID].pMesh->DrawSubset(nCntMat);
			}
		
			// �e�̕`��
			SetShadow(pDevice, pMat, m_nModelID);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//========================================
// �e�̐ݒ�
//========================================
void CModel::SetShadow(LPDIRECT3DDEVICE9 pDevice, D3DXMATERIAL *pMat, int nModelID)
{
	if (m_material[nModelID].bShadow)
	{
		if (m_pos.y >= SHADOW_MINPOS.y)
		{
			D3DLIGHT9	light;			//���C�g���
			D3DXVECTOR4	posLight;		//���C�g�̈ʒu
			D3DXVECTOR3	pos, normal;	//���ʏ�̔C�ӂ̓_�A�@���x�N�g��
			D3DXPLANE	plane;			//���ʏ��

			//���C�g�̈ʒu��ݒ�
			pDevice->GetLight(0, &light);
			posLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);

			//���ʏ��𐶐�
			pos = SHADOW_MINPOS;
			normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			D3DXPlaneFromPointNormal(&plane, &pos, &normal);

			//�V���h�E�}�g���b�N�X
			{
				D3DXMATRIX	mtxShadow;

				//�V���h�E�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&mtxShadow);

				//�V���h�E�}�g���b�N�X�̍쐬
				D3DXMatrixShadow(&mtxShadow, &posLight, &plane);
				D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

				//�V���h�E�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);
			}

			for (int nCntMat = 0; nCntMat < (int)m_material[nModelID].nNumMat; nCntMat++)
			{
				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)m_material[nModelID].pBuffer->GetBufferPointer();

				D3DMATERIAL9 MatCopy = InitMtrl(
					D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),
					D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),
					D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),
					D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),
					0.0f);

				//���F�ɐݒ�
				MatCopy.Diffuse.a = 1.0f;

				//�}�e���A���ݒ�
				pDevice->SetMaterial(&MatCopy);

				//�e�N�X�`���ݒ�
				pDevice->SetTexture(0, NULL);

				// ���f���p�[�c�̕`��
				m_material[nModelID].pMesh->DrawSubset(nCntMat);
			}
		}
	}

}

//========================================
// ���_���W�̍ŏ��l�E�ő�l�̎Z�o
//========================================
void CModel::CalcSize(int nCntModel)
{
	int		nNumVtx;	// ���_��
	DWORD	sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE	*pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	// ���_���̎擾
	nNumVtx = m_material[nCntModel].pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(m_material[nCntModel].pMesh->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	m_material[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// �ł��傫�Ȓ��_
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (vtx.x < vtxMin.x)
		{// ��r�Ώۂ����݂̒��_���W(X)�̍ŏ��l��菬����
			vtxMin.x = vtx.x;
		}
		if (vtx.y < vtxMin.y)
		{// ��r�Ώۂ����݂̒��_���W(Y)�̍ŏ��l��菬����
			vtxMin.y = vtx.y;
		}
		if (vtx.z < vtxMin.z)
		{// ��r�Ώۂ����݂̒��_���W(Z)�̍ŏ��l��菬����
			vtxMin.z = vtx.z;
		}

		if (vtx.x > vtxMax.x)
		{// ��r�Ώۂ����݂̒��_���W(X)�̍ő�l���傫��
			vtxMax.x = vtx.x;
		}
		if (vtx.y > vtxMax.y)
		{// ��r�Ώۂ����݂̒��_���W(Y)�̍ő�l���傫��
			vtxMax.y = vtx.y;
		}
		if (vtx.z > vtxMax.z)
		{// ��r�Ώۂ����݂̒��_���W(Z)�̍ő�l���傫��
			vtxMax.z = vtx.z;
		}

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_material[nCntModel].pMesh->UnlockVertexBuffer();

	// �傫���̐ݒ�
	m_material[nCntModel].size = D3DXVECTOR3(vtxMax.x - vtxMin.x, vtxMax.y - vtxMin.y, vtxMax.z - vtxMin.z);

	m_material[nCntModel].fWidth = vtxMax.x;
	m_material[nCntModel].fHeight = vtxMax.y;
	m_material[nCntModel].fDepth = vtxMax.z;
}

//========================================
// �����蔻��̎擾
//========================================
D3DXVECTOR3 CModel::GetSize(const int nModelID)
{
	m_size = m_material[nModelID].size;

	return m_size;
}

//========================================
// ���̎擾
//========================================
float CModel::GetWidth(const int nModelID)
{
	m_Width = m_material[nModelID].fWidth;

	return m_Width;
}

//========================================
// �����̎擾
//========================================
float CModel::GetHeight(const int nModelID)
{
	m_Height = m_material[nModelID].fHeight;

	return m_Height;
}

//========================================
// ���s���̎擾
//========================================
float CModel::GetDepth(const int nModelID)
{
	m_Depth = m_material[nModelID].fDepth;

	return m_Depth;
}

//========================================
// �}�e���A���̏�����
//========================================
D3DMATERIAL9 CModel::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}

//========================================
// �v���C���[�e�̕\���E��\��
//========================================
void CModel::SetPlayerShadow(bool bShadow)
{
	if (bShadow)
	{
		if (!m_bPlayerShadow)
		{
			for (int nCnt = 0; nCnt < 6; nCnt++)
			{
				m_material[nCnt + CPhysics::MODEL_PLAYER_00].bShadow = true;
			}
			m_bPlayerShadow = true;
		}
	}
	else
	{
		if (m_bPlayerShadow)
		{
			for (int nCnt = 0; nCnt < 6; nCnt++)
			{
				m_material[nCnt + CPhysics::MODEL_PLAYER_00].bShadow = false;
			}
			m_bPlayerShadow = false;
		}
	}
}