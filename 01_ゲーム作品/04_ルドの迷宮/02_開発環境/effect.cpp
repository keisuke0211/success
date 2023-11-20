//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�G�t�F�N�g����    �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "effect.h"
#include "game.h"
#include "camera.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define MAX_EFFECT (48000) //�G�t�F�N�g�̍ő吔


//��====================��
//�b �@�@���\���� �@�@�b
//��====================��

//�G�t�F�N�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3	rot;	// ����
	D3DXVECTOR3 move;	//�ړ���
	D3DXMATRIX	mtxWorld;	//���[���h�}�g���b�N�X
	D3DXCOLOR col;		//���_�J���[
	float fRadius;		//���a�i�傫���j
	int  nLife;			//�����i�\�����ԁj
	int nType;			//�G�t�F�N�g���
	bool bUse;			//�g�p���Ă��邩�ǂ���
	float rRot;
} Effect;

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;			//�e�N�X�`���ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];

//��==================================��
//�b�@�@ �G�t�F�N�g�̏����������@�@ �@�b
//��==================================��
void InitEffect(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEffect;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//���e�̏��̏���������
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos	  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col	  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 6.0f;
		g_aEffect[nCntEffect].nLife	  = 25;
		g_aEffect[nCntEffect].bUse	  = false;
	}

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�@�@rhw�̐ݒ�@�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�@ ���_�J���[ �@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//��================================��
//�b�@�@ �G�t�F�N�g�̏I�������@�@ �@�b
//��================================��
void UninitEffect(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//��================================��
//�b�@�@ �G�t�F�N�g�̍X�V�����@�@ �@�b
//��================================��
void UpdateEffect(void)
{
	int nCntEffect;

	//�e�N�X�`�����W�̍X�V
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEffect->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���

			//�G�t�F�N�̈ʒu�X�V
			g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
			g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;
			g_aEffect[nCntEffect].pos.z += g_aEffect[nCntEffect].move.z;

			//�T�C�Y�ύX
			g_aEffect[nCntEffect].fRadius -= g_aEffect[nCntEffect].fRadius / g_aEffect[nCntEffect].nLife;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius);

			//�s�����x�X�V
			g_aEffect[nCntEffect].col.a += 1.0f / g_aEffect[nCntEffect].nLife;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			//�����Ƒ傫�������炵�Ă���
			g_aEffect[nCntEffect].nLife--;

			if (g_aEffect[nCntEffect].nLife == 0)
			{//�������s����

				g_aEffect[nCntEffect].bUse = false;
			}
		}
		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//��================================��
//�b�@�@ �G�t�F�N�g�̕`�揈���@�@ �@�b
//��================================��
void DrawEffect(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							//�r���[�}�g���b�N�X�擾�p

	int nCntEffect;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_3D);

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);				// ���̖�����

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���
		 //���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			//�r���[�}�g���b�N�X��Get
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aEffect[nCntEffect].mtxWorld, NULL, &mtxView);	//�t�s������߂�
			g_aEffect[nCntEffect].mtxWorld._41 = DEFAULT_FLOA;
			g_aEffect[nCntEffect].mtxWorld._42 = DEFAULT_FLOA;
			g_aEffect[nCntEffect].mtxWorld._43 = DEFAULT_FLOA;	

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);

			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�e�N�X�`���̐ݒ�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}
	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	Fog1 *pFog = GetFog();
	Camera *pCamera = Getcamara(0);

	pDevice->SetRenderState(D3DRS_FOGENABLE, pFog->bUse);				// ���̗L����
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, 0, 0, 0));	// ���̐F
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);			// ���_���[�h
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&pFog->Start));	// �J�n�ʒu
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&pFog->End));		// �I���ʒu
}

//��================================��
//�b�@ �@�G�t�F�N�g�̐ݒ菈���@�@ �@�b
//��================================��
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,int nType)
{
	int nCntEffect;

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEffect->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].nType = nType;
			g_aEffect[nCntEffect].bUse = true;

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b �@�@���_���W��ݒ�@�@ �b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�@ ���_�J���[ �@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;
			
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//���_�o�b�t�@�̃A�����b�N
			g_pVtxBuffEffect->Unlock();
			break;
		}
	}
}