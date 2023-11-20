//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@���C�t�̏���      �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "life.h"

//****************************************
//�}�N����`
//****************************************
#define NUM_PLACE (2) //���C�t�̌���

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffLife = NULL;
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;
D3DXVECTOR3 g_posLife;			//�X�R�A�̈ʒu
int g_nLife;					//�X�R�A�̒l

//****************************************
//���C�t�̏���������
//****************************************
void InitLife(void)
{
	int nCntLife;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\number000.png", &g_pTextureLife);

	g_posLife = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 0);	//�ʒu��������
	g_nLife = 0;														//�l��������

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffLife,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffLife->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++, pVtx += 4)
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
	g_pVtxbuffLife->Unlock();

	SetLife(g_nLife);
}
//****************************************
// ���C�t�̏I������
//****************************************
void UninitLife(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffLife != NULL)
	{
		g_pVtxbuffLife->Release();
		g_pVtxbuffLife = NULL;
	}
}
//****************************************
// ���C�t�̍X�V����
//****************************************
void UpdateLife(void)
{
	int nCntLife;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffLife->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pVtx[0].pos = D3DXVECTOR3(1200.0f + (nCntLife * 25.0f), 350.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1220.0f + (nCntLife * 25.0f), 350.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1200.0f + (nCntLife * 25.0f), 390.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1220.0f + (nCntLife * 25.0f), 390.0f, 0.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffLife->Unlock();
}
//****************************************
// ���C�t�̕`�揈��
//****************************************
void DrawLife(void)
{
	int nCntLife;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffLife, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->SetTexture(0, g_pTextureLife);

	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
	}
}
//****************************************
// ���C�t�̐ݒ菈��
//****************************************
void SetLife(int nScore)
{
	int nCntLife;
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	g_nLife = nScore;

	aTexU[0] = g_nLife % 100 / 10;
	aTexU[1] = g_nLife % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffLife->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntLife] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntLife] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntLife] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntLife] * 0.1f), 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffLife->Unlock();
}
//****************************************
// ���C�t�̉��Z����
//****************************************
void AddLife(int nValue)
{
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	int nCntLife;

	g_nLife += nValue;

	aTexU[0] = g_nLife % 100 / 10;
	aTexU[1] = g_nLife % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffLife->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntLife] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntLife] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntLife] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntLife] * 0.1f), 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffLife->Unlock();
}
//****************************************
// ���C�t�̌��Z����
//****************************************
void DeleteLife(int nValue)
{
	int aTexU[NUM_PLACE]; //�e���̐������i�[
	int nCntLife;

	//�v���C���[�̗̑͂��Ȃ��Ȃ�����
	if (g_nLife == 0)
	{ }

	else if (g_nLife > 0)
	{
		g_nLife -= nValue;
	}

	aTexU[0] = g_nLife % 100 / 10;
	aTexU[1] = g_nLife % 10 / 1;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffLife->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntLife] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntLife] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntLife] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntLife] * 0.1f), 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffLife->Unlock();
}
//��========================��
//�b�@�@ �X�R�A�̏����@�@ �@�b
//��========================��
int GetLife(void)
{
	return g_nLife;
}