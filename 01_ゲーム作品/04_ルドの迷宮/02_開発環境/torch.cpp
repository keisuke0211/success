//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�e�̏����@�@�@    �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "Torch.h"

//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTorch = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureTorch = NULL;			//�e�N�X�`���ւ̃|�C���^
Torch g_aTorch[NUM_TORCH];
//****************************************
// ����������
//****************************************
void InitTorch(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\effect000.jpg",
		&g_pTextureTorch);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUM_TORCH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTorch,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTorch->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < NUM_TORCH; nCntShadow++)
	{
		g_aTorch[nCntShadow].pos = DEFAULT_D3DXVECTOR3;
		g_aTorch[nCntShadow].rot = DEFAULT_D3DXVECTOR3;
		g_aTorch[nCntShadow].fRadius = 25.0f;
		g_aTorch[nCntShadow].aColor = 200;
		g_aTorch[nCntShadow].bSet = false;
		g_aTorch[nCntShadow].bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTorch[nCntShadow].pos.x - g_aTorch[nCntShadow].fRadius, g_aTorch[nCntShadow].pos.y, g_aTorch[nCntShadow].pos.z + g_aTorch[nCntShadow].fRadius);
		pVtx[1].pos = D3DXVECTOR3(g_aTorch[nCntShadow].pos.x + g_aTorch[nCntShadow].fRadius, g_aTorch[nCntShadow].pos.y, g_aTorch[nCntShadow].pos.z + g_aTorch[nCntShadow].fRadius);
		pVtx[2].pos = D3DXVECTOR3(g_aTorch[nCntShadow].pos.x - g_aTorch[nCntShadow].fRadius, g_aTorch[nCntShadow].pos.y, g_aTorch[nCntShadow].pos.z - g_aTorch[nCntShadow].fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_aTorch[nCntShadow].pos.x + g_aTorch[nCntShadow].fRadius, g_aTorch[nCntShadow].pos.y, g_aTorch[nCntShadow].pos.z - g_aTorch[nCntShadow].fRadius);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aTorch[nCntShadow].aColor);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aTorch[nCntShadow].aColor);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aTorch[nCntShadow].aColor);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aTorch[nCntShadow].aColor);

		//�e�N�X�`�����W�̂̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTorch->Unlock();
}
//****************************************
// �I������
//****************************************
void UninitTorch(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureTorch != NULL)
	{
		g_pTextureTorch->Release();
		g_pTextureTorch = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffTorch != NULL)
	{
		g_pVtxbuffTorch->Release();
		g_pVtxbuffTorch = NULL;
	}
}
//****************************************
// �X�V����
//****************************************
void UpdatTorch(void)
{

}
//****************************************
// �`�揈��
//****************************************
void DrawTorch(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							//�r���[�}�g���b�N�X�擾�p

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = DEFAULT_INT; nCntShadow < NUM_TORCH; nCntShadow++)
	{
		if (g_aTorch[nCntShadow].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aTorch[nCntShadow].mtxWorld);

			//pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//D3DXMatrixInverse(&g_aTorch[nCntShadow].mtxWorld, NULL, &mtxView);	//�t�s������߂�
			//g_aTorch[nCntShadow].mtxWorld._41 = DEFAULT_FLOA;
			//g_aTorch[nCntShadow].mtxWorld._42 = DEFAULT_FLOA;
			//g_aTorch[nCntShadow].mtxWorld._43 = DEFAULT_FLOA;

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aTorch[nCntShadow].rot.y, g_aTorch[nCntShadow].rot.x, g_aTorch[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_aTorch[nCntShadow].mtxWorld, &g_aTorch[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aTorch[nCntShadow].pos.x, g_aTorch[nCntShadow].pos.y, g_aTorch[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_aTorch[nCntShadow].mtxWorld, &g_aTorch[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aTorch[nCntShadow].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxbuffTorch, 0, sizeof(VERTEX_3D));

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b���_�t�H�[�}�b�g�̐ݒ�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�e�N�X�`���̐ݒ�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			pDevice->SetTexture(0, g_pTextureTorch);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�|���S���̕`��@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			//���_���\���̂̃T�C�Y
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}

//****************************************
// �ݒ菈��
//****************************************
int SetTorch(void)
{
	int nCntShadow = -1;

	for (int mCntShadow = 0; mCntShadow < NUM_TORCH; mCntShadow++)
	{
		nCntShadow++;

		if (g_aTorch[mCntShadow].bUse == false && g_aTorch[mCntShadow].bSet == false)
		{
			g_aTorch[mCntShadow].pos = DEFAULT_D3DXVECTOR3;	//�ʒu������
			g_aTorch[mCntShadow].rot = DEFAULT_D3DXVECTOR3;	//����������
			g_aTorch[mCntShadow].bSet = true;		//�Ώۂ����܂���
			break;
		}
	}

	return nCntShadow;
}
//****************************************
// �ʒu�ݒ菈��
//****************************************
void SetPositionTorch(int nIdxShadow, D3DXVECTOR3 pos, float fRadius)
{
	g_aTorch[nIdxShadow].pos = pos;
	g_aTorch[nIdxShadow].pos.y = 1;

	//�|�C���^��ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxbuffTorch->Lock(0, 0, (void* *)&pVtx, 0);

	pVtx += 4 * nIdxShadow;		//���_���W���C���f�b�N�X���i�߂�

	g_aTorch[nIdxShadow].fRadius = fRadius;
	g_aTorch[nIdxShadow].aColor = 160 - (int)(pos.y * 1.3f);			//���l����	
	g_aTorch[nIdxShadow].bUse = true;									//�g�p����

	pVtx[0].pos = D3DXVECTOR3(-g_aTorch[nIdxShadow].fRadius, 0.0f, +g_aTorch[nIdxShadow].fRadius);
	pVtx[1].pos = D3DXVECTOR3(+g_aTorch[nIdxShadow].fRadius, 0.0f, +g_aTorch[nIdxShadow].fRadius);
	pVtx[2].pos = D3DXVECTOR3(-g_aTorch[nIdxShadow].fRadius, 0.0f, -g_aTorch[nIdxShadow].fRadius);
	pVtx[3].pos = D3DXVECTOR3(+g_aTorch[nIdxShadow].fRadius, 0.0f, -g_aTorch[nIdxShadow].fRadius);


	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 196, 96, g_aTorch[nIdxShadow].aColor);
	pVtx[1].col = D3DCOLOR_RGBA(255, 196, 96, g_aTorch[nIdxShadow].aColor);
	pVtx[2].col = D3DCOLOR_RGBA(255, 196, 96, g_aTorch[nIdxShadow].aColor);
	pVtx[3].col = D3DCOLOR_RGBA(255, 196, 96, g_aTorch[nIdxShadow].aColor);

	//���_�o�b�t�@�����b�N����
	g_pVtxbuffTorch->Unlock();
}
