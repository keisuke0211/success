//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�ǂ̏���          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "game.h"
#include "wall.h"
#include "fade.h"
#include "Player_model.h"
#include "bullet.h"
#include "particle.h"
#include "camera.h"

//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffWall = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureWall[WALL_LABEL_MAX] = {};			//�e�N�X�`���ւ̃|�C���^
Wall g_Wall[MAX_WALL];
BreakWall g_BreakWall;
float g_GroundMoveX;//�n�ʂ����ɓ�����
float g_GroundMoveY;//�n�ʂ��c�ɓ�����
//****************************************
//�e�N�X�`���t�@�C����
//****************************************
const char *c_apFllenameBlock[WALL_LABEL_MAX] =
{
	"data/TEXTURE/wall2.png",
	"data/TEXTURE/wall1.png",
	"data/TEXTURE/Transparent.png",//stone brick  Transparent
};
//****************************************
// ����������
//****************************************
void InitWall(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (int nCntTexture = 0; nCntTexture < WALL_LABEL_MAX; nCntTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFllenameBlock[nCntTexture],
			&g_pTextureWall[nCntTexture]);
	}

	g_BreakWall.Current = 0;
	g_BreakWall.Pull = 0;
	g_BreakWall.Total = 0;
	g_BreakWall.Current_F = 0.0f;
	g_BreakWall.Break = 0;

	//�ǃf�[�^�̓ǂݍ��߁��ݒ�
	LoadWall();

	//g_BreakWall.Current_F = g_BreakWall.Current / g_BreakWall.Total;
	g_BreakWall.Current_F = (float)g_BreakWall.Break / g_BreakWall.Total;

	g_BreakWall.Pull = (float)g_BreakWall.Total - (g_BreakWall.Total * 0.8);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].nCype == 0)
		{
			g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		if (g_Wall[nCntWall].nCype == 1)
		{
			g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 3.1425f, 0.0f);
		}
		if (g_Wall[nCntWall].nCype == 2)
		{
			g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
		}
		if (g_Wall[nCntWall].nCype == 3)
		{
			g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 4.7125f, 0.0f);
		}
		if (g_Wall[nCntWall].nType == 0 || g_Wall[nCntWall].nType == 2)
		{
			g_Wall[nCntWall].nLife = 100;
		}
		else if(g_Wall[nCntWall].nType == 1)
		{
			g_Wall[nCntWall].nLife = 1;
		}

		//�e�N�X�`���̕��������v�Z
		g_Wall[nCntWall].nSplitX = (int)g_Wall[nCntWall].fWidth / 50;
		g_Wall[nCntWall].nSplitY = (int)g_Wall[nCntWall].fHight / 50;
		g_Wall[nCntWall].nCntTime = 0;
		g_Wall[nCntWall].bUse = true;

		if (g_Wall[nCntWall].nType == 2)
		{
			g_Wall[nCntWall].bDraw = false;
		}
		else
		{
			g_Wall[nCntWall].bDraw = true;
		}
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffWall,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffWall->Lock(0, 0, (void **)&pVtx, 0);


	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pVtx += 4)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_Wall[nCntWall].fWidth, +g_Wall[nCntWall].fHight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+g_Wall[nCntWall].fWidth, +g_Wall[nCntWall].fHight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_Wall[nCntWall].fWidth, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+g_Wall[nCntWall].fWidth, 0.0f, 0.0f);


		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̂̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + g_Wall[nCntWall].nSplitX, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f + g_Wall[nCntWall].nSplitY);
		pVtx[3].tex = D3DXVECTOR2(0.0f + g_Wall[nCntWall].nSplitX, 0.0f + g_Wall[nCntWall].nSplitY);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffWall->Unlock();

	
}
//****************************************
// �I������
//****************************************
void UninitWall(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (int nCntBlock = 0; nCntBlock < WALL_LABEL_MAX; nCntBlock++)
	{

		if (g_pTextureWall[nCntBlock] != NULL)
		{
			g_pTextureWall[nCntBlock]->Release();
			g_pTextureWall[nCntBlock] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffWall != NULL)
	{
		g_pVtxbuffWall->Release();
		g_pVtxbuffWall = NULL;
	}
}
//****************************************
// �X�V����
//****************************************
void UpdateWall(void)
{

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffWall->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++,pVtx += 4)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			/*g_GroundMoveX += 1.0f;
			g_GroundMoveY += 1.0f;*/

			pVtx[0].tex.x = g_GroundMoveX;
			pVtx[1].tex.x = g_GroundMoveX + g_Wall[nCntWall].nSplitX;
			pVtx[2].tex.x = g_GroundMoveX;
			pVtx[3].tex.x = g_GroundMoveX + g_Wall[nCntWall].nSplitX;

			pVtx[0].tex.y = g_GroundMoveY;
			pVtx[1].tex.y = g_GroundMoveY;
			pVtx[2].tex.y = g_GroundMoveY + g_Wall[nCntWall].nSplitY;
			pVtx[3].tex.y = g_GroundMoveY + g_Wall[nCntWall].nSplitY;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffWall->Unlock();
}
//****************************************
// �`�揈��
//****************************************
void DrawWall(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bDraw == true && g_Wall[nCntWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);

			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);

			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxbuffWall, 0, sizeof(VERTEX_3D));

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b���_�t�H�[�}�b�g�̐ݒ�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�e�N�X�`���̐ݒ�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pDevice->SetTexture(0, g_pTextureWall[g_Wall[nCntWall].nType]);

			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�|���S���̕`��@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			//���_���\���̂̃T�C�Y
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}
	}
}
//****************************************
// �ǂݍ��ݏ���
//****************************************
void LoadWall(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int row = 0;//�s���𐔂���ϐ�

	char aData[150];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data/csv/WallData.csv", "r");

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
		case 1:		g_Wall[row].nCype		= atoi(aData);			break;	//�P��ځF�v�Z���
		case 2:		g_Wall[row].nType		= atoi(aData);			break;	//�@��ځF�摜���
		case 3:		g_Wall[row].pos.x		= (float)(atoi(aData));	break;	//�@��ځFX���W
		case 4:		g_Wall[row].pos.y		= (float)(atoi(aData));	break;	//�@��ځFY���W
		case 5:		g_Wall[row].pos.z		= (float)(atoi(aData));	break;	//�@��ځFZ���W
		case 6:		g_Wall[row].fHight		= (float)(atoi(aData));	break;	//�@��ځF����
		case 7:		g_Wall[row].fWidth		= (float)(atoi(aData));	break;	//�@��ځF����
		}
		//�o�b�t�@��������
		memset(aData, 0, sizeof(aData));

		//�񐔂𑫂�
		column++;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			if (g_Wall[row].nType == 1)
			{
				g_BreakWall.Current++;
				g_BreakWall.Total++;
			}
			column = 1;
			row++;
		}
	}
	//�t�@�C�������
	fclose(pFile);
}
//****************************************
// �����蔻�菈��
//****************************************

//�v���C���[
void CollisionWallPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	//�����̌�������(���s)t
	{
		////�ݒ�p�|�C���^
		//VERTEX_3D *pVtx;

		////���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		//g_pVtxbuffWall->Lock(0, 0, (void **)&pVtx, 0);

		//for (int nCntWall1 = 0; nCntWall1 < MAX_WALL;nCntWall1++,pVtx += 4)
		//{
		//	//���E����ݒ�
		//	g_Wall[nCntWall1].vecLine = pVtx[1].pos - pVtx[0].pos;

		//	g_Wall[nCntWall1].vecToPos = *pPos - g_Wall[nCntWall1].pos;

		//	g_Wall[nCntWall1].fRate = (g_Wall[nCntWall1].vecLine.z * g_Wall[nCntWall1].vecToPos.x) - (g_Wall[nCntWall1].vecLine.x * g_Wall[nCntWall1].vecToPos.z);

		//	if (g_Wall[nCntWall1].fRate <= 0)
		//	{
		//		GetPlayer()->pos = GetPlayer()->posOld;
		//		Getcamara()->posV = Getcamara()->posOldV;
		//		Getcamara()->posR = Getcamara()->posOldR;
		//	}
		//}
		////���_�o�b�t�@�̃A�����b�N
		//g_pVtxbuffWall->Unlock();
	}

	{
		for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
		{
			if (g_Wall[nCntWall].bUse == true)
			{
				if (pPos->x >= g_Wall[nCntWall].pos.x - (g_Wall[nCntWall].fWidth + SIZE_WIDTH) &&
					pPos->x <= g_Wall[nCntWall].pos.x + (g_Wall[nCntWall].fWidth + SIZE_WIDTH) &&
					pPos->y >= g_Wall[nCntWall].pos.y - (g_Wall[nCntWall].fHight + SIZE_HEIGHT) &&
					pPos->y <= g_Wall[nCntWall].pos.y + (g_Wall[nCntWall].fHight + SIZE_HEIGHT) &&
					pPos->z >= g_Wall[nCntWall].pos.z - (g_Wall[nCntWall].fWidth + SIZE_WIDTH) &&
					pPos->z <= g_Wall[nCntWall].pos.z + (g_Wall[nCntWall].fWidth + SIZE_WIDTH))
				{
					if (g_Wall[nCntWall].nType == 2)
					{
						
					}
					else if (g_Wall[nCntWall].nCype == 0 || g_Wall[nCntWall].nCype == 1)
					{
						if (g_Wall[nCntWall].pos.y + g_Wall[nCntWall].fHight >= pPosOld->y + SIZE_HEIGHT &&
							g_Wall[nCntWall].pos.y - g_Wall[nCntWall].fHight <= pPosOld->y - SIZE_HEIGHT &&
							g_Wall[nCntWall].pos.z - 2 >= pPosOld->z + SIZE_WIDTH &&
							g_Wall[nCntWall].pos.z - 2 <= pPos->z + SIZE_WIDTH)
						{
							pPos->z = g_Wall[nCntWall].pos.z - (2 + SIZE_WIDTH);
						}
						else if (g_Wall[nCntWall].pos.y + g_Wall[nCntWall].fHight >= pPosOld->y + SIZE_HEIGHT &&
							g_Wall[nCntWall].pos.y - g_Wall[nCntWall].fHight <= pPosOld->y - SIZE_HEIGHT &&
							g_Wall[nCntWall].pos.z + 2 <= pPosOld->z - SIZE_WIDTH &&
							g_Wall[nCntWall].pos.z + 2 >= pPos->z - SIZE_WIDTH)
						{
							pPos->z = g_Wall[nCntWall].pos.z + (2 + SIZE_WIDTH);
						}
					}
					else if (g_Wall[nCntWall].nCype == 2 || g_Wall[nCntWall].nCype == 3)
					{
						if (g_Wall[nCntWall].pos.y + g_Wall[nCntWall].fHight >= pPosOld->y + SIZE_HEIGHT &&
							g_Wall[nCntWall].pos.y - g_Wall[nCntWall].fHight <= pPosOld->y - SIZE_HEIGHT &&
							g_Wall[nCntWall].pos.x - 2 >= pPosOld->x + SIZE_WIDTH &&
							g_Wall[nCntWall].pos.x - 2 <= pPos->x + SIZE_WIDTH)
						{
							pPos->x = g_Wall[nCntWall].pos.x - (2 + SIZE_WIDTH);
						}
						else if (g_Wall[nCntWall].pos.y + g_Wall[nCntWall].fHight >= pPosOld->y + SIZE_HEIGHT &&
							g_Wall[nCntWall].pos.y - g_Wall[nCntWall].fHight <= pPosOld->y - SIZE_HEIGHT &&
							g_Wall[nCntWall].pos.x + 2 <= pPosOld->x - SIZE_WIDTH &&
							g_Wall[nCntWall].pos.x + 2 >= pPos->x - SIZE_WIDTH)
						{
							pPos->x = g_Wall[nCntWall].pos.x + (2 + SIZE_WIDTH);
						}
					}
				}
			}
		}
	}
}
//****************************************
// �f�[�^�̏���
//****************************************
Wall *GetWall(void)
{
	return &g_Wall[0];
}
BreakWall *GetBreakWall(void)
{
	return &g_BreakWall;
}