//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�e�̏����@�@�@    �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "shadow.h"

//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffShadow = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;			//�e�N�X�`���ւ̃|�C���^
Shadow g_aShadow[MAX_SHADOW];
//****************************************
// ����������
//****************************************
void InitShadow(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffShadow,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffShadow->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = DEFAULT_D3DXVECTOR3;
		g_aShadow[nCntShadow].rot = DEFAULT_D3DXVECTOR3;
		g_aShadow[nCntShadow].fWidhtX = 5.0f;
		g_aShadow[nCntShadow].fWidhtZ = 5.0f;
		g_aShadow[nCntShadow].aColor = 200;
		g_aShadow[nCntShadow].bSet = false;			
		g_aShadow[nCntShadow].bUse = false;	

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - g_aShadow[nCntShadow].fWidhtX, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z + g_aShadow[nCntShadow].fWidhtZ);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + g_aShadow[nCntShadow].fWidhtX, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z + g_aShadow[nCntShadow].fWidhtZ);
		pVtx[2].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - g_aShadow[nCntShadow].fWidhtX, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z - g_aShadow[nCntShadow].fWidhtZ);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + g_aShadow[nCntShadow].fWidhtX, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z - g_aShadow[nCntShadow].fWidhtZ);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aShadow[nCntShadow].aColor);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aShadow[nCntShadow].aColor);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aShadow[nCntShadow].aColor);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aShadow[nCntShadow].aColor);

		//�e�N�X�`�����W�̂̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffShadow->Unlock();
}
//****************************************
// �I������
//****************************************
void UninitShadow(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffShadow != NULL)
	{
		g_pVtxbuffShadow->Release();
		g_pVtxbuffShadow = NULL;
	}
}
//****************************************
// �X�V����
//****************************************
void UpdateShadow(void)
{
	
}
//****************************************
// �`�揈��
//****************************************
void DrawShadow(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	
	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = DEFAULT_INT; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxbuffShadow, 0, sizeof(VERTEX_3D));

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b���_�t�H�[�}�b�g�̐ݒ�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�e�N�X�`���̐ݒ�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			pDevice->SetTexture(0, g_pTextureShadow);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�|���S���̕`��@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			//���_���\���̂̃T�C�Y
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//****************************************
// �ݒ菈��
//****************************************
int SetShadow(void)
{
	int nCntShadow = -1;

	for (int mCntShadow = 0; mCntShadow < MAX_SHADOW; mCntShadow++)
	{
		nCntShadow++;

		if (g_aShadow[mCntShadow].bUse == false && g_aShadow[mCntShadow].bSet == false)
		{
			g_aShadow[mCntShadow].pos = DEFAULT_D3DXVECTOR3;	//�ʒu������
			g_aShadow[mCntShadow].rot = DEFAULT_D3DXVECTOR3;	//����������
			g_aShadow[mCntShadow].bSet = true;		//�Ώۂ����܂���
			break;
		}
	}

	return nCntShadow;
}
//****************************************
// �ʒu�ݒ菈��
//****************************************
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos,float fWidht, float fHight)
{
	g_aShadow[nIdxShadow].pos = pos;
	g_aShadow[nIdxShadow].pos.y = 0;

	//�|�C���^��ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxbuffShadow->Lock(0, 0, (void* *)&pVtx, 0);

	pVtx += 4 * nIdxShadow;		//���_���W���C���f�b�N�X���i�߂�
	
	g_aShadow[nIdxShadow].fWidhtX = fWidht;
	g_aShadow[nIdxShadow].fWidhtZ = fHight;
	g_aShadow[nIdxShadow].aColor = 200 - (int)(pos.y * 1.3f);			//���l����	
	g_aShadow[nIdxShadow].bUse = true;									//�g�p����

	pVtx[0].pos = D3DXVECTOR3(- g_aShadow[nIdxShadow].fWidhtX, 0.0f, + g_aShadow[nIdxShadow].fWidhtZ);
	pVtx[1].pos = D3DXVECTOR3(+ g_aShadow[nIdxShadow].fWidhtX, 0.0f, + g_aShadow[nIdxShadow].fWidhtZ);
	pVtx[2].pos = D3DXVECTOR3(- g_aShadow[nIdxShadow].fWidhtX, 0.0f, - g_aShadow[nIdxShadow].fWidhtZ);
	pVtx[3].pos = D3DXVECTOR3(+ g_aShadow[nIdxShadow].fWidhtX, 0.0f, - g_aShadow[nIdxShadow].fWidhtZ);


	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aShadow[nIdxShadow].aColor);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aShadow[nIdxShadow].aColor);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aShadow[nIdxShadow].aColor);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aShadow[nIdxShadow].aColor);

	//���_�o�b�t�@�����b�N����
	g_pVtxbuffShadow->Unlock();
}

//****************************************
// �e������
//****************************************
void DeleteShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}