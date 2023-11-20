//��======================��
//�b�@�@  �@�@�@�@�@�@�@�@�b
//�b�@���U���g��ʂ̏����@�b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include"result ver2.h"
#include "ResultSource.h"
#include"sound.h"
#include "fade.h"

//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_BG (1)      //�w�i�̐�
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffResult2 = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureResult2[NUM_BG] = {};		//�e�N�X�`���ւ̃|�C���^
int g_nCntTime2;											//��莞�Ԍo�߂ŉ�ʐ��ڂ��鏈���Ɏg��

//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y���U���g��ʁE�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��======================================��
//�b�@�@�@ ���U���g��ʂ̏����������@�@ �@�b
//��======================================��
void InitResult2(void)
{
	int nCntResult2;
	g_nCntTime2 = 0;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\WireWAARRIOR�@�Q�[���N���A.png", &g_pTextureResult2[0]);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffResult2,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffResult2->Lock(0, 0, (void **)&pVtx, 0);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	for (nCntResult2 = 0; nCntResult2 < NUM_BG; nCntResult2++, pVtx += 4)
	{
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
	g_pVtxbuffResult2->Unlock();

	InitResulyScore();
	UpdateResulyScore();
	PlaySound(SOUND_LABEL_BGM003); //���Đ��������T�E���h���w��

}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̏I�������@�@ �@�b
//��====================================��
void UninitResult2(void)
{
	int nCntResult2;

	//�T�E���h�̒�~
	StopSound();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntResult2 = 0; nCntResult2 < NUM_BG; nCntResult2++)
	{
		if (g_pTextureResult2[nCntResult2] != NULL)
		{
			g_pTextureResult2[nCntResult2]->Release();
			g_pTextureResult2[nCntResult2] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffResult2 != NULL)
	{
		g_pVtxbuffResult2->Release();
		g_pVtxbuffResult2 = NULL;
	}
	UninitResulyScore();

}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̍X�V�����@�@ �@�b
//��====================================��
void UpdateResult2(void)
{
	//��ʐ��ځi���U���g2 �� �^�C�g���j
	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE) {// ����L�[ [ ENTER�L�[ ] �������ꂽ

	 //���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_START && GetFade() == FADE_NONE)
	{
		//���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_A&& GetFade() == FADE_NONE)
	{
		//���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (GetFade() == FADE_NONE && g_nCntTime2 == SWITCH_TIME)
	{//���U���g��ʂɗ��Ă���10�b��������^�C�g����ʂɐ؂�ւ��

	 //���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (GetFade() == FADE_NONE)
	{
		g_nCntTime2++;		//�t�F�[�h�� FADE_NONE �̏�ԂɂȂ�����1�t���[�����J�E���g����
	}
}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̕`�揈���@�@ �@�b
//��====================================��
void DrawResult2(void)
{
	int nCntResult2;

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffResult2, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	for (nCntResult2 = 0; nCntResult2 < NUM_BG; nCntResult2++)
	{
		pDevice->SetTexture(0, g_pTextureResult2[nCntResult2]);
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,       //�v���~�e�B�u�̎��
		//	2,                                               //�v���~�e�B�u(�|���S��)��
		//	&g_aVertex[0],                                   //���_���̐擪�A�h���X
		//	sizeof(VERTEX_2D));                              //���_���\���̂̃T�C�Y

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntResult2 * 4, 2);
	}

	DrawResulyScore();

}