//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@ �@�w�i�̏����@�@ �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "bg.h"
#include "camera.h"
//****************************************
// �}�N����`
//****************************************
#define NUM_BG	(5) //�u���b�N�̎��
//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBg = NULL; //���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBg[NUM_BG] = {};//�e�N�X�`��(3����)�ւ̃|�C���^

float g_aTexV[NUM_BG];						 //�e�N�X�`�����W�̊J�n�ʒu(V�l)
//****************************************
// �w�i�̏���������
//****************************************
void InitBg(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,".\\data\\TEXTURE\\Dir.png",&g_pTextureBg[0]);
	D3DXCreateTextureFromFile(pDevice,".\\data\\TEXTURE\\PixelSky_layer01.png",&g_pTextureBg[1]);
	D3DXCreateTextureFromFile(pDevice,".\\data\\TEXTURE\\PixelSky_layer02.png",&g_pTextureBg[2]);
	D3DXCreateTextureFromFile(pDevice,".\\data\\TEXTURE\\PixelSky_layer03.png",&g_pTextureBg[3]);
	D3DXCreateTextureFromFile(pDevice,".\\data\\TEXTURE\\bg_mountain_000.png",&g_pTextureBg[4]);


	//�e�N�X�`�����W�̊J�n�ʒu(V�l)�̏�����
	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aTexV[nCntBG] = 0.0f;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

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

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++, pVtx += 4)
	{
		if (nCntBg == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 490.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 490.0f, 0.0f); //�E���Őݒ肷��
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f); //�����Őݒ肷��
		}
		else if (nCntBg == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f); //�E���Őݒ肷��
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f); //�����Őݒ肷��
		}
		else  if(nCntBg == 2 || nCntBg == 3)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f); //�E���Őݒ肷��
			pVtx[2].pos = D3DXVECTOR3(0.0f, 575, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 575, 0.0f); //�����Őݒ肷��
		}
		else if (nCntBg == 4)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 400.0f, 0.0f); //�E���Őݒ肷��
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f); //�����Őݒ肷��
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

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffBg->Unlock();
}
//****************************************
// �w�i�̏I������
//****************************************
void UninitBg(void)
{

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (int nCnt = 0; nCnt < NUM_BG; nCnt++)
	{
		if (g_pTextureBg[nCnt] != NULL)
		{
			g_pTextureBg[nCnt]->Release();
			g_pTextureBg[nCnt] = NULL;
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
//****************************************
// �w�i�̍X�V����
//****************************************
void UpdateBg(void)
{
	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBg->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++,pVtx += 4)
	{
		//�e�N�X�`�����W�̊J�n�ʒu(V�l)�̍X�V
		g_aTexV[1] += 0.0000f;
		g_aTexV[2] += 0.0002f;
		g_aTexV[3] += 0.0001f;

		//�e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(g_aTexV[nCntBG],0.09f);
		pVtx[1].tex = D3DXVECTOR2(g_aTexV[nCntBG] + 1.0f,0.09f);
		pVtx[2].tex = D3DXVECTOR2(g_aTexV[nCntBG],1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aTexV[nCntBG] + 1.0f,1.0f);
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffBg->Unlock();
}
//****************************************
// �w�i�̕`�揈��
//****************************************
void DrawBg(void)
{

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
	for (int nCnt = 0; nCnt < NUM_BG; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureBg[nCnt]);
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt* 4, 2);
	}
}