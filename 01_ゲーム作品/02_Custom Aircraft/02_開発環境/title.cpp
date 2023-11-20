//��======================��
//�b�@�@  �@�@�@�@�@�@�@�@�b
//�b�@�^�C�g����ʂ̏����@�b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include"title.h"
#include"sound.h"
#include "fade.h"
#include "player.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_BG (4)      //�w�i�̐�
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitle = NULL;		//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_BG] = {};    //�e�N�X�`��(4����)�ւ̃|�C���^
D3DXCOLOR g_colorTitle;								//�|���S��(�t�F�[�h)�̐F

int g_nCnTFlash;									 //�_�Ŏ���
bool bFlash;										 //�_�Ő؂�ւ�
TITLE g_Title[NUM_BG];								 //�G�̏��
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�^�C�g����ʁE�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��======================================��
//�b�@�@�@ �^�C�g����ʂ̏����������@�@ �@�b
//��======================================��
void InitTitle(void)
{
	int nCntTitle;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\bg000.jpg",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Custom.png",
		&g_pTextureTitle[1]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Aircraft.png",
		&g_pTextureTitle[2]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\-PRESS ENTER-.png",
		&g_pTextureTitle[3]);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	g_nCnTFlash = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitle,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);

	bFlash = false;
	for (nCntTitle = 0; nCntTitle < NUM_BG; nCntTitle++, pVtx += 4)
	{
		g_colorTitle = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(�s����)�ɂ��Ă���
		g_Title[nCntTitle].bUse = true;
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		//�@�@�@�@�@�@�@�@�@�@�@�@ x       y     z
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f); //�E���Őݒ肷��
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f); //�����Őݒ肷��

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

		if (nCntTitle == 1 || nCntTitle == 2)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		}
		else if (nCntTitle == 0 || nCntTitle == 3)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	g_Title[4].state = TITLESTATE_NORMAL;
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM000); //���Đ��������T�E���h���w��

}
//��====================================��
//�b�@�@�@ �^�C�g����ʂ̏I�������@�@ �@�b
//��====================================��
void UninitTitle(void)
{
	int nCntTitle;

	//�T�E���h�̒�~
	StopSound();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntTitle = 0; nCntTitle < NUM_BG; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffTitle != NULL)
	{
		g_pVtxbuffTitle->Release();
		g_pVtxbuffTitle = NULL;
	}
}
//��====================================��
//�b�@�@�@ �^�C�g����ʂ̍X�V�����@�@ �@�b
//��====================================��
void UpdateTitle(void)
{	
	XINPUT_STATE *xInput = GetXInputState();
	Player *pPlayer = Getplayer();						//�v���C���[�̏��ւ̃|�C���^


	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{// ����L�[ [ ENTER�L�[ ] �������ꂽ

		pPlayer->bBph = false;												//�R���g���[���̐U���I�t
		PlaySound(SOUND_LABEL_SE_START);									//���Đ��������T�E���h���w��
		bFlash = true;
		//���[�h�̐ݒ�
		SetFade(MODE_TUTORIAL);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_START && GetFade() == FADE_NONE)
	{
		pPlayer->bBph = true;												//�R���g���[���̐U���I��
		PlaySound(SOUND_LABEL_SE_START);									//���Đ��������T�E���h���w��
		bFlash = true;
		//���[�h�̐ݒ�
		SetFade(MODE_TUTORIAL);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_A&& GetFade() == FADE_NONE)
	{
		pPlayer->bBph = true;												//�R���g���[���̐U���I��
		PlaySound(SOUND_LABEL_SE_START);									//���Đ��������T�E���h���w��
		bFlash = true;
		//���[�h�̐ݒ�
		SetFade(MODE_TUTORIAL);
	}
	//�_��
	g_nCnTFlash++;

			//�t�F�[�h�A�E�g
			g_colorTitle.a += 0.015f; //�|���S����s�����ɂ��Ă���

			if (g_colorTitle.a >= 1.0f)
			{
				g_colorTitle.a = 1.0f;
			}

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorTitle.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorTitle.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorTitle.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorTitle.a);

	for (int nCntTitle = 0; nCntTitle < NUM_BG; nCntTitle++, pVtx += 4)
	{
		if (nCntTitle >= 1 && nCntTitle <= 2)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorTitle.a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorTitle.a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorTitle.a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorTitle.a);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	g_pVtxbuffTitle->Unlock();


	if (g_nCnTFlash >= 26 && bFlash == false)
	{//�_�Ő؂�ւ����ԂɂȂ���
		g_Title[3].bUse = g_Title[3].bUse ? false : true;
		g_nCnTFlash = 0;
	}
	else if (g_nCnTFlash >= 6 && bFlash == true)
	{
		g_Title[3].bUse = g_Title[3].bUse ? false : true;
		g_nCnTFlash = 0;
	}
}
//��====================================��
//�b�@�@�@ �^�C�g����ʂ̕`�揈���@�@ �@�b
//��====================================��
void DrawTitle(void)
{
	int nCntTitle;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTitle, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	
	for (nCntTitle = 0; nCntTitle < NUM_BG; nCntTitle++)
	{
		if (g_Title[nCntTitle].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�|���S���̕`��@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 4);
		}
	}
}