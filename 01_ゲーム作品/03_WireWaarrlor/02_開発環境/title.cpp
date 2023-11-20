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
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitle = NULL;		//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_MAX] = {}; //�e�N�X�`��(4����)�ւ̃|�C���^
D3DXCOLOR g_colorTitle;								//�|���S��(�t�F�[�h)�̐F

int g_nCnTFlash;									 //�_�Ŏ���
bool bFlash;										 //�_�Ő؂�ւ�
TITLE g_Title[TITLE_MAX];							 //�^�C�g���̏��
float g_aTexV1[TITLE_MAX];								 //�e�N�X�`�����W�̊J�n�ʒu(V�l)
//****************************************
//�e�N�X�`���t�@�C����
//****************************************
const char *c_apFllenameTitle[TITLE_MAX] =
{
	"data/TEXTURE/PixelSky_layer01.png",
	"data/TEXTURE/PixelSky_layer04.png",
	"data/TEXTURE/PixelSky_layer05.png",
	"data/TEXTURE/TitleBg000.png",
	"data/TEXTURE/TitleBg001.png",
	"data/TEXTURE/TitleBg002.png",
};
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
	for (int nCntTexture = 0; nCntTexture < TITLE_MAX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFllenameTitle[nCntTexture],
			&g_pTextureTitle[nCntTexture]);
	}

	//�e�N�X�`�����W�̊J�n�ʒu(V�l)�̏�����
	for (int nCntBG = 0; nCntBG < TITLE_MAX; nCntBG++)
	{
		g_aTexV1[nCntBG] = 0.0f;
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	g_nCnTFlash = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_MAX,
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
	for (nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++, pVtx += 4)
	{
		g_colorTitle = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(�s����)�ɂ��Ă���
		g_Title[nCntTitle].bUse = true;
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		if (nCntTitle == TITLE_BG001 || nCntTitle == TITLE_BG002)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 450.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 450.0f, 0.0f);
		}
		else
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
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
	g_Title[TITLE_TEXT002].state = TITLESTATE_NORMAL;
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM000); //���A��BJM
	//g_Title[1].bUse = false;
	//g_Title[2].bUse = false;


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
	for (nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
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


	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntBG = 0; nCntBG < TITLE_MAX; nCntBG++, pVtx += 4)
	{
		//�e�N�X�`�����W�̊J�n�ʒu(V�l)�̍X�V
		g_aTexV1[TITLE_BG001] += 0.0002f;
		g_aTexV1[TITLE_BG002] += 0.0001f;

		//�e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(g_aTexV1[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aTexV1[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aTexV1[nCntBG], 0.99f);
		pVtx[3].tex = D3DXVECTOR2(g_aTexV1[nCntBG] + 1.0f, 0.99f);
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTitle->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{// ����L�[ [ ENTER�L�[ ] �������ꂽ

		//pPlayer->bBph = false;											//�R���g���[���̐U���I�t
		//PlaySound(SOUND_LABEL_SE_START);									//���Đ��������T�E���h���w��
		bFlash = true;
		//���[�h�̐ݒ�

		//SetFade(MODE_TUTORIAL);
		SetFade(MODE_TUTORIAL);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_START && GetFade() == FADE_NONE)
	{
		//pPlayer->bBph = true;												//�R���g���[���̐U���I��
		//PlaySound(SOUND_LABEL_SE_START);									//���Đ��������T�E���h���w��
		bFlash = true;
		//���[�h�̐ݒ�
		SetFade(MODE_TUTORIAL);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_A&& GetFade() == FADE_NONE)
	{
		//pPlayer->bBph = true;												//�R���g���[���̐U���I��
		//PlaySound(SOUND_LABEL_SE_START);									//���Đ��������T�E���h���w��
		bFlash = true;
		//���[�h�̐ݒ�
		SetFade(MODE_TUTORIAL);
	}
	//�_��
	g_nCnTFlash++;

	if (g_nCnTFlash >= 26 && bFlash == false)
	{//�_�Ő؂�ւ����ԂɂȂ���
		g_Title[TITLE_TEXT002].bUse = g_Title[TITLE_TEXT002].bUse ? false : true;
		g_nCnTFlash = 0;
	}
	else if (g_nCnTFlash >= 6 && bFlash == true)
	{
		g_Title[TITLE_TEXT002].bUse = g_Title[TITLE_TEXT002].bUse ? false : true;
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
	
	for (nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		if (g_Title[nCntTitle].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�|���S���̕`��@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4,2);
		}
	}
}