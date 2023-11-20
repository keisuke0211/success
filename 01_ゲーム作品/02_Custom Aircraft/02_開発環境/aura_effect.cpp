//��========================��
//�b�@�@�@�@	�@�@�@�@�@�@�b
//�b�@�I�[���G�t�F�N�g����  �b
//�b�@Author:��a�c��@		�b
//�b						�b
//��========================��
#include "aura_effect.h"
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
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//���_�J���[
	float fRadius;		//���a�i�傫���j
	int  nLife;			//�����i�\�����ԁj
	int nType;			//�G�t�F�N�g���
	bool bUse;			//�g�p���Ă��邩�ǂ���
	float rRot;
} AuraEffect;

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAuraEffect = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureAuraEffect = NULL;			//�e�N�X�`���ւ̃|�C���^
AuraEffect g_aAuraEffect[MAX_EFFECT];

//��==================================��
//�b�@�@ �G�t�F�N�g�̏����������@�@ �@�b
//��==================================��
void InitAuraEffect(void)
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
		".\\data\\TEXTURE\\effect000.jpg",
		&g_pTextureAuraEffect);

	//���e�̏��̏���������
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aAuraEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAuraEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aAuraEffect[nCntEffect].fRadius = 6.0f;
		g_aAuraEffect[nCntEffect].nLife = 25;
		g_aAuraEffect[nCntEffect].bUse = false;

	}

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffAuraEffect,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffAuraEffect->Lock(0, 0, (void **)&pVtx, 0);

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
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
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
	g_pVtxBuffAuraEffect->Unlock();
}
//��================================��
//�b�@�@ �G�t�F�N�g�̏I�������@�@ �@�b
//��================================��
void UninitAuraEffect(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureAuraEffect != NULL)
	{
		g_pTextureAuraEffect->Release();
		g_pTextureAuraEffect = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxBuffAuraEffect != NULL)
	{
		g_pVtxBuffAuraEffect->Release();
		g_pVtxBuffAuraEffect = NULL;
	}
}
//��================================��
//�b�@�@ �G�t�F�N�g�̍X�V�����@�@ �@�b
//��================================��
void UpdateAuraEffect(void)
{
	int nCntEffect;

	//�e�N�X�`�����W�̍X�V
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffAuraEffect->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aAuraEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���

		 //�G�t�F�N�̈ʒu�X�V
			g_aAuraEffect[nCntEffect].pos.x += g_aAuraEffect[nCntEffect].move.x;
			g_aAuraEffect[nCntEffect].pos.y += g_aAuraEffect[nCntEffect].move.y;

			//�T�C�Y�ύX
			g_aAuraEffect[nCntEffect].fRadius -= g_aAuraEffect[nCntEffect].fRadius / g_aAuraEffect[nCntEffect].nLife;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aAuraEffect[nCntEffect].pos.x - g_aAuraEffect[nCntEffect].fRadius;
			pVtx[0].pos.y = g_aAuraEffect[nCntEffect].pos.y - g_aAuraEffect[nCntEffect].fRadius;
			pVtx[1].pos.x = g_aAuraEffect[nCntEffect].pos.x + g_aAuraEffect[nCntEffect].fRadius;
			pVtx[1].pos.y = g_aAuraEffect[nCntEffect].pos.y - g_aAuraEffect[nCntEffect].fRadius;
			pVtx[2].pos.x = g_aAuraEffect[nCntEffect].pos.x - g_aAuraEffect[nCntEffect].fRadius;
			pVtx[2].pos.y = g_aAuraEffect[nCntEffect].pos.y + g_aAuraEffect[nCntEffect].fRadius;
			pVtx[3].pos.x = g_aAuraEffect[nCntEffect].pos.x + g_aAuraEffect[nCntEffect].fRadius;
			pVtx[3].pos.y = g_aAuraEffect[nCntEffect].pos.y + g_aAuraEffect[nCntEffect].fRadius;

			//�s�����x�X�V
			g_aAuraEffect[nCntEffect].col.a += 1.0f / g_aAuraEffect[nCntEffect].nLife;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aAuraEffect[nCntEffect].col;
			pVtx[1].col = g_aAuraEffect[nCntEffect].col;
			pVtx[2].col = g_aAuraEffect[nCntEffect].col;
			pVtx[3].col = g_aAuraEffect[nCntEffect].col;

			//�����Ƒ傫�������炵�Ă���
			g_aAuraEffect[nCntEffect].nLife--;

			if (g_aAuraEffect[nCntEffect].nLife == 0)
			{//�������s����

				g_aAuraEffect[nCntEffect].bUse = false;
			}
		}
		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffAuraEffect->Unlock();
}
//��================================��
//�b�@�@ �G�t�F�N�g�̕`�揈���@�@ �@�b
//��================================��
void DrawAuraEffect(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEffect;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffAuraEffect, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetTexture(0, g_pTextureAuraEffect);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aAuraEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���

		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//��================================��
//�b�@ �@�G�t�F�N�g�̐ݒ菈���@�@ �@�b
//��================================��
void SetAuraEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, int nType)
{
	int nCntEffect;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffAuraEffect->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (g_aAuraEffect[nCntEffect].bUse == false)
		{
			g_aAuraEffect[nCntEffect].pos = pos;
			g_aAuraEffect[nCntEffect].move = move;
			g_aAuraEffect[nCntEffect].col = col;
			g_aAuraEffect[nCntEffect].fRadius = fRadius;
			g_aAuraEffect[nCntEffect].nLife = nLife;
			g_aAuraEffect[nCntEffect].nType = nType;
			g_aAuraEffect[nCntEffect].bUse = true;

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b �@�@���_���W��ݒ�@�@ �b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			pVtx[0].pos.x = g_aAuraEffect[nCntEffect].pos.x - g_aAuraEffect[nCntEffect].fRadius;
			pVtx[0].pos.y = g_aAuraEffect[nCntEffect].pos.y - g_aAuraEffect[nCntEffect].fRadius;
			pVtx[1].pos.x = g_aAuraEffect[nCntEffect].pos.x + g_aAuraEffect[nCntEffect].fRadius;
			pVtx[1].pos.y = g_aAuraEffect[nCntEffect].pos.y - g_aAuraEffect[nCntEffect].fRadius;
			pVtx[2].pos.x = g_aAuraEffect[nCntEffect].pos.x - g_aAuraEffect[nCntEffect].fRadius;
			pVtx[2].pos.y = g_aAuraEffect[nCntEffect].pos.y + g_aAuraEffect[nCntEffect].fRadius;
			pVtx[3].pos.x = g_aAuraEffect[nCntEffect].pos.x + g_aAuraEffect[nCntEffect].fRadius;
			pVtx[3].pos.y = g_aAuraEffect[nCntEffect].pos.y + g_aAuraEffect[nCntEffect].fRadius;

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�@ ���_�J���[ �@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pVtx[0].col = g_aAuraEffect[nCntEffect].col;
			pVtx[1].col = g_aAuraEffect[nCntEffect].col;
			pVtx[2].col = g_aAuraEffect[nCntEffect].col;
			pVtx[3].col = g_aAuraEffect[nCntEffect].col;

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//���_�o�b�t�@�̃A�����b�N
			g_pVtxBuffAuraEffect->Unlock();
			break;
		}
	}
}