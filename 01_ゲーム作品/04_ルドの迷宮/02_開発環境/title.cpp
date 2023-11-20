//��======================��
//�b�@�@  �@�@�@�@�@�@�@�@�b
//�b�@�^�C�g����ʂ̏����@�b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include"title.h"
#include "camera.h"
#include "floor.h"
#include "wall.h"
#include "torch.h"
#include "figure_model.h"
#include "enemy_model.h"
#include "torch_model.h"
#include "stone_pillar.h"
#include "jewel.h"
#include "effect.h"
#include "particle.h"
#include"sound.h"
#include "fade.h"
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffTitle = NULL;		//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_MAX] = {}; //�e�N�X�`��(4����)�ւ̃|�C���^
D3DXCOLOR g_colorTitle;								//�|���S��(�t�F�[�h)�̐F

int g_nCnTFlash;									//�_�Ŏ���
bool bFlash;										//�_�Ő؂�ւ�
TITLE g_Title[TITLE_MAX];							//�^�C�g���̏��
float g_aTexV1[TITLE_MAX];							//�e�N�X�`�����W�̊J�n�ʒu(V�l)

float length_x;
float length_y;
//****************************************
//�e�N�X�`���t�@�C����
//****************************************
const char *c_apFllenameTitle[TITLE_MAX] =
{
	"data/TEXTURE/���h�̖��{.png",
	"data/TEXTURE/PressEnter.png",
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

	//�f�[�^�̏�����
	for (nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		if (nCntTitle == 0)
		{

			g_Title[nCntTitle].pos = D3DXVECTOR3(0.0f, 50.0f, 150.0f);
			g_Title[nCntTitle].fHight = 80.0f;
			g_Title[nCntTitle].fWidth = 160.0f;
		}
		else if (nCntTitle == 1)
		{
			g_Title[nCntTitle].pos = D3DXVECTOR3(0.0f, -30.0f, 150.0f);
			g_Title[nCntTitle].fHight = 30.0f;
			g_Title[nCntTitle].fWidth = 120.0f;
		}
		g_Title[nCntTitle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Title[nCntTitle].bUse = true;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	g_nCnTFlash = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * TITLE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffTitle,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffTitle->Lock(0, 0, (void **)&pVtx, 0);

	bFlash = false;
	for (nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++, pVtx += 4)
	{
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].pos = D3DXVECTOR3(-g_Title[nCntTitle].fWidth, +g_Title[nCntTitle].fHight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+g_Title[nCntTitle].fWidth, +g_Title[nCntTitle].fHight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_Title[nCntTitle].fWidth, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+g_Title[nCntTitle].fWidth, 0.0f, 0.0f);
		
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);

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

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.01f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.01f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	g_Title[TITLE_BG001].state = TITLESTATE_NORMAL;
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM000); //���{BJM

	//��
	InitFloor();
	//��
	InitWall();
	//�G�l�~�[
	InitEnemyeModel();
	//���f���E�u��
	InitFigureModel();
	//�����E���f��
	InitTorch_Model();
	//�Β�
	InitPillar_Model();
	//����
	InitTorch();
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

	//��
	UninitFloor();
	//��
	UninitWall();
	//����
	UninitTorch();
	//�G�l�~�[
	UninitEnemyeModel();
	//���f���E�u��
	UninitFigureModel();
	//�����E���f��
	UninitTorch_Model();
	//�Β�
	UninitPillar_Model();
}
//��====================================��
//�b�@�@�@ �^�C�g����ʂ̍X�V�����@�@ �@�b
//��====================================��
void UpdateTitle(void)
{	

	XINPUT_STATE *xInput = GetXInputState();

	//�J�n����O�̃J�����̓���
	if (GetFade() == FADE_NONE)
	{
		Getcamara(0)->rot.z += 0.001f;

		Getcamara(0)->posR.x = g_Title[0].pos.x;
		Getcamara(0)->posR.z = g_Title[0].pos.z;

		Getcamara(0)->posV.x = Getcamara(0)->posR.x + sinf(D3DX_PI * (1.0f - Getcamara(0)->rot.z)) * 300;
		Getcamara(0)->posV.z = Getcamara(0)->posR.z + cosf(D3DX_PI * (1.0f - Getcamara(0)->rot.z)) * 300;
	}

	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || xInput->Gamepad.wButtons & XINPUT_GAMEPAD_START ||
			xInput->Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{// ����L�[ [ ENTER�L�[ ] �������ꂽ

			bFlash = true;
			//���[�h�̐ݒ�

			SetFade(MODE_TUTORIAL);
		}
	}
	//�_��
	g_nCnTFlash++;

	if (g_nCnTFlash >= 30 && bFlash == false)
	{//�_�Ő؂�ւ����ԂɂȂ���
		g_Title[TITLE_BG001].bUse = g_Title[TITLE_BG001].bUse ? false : true;
		g_nCnTFlash = 0;
	}
	else if (g_nCnTFlash >= 6 && bFlash == true)
	{
		g_Title[TITLE_BG001].bUse = g_Title[TITLE_BG001].bUse ? false : true;
		g_nCnTFlash = 0;
	}

	//�G�l�~�[
	UpdateEnemyeModel();
	//���f���E�u��
	UpdateFigureModel();
	//�����E���f��
	UpdateTorch_Model();
	//�Β�
	UpdatePillar_Model();
	//����
	UpdatTorch();
	//��
	UpdateFloor();
	//��
	UpdateWall();
}
//��====================================��
//�b�@�@�@ �^�C�g����ʂ̕`�揈���@�@ �@�b
//��====================================��
void DrawTitle(void)
{
	//��
	DrawFloor();
	//��
	DrawWall();
	//����
	DrawTorch();
	//�G�l�~�[
	DrawEnemyeModel();
	//���f���E�u��
	DrawFigureModel();
	//�����E���f��
	DrawTorch_Model();
	//�Β�
	DrawPillar_Model();

	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;					//�r���[�}�g���b�N�X�擾�p

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);//Z�e�X�g�̐ݒ�,��r���@
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);//Z�o�b�t�@�X�V�̗L�������ݒ�,�L��������

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//�A���t�@�e�X�g�̗L�������ݒ�A�L���E�����ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//�A���t�@�e�X�g�̐ݒ�,��r���@
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//�A���t�@�e�X�g�̎Q�ƒl�ݒ�i0�`255�j

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		if (g_Title[nCntTitle].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Title[nCntTitle].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_Title[nCntTitle].mtxWorld, NULL, &mtxView);//�t�s������߂�
			g_Title[nCntTitle].mtxWorld._41 = 0.0f;
			g_Title[nCntTitle].mtxWorld._42 = 0.0f;
			g_Title[nCntTitle].mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Title[nCntTitle].pos.x, g_Title[nCntTitle].pos.y, g_Title[nCntTitle].pos.z);

			D3DXMatrixMultiply(&g_Title[nCntTitle].mtxWorld, &g_Title[nCntTitle].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Title[nCntTitle].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxbuffTitle, 0, sizeof(VERTEX_3D));


			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b���_�t�H�[�}�b�g�̐ݒ�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�e�N�X�`���̐ݒ�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�|���S���̕`��@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}
	
	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//Z�e�X�g�̐ݒ�,��r���@
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);//Z�o�b�t�@�X�V�̗L�������ݒ�,�L��������

	 //�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//�A���t�@�e�X�g�̗L�������ݒ�A�L���E�����ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);//�A���t�@�e�X�g�̐ݒ�,��r���@
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//�A���t�@�e�X�g�̎Q�ƒl�ݒ�i0�`255�j
}