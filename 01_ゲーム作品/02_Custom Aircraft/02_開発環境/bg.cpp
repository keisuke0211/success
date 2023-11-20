//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@ �@�w�i�̏����@�@ �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "bg.h"

//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_BG (3)      //�w�i�̐�

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBg = NULL; //���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBg[NUM_BG] = {};//�e�N�X�`��(3����)�ւ̃|�C���^
float g_aTexV[NUM_BG];						 //�e�N�X�`�����W�̊J�n�ʒu(V�l)

int directionMode;
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�w�i�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��==============================��
//�b�@�@�@ �w�i�̏����������@�@ �@�b
//��==============================��
void InitBg(void)
{
	int nCntBG;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Plains.png",
		&g_pTextureBg[0]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\cloud001.png",
		&g_pTextureBg[1]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\cloud002.png",
		&g_pTextureBg[2]);

	//�e�N�X�`�����W�̊J�n�ʒu(V�l)�̏�����
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aTexV[nCntBG] = 0.0f;
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	directionMode = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBg,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBg->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		if (nCntBG == 0)
		{
			//�@�@�@�@�@�@�@�@�@�@�@�@ x       y     z
			pVtx[0].pos = D3DXVECTOR3(000.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f); //�E���Őݒ肷��
			pVtx[2].pos = D3DXVECTOR3(000.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1000.0f, 720.0f, 0.0f); //�����Őݒ肷��
		}
		else if (nCntBG == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(000.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(000.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1000.0f, 720.0f, 0.0f);
		}
		else if (nCntBG == 2)
		{
			pVtx[0].pos = D3DXVECTOR3(000.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(000.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1000.0f, 720.0f, 0.0f);
		}
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pVtx[0].tex = D3DXVECTOR2(0.0f, g_aTexV[nCntBG]);
		pVtx[1].tex = D3DXVECTOR2(1.0f, g_aTexV[nCntBG]);
		pVtx[2].tex = D3DXVECTOR2(0.0f, g_aTexV[nCntBG] + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, g_aTexV[nCntBG] + 1.0f);

		pVtx += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffBg->Unlock();
}
//��==============================��
//�b�@�@  �@�w�i�̏I�������@�@ �@ �b
//��==============================��
void UninitBg(void)
{
	int nCntBG;


	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_pTextureBg[nCntBG] != NULL)
		{
			g_pTextureBg[nCntBG]->Release();
			g_pTextureBg[nCntBG] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffBg != NULL)
	{
		g_pVtxbuffBg->Release();
		g_pVtxbuffBg = NULL;
	}
}
//��==============================��
//�b�@�@�@  �w�i�̍X�V�����@ �@�@ �b
//��==============================��
void UpdateBg(void)
{
	int nCntBG;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBg->Lock(0, 0, (void **)&pVtx, 0);

		for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
		{
			//�e�N�X�`�����W�̊J�n�ʒu(V�l)�̍X�V
			g_aTexV[0] += -0.0009f;
			g_aTexV[1] += -0.0005f;
			g_aTexV[2] += -0.0005f;

			//�e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f, g_aTexV[nCntBG]);
			pVtx[1].tex = D3DXVECTOR2(1.0f, g_aTexV[nCntBG]);
			pVtx[2].tex = D3DXVECTOR2(0.0f, g_aTexV[nCntBG] + 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, g_aTexV[nCntBG] + 1.0f);

			pVtx += 4;
		}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffBg->Unlock();
}
//��==============================��
//�b�@�@ �@ �w�i�̕`�揈�� �@�@�@ �b
//��==============================��
void DrawBg(void)
{
	int nCntBG;

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffBg, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		pDevice->SetTexture(0, g_pTextureBg[nCntBG]);
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,        //�v���~�e�B�u�̎��
		//	2,                                               //�v���~�e�B�u(�|���S��)��
		//	&g_aVertex[0],                                   //���_���̐擪�A�h���X
		//	sizeof(VERTEX_2D));                              //���_���\���̂̃T�C�Y
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 3);
	}
}
