//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@ ���[�v�̏����@�@ �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "lure.h"
#include "rope.h"
#include "camera.h"
#include "player.h"
//****************************************
// �O���[�o���ϐ�
//****************************************

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffRope = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureRope = NULL;			//�e�N�X�`���ւ̃|�C���^

Rope g_Rope;											//�v���C���[�̏��
//****************************************
// ���[�v�̏���������
//****************************************
void InitRope(void)
{
	//�Ίp���̒������Z�o����(p��*p��+p����*p����);
	g_Rope.Length = sqrtf(SIZE_LURE_WIDTH * SIZE_LURE_WIDTH + SIZE_LURE_HEIGHT * SIZE_LURE_HEIGHT);

	//�Ίp���̊p�x���Z�o����(p��,p����)
	g_Rope.Angle = atan2f(SIZE_LURE_WIDTH, SIZE_LURE_HEIGHT);

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Rope.png",
		&g_pTextureRope);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	g_Rope.posA	  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//���݂̈ʒu
	g_Rope.posB	  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//���݂̈ʒu

	g_Rope.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�O��̈ʒu
	g_Rope.rot	  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//����

	g_Rope.bUse = false;												//�g�p����Ă��邩�ǂ���
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffRope,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffRope->Lock(0, 0, (void **)&pVtx, 0);
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��	

	pVtx[0].pos.x = g_Rope.posB.x - SIZE_LURE_WIDTH;
	pVtx[0].pos.y = g_Rope.posB.y - SIZE_LURE_HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Rope.posB.x + SIZE_LURE_WIDTH;
	pVtx[1].pos.y = g_Rope.posB.y - SIZE_LURE_HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Rope.posA.x - SIZE_LURE_WIDTH;
	pVtx[2].pos.y = g_Rope.posA.y + SIZE_LURE_HEIGHT;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Rope.posA.x + SIZE_LURE_WIDTH;
	pVtx[3].pos.y = g_Rope.posA.y + SIZE_LURE_HEIGHT;
	pVtx[3].pos.z = 0.0f;

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
	pVtx[2].tex = D3DXVECTOR2(0.0f, 50.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 50.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffRope->Unlock();
}
//****************************************
// ���[�v�̏I������
//****************************************
void UninitRope(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureRope != NULL)
	{
		g_pTextureRope->Release();
		g_pTextureRope = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffRope != NULL)
	{
		g_pVtxbuffRope->Release();
		g_pVtxbuffRope = NULL;
	}
}
//****************************************
// ���[�v�̍X�V����
//****************************************
void UpdateRope(void)
{
	Camera *pCamera = GetCamera();
	Player *pPlayer = Getplayer();
	Lure   *pLure = GetLure();
	if (g_Rope.bUse == true)
	{
		//�ݒ�p�|�C���^
		VERTEX_2D *pVtx;

		//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		g_pVtxbuffRope->Lock(0, 0, (void **)&pVtx, 0);

		g_Rope.posOld = g_Rope.posA;		//�O��̈ʒu��ۑ�
		g_Rope.posA	  = D3DXVECTOR3(pPlayer->pos.x,pPlayer->pos.y + 10.0f, 0.0f);
		g_Rope.posB   = D3DXVECTOR3(pLure->pos.x,pLure->pos.y, 0.0f);

		//�v���C���[�𒆐S�ɉ�ʂ𓮂���

		D3DXVECTOR3 drawPosA = g_Rope.posA;
		D3DXVECTOR3 drawPosB = g_Rope.posB;

		CameraPosition(&drawPosA);
		CameraPosition(&drawPosB);

		/*pVtx[0].pos.x = drawPosB.x - SIZE_LURE_WIDTH;
		pVtx[1].pos.x = drawPosB.x + SIZE_LURE_WIDTH;
		pVtx[2].pos.x = drawPosA.x - SIZE_LURE_WIDTH;
		pVtx[3].pos.x = drawPosA.x + SIZE_LURE_WIDTH;

		pVtx[0].pos.y = drawPosB.y - SIZE_LURE_HEIGHT;
		pVtx[1].pos.y = drawPosB.y - SIZE_LURE_HEIGHT;
		pVtx[2].pos.y = drawPosA.y + SIZE_LURE_HEIGHT;
		pVtx[3].pos.y = drawPosA.y + SIZE_LURE_HEIGHT;*/

		pVtx[0].pos.x = drawPosB.x + sinf(pLure->rot.z + (-D3DX_PI + g_Rope.Angle)) * g_Rope.Length;
		pVtx[0].pos.y = drawPosB.y + cosf(pLure->rot.z + (-D3DX_PI + g_Rope.Angle)) * g_Rope.Length;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = drawPosB.x + sinf(pLure->rot.z + (D3DX_PI - g_Rope.Angle)) * g_Rope.Length;
		pVtx[1].pos.y = drawPosB.y + cosf(pLure->rot.z + (D3DX_PI - g_Rope.Angle)) * g_Rope.Length;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = drawPosA.x + sinf(pLure->rot.z + (0 - g_Rope.Angle)) * g_Rope.Length;
		pVtx[2].pos.y = drawPosA.y + cosf(pLure->rot.z + (0 - g_Rope.Angle)) * g_Rope.Length;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = drawPosA.x + sinf(pLure->rot.z + (0 + g_Rope.Angle)) * g_Rope.Length;
		pVtx[3].pos.y = drawPosA.y + cosf(pLure->rot.z + (0 + g_Rope.Angle)) * g_Rope.Length;
		pVtx[3].pos.z = 0.0f;

		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.z = 0.0f;

		//���_�o�b�t�@�̃A�����b�N
		g_pVtxbuffRope->Unlock();
	}
}
//****************************************
// ���[�v�̕`�揈��
//****************************************
void DrawRope(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffRope, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_Rope.bUse == true)
	{
		pDevice->SetTexture(0, g_pTextureRope);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		//���_���\���̂̃T�C�Y
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//****************************************
// ���[�v�̏��̎擾
//****************************************
Rope *GetRope(void)
{
	return &g_Rope;
}
