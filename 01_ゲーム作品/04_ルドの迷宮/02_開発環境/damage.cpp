//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�^�C���̏���      �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "damage.h"
#include "wall.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_PLACE (3) //�X�R�A�̌���

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffDamage = NULL;
LPDIRECT3DTEXTURE9 g_pTextureDamage = NULL;
D3DXVECTOR3 g_posDamage;			//�X�R�A�̈ʒu
int g_nDamage;					//�X�R�A�̒l

//==================================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�X�R�A�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==================================================================================================================================================

//��================================��
//�b�@�@�@ �^�C���̏����������@�@ �@�b
//��================================��
void InitDamage(void)
{
	BreakWall *pBreakWall = GetBreakWall();

	int nCntScore;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\number002.png", &g_pTextureDamage);

	g_posDamage = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);	//�ʒu��������
	g_nDamage = 100;											//�l��������

	g_nDamage = pBreakWall->Current_F * 100;

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffDamage,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffDamage->Lock(0, 0, (void **)&pVtx, 0);

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
	g_pVtxbuffDamage->Unlock();

	SetDamage(g_nDamage);
}
//��==============================��
//�b�@�@�@ �X�R�A�̏I�������@�@ �@�b
//��==============================��
void UninitDamage(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureDamage != NULL)
	{
		g_pTextureDamage->Release();
		g_pTextureDamage = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffDamage != NULL)
	{
		g_pVtxbuffDamage->Release();
		g_pVtxbuffDamage = NULL;
	}
}
//��==============================��
//�b�@�@�@ �X�R�A�̍X�V�����@�@ �@�b
//��==============================��
void UpdateDamage(void)
{
	int nCntScore;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffDamage->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pVtx[0].pos = D3DXVECTOR3(220.0f + (nCntScore * 25.0f), 90.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(245.0f + (nCntScore * 25.0f), 90.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(220.0f + (nCntScore * 25.0f), 130.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(245.0f + (nCntScore * 25.0f), 130.0f, 0.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffDamage->Unlock();
}
//��==============================��
//�b�@�@�@ �X�R�A�̕`�揈���@�@ �@�b
//��==============================��
void DrawDamage(void)
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
	pDevice->SetStreamSource(0, g_pVtxbuffDamage, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->SetTexture(0, g_pTextureDamage);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//��==============================��
//�b�@�@�@ �X�R�A�̐ݒ菈���@�@ �@�b
//��==============================��
void SetDamage(int nScore)
{
	int nCntScore;
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	g_nDamage = nScore;

	aTexU[0] = g_nDamage % 1000 / 100;
	aTexU[1] = g_nDamage % 100 / 10;
	aTexU[2] = g_nDamage % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffDamage->Lock(0, 0, (void **)&pVtx, 0);
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
	g_pVtxbuffDamage->Unlock();
}
//��==============================��
//�b�@�@�@ �X�R�A�̉��Z�����@�@ �@�b
//��==============================��
void AddDamage(int nValue)
{
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	int nCntScore;

	g_nDamage += nValue;

	/*if (g_nScore >= GetTopScore())
	{
	SetTopScore(g_nScore);
	}*/
	aTexU[0] = g_nDamage % 1000 / 100;
	aTexU[1] = g_nDamage % 100 / 10;
	aTexU[2] = g_nDamage % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffDamage->Lock(0, 0, (void **)&pVtx, 0);

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
	g_pVtxbuffDamage->Unlock();
}
//��========================��
//�b�@�@ �X�R�A�̏����@�@ �@�b
//��========================��
int GetDamage(void)
{
	return g_nDamage;
}