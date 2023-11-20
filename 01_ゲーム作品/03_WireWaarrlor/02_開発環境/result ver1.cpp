//��======================��
//�b�@�@  �@�@�@�@�@�@�@�@�b
//�b�@���U���g��ʂ̏����@�b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include"result ver1.h"
#include"sound.h"
#include "fade.h"

//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_BG (2)      //�w�i�̐�
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffResult1 = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureResult1[NUM_BG] = {};		//�e�N�X�`���ւ̃|�C���^
int g_nCntTime1;											//��莞�Ԍo�߂ŉ�ʐ��ڂ��鏈���Ɏg��
int g_nCnTFlash1;
bool bFlash1;
Result1 g_Result1[NUM_BG];
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y���U���g��ʁE�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��======================================��
//�b�@�@�@ ���U���g��ʂ̏����������@�@ �@�b
//��======================================��
void InitResult1(void)
{
	int nCntResult1;
	g_nCntTime1 = 0;				//�^�C�}�[��������
	g_nCnTFlash1 = 0;
	bFlash1 = false;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\WireWAARRIOR�@�Q�[���I�[�o�[.png", &g_pTextureResult1[0]);

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\WireWAARRIOR�@�Q�[���I�[�o�[1.png", &g_pTextureResult1[1]);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffResult1,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffResult1->Lock(0, 0, (void **)&pVtx, 0);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntResult1 = 0; nCntResult1 < NUM_BG; nCntResult1++, pVtx += 4)
	{
		g_Result1[nCntResult1].bUse;
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
	g_pVtxbuffResult1->Unlock();
	PlaySound(SOUND_LABEL_BGM004); //���Đ��������T�E���h���w��
}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̏I�������@�@ �@�b
//��====================================��
void UninitResult1(void)
{
	int nCntResult1;

	//�T�E���h�̒�~
	StopSound();

	for (nCntResult1 = 0; nCntResult1 < NUM_BG; nCntResult1++)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�e�N�X�`���̔j���@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		if (g_pTextureResult1[nCntResult1] != NULL)
		{
			g_pTextureResult1[nCntResult1]->Release();
			g_pTextureResult1[nCntResult1] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffResult1 != NULL)
	{
		g_pVtxbuffResult1->Release();
		g_pVtxbuffResult1 = NULL;
	}
}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̍X�V�����@�@ �@�b
//��====================================��
void UpdateResult1(void)
{
	//��ʐ��ځi���U���g1 �� �^�C�g���j

	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{// ����L�[ [ ENTER�L�[ ] �������ꂽ

		 //���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_START && GetFade() == FADE_NONE)
	{
		//���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_A && GetFade() == FADE_NONE)
	{
		//���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (GetFade() == FADE_NONE && g_nCntTime1 == SWITCH_TIME)
	{//���U���g��ʂɗ��Ă���10�b��������^�C�g����ʂɐ؂�ւ��

		//���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (GetFade() == FADE_NONE)
	{
		g_nCntTime1++;		//�t�F�[�h�� FADE_NONE �̏�ԂɂȂ�����1�t���[�����J�E���g����
	}
	//�_��
	g_nCnTFlash1++;

	if (g_nCnTFlash1 >= 26 && bFlash1 == false)
	{//�_�Ő؂�ւ����ԂɂȂ���
		g_Result1[0].bUse = g_Result1[0].bUse ? false : true;
		g_nCnTFlash1 = 0;
	}
	else if (g_nCnTFlash1 >= 6 && bFlash1 == true)
	{
		g_Result1[0].bUse = g_Result1[0].bUse ? false : true;
		g_nCnTFlash1 = 0;
	}

}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̕`�揈���@�@ �@�b
//��====================================��
void DrawResult1(void)
{
	int nCntResult1;

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffResult1, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntResult1 = 0; nCntResult1 < NUM_BG; nCntResult1++)
	{
		pDevice->SetTexture(0, g_pTextureResult1[nCntResult1]);
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntResult1 * 4, 2);
	}
}