//��======================��
//�b�@�@�@�@�@�@�@�@�@�@�@�b
//�b�@�����摜�E�\������  �b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include"text.h"

//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_MAX (1) //�e�L�X�g�摜�̐�

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffText = NULL;
LPDIRECT3DTEXTURE9 g_pTextureText[NUM_MAX] = {};

//====================================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�e�L�X�g�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//====================================================================================================================================================

//��==================================��
//�b�@�@�@ �e�L�X�g�̏����������@�@ �@�b
//��==================================��
void InitText(void)
{
	int nCntText;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\TIME.png", &g_pTextureText[0]);



	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffText,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffText->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntText = 0; nCntText < NUM_MAX; nCntText++,pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
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
		pVtx[0].tex = D3DXVECTOR2(0.01f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.01f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffText->Unlock();
}

//��==============================��
//�b�@�@�@ �e�L�X�g�̏I�������@�@ �@�b
//��==============================��
void UninitText(void)
{
	int nCnttext;
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCnttext = 0; nCnttext < NUM_MAX; nCnttext++)
	{
		if (g_pTextureText[nCnttext] != NULL)
		{
			g_pTextureText[nCnttext]->Release();
			g_pTextureText[nCnttext] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffText != NULL)
	{
		g_pVtxbuffText->Release();
		g_pVtxbuffText = NULL;
	}
}
//��============================��
//�b�@�@�@ �����̍X�V�����@�@ �@�b
//��============================��
void UpdateText(void)
{
	int nCntText;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffText->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntText = 0; nCntText < NUM_MAX; nCntText++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		if (nCntText == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(1000.0f, 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1150.0f, 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1000.0f, 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1150.0f, 50.0f, 0.0f);
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffText->Unlock();
}
//��============================��
//�b�@�@�@ �e�L�X�g�̕`�揈���@ �b
//��============================��
void DrawaText(void)
{
	int nCntText;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffText, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntText = 0; nCntText < NUM_MAX; nCntText++)
	{
		pDevice->SetTexture(0, g_pTextureText[nCntText]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntText * 4, 2);
	}
}