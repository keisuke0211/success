//��======================��
//�b�@�@�@�@�@�@�@�@�@�@�@�b
//�b�@�g�E�\������		�@�b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include "camera.h"
#include "frame.h"

//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define MAX_FRAME (3) //�e�L�X�g�摜�̐�

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFrame = NULL;
LPDIRECT3DTEXTURE9 g_pTextureFrame = NULL;
Frame g_aFrame[MAX_FRAME];
//====================================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�e�L�X�g�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//====================================================================================================================================================

//��==================================��
//�b�@�@�@ �e�L�X�g�̏����������@�@ �@�b
//��==================================��
void InitFrame(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\frame.png", &g_pTextureFrame);


	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		g_aFrame[nCntFrame].pos = DEFAULT_D3DXVECTOR3;
		g_aFrame[nCntFrame].fHight = 0.0f;
		g_aFrame[nCntFrame].fWidth = 0.0f;
		g_aFrame[nCntFrame].bUse = false;
	}

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFrame,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFrame->Lock(0, 0, (void **)&pVtx, 0);
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x, g_aFrame[nCntFrame].pos.y, g_aFrame[nCntFrame].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x + g_aFrame[nCntFrame].fWidth, g_aFrame[nCntFrame].pos.y, g_aFrame[nCntFrame].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x, g_aFrame[nCntFrame].pos.y + g_aFrame[nCntFrame].fHight, g_aFrame[nCntFrame].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x + g_aFrame[nCntFrame].fWidth, g_aFrame[nCntFrame].pos.y + g_aFrame[nCntFrame].fHight, g_aFrame[nCntFrame].pos.z);
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
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffFrame->Unlock();
}

//��==============================��
//�b�@�@�@ �e�L�X�g�̏I�������@�@ �b
//��==============================��
void UninitFrame(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureFrame != NULL)
	{
		g_pTextureFrame ->Release();
		g_pTextureFrame = NULL;
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffFrame != NULL)
	{
		g_pVtxbuffFrame->Release();
		g_pVtxbuffFrame = NULL;
	}
}
//��============================��
//�b�@�@�@ �����̍X�V�����@�@ �@�b
//��============================��
void UpdateFrame(void)
{
	Camera *pCamera = Getcamara(0);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFrame->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++, pCamera++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		if (pCamera->bUse == true && nCntFrame >= 1)
		{
			g_aFrame[nCntFrame].pos.x = pCamera->viewport.X;
			g_aFrame[nCntFrame].pos.y = pCamera->viewport.Y;
			g_aFrame[nCntFrame].fWidth = pCamera->viewport.Width;
			g_aFrame[nCntFrame].fHight = pCamera->viewport.Height;
			g_aFrame[nCntFrame].bUse = true;


			pVtx[0].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x, g_aFrame[nCntFrame].pos.y, g_aFrame[nCntFrame].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x + g_aFrame[nCntFrame].fWidth, g_aFrame[nCntFrame].pos.y, g_aFrame[nCntFrame].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x, g_aFrame[nCntFrame].pos.y + g_aFrame[nCntFrame].fHight, g_aFrame[nCntFrame].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x + g_aFrame[nCntFrame].fWidth, g_aFrame[nCntFrame].pos.y + g_aFrame[nCntFrame].fHight, g_aFrame[nCntFrame].pos.z);
		}
		else if (pCamera->bUse == false)
		{
			g_aFrame[nCntFrame].bUse = false;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffFrame->Unlock();
}
//��============================��
//�b�@�@�@ �e�L�X�g�̕`�揈���@ �b
//��============================��
void DrawaFrame(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		if (g_aFrame[nCntFrame].bUse == true)
		{
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�f�[�^�X�g���[���̐ݒ�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxbuffFrame, 0, sizeof(VERTEX_2D));

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b���_�t�H�[�}�b�g�̐ݒ�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pDevice->SetFVF(FVF_VERTEX_2D);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�e�N�X�`���̐ݒ�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
				pDevice->SetTexture(0, g_pTextureFrame);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFrame * 4, 2);
		}
	}
}