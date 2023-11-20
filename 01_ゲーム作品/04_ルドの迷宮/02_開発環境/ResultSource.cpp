//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�^�C�}�[�̏���    �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "ResultSource.h"
#include "time.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_PLACE (2) //�X�R�A�̌���

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTime11 = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTime11 = NULL;
D3DXVECTOR3 g_posTime11;			//�X�R�A�̈ʒu
int g_nTime11;					//�X�R�A�̒l
int g_InitTime11;					//�����̃X�R�A
//==================================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�X�R�A�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==================================================================================================================================================

//��================================��
//�b�@�@�@ �X�R�A�̏����������@�@ �@�b
//��================================��
void InitResulyScore(void)
{
	int nCntScore;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\number005.png", &g_pTextureTime11);

	g_posTime11 = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0);	//�ʒu��������
	g_nTime11 = 300;														//�l��������
	g_InitTime11 = 300;

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTime11,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTime11->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(16.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(16.0f, 50.0f, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTime11->Unlock();

	SetResult(g_nTime11);
}
//��==============================��
//�b�@�@�@ �X�R�A�̏I�������@�@ �@�b
//��==============================��
void UninitResulyScore(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureTime11 != NULL)
	{
		g_pTextureTime11->Release();
		g_pTextureTime11 = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffTime11 != NULL)
	{
		g_pVtxbuffTime11->Release();
		g_pVtxbuffTime11 = NULL;
	}
}
//��==============================��
//�b�@�@�@ �X�R�A�̍X�V�����@�@ �@�b
//��==============================��
void UpdateResulyScore(void)
{
	int Score;

	Score = 90 - GetTime();
	SetResult(Score);
}
//��==============================��
//�b�@�@�@ �X�R�A�̕`�揈���@�@ �@�b
//��==============================��
void DrawResulyScore(void)
{
	int nCntScore;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTime11, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->SetTexture(0, g_pTextureTime11);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//��==============================��
//�b�@�@�@ �X�R�A�̐ݒ菈���@�@ �@�b
//��==============================��
void SetResult(int nScore)
{
	int nCntScore;
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	g_nTime11 = nScore;

	aTexU[0] = g_nTime11 % 100 / 10;
	aTexU[1] = g_nTime11 % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffTime11->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pVtx[0].pos = D3DXVECTOR3(500.0f + (nCntScore * 65.0f), 390.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(540.0f + (nCntScore * 65.0f), 390.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f + (nCntScore * 65.0f), 440.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(540.0f + (nCntScore * 65.0f), 440.0f, 0.0f);
		
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTime11->Unlock();
}