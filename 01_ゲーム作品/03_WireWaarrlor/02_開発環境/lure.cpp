//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@ ���A�[�̏����@�@ �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "lure.h"
#include "block.h"
#include "camera.h"
#include "player.h"
#include "rope.h"
//****************************************
// �O���[�o���ϐ�
//****************************************

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffLure = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureLure = NULL;			//�e�N�X�`���ւ̃|�C���^

Lure g_Lure;											//�v���C���[�̏��

//****************************************
// ���A�[�̏���������
//****************************************
void InitLure(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�Ίp���̒������Z�o����(p��*p��+p����*p����);
	g_Lure.Length = sqrtf(SIZE_LURE_WIDTH * SIZE_LURE_WIDTH + SIZE_LURE_HEIGHT * SIZE_LURE_HEIGHT);

	//�Ίp���̊p�x���Z�o����(p��,p����)
	g_Lure.Angle = atan2f(SIZE_LURE_WIDTH, SIZE_LURE_HEIGHT);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Hook.png",
		&g_pTextureLure);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	g_Lure.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);							//���݂̈ʒu
	g_Lure.posOld = D3DXVECTOR3(0.0f,0.0f,0.0f);						//�O��̈ʒu
	g_Lure.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�ړ���
	g_Lure.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//����

	g_Lure.nCntReturn = 0;												//�߂鎞��
	g_Lure.nLife = 0;													//����

	g_Lure.bUse	 = false;												//�g�p����Ă��邩�ǂ���
	g_Lure.bStab = false;												//�ǂɓ����������ǂ���
	g_Lure.bRope = false;
	g_Lure.bWireA = false;
	g_Lure.bReturn = false;
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffLure,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffLure->Lock(0, 0, (void **)&pVtx, 0);
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��	

	pVtx[0].pos.x = g_Lure.pos.x - SIZE_LURE_WIDTH;
	pVtx[0].pos.y = g_Lure.pos.y - SIZE_LURE_HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Lure.pos.x + SIZE_LURE_WIDTH;
	pVtx[1].pos.y = g_Lure.pos.y - SIZE_LURE_HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Lure.pos.x - SIZE_LURE_WIDTH;
	pVtx[2].pos.y = g_Lure.pos.y + SIZE_LURE_HEIGHT;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Lure.pos.x + SIZE_LURE_WIDTH;
	pVtx[3].pos.y = g_Lure.pos.y + SIZE_LURE_HEIGHT;
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
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffLure->Unlock();
}
//****************************************
// ���A�[�̏I������
//****************************************
void UninitLure(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureLure != NULL)
	{
		g_pTextureLure->Release();
		g_pTextureLure = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffLure != NULL)
	{
		g_pVtxbuffLure->Release();
		g_pVtxbuffLure = NULL;
	}
}
//****************************************
// ���A�[�̍X�V����
//****************************************
void UpdateLure(void)
{
	Camera *pCamera = GetCamera();
	Player *pPlayer = Getplayer();
	Rope   *pRope   = GetRope();

		if (g_Lure.bUse == true)
		{
			//�ݒ�p�|�C���^
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
			g_pVtxbuffLure->Lock(0, 0, (void **)&pVtx, 0);

			//�v���C���[�ƃt�b�N�̋����𒲂ׂ�
			pPlayer->lengthFixed = sqrtf(pow(fabs(g_Lure.pos.x - pPlayer->posOld.x), 2)
				+ pow(fabs(g_Lure.pos.y - pPlayer->posOld.y), 2));

			g_Lure.posOld = g_Lure.pos;		//�O��̈ʒu��ۑ�

			//�e�̈ʒu�X�V
			g_Lure.pos += g_Lure.move;

			//�v���C���[�𒆐S�ɉ�ʂ𓮂���

			D3DXVECTOR3 drawPos = g_Lure.pos;
			CameraPosition(&drawPos);

			/*pVtx[0].pos.x = drawPos.x - SIZE_LURE_WIDTH;
			pVtx[1].pos.x = drawPos.x + SIZE_LURE_WIDTH;
			pVtx[2].pos.x = drawPos.x - SIZE_LURE_WIDTH;
			pVtx[3].pos.x = drawPos.x + SIZE_LURE_WIDTH;
			pVtx[0].pos.y = drawPos.y - SIZE_LURE_HEIGHT;
			pVtx[1].pos.y = drawPos.y - SIZE_LURE_HEIGHT;
			pVtx[2].pos.y = drawPos.y + SIZE_LURE_HEIGHT;
			pVtx[3].pos.y = drawPos.y + SIZE_LURE_HEIGHT;

			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.z = 0.0f;*/

			pVtx[0].pos.x = drawPos.x + sinf(g_Lure.rot.z + (-D3DX_PI + g_Lure.Angle)) * g_Lure.Length;
			pVtx[0].pos.y = drawPos.y + cosf(g_Lure.rot.z + (-D3DX_PI + g_Lure.Angle)) * g_Lure.Length;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = drawPos.x + sinf(g_Lure.rot.z + (D3DX_PI - g_Lure.Angle)) * g_Lure.Length;
			pVtx[1].pos.y = drawPos.y + cosf(g_Lure.rot.z +	(D3DX_PI - g_Lure.Angle)) * g_Lure.Length;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = drawPos.x + sinf(g_Lure.rot.z + (0 - g_Lure.Angle)) * g_Lure.Length;
			pVtx[2].pos.y = drawPos.y + cosf(g_Lure.rot.z + (0 - g_Lure.Angle)) * g_Lure.Length;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = drawPos.x + sinf(g_Lure.rot.z + (0 + g_Lure.Angle)) * g_Lure.Length;
			pVtx[3].pos.y = drawPos.y + cosf(g_Lure.rot.z + (0 + g_Lure.Angle)) * g_Lure.Length;
			pVtx[3].pos.z = 0.0f;

			if (g_Lure.bStab == false)
			{
				//���̌��E�n��ݒ�
				if (pPlayer->lengthFixed >= MAX_STRING)
				{
					pPlayer->lengthFixed = MAX_STRING;
					g_Lure.nLife = 0;
				}

				//�����̃J�E���g�_�E��
				g_Lure.nLife--;
				D3DXVECTOR3 movevec;

				if (g_Lure.nLife <= 0)
				{
					/*D3DXVECTOR3 drawPos1 = pPlayer->Draepos;
					CameraPosition(&drawPos1);*/

					//g_Lure.nCntReturn++;
					//g_Lure.pos = (g_Lure.pos * (1.0f - (float)(g_Lure.nCntReturn / (float)50)) + ((Getplayer()->pos) *(float)(g_Lure.nCntReturn / (float)50)));//�J�E���g�̑O��(float)������

					//if (pPlayer->pos.x >= g_Lure.pos.x - SIZE_LURE_WIDTH * 2 &&
					//	pPlayer->pos.x <= g_Lure.pos.x + SIZE_LURE_WIDTH * 2 &&
					//	pPlayer->pos.y >= g_Lure.pos.y - SIZE_LURE_HEIGHT * 2 &&
					//	pPlayer->pos.y <= g_Lure.pos.y + SIZE_LURE_HEIGHT * 2)
					//{
					//	g_Lure.bUse = false;
					//	pRope->bUse = false;
					//	g_Lure.nCntReturn = 0;
					//}
					if (g_Lure.bReturn == false)
					{
						g_Lure.bReturn = true;
					}
				}
			}

			if (g_Lure.bReturn == false)
			{
				//�u���b�N�Ƃ̓����蔻��
				if (CollisionBlockLure(&g_Lure.pos, &g_Lure.posOld, &g_Lure.move) == true)
				{
					g_Lure.bStab = true;
					g_Lure.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
			//���_�o�b�t�@�̃A�����b�N
			g_pVtxbuffLure->Unlock();
		}
}
//****************************************
// ���A�[�̕`�揈��
//****************************************
void DrawLure(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffLure, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_Lure.bUse == true)
	{
		pDevice->SetTexture(0, g_pTextureLure);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		//���_���\���̂̃T�C�Y
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//****************************************
// ���A�[�̐ݒ菈��
//****************************************
void SetLure(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	Rope *pRope = GetRope();
	if (g_Lure.bUse == false)
	{
		g_Lure.pos = pos;
		g_Lure.move = move;
		g_Lure.rot = rot;
		g_Lure.nLife = 30;
		g_Lure.bUse = true;
		g_Lure.bRope = false;
		g_Lure.bWireA = false;
		pRope->bUse = true;
	}
}
//****************************************
// ���A�[�̏��̎擾
//****************************************
Lure *GetLure(void)
{
	return &g_Lure;
}
