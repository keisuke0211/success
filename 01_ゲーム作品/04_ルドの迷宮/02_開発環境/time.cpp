//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�^�C���̏���      �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "time.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_PLACE (2) //�X�R�A�̌���

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTime = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;
D3DXVECTOR3 g_posTime;			//�X�R�A�̈ʒu
int g_nTime;					//�X�R�A�̒l

//==================================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�X�R�A�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==================================================================================================================================================

//��================================��
//�b�@�@�@ �^�C���̏����������@�@ �@�b
//��================================��
void InitTime(void)
{
	int nCntScore;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\number002.png", &g_pTextureTime);

	g_posTime = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);	//�ʒu��������
	g_nTime = 90;												//�l��������

																		//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTime,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTime->Lock(0, 0, (void **)&pVtx, 0);

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
	g_pVtxbuffTime->Unlock();

	SetTime(g_nTime);
}
//��==============================��
//�b�@�@�@ �X�R�A�̏I�������@�@ �@�b
//��==============================��
void UninitTime(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffTime != NULL)
	{
		g_pVtxbuffTime->Release();
		g_pVtxbuffTime = NULL;
	}
}
//��==============================��
//�b�@�@�@ �X�R�A�̍X�V�����@�@ �@�b
//��==============================��
void UpdateTime(void)
{
	int nCntScore;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTime->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pVtx[0].pos = D3DXVECTOR3(635.0f + (nCntScore * 25.0f), 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(660.0f + (nCntScore * 25.0f), 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(635.0f + (nCntScore * 25.0f), 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(660.0f + (nCntScore * 25.0f), 60.0f, 0.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTime->Unlock();
}
//��==============================��
//�b�@�@�@ �X�R�A�̕`�揈���@�@ �@�b
//��==============================��
void DrawTime(void)
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
	pDevice->SetStreamSource(0, g_pVtxbuffTime, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->SetTexture(0, g_pTextureTime);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//��==============================��
//�b�@�@�@ �X�R�A�̐ݒ菈���@�@ �@�b
//��==============================��
void SetTime(int nScore)
{
	int nCntScore;
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	g_nTime = nScore;

	aTexU[0] = g_nTime % 100 / 10;
	aTexU[1] = g_nTime % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffTime->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTime->Unlock();
}
//��==============================��
//�b�@�@�@ �X�R�A�̉��Z�����@�@ �@�b
//��==============================��
void AddTime(int nValue)
{
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	int nCntScore;

	g_nTime += nValue;

	/*if (g_nScore >= GetTopScore())
	{
	SetTopScore(g_nScore);
	}*/
	aTexU[0] = g_nTime % 100 / 10;
	aTexU[1] = g_nTime % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffTime->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTime->Unlock();
}
//��========================��
//�b�@�@ �X�R�A�̏����@�@ �@�b
//��========================��
int GetTime(void)
{
	return g_nTime;
}