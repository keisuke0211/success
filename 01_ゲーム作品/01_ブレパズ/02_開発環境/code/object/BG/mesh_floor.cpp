//========================================
// 
// ���b�V���t�B�[���h
// 
//========================================
// *** mesh_floor.h ***
//========================================
#include "mesh_floor.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"
#include "../../scene/pause.h"

//****************************************
// �}�N����`
//****************************************

// ���_�t�H�[�}�b�g�y3D_MULTI�z
#define FVF_VERTEX_3D_MULTI (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX3)

//****************************************
// �R���X�g���N�^
//****************************************
CFloor::CFloor(int nPriority) : CObject(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.color = INIT_D3DXCOLOR;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.nNumTex = 0;
	m_Info.nDivisionX = 1;
	m_Info.nDivisionY = 1;
	m_Info.nNumDivisionX = 1;
	m_Info.nNumDivisionY = 1;

	for (int nTex = 0; nTex < m_Info.nNumTex; nTex++)
	{
		m_Info.pMulti[nTex].nType = 0;
		m_Info.pMulti[nTex].fTexX = 0;
		m_Info.pMulti[nTex].fTexY = 0;
		m_Info.pMulti[nTex].fTexXSpeed = 0;
		m_Info.pMulti[nTex].fTexYSpeed = 0;
	}
}
//****************************************
// �f�X�g���N�^
//****************************************
CFloor::~CFloor()
{

}

//========================================
// ��������
//========================================
CFloor *CFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR color, float fWidth, float fHeight, int *nType, int nNumTex, bool bDivision, int nDivisionX, int nDivisionY, float *fTexX, float *fTexY)
{
	CFloor *pObj = new CFloor;

	if (pObj != NULL)
	{
		pObj->m_Info.pos = pos;
		pObj->m_Info.rot = rot;
		pObj->m_Info.color = color;
		pObj->m_Info.fWidth = fWidth;
		pObj->m_Info.fHeight = fHeight;
		pObj->m_Info.nNumTex = nNumTex;

		// �e�N�X�`���̕���
		if (bDivision)
		{
			pObj->m_Info.nNumDivisionX = nDivisionX;
			pObj->m_Info.nNumDivisionY = nDivisionY;
		}

		// �������̉��
		pObj->m_Info.pMulti = new Multi[nNumTex];

		for (int nTex = 0; nTex < nNumTex; nTex++)
		{
			pObj->m_Info.pMulti[nTex].nType = nType[nTex];
			pObj->m_Info.pMulti[nTex].fTexX = 0.0f;
			pObj->m_Info.pMulti[nTex].fTexY = 0.0f;
			pObj->m_Info.pMulti[nTex].fTexXSpeed = fTexX[nTex];
			pObj->m_Info.pMulti[nTex].fTexYSpeed = fTexY[nTex];
		}

		pObj->m_Info.nDivisionX = nDivisionX;
		pObj->m_Info.nDivisionY = nDivisionY;

		// ����������
		pObj->Init();
	}

	return pObj;
}

//========================================
// ����������
//========================================
HRESULT CFloor::Init(void)
{
	SetType(TYPE_BG);

	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_MULTI) * ((m_Info.nDivisionX + 1) * (m_Info.nDivisionY + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D_MULTI,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D_MULTI *pVtx;	// �ݒ�p�|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W/�@���x�N�g��/�e�N�X�`�����W�̐ݒ�
	for (int nCntHeight = 0; nCntHeight < m_Info.nDivisionY + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < m_Info.nDivisionX + 1; nCntWidth++)
		{
			// �ʒu
			pVtx[(nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth].pos
				= D3DXVECTOR3(
					(((float)nCntWidth - (float)m_Info.nDivisionX / 2)) * m_Info.fWidth,
					0.0f,
					(((float)nCntHeight - (float)m_Info.nDivisionY / 2)) * -m_Info.fHeight);


			float n,i;
			n = (((float)nCntWidth - (float)m_Info.nDivisionX / 2)) * m_Info.fWidth;
			i = (((float)nCntHeight - (float)m_Info.nDivisionY / 2)) * -m_Info.fHeight;


			// �@���x�N�g��
			pVtx[(nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth].nor
				= D3DXVECTOR3(
					0.0f,
					1.0f,
					0.0f);


			if (m_Info.nNumTex >= 1)
			{
				// �e�N�X�`���P
				pVtx[(nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth].tex1
					= D3DXVECTOR2(
						nCntWidth * ((float)m_Info.nNumDivisionX / (float)m_Info.nDivisionX),
						nCntHeight * ((float)m_Info.nNumDivisionY / (float)m_Info.nDivisionY));
			}

			float k, l,a;
			a = (nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth;
			k = nCntWidth * (m_Info.nDivisionX / (float)m_Info.nDivisionX);
			l = nCntHeight * (m_Info.nDivisionY / (float)m_Info.nDivisionY);

			if (m_Info.nNumTex >= 2)
			{
				// �e�N�X�`��2
				pVtx[(nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth].texM
					= D3DXVECTOR2(
						nCntWidth * ((float)m_Info.nNumDivisionX / (float)m_Info.nDivisionX),
						nCntHeight * ((float)m_Info.nNumDivisionY / (float)m_Info.nDivisionY));
			}
			if (m_Info.nNumTex >= 3)
			{
				// �e�N�X�`��3
				pVtx[(nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth].texM2
					= D3DXVECTOR2(
						nCntWidth * ((float)m_Info.nNumDivisionX / (float)m_Info.nDivisionX),
						nCntHeight * ((float)m_Info.nNumDivisionY / (float)m_Info.nDivisionY));
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_Info.nDivisionY * 2 * (m_Info.nDivisionX + 1)) + ((m_Info.nDivisionY - 1) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuf,
		NULL);

	WORD *pIdx;	// �C���f�b�N�X���ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuf->Lock(0, 0, (void**)&pIdx, 0);

	// ���_�ԍ��f�[�^�̐ݒ�
	int nCntIdx = 0;	// �C���f�b�N�X�̃J�E���g

	for (int nCntDepth = 0; nCntDepth < m_Info.nDivisionY; nCntDepth++)
	{
		for (int nCntWidth = 0; nCntWidth < m_Info.nDivisionX + 1; nCntWidth++)
		{
			pIdx[nCntIdx] = (nCntWidth + ((m_Info.nDivisionX + 1) * (nCntDepth + 1)));
			pIdx[nCntIdx + 1] = nCntWidth + ((m_Info.nDivisionX + 1) * nCntDepth);
			nCntIdx += 2;
		}

		if (nCntDepth < m_Info.nDivisionY - 1)
		{
			pIdx[nCntIdx] = ((m_Info.nDivisionX + 1) * (nCntDepth + 1)) - 1;
			pIdx[nCntIdx + 1] = (m_Info.nDivisionX + 1) * (nCntDepth + 2);
			nCntIdx += 2;
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuf->Unlock();

	for (int nCntVtx = 0; nCntVtx < ((m_Info.nDivisionX + 1) * (m_Info.nDivisionY + 1)); nCntVtx++)
	{
		// ���_�J���[�̐ݒ�
		pVtx[nCntVtx].col = m_Info.color;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �e�N�X�`���ݒ�
	CTexture *pTexture = CManager::GetTexture();

	if (m_Info.nNumTex >= 1)
	{
		m_pTextureMeshfield1 = pTexture->GetAddress(m_Info.pMulti[0].nType);
	}
	if (m_Info.nNumTex >= 2)
	{
		m_pTextureMeshfield2 = pTexture->GetAddress(m_Info.pMulti[1].nType);
	}
	if (m_Info.nNumTex >= 3)
	{
		m_pTextureMeshfield3 = pTexture->GetAddress(m_Info.pMulti[2].nType);
	}

	return S_OK;
}

//========================================
// �I������
//========================================
void CFloor::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuf != NULL)
	{
		m_pIdxBuf->Release();
		m_pIdxBuf = NULL;
	}

	delete[] m_Info.pMulti;
	m_Info.pMulti = NULL;
}

//========================================
// �X�V����
//========================================
void CFloor::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		VERTEX_3D_MULTI *pVtx;	// �ݒ�p�|�C���^

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̊J�n�ʒu(X��)�̍X�V
		for (int nTex = 0; nTex < m_Info.nNumTex; nTex++)
		{
			m_Info.pMulti[nTex].fTexX += m_Info.pMulti[nTex].fTexXSpeed;
			m_Info.pMulti[nTex].fTexY += m_Info.pMulti[nTex].fTexYSpeed;
		}

		// �e�N�X�`�����W�̍X�V
		for (int nCntHeight = 0; nCntHeight < m_Info.nDivisionY + 1; nCntHeight++)
		{
			for (int nCntWidth = 0; nCntWidth < m_Info.nDivisionX + 1; nCntWidth++)
			{
				if (m_Info.nNumTex >= 1)
				{
					// �e�N�X�`��1
					pVtx[(nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth].tex1
						= D3DXVECTOR2(
							m_Info.pMulti[0].fTexX + (nCntWidth * (m_Info.nNumDivisionX / (float)m_Info.nDivisionX)),
							m_Info.pMulti[0].fTexY + (nCntHeight * (m_Info.nNumDivisionY / (float)m_Info.nDivisionY)));
				}
				if (m_Info.nNumTex >= 2)
				{
					// �e�N�X�`��2
					pVtx[(nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth].texM
						= D3DXVECTOR2(
							m_Info.pMulti[1].fTexX + (nCntWidth * (m_Info.nNumDivisionX / (float)m_Info.nDivisionX)),
							m_Info.pMulti[1].fTexY + (nCntHeight * (m_Info.nNumDivisionY / (float)m_Info.nDivisionY)));
				}
				if (m_Info.nNumTex >= 3)
				{
					// �e�N�X�`��3
					pVtx[(nCntHeight * (m_Info.nDivisionX + 1)) + nCntWidth].texM2
						= D3DXVECTOR2(
							m_Info.pMulti[2].fTexX + (nCntWidth * (m_Info.nNumDivisionX / (float)m_Info.nDivisionX)),
							m_Info.pMulti[2].fTexY + (nCntHeight * (m_Info.nNumDivisionY / (float)m_Info.nDivisionY)));
				}
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//========================================
// �`�揈��
//========================================
void CFloor::Draw(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	if (m_Info.nNumTex >= 1)
	{
		pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	}
	if (m_Info.nNumTex >= 2)
	{
		pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
		pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	}
	if (m_Info.nNumTex >= 3)
	{
		pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);
		pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
		pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		pDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	}

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D_MULTI));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuf);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_MULTI);

	// �e�N�X�`���̐ݒ�
	if (m_Info.nNumTex >= 1)
	{
		pDevice->SetTexture(0, m_pTextureMeshfield1);
	}
	if (m_Info.nNumTex >= 2)
	{
		pDevice->SetTexture(1, m_pTextureMeshfield2);
	}
	if (m_Info.nNumTex >= 3)
	{
		pDevice->SetTexture(2, m_pTextureMeshfield3);
	}

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		((m_Info.nDivisionX + 1) * (m_Info.nDivisionY + 1)),
		0,
		((m_Info.nDivisionX * m_Info.nDivisionY) * 2) + (4 * (m_Info.nDivisionX - 1)));

	// �e�N�X�`���X�e�[�W�X�e�[�g��߂�
	if (m_Info.nNumTex >= 1)
	{
		pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	}
	if (m_Info.nNumTex >= 2)
	{
		pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	}
	if (m_Info.nNumTex >= 3)
	{
		pDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
		pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	}

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}