//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�u���b�N�̏���    �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "block.h"
#include "game.h"
#include "player.h"
#include "bg.h"
#include "camera.h"
#include "lure.h"
#include "sound.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DVERTEXBUFFER9  g_pVtxbuffBlosk = NULL;						//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureBlock [BLOCK_LABEL_MAX] = {};			//�e�N�X�`���ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];												//�u���b�N�̏��
float g_GroundMoveX;													//�n�ʂ����ɓ�����
//****************************************
//�e�N�X�`���t�@�C����
//****************************************
const char *c_apFllenameBlock[BLOCK_LABEL_MAX] =
{
	"data/TEXTURE/Rocks02.png",
	"data/TEXTURE/Rocks00.png",
	"data/TEXTURE/Rocks01.png",
	"data/TEXTURE/Dir.png",
	"data/TEXTURE/block001.jpg",
	"data/TEXTURE/block002.jpg",
	"data/TEXTURE/Treasure Chest.png",
	"data/TEXTURE/Checkpoint (Flag Idle)(64x64).png",
	"data/TEXTURE/Checkpoint (Flag Idle)(64x64).png",
};
//****************************************
// �u���b�N�̏���������
//****************************************
void InitBlock(void)
{
	Camera *pCamera = GetCamera();

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (int nCntTexture = 0; nCntTexture < BLOCK_LABEL_MAX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFllenameBlock[nCntTexture],
			&g_pTextureBlock[nCntTexture]);
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBlosk,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBlosk->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pVtx += 4)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0, 0, 0);										//�ʒu
		g_aBlock[nCntBlock].posOld = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0);		//�O��̈ʒu
		g_aBlock[nCntBlock].fWidth = 0;														//��
		g_aBlock[nCntBlock].fHight = 0;														//����
		g_aBlock[nCntBlock].nType = 0;														//���
		g_aBlock[nCntBlock].nSpeed = 0;														//�ړ���
		g_aBlock[nCntBlock].nCounterAnim = 0;												//�`���X�g�̃A�j���[�V�����J�E���g
		g_aBlock[nCntBlock].nPatternAnim = 0;												//�`���X�g�̃A�j���[�V�����J�E���g
		g_aBlock[nCntBlock].nCounterAnim1 = 0;												//���Ԓn�_�̃A�j���[�V�����J�E���g
		g_aBlock[nCntBlock].nPatternAnim1 = 0;												//���Ԓn�_�̃A�j���[�V�����J�E���g
		g_aBlock[nCntBlock].nSplitX = 0;													//�e�N�X�`���̏c�̕�����
		g_aBlock[nCntBlock].nSplitY = 0;													//�e�N�X�`���̉��̕�����
		g_aBlock[nCntBlock].bUse = false;													//�g�p���Ă��邩�ǂ���
		g_aBlock[nCntBlock].bChat = false;													//�󔠂ɂӂꂽ��
		g_aBlock[nCntBlock].bClear = false;													//�N���A������
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��	

		pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
		pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
		pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
		pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
		pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight;
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
		if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_TreasureChest)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
		}
		else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint1)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
		}
		else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint2)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	//�u���b�N�̔z�u
	LoadBlock();

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffBlosk->Unlock();
}
//****************************************
// �u���b�N�̏I������
//****************************************
void UninitBlock(void)
{
	//�T�E���h�̒�~
	StopSound();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (int nCntBlock = 0; nCntBlock < BLOCK_LABEL_MAX; nCntBlock++)
	{

		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffBlosk != NULL)
	{
		g_pVtxbuffBlosk->Release();
		g_pVtxbuffBlosk = NULL;
	}
}
//****************************************
// �u���b�N�̍X�V����
//****************************************
void UpdateBlock(void)
{
	Player *pPlayer = Getplayer();	//�v���C���[�̏��ւ̃|�C���^

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBlosk->Lock(0, 0, (void **)&pVtx, 0);
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��	
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pVtx += 4)
	{
			D3DXVECTOR3 drawPos = g_aBlock[nCntBlock].pos;

			CameraPosition(&drawPos);

			pVtx[0].pos.x = drawPos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[0].pos.y = drawPos.y - g_aBlock[nCntBlock].fHight;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = drawPos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[1].pos.y = drawPos.y - g_aBlock[nCntBlock].fHight;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = drawPos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[2].pos.y = drawPos.y + g_aBlock[nCntBlock].fHight;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = drawPos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[3].pos.y = drawPos.y + g_aBlock[nCntBlock].fHight;
			pVtx[3].pos.z = 0.0f;

			if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_TreasureChest)
			{
				if (g_aBlock[nCntBlock].bChat == true && g_aBlock[nCntBlock].bClear == false)
				{
					g_aBlock[nCntBlock].nCounterAnim++;
					if (g_aBlock[nCntBlock].nCounterAnim % 10 == 0)
					{
						if (g_aBlock[nCntBlock].nPatternAnim >= 0 && g_aBlock[nCntBlock].nPatternAnim <= 6)
						{
							if (g_aBlock[nCntBlock].nPatternAnim == 0)
							{
								PlaySound(SOUND_LABEL_SE_CHEST); //�t�b�N��߂�
							}
							g_aBlock[nCntBlock].nPatternAnim++;
						}
						else if (g_aBlock[nCntBlock].nPatternAnim == 7)
						{
							g_aBlock[nCntBlock].bClear = true;
							SetGameState(GAMESTATE_END1, 1);
						}
					}
				}
				pVtx[0].tex = D3DXVECTOR2(0.0f	+ ((g_aBlock[nCntBlock].nPatternAnim % 4)* 0.25f), 0.0f	+ ((g_aBlock[nCntBlock].nPatternAnim / 4)* 0.5));
				pVtx[1].tex = D3DXVECTOR2(0.25f + ((g_aBlock[nCntBlock].nPatternAnim % 4)* 0.25f), 0.0f	+ ((g_aBlock[nCntBlock].nPatternAnim / 4)* 0.5));
				pVtx[2].tex = D3DXVECTOR2(0.0f	+ ((g_aBlock[nCntBlock].nPatternAnim % 4)* 0.25f), 0.5f	+ ((g_aBlock[nCntBlock].nPatternAnim / 4)* 0.5));
				pVtx[3].tex = D3DXVECTOR2(0.25f + ((g_aBlock[nCntBlock].nPatternAnim % 4)* 0.25f), 0.5f	+ ((g_aBlock[nCntBlock].nPatternAnim / 4)* 0.5));
			}
			else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint1)
			{
				g_aBlock[nCntBlock].nCounterAnim1++;
				if (g_aBlock[nCntBlock].nCounterAnim1 % 10 == 0)
				{
					if (g_aBlock[nCntBlock].nPatternAnim1 >= 0 && g_aBlock[nCntBlock].nPatternAnim1 <= 9)
					{
						g_aBlock[nCntBlock].nPatternAnim1++;
					}
					else if (g_aBlock[nCntBlock].nPatternAnim1 == 10)
					{
						g_aBlock[nCntBlock].nPatternAnim1 = 1;
					}
				}
				pVtx[0].tex = D3DXVECTOR2(0.0f	+ ((g_aBlock[nCntBlock].nPatternAnim1 % 4)* 0.1f), 0.05f);
				pVtx[1].tex = D3DXVECTOR2(0.1f	+ ((g_aBlock[nCntBlock].nPatternAnim1 % 4)* 0.1f), 0.05f);
				pVtx[2].tex = D3DXVECTOR2(0.0f	+ ((g_aBlock[nCntBlock].nPatternAnim1 % 4)* 0.1f), 1.0f	);
				pVtx[3].tex = D3DXVECTOR2(0.1f	+ ((g_aBlock[nCntBlock].nPatternAnim1 % 4)* 0.1f), 1.0f	);
			}
			else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint2)
			{
				g_aBlock[nCntBlock].nCounterAnim1++;
				if (g_aBlock[nCntBlock].nCounterAnim1 % 10 == 0)
				{
					if (g_aBlock[nCntBlock].nPatternAnim1 >= 0 && g_aBlock[nCntBlock].nPatternAnim1 <= 9)
					{
						g_aBlock[nCntBlock].nPatternAnim1++;
					}
					else if (g_aBlock[nCntBlock].nPatternAnim1 == 10)
					{
						g_aBlock[nCntBlock].nPatternAnim1 = 1;
					}
				}
				pVtx[0].tex = D3DXVECTOR2(0.0f + ((g_aBlock[nCntBlock].nPatternAnim1 % 4)* 0.1f), 0.05f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + ((g_aBlock[nCntBlock].nPatternAnim1 % 4)* 0.1f), 0.05f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + ((g_aBlock[nCntBlock].nPatternAnim1 % 4)* 0.1f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + ((g_aBlock[nCntBlock].nPatternAnim1 % 4)* 0.1f), 1.0f);
			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + g_aBlock[nCntBlock].nSplitX, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f + g_aBlock[nCntBlock].nSplitY);
				pVtx[3].tex = D3DXVECTOR2(0.0f + g_aBlock[nCntBlock].nSplitX, 0.0f + g_aBlock[nCntBlock].nSplitY);

				g_GroundMoveX = 1.0f;

				pVtx[0].tex.x = g_GroundMoveX;
				pVtx[1].tex.x = g_GroundMoveX + g_aBlock[nCntBlock].nSplitX;
				pVtx[2].tex.x = g_GroundMoveX;
				pVtx[3].tex.x = g_GroundMoveX + g_aBlock[nCntBlock].nSplitX;

				pVtx[0].tex.y = g_GroundMoveX;
				pVtx[1].tex.y = g_GroundMoveX;
				pVtx[2].tex.y = g_GroundMoveX + g_aBlock[nCntBlock].nSplitY;
				pVtx[3].tex.y = g_GroundMoveX + g_aBlock[nCntBlock].nSplitY;
			}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffBlosk->Unlock();
}
//****************************************
// �u���b�N�̕`�揈��
//****************************************
void DrawBlock(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffBlosk, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�|���S���̕`��@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			//���_���\���̂̃T�C�Y
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}
//****************************************
// �u���b�N�̓ǂݍ���
//****************************************
void LoadBlock(void)
{
	int c = 0;		//1�������m�F����ϐ�
	int column = 1;	//�s���𐔂���ϐ�
	int line = 0;	//�񐔂𐔂���ϐ�

	char aData[150];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data/csv/BlockData.csv", "r");

	//�t�@�C������P�������ǂݍ���
	while (fgetc(pFile) != '\n');

	while (c != EOF)
	{
		//�P�Z�����̕���������
		while (1)
		{
			c = fgetc(pFile);

			//�����Ȃ烋�[�v�𔲂���
			if (c == EOF)
				break;

			//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (c != ',' && c != '\n')
				strcat(aData, (const char*)&c);

			//�J���}�����s�Ȃ烋�[�v������
			else
				break;
		}

		switch (column)
		{
			//atoi�֐��Ő��l�Ƃ��đ��
		case 1:		g_aBlock[line].nType	= atoi(aData);			break;	//�P��ځF���
		case 2:		g_aBlock[line].fWidth	= (float)(atoi(aData));	break;	//  ��ځF��
		case 3:		g_aBlock[line].fHight	= (float)(atoi(aData));	break;	//�@��ځF����
		case 4:		g_aBlock[line].pos.x	= (float)(atoi(aData));	break;	//�@��ځFX���W
		case 5:		g_aBlock[line].pos.y	= (float)(atoi(aData));	break;	//�@��ځFY���W
		case 6:		g_aBlock[line].nSplitX	= atoi(aData);			break;	//�@��ځF�c�̕�����
		case 7:		g_aBlock[line].nSplitY	= atoi(aData);			break;	//�@��ځF�c�̕�����

		}
		//�o�b�t�@��������
		memset(aData, 0, sizeof(aData));
		
		//�񐔂𑫂�
		column++;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			column = 1;
			line++;
		}
		for (int nCntBlock = 0; nCntBlock < line; nCntBlock++)
		{
			//�g�p���Ă��邩�ǂ���
			g_aBlock[nCntBlock].bUse = true;
		}
	}
	//�t�@�C�������
	fclose(pFile);
}
//****************************************
// �u���b�N�Ƃ̓����蔻��(�v���C���[)
//****************************************
bool CollisionBlockPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bLand = false;//���n�������ǂ��� 

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x >= g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH ) &&
				pPos->x <= g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH	) &&
				pPos->y >= g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT) &&
				pPos->y <= g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT))//�n�ʂɂ߂荞��
			{
				if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_TreasureChest || g_aBlock[nCntBlock].nType == BLOCK_LABEL_ROCKS02)
				{
					g_aBlock[nCntBlock].bChat = true;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint1)
				{
					Getplayer()->bCheckpoint = 1;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint2)
				{
					Getplayer()->bCheckpoint = 2;
				}
				else
				{
					if (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight >= pPosOld->y + SIZE_HEIGHT &&
						g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight <= pPos->y + SIZE_HEIGHT)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT);	//�u���b�N�̏�ɗ�������
						pMove->y = 0.0f;																		//�ړ��ʂ��O�ɂ���
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight <= pPosOld->y - SIZE_HEIGHT &&
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight >= pPos->y - SIZE_HEIGHT)
					{
						pPos->y = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT);		//�u���b�N�̏�ɗ�������
						pMove->y = 10.0f;
					}

					else if (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth >= pPosOld->x + SIZE_WIDTH &&
						g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth <= pPos->x + SIZE_WIDTH)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH);		//�u���b�N�̏�ɗ�������
					}
					else if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth <= pPosOld->x - SIZE_WIDTH &&
						g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - SIZE_WIDTH)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH);		//�u���b�N�̏�ɗ�������
					}
				}
			}
		}

	}
	return bLand;
}
//****************************************
// �u���b�N�Ƃ̓����蔻��(���A�[)
//****************************************
bool CollisionBlockLure(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bLand = false;//���n�������ǂ��� 

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x >= g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_LURE_WIDTH*2) &&
				pPos->x <= g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_LURE_WIDTH*2) &&
				pPos->y >= g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_LURE_HEIGHT*2) &&
				pPos->y <= g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_LURE_HEIGHT*2))//�n�ʂɂ߂荞��
			{
				if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_TreasureChest || g_aBlock[nCntBlock].nType == BLOCK_LABEL_ROCKS02)
				{

				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint1)
				{

				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint2)
				{

				}
				else
				{
					if (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight >= pPosOld->y + SIZE_LURE_HEIGHT &&
						g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight <= pPos->y + SIZE_LURE_HEIGHT)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_LURE_HEIGHT);	//�u���b�N�̏�ɗ�������
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight <= pPosOld->y - SIZE_LURE_HEIGHT &&
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight >= pPos->y - SIZE_LURE_HEIGHT)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_LURE_HEIGHT);		//�u���b�N�̏�ɗ�������
					}

					else if (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth >= pPosOld->x + SIZE_LURE_WIDTH &&
						g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth <= pPos->x + SIZE_LURE_WIDTH)
					{
						bLand = true;
						pPos->x = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_LURE_WIDTH);		//�u���b�N�̏�ɗ�������
					}
					else if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth <= pPosOld->x - SIZE_LURE_WIDTH &&
						g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - SIZE_LURE_WIDTH)
					{
						bLand = true;
						pPos->x = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_LURE_WIDTH);		//�u���b�N�̏�ɗ�������
					}
				}
			}
		}

	}
	return bLand;
}

//****************************************
// �u���b�N�Ƃ̓����蔻��(�U��q�p)
//****************************************
bool CollisionBlockPendulumX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bLand = false;//�ǂɓ���������

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x >= g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH) &&
				pPos->x <= g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH) &&
				pPos->y >= g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT) &&
				pPos->y <= g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT))//�n�ʂɂ߂荞��
			{
				if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_TreasureChest || g_aBlock[nCntBlock].nType == BLOCK_LABEL_ROCKS02)
				{
					g_aBlock[nCntBlock].bChat = true;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint1)
				{
					Getplayer()->bCheckpoint = 1;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint2)
				{
					Getplayer()->bCheckpoint = 2;
				}
				else
				{
					if (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth >= pPosOld->x + SIZE_WIDTH &&
						g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth <= pPos->x + SIZE_WIDTH)
					{
						bLand = true;
						pPos->x = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH);		//�u���b�N�̏�ɗ�������
					}
					else if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth <= pPosOld->x - SIZE_WIDTH &&
						g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - SIZE_WIDTH)
					{
						bLand = true;
						pPos->x = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH);		//�u���b�N�̏�ɗ�������
					}
				}
			}
		}

	}
	return bLand;
}
bool CollisionBlockPendulumY(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bLand = false;//�ǂɓ���������

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x >= g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH) &&
				pPos->x <= g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH) &&
				pPos->y >= g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT) &&
				pPos->y <= g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT))//�n�ʂɂ߂荞��
			{
				if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_TreasureChest || g_aBlock[nCntBlock].nType == BLOCK_LABEL_ROCKS02)
				{
					g_aBlock[nCntBlock].bChat = true;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint1)
				{
					Getplayer()->bCheckpoint = 1;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint2)
				{
					Getplayer()->bCheckpoint = 2;
				}
				else
				{
					if (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight >= pPosOld->y + SIZE_HEIGHT &&
						g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight <= pPos->y + SIZE_HEIGHT)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT);	//�u���b�N�̏�ɗ�������
						pMove->y = 0.0f;																		//�ړ��ʂ��O�ɂ���
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight <= pPosOld->y - SIZE_HEIGHT &&
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight >= pPos->y - SIZE_HEIGHT)
					{
						pPos->y = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT);		//�u���b�N�̏�ɗ�������
						pMove->y = 10.0f;
					}
				}
			}
		}

	}
	return bLand;
}

//****************************************
// �u���b�N�Ƃ̓����蔻��(�������p)
//****************************************
bool CollisionBlockParabola(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bLand = false;//�ǂɓ���������

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x >= g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH) &&
				pPos->x <= g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH) &&
				pPos->y >= g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT) &&
				pPos->y <= g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT))//�n�ʂɂ߂荞��
			{
				if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_TreasureChest || g_aBlock[nCntBlock].nType == BLOCK_LABEL_ROCKS02)
				{
					g_aBlock[nCntBlock].bChat = true;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint1)
				{
					Getplayer()->bCheckpoint = 1;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint2)
				{
					Getplayer()->bCheckpoint = 2;
				}
				else
				{
					if (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight >= pPosOld->y + SIZE_HEIGHT &&
						g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight <= pPos->y + SIZE_HEIGHT)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT);	//�u���b�N�̏�ɗ�������
						pMove->y = 0.0f;																		//�ړ��ʂ��O�ɂ���
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight <= pPosOld->y - SIZE_HEIGHT &&
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight >= pPos->y - SIZE_HEIGHT)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_HEIGHT);		//�u���b�N�̏�ɗ�������
						pMove->y = 10.0f;
					}

					else if (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth >= pPosOld->x + SIZE_WIDTH &&
						g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth <= pPos->x + SIZE_WIDTH)
					{
						bLand = true;
						pPos->x = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH);		//�u���b�N�̏�ɗ�������
					}
					else if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth <= pPosOld->x - SIZE_WIDTH &&
						g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - SIZE_WIDTH)
					{
						bLand = true;
						pPos->x = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_WIDTH);		//�u���b�N�̏�ɗ�������
					}
				}
			}
		}

	}
	return bLand;
}

//****************************************
// �u���b�N�Ƃ̓����蔻��(�����ړ��p)
//****************************************
bool CollisionBlockAutoLure(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bLand = false;//�ǂɓ���������

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x >= g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_LURE_WIDTH * 2) &&
				pPos->x <= g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_LURE_WIDTH * 2) &&
				pPos->y >= g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_LURE_HEIGHT * 2) &&
				pPos->y <= g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_LURE_HEIGHT * 2))//�n�ʂɂ߂荞��
			{
				if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_TreasureChest || g_aBlock[nCntBlock].nType == BLOCK_LABEL_ROCKS02)
				{
					g_aBlock[nCntBlock].bChat = true;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint1)
				{
					Getplayer()->bCheckpoint = 1;
				}
				else if (g_aBlock[nCntBlock].nType == BLOCK_LABEL_Checkpoint2)
				{
					Getplayer()->bCheckpoint = 2;
				}
				else
				{
					if (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight >= pPosOld->y + SIZE_LURE_HEIGHT * 2 &&
						g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHight <= pPos->y + SIZE_LURE_HEIGHT * 2)
					{
						pPos->y = g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHight + SIZE_LURE_HEIGHT * 2);	//�u���b�N�̏�ɗ�������
						pMove->y = 0.0f;																		//�ړ��ʂ��O�ɂ���
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight <= pPosOld->y - SIZE_LURE_HEIGHT * 2 &&
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHight >= pPos->y - SIZE_LURE_HEIGHT * 2)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHight + SIZE_LURE_HEIGHT * 2);		//�u���b�N�̏�ɗ�������
						pMove->y = 10.0f;
					}

					else if (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth >= pPosOld->x + SIZE_LURE_WIDTH * 2 &&
						g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth <= pPos->x + SIZE_LURE_WIDTH * 2)
					{
						bLand = true;
						pPos->x = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth + SIZE_LURE_WIDTH * 2);		//�u���b�N�̏�ɗ�������
					}
					else if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth <= pPosOld->x - SIZE_LURE_WIDTH * 2 &&
						g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - SIZE_LURE_WIDTH * 2)
					{
						bLand = true;
						pPos->x = g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth + SIZE_LURE_WIDTH * 2);		//�u���b�N�̏�ɗ�������
					}
				}
			}
		}

	}
	return bLand;
}

//****************************************
// �u���b�N�̏���
//****************************************
Block *GetBlock(void)
{
	return &g_aBlock[0];
}