//��============================��
//�b�@�@  �@�@�@�@�@	  �@�@�@�b
//�b�@�`���[�g���A����ʂ̏����@�b
//�b�@Author:��a�c��@			�b
//�b							�b
//��============================��
#include"tutorial.h"
#include"sound.h"
#include "fade.h"

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTutorial = NULL;							//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureTutorial [TUTORIAL_LABEL_MAX] = {};			//�e�N�X�`���ւ̃|�C���^

int g_nCntTime5;
int nType;
//****************************************
//�e�N�X�`���t�@�C����
//****************************************
const char *c_apFllenameTUTORIAL[TUTORIAL_LABEL_MAX] =
{
	"data/TEXTURE/WireWAARRIOR�@������@�i�L�[�{�[�h�j1-1.png",
	"data/TEXTURE/WireWAARRIOR�@������@�i�L�[�{�[�h�j1-2.png",
	"data/TEXTURE/WireWAARRIOR�@������@�i�L�[�{�[�h�j1-3.png",
	"data/TEXTURE/WireWAARRIOR�@������@�i�L�[�{�[�h�j1-4.png",
	"data/TEXTURE/WireWAARRIOR�@������@�i�L�[�{�[�h�j1-5.png",

};
//��======================================��
//�b�@�@�@ ���U���g��ʂ̏����������@�@ �@�b
//��======================================��
void InitTutorial(void)
{
	int nCntResult1;
	g_nCntTime5 = 0;				//�^�C�}�[��������
	nType = 0;
									//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	for (int nCntTexture = 0; nCntTexture < TUTORIAL_LABEL_MAX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFllenameTUTORIAL[nCntTexture],
			&g_pTextureTutorial[nCntTexture]);
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTutorial,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTutorial->Lock(0, 0, (void **)&pVtx, 0);

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

		PlaySound(SOUND_LABEL_BGM000); //���A��BJM

}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̏I�������@�@ �@�b
//��====================================��
void UninitTutorial(void)
{
	//�T�E���h�̒�~
	StopSound();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (int nCntBlock = 0; nCntBlock < TUTORIAL_LABEL_MAX; nCntBlock++)
	{

		if (g_pTextureTutorial[nCntBlock] != NULL)
		{
			g_pTextureTutorial[nCntBlock]->Release();
			g_pTextureTutorial[nCntBlock] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffTutorial != NULL)
	{
		g_pVtxbuffTutorial->Release();
		g_pVtxbuffTutorial = NULL;
	}
}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̍X�V�����@�@ �@�b
//��====================================��
void UpdateTutorial(void)
{
	//��ʐ��ځi���U���g1 �� �^�C�g���j

	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{// ����L�[ [ ENTER�L�[ ] �������ꂽ

		if (nType < 4)
		{
			nType += 1;
		}
		else if (nType == 4)
		{
			//���[�h�̐ݒ�
			SetFade(MODE_GAME);
		}
	}
	else if (GetKeyboardTrigger(DIK_A) == true && GetFade() == FADE_NONE)
	{// ����L�[ [ ENTER�L�[ ] �������ꂽ

		if (nType >= 1 && nType < 4)
		{
			nType -= 1;
		}
		else if (nType == 4)
		{
			nType -= 1;
		}
	}
	else if (GetKeyboardTrigger(DIK_D) == true && GetFade() == FADE_NONE)
	{// ����L�[ [ ENTER�L�[ ] �������ꂽ

		if (nType >= 0 && nType < 4)
		{
			nType += 1;
		}
		else if (nType == 4)
		{
			//���[�h�̐ݒ�
			SetFade(MODE_GAME);
		}
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_START && GetFade() == FADE_NONE)
	{
		if (nType < 4)
		{
			nType += 1;
		}
		else if (nType == 4)
		{
			//���[�h�̐ݒ�
			SetFade(MODE_GAME);
		}
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_A && GetFade() == FADE_NONE)
	{
		if (nType < 4)
		{
			nType += 1;
		}
		else if (nType == 4)
		{
			//���[�h�̐ݒ�
			SetFade(MODE_GAME);
		}
	}

	else if (GetFade() == FADE_NONE && g_nCntTime5 == SWITCH_TIME * 3)
	{//���U���g��ʂɗ��Ă���10�b��������^�C�g����ʂɐ؂�ւ��

		if (nType < 4)
		{
			nType += 1;
			g_nCntTime5 = 0;
		}
		else if (nType == 4)
		{
			//���[�h�̐ݒ�
			SetFade(MODE_GAME);
		}
	}
	else if (GetFade() == FADE_NONE)
	{
		g_nCntTime5++;		//�t�F�[�h�� FADE_NONE �̏�ԂɂȂ�����1�t���[�����J�E���g����
	}

}
//��====================================��
//�b�@�@�@ ���U���g��ʂ̕`�揈���@�@ �@�b
//��====================================��
void DrawTutorial1(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffTutorial, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetTexture(0, g_pTextureTutorial[nType]);
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�|���S���̕`��@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}