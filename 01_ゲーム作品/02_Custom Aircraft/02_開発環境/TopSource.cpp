//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�X�R�A�̏���      �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "TopSource.h"

//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_PLACE (8) //�X�R�A�̌���

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTopScore = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTopScore = NULL;
D3DXVECTOR3 g_posTopScore;							//�X�R�A�̈ʒu
int g_nTopScore;									//�X�R�A�̒l

//==================================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�X�R�A�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==================================================================================================================================================

//��================================��
//�b�@�@�@ �X�R�A�̏����������@�@ �@�b
//��================================��
void InitTopScore(void)
{
	int nCntScore;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\number000.png", &g_pTextureTopScore);

	g_posTopScore = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0);	//�ʒu��������

	FILE *pFile;	//�t�@�C���|�C���^��錾


	// �t�@�C�����J��
	pFile = fopen("data\\ranking.bin", "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�t�@�C������f�[�^������������
		fread(&g_nTopScore, sizeof(int), 1, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		g_nTopScore = 5000;
	}
	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTopScore,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTopScore->Lock(0, 0, (void **)&pVtx, 0);

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
	g_pVtxbuffTopScore->Unlock();

	SetTopScore(g_nTopScore);
}
//��==============================��
//�b�@�@�@ �X�R�A�̏I�������@�@ �@�b
//��==============================��
void UninitTopScore(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureTopScore != NULL)
	{
		g_pTextureTopScore->Release();
		g_pTextureTopScore = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffTopScore != NULL)
	{
		g_pVtxbuffTopScore->Release();
		g_pVtxbuffTopScore = NULL;
	}
}
//��==============================��
//�b�@�@�@ �X�R�A�̍X�V�����@�@ �@�b
//��==============================��
void UpdateTopScore(void)
{
	int nCntScore;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTopScore->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pVtx[0].pos = D3DXVECTOR3(1070.0f + (nCntScore * 25.0f), 90.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1090.0f + (nCntScore * 25.0f), 90.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1070.0f + (nCntScore * 25.0f), 130.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1090.0f + (nCntScore * 25.0f), 130.0f, 0.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTopScore->Unlock();
}
//��==============================��
//�b�@�@�@ �X�R�A�̕`�揈���@�@ �@�b
//��==============================��
void DrawTopScore(void)
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
	pDevice->SetStreamSource(0, g_pVtxbuffTopScore, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->SetTexture(0, g_pTextureTopScore);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//��==============================��
//�b�@�@�@ �X�R�A�̐ݒ菈���@�@ �@�b
//��==============================��
void SetTopScore(int nScore)
{
	int nCntScore;
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	g_nTopScore = nScore;

	aTexU[0] = g_nTopScore % 100000000 / 10000000;
	aTexU[1] = g_nTopScore % 10000000 / 1000000;
	aTexU[2] = g_nTopScore % 1000000 / 100000;
	aTexU[3] = g_nTopScore % 100000 / 10000;
	aTexU[4] = g_nTopScore % 10000 / 1000;
	aTexU[5] = g_nTopScore % 1000 / 100;
	aTexU[6] = g_nTopScore % 100 / 10;
	aTexU[7] = g_nTopScore % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffTopScore->Lock(0, 0, (void **)&pVtx, 0);
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
	g_pVtxbuffTopScore->Unlock();
}
//��========================��
//�b�@�@ �X�R�A�̏����@�@ �@�b
//��========================��
int GetTopScore(void)
{
	return g_nTopScore;
}
//��==============================��
//�b�@�@�@ �X�R�A�̉��Z�����@�@ �@�b
//��==============================��

//void AddTopScore(int nValue)
//{
//	int aTexU[NUM_PLACE]; //�e���̐������i�[
//	int nCntScore;
//
//	g_nTopScore += nValue;
//
//	aTexU[0] = g_nTopScore % 100000000 / 10000000;
//	aTexU[1] = g_nTopScore % 10000000 / 1000000;
//	aTexU[2] = g_nTopScore % 1000000 / 100000;
//	aTexU[3] = g_nTopScore % 100000 / 10000;
//	aTexU[4] = g_nTopScore % 10000 / 1000;
//	aTexU[5] = g_nTopScore % 1000 / 100;
//	aTexU[6] = g_nTopScore % 100 / 10;
//	aTexU[7] = g_nTopScore % 10 / 1;
//
//	//�ݒ�p�|�C���^
//	VERTEX_2D *pVtx;
//
//	//���_�o�b�t�@�̃��b�N
//	g_pVtxbuffTopScore->Lock(0, 0, (void **)&pVtx, 0);
//
//	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
//	{
//		//���\�\�\�\�\�\�\�\�\�\�\�\��
//		//�b�@�e�N�X�`�����W�̐ݒ�@�b
//		//���\�\�\�\�\�\�\�\�\�\�\�\��
//		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);
//	}
//	//���_�o�b�t�@�̃A�����b�N
//	g_pVtxbuffTopScore->Unlock();
//}