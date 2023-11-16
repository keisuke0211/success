//========================================
// 
// �w�i�i�V��j�y 3D �z����
// 
//========================================
// *** bg_ceiling.h ***
//========================================
#include "bg_ceiling.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"
#include "../../scene/pause.h"
#include "../../scene/game.h"

//****************************************
// �}�N����`
//****************************************

// ���_�t�H�[�}�b�g�y3D�z
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


#define BG_POS				(D3DXVECTOR3(0.0f,580.0f,0.0f))			// �ʒu
#define BG_HEIGHT			(475.0f)								// ����
#define BG_RADIUS			(960.0f)								// ���a
#define BG_DIVISION_WIDTH	(32)									// ������
#define BG_DIVISION_HEIGHT	(8)										// ��������
#define BG_SPIN				(D3DXVECTOR3(0.0f,-0.001f,0.0f))		// ��]��

//****************************************
// �R���X�g���N�^
//****************************************
CBgCeiling::CBgCeiling(int nPriority) : CObject(nPriority)
{
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
	m_color = INIT_D3DXCOLOR;
	m_nStage = 0;
}
//****************************************
// �f�X�g���N�^
//****************************************
CBgCeiling::~CBgCeiling()
{

}

//========================================
// ��������
//========================================
CBgCeiling *CBgCeiling::Create(int nStage)
{
	CBgCeiling *pObj = new CBgCeiling;

	if (pObj != NULL)
	{
		pObj->m_nStage = nStage;
		// ����������
		pObj->Init();
	}

	return pObj;
}

//========================================
// ����������
//========================================
HRESULT CBgCeiling::Init(void)
{
	m_pos = BG_POS;

	SetType(TYPE_BG);
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((BG_DIVISION_WIDTH + 1) * (BG_DIVISION_HEIGHT + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;	// �ݒ�p�|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �^��̒��_���W/�e�N�X�`�����W�̐ݒ�
	pVtx[(BG_DIVISION_WIDTH + 1) * BG_DIVISION_HEIGHT].pos = D3DXVECTOR3(0.0f, BG_HEIGHT, 0.0f);
	pVtx[(BG_DIVISION_WIDTH + 1) * BG_DIVISION_HEIGHT].tex = D3DXVECTOR2(0.0f, 0.0f);

	// ���_���W/�@���x�N�g��/�e�N�X�`�����W�̐ݒ�
	for (int nCntHeight = 0; nCntHeight < BG_DIVISION_HEIGHT; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < BG_DIVISION_WIDTH + 1; nCntWidth++)
		{
			// ���_���W
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].pos
				= D3DXVECTOR3(
					sinf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))) * (BG_RADIUS * sinf(D3DX_PI - ((nCntHeight + 1) * ((D3DX_PI * 0.5f) / (float)BG_DIVISION_HEIGHT)))),
					BG_HEIGHT - (((nCntHeight + 1) * (BG_HEIGHT / BG_DIVISION_HEIGHT)) * sinf(D3DX_PI - ((nCntHeight + 1) * ((D3DX_PI * 0.5f) / (float)BG_DIVISION_HEIGHT)))),
					cosf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))) * (BG_RADIUS * sinf(D3DX_PI - ((nCntHeight + 1) * ((D3DX_PI * 0.5f) / (float)BG_DIVISION_HEIGHT)))));

			// �@���x�N�g��
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].nor
				= D3DXVECTOR3(
					sinf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))),
					0.0f,
					cosf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))));;

			// �e�N�X�`�����W
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].tex
				= D3DXVECTOR2(
					nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH),
					(nCntHeight + 1) * (2.0f / (float)BG_DIVISION_HEIGHT));
		}
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((((BG_DIVISION_HEIGHT - 1) * 2 * (BG_DIVISION_WIDTH + 1)) + ((BG_DIVISION_HEIGHT - 2) * 2)) + 1),
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

	for (int nCntHeight = 0; nCntHeight < BG_DIVISION_HEIGHT - 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < BG_DIVISION_WIDTH + 1; nCntWidth++)
		{
			pIdx[nCntIdx] = (nCntWidth + ((BG_DIVISION_WIDTH + 1) * (nCntHeight + 1)));
			pIdx[nCntIdx + 1] = nCntWidth + ((BG_DIVISION_WIDTH + 1) * nCntHeight);
			nCntIdx += 2;
		}

		if (nCntHeight < BG_DIVISION_HEIGHT - 2)
		{
			pIdx[nCntIdx] = ((BG_DIVISION_WIDTH + 1) * (nCntHeight + 1)) - 1;
			pIdx[nCntIdx + 1] = (BG_DIVISION_WIDTH + 1) * (nCntHeight + 2);
			nCntIdx += 2;
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuf->Unlock();

	{
		// �V��̃C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * (BG_DIVISION_WIDTH + 2),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&m_pIdxBufLid,
			NULL);

		WORD *pIdx;	// �V��̃C���f�b�N�X���ւ̃|�C���^

		// �V��̃C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
		m_pIdxBufLid->Lock(0, 0, (void**)&pIdx, 0);

		pIdx[0] = (BG_DIVISION_WIDTH + 1) * BG_DIVISION_HEIGHT;
		for (int nCntIdx = 0; nCntIdx < BG_DIVISION_WIDTH + 1; nCntIdx++)
		{
			pIdx[nCntIdx + 1] = BG_DIVISION_WIDTH - nCntIdx;
		}

		// �V��̃C���f�b�N�X�o�b�t�@���A�����b�N����
		m_pIdxBufLid->Unlock();
	}

	for (int nCntVtx = 0; nCntVtx < ((BG_DIVISION_WIDTH + 1) * BG_DIVISION_HEIGHT) + 1; nCntVtx++)
	{
		// ���_�J���[�̐ݒ�
		pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �e�N�X�`���ݒ�
	CTexture *pTexture = CManager::GetTexture();

	m_pTexture = pTexture->GetAddress(CTexture::TEX_NIGHT_SKY00);
	
	return S_OK;
}

//========================================
// �I������
//========================================
void CBgCeiling::Uninit(void)
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

	// �V��̃C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBufLid != NULL)
	{
		m_pIdxBufLid->Release();
		m_pIdxBufLid = NULL;
	}
}

//========================================
// �X�V����
//========================================
void CBgCeiling::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		m_rot += BG_SPIN;	// ��]�ʂ����Z
		RotControl(&m_rot);	// �����𐧌�
	}
}

//========================================
// �`�揈��
//========================================
void CBgCeiling::Draw(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

									// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuf);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		((BG_DIVISION_WIDTH + 1) * (BG_DIVISION_HEIGHT + 1)),
		0,
		((BG_DIVISION_WIDTH * BG_DIVISION_HEIGHT) * 2) + (4 * (BG_DIVISION_HEIGHT - 1)));

	// �V��̃C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBufLid);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,
		0,
		0,
		(BG_DIVISION_WIDTH + 2),
		0,
		BG_DIVISION_WIDTH);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}