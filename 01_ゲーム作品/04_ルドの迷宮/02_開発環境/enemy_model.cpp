//****************************************
//
//	���f���i�G�j�̏���
//	Author:��a�c��
//
//****************************************
#include "enemy_model.h"
#include "Player_model.h"
#include "bullet.h"
#include "camera.h"
#include "particle.h"
#include "wall.h"
#include "score.h"
#include "sound.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPD3DXMESH g_pMeshOrnamentEnemyModel[NUM_MODEL] = {};							//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatOrnamentEnemyModel[NUM_MODEL] = {};						//�}�e���A���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureOrnamentEnemyModel[NUM_MODEL][MAX_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
DWORD g_dwNumMatOrnamentEnemyModel[NUM_MODEL] = {};								//�}�e���A���̐�
D3DXMATRIX  g_mtxWoridFigureEnemyModel[NUM_MODEL];								//���[���h�}�g���b�N�X

Enemy g_enemy[NUM_MODEL];
//****************************************
// ���f���̏���������
//****************************************
void InitEnemyeModel(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

	for (int nCntType = 0; nCntType < NUM_MODEL; nCntType++)
	{
		g_enemy[nCntType].pos = D3DXVECTOR3(g_enemy[nCntType].pos.x, g_enemy[nCntType].pos.y, g_enemy[nCntType].pos.z);
		g_enemy[nCntType].posOld = D3DXVECTOR3(g_enemy[nCntType].pos.x, g_enemy[nCntType].pos.y, g_enemy[nCntType].pos.z);
		g_enemy[nCntType].Initpos = D3DXVECTOR3(g_enemy[nCntType].pos.x, g_enemy[nCntType].pos.y, g_enemy[nCntType].pos.z);

		if (g_enemy[nCntType].nType_M == 0)
		{
			g_enemy[nCntType].rot = D3DXVECTOR3(DEFAULT_FLOA,DEFAULT_FLOA,DEFAULT_FLOA);
		}
		else if (g_enemy[nCntType].nType_M == 1)
		{
			g_enemy[nCntType].rot = D3DXVECTOR3(DEFAULT_FLOA,3.24f,DEFAULT_FLOA);
		}
		else if (g_enemy[nCntType].nType_M == 2)
		{
			g_enemy[nCntType].rot = D3DXVECTOR3(DEFAULT_FLOA, 1.57f, DEFAULT_FLOA);
		}
		else if (g_enemy[nCntType].nType_M == 3)
		{
			g_enemy[nCntType].rot = D3DXVECTOR3(DEFAULT_FLOA, -1.57f, DEFAULT_FLOA);
		}

		if (g_enemy[nCntType].nType == 0)
		{
			g_enemy[nCntType].nSpeed = 4;
			g_enemy[nCntType].nLife = 3;
			g_enemy[nCntType].fWidth = 15.0f;
			g_enemy[nCntType].fHight = 15.0f;
			g_enemy[nCntType].nScore = 60;
		}
		else if (g_enemy[nCntType].nType == 1)
		{
			g_enemy[nCntType].nSpeed = 6;
			g_enemy[nCntType].nLife = 2;
			g_enemy[nCntType].fWidth = 15.0f;
			g_enemy[nCntType].fHight = 15.0f;
			g_enemy[nCntType].nScore = 80;
		}
		else if (g_enemy[nCntType].nType == 2)
		{
			g_enemy[nCntType].nSpeed = 6;
			g_enemy[nCntType].nLife = 2;
			g_enemy[nCntType].fWidth = 15.0f;
			g_enemy[nCntType].fHight = 15.0f;
			g_enemy[nCntType].nScore = 80;
		}
		else
		{
			g_enemy[nCntType].nSpeed = 2;
			g_enemy[nCntType].nLife = 10;
			g_enemy[nCntType].fWidth = 50.0f;
			g_enemy[nCntType].fHight = 65.0f;
			g_enemy[nCntType].nScore = 100;
		}

		g_enemy[nCntType].r = 1.0f;
		g_enemy[nCntType].b = 1.0f;
		g_enemy[nCntType].g = 1.0f;
		g_enemy[nCntType].a = 1.0f;

		g_enemy[nCntType].nCntDamage = 0;
		g_enemy[nCntType].nCntSummon = 0;

		g_enemy[nCntType].bUse = true;
		g_enemy[nCntType].bDraw = true;
		g_enemy[nCntType].bReturn = false;
	}
	for (int nCntType = 0; nCntType < NUM_MODEL; nCntType++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(g_enemy[nCntType].aModelPath,/*�ǂݍ��ރt�@�C����*/
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatOrnamentEnemyModel[nCntType],
			NULL,
			&g_dwNumMatOrnamentEnemyModel[nCntType],
			&g_pMeshOrnamentEnemyModel[nCntType]);

		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatOrnamentEnemyModel[nCntType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatOrnamentEnemyModel[nCntType]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

			 //���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureOrnamentEnemyModel[nCntType][nCntMat]);
			}
		}
	}
}
//****************************************
// ���f���̏I������
//****************************************
void UninitEnemyeModel(void)
{
	for (int nCntType = 0; nCntType < NUM_MODEL; nCntType++)
	{
		//���b�V���̔j��
		if (g_pMeshOrnamentEnemyModel[nCntType] != NULL)
		{
			g_pMeshOrnamentEnemyModel[nCntType]->Release();
			g_pMeshOrnamentEnemyModel[nCntType] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatOrnamentEnemyModel[nCntType] != NULL)
		{
			g_pBuffMatOrnamentEnemyModel[nCntType]->Release();
			g_pBuffMatOrnamentEnemyModel[nCntType] = NULL;
		}
	}
}
//****************************************
// ���f���̍X�V����
//****************************************
void UpdateEnemyeModel(void)
{
	for (int nCntModel = 0; nCntModel < NUM_MODEL; nCntModel++)
	{
		if (g_enemy[nCntModel].bUse == true)
		{
			g_enemy[nCntModel].posOld = g_enemy[nCntModel].pos;
			if (g_enemy[nCntModel].bReturn == false)
			{
				if (g_enemy[nCntModel].nType_M == 0)
				{
					g_enemy[nCntModel].move.z = -g_enemy[nCntModel].nSpeed;
				}
				else if (g_enemy[nCntModel].nType_M == 1)
				{
					g_enemy[nCntModel].move.z = g_enemy[nCntModel].nSpeed;
				}
				else if (g_enemy[nCntModel].nType_M == 2)
				{
					g_enemy[nCntModel].move.x = -g_enemy[nCntModel].nSpeed;
				}
				else if (g_enemy[nCntModel].nType_M == 3)
				{
					g_enemy[nCntModel].move.x = g_enemy[nCntModel].nSpeed;
				}
				g_enemy[nCntModel].pos.x += g_enemy[nCntModel].move.x;
				g_enemy[nCntModel].pos.z += g_enemy[nCntModel].move.z;

				CollisionEnemy_Wall(&g_enemy[nCntModel], &g_enemy[nCntModel].pos, &g_enemy[nCntModel].posOld, &g_enemy[nCntModel].move);
			}
			else if (g_enemy[nCntModel].bReturn == true)
			{
				if (g_enemy[nCntModel].nCntSummon <= 0)
				{
					if (g_enemy[nCntModel].nType_M == 0)
					{
						g_enemy[nCntModel].rot.y = ABOVE;
					}
					else if (g_enemy[nCntModel].nType_M == 1)
					{
						g_enemy[nCntModel].rot.y = 3.24f;
					}
					else if (g_enemy[nCntModel].nType_M == 2)
					{
						g_enemy[nCntModel].rot.y = 1.57f;
					}
					else if (g_enemy[nCntModel].nType_M == 3)
					{
						g_enemy[nCntModel].rot.y = -1.57f;
					}

					g_enemy[nCntModel].bReturn = false;
				}
				else if (g_enemy[nCntModel].nCntSummon == (RETURN_COUNT - RETURN_COUNT * 0.9))
				{
					g_enemy[nCntModel].nCntSummon--;
				}
				else if (g_enemy[nCntModel].nCntSummon == RETURN_COUNT)
				{
					g_enemy[nCntModel].nCntSummon--;
				}
				else
				{
					g_enemy[nCntModel].nCntSummon--;
				}
			}

			if (g_enemy[nCntModel].nCntDamage <= 0)
			{
				g_enemy[nCntModel].r = 1.0f;
				g_enemy[nCntModel].b = 1.0f;
				g_enemy[nCntModel].g = 1.0f;
				g_enemy[nCntModel].a = 1.0f;
			}
			else
			{
				g_enemy[nCntModel].nCntDamage -= 1;
			}
		}

	}
}
//****************************************
// ���f���̕`�揈��
//****************************************
void DrawEnemyeModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̏���
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	Enemy *pEnemy = &g_enemy[0];

	for (int nCntModel = 0; nCntModel < NUM_MODEL; nCntModel++, pEnemy++)
	{
		if (g_enemy[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pEnemy->mtxWorld);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pEnemy->rot.y, pEnemy->rot.x, pEnemy->rot.z);

			D3DXMatrixMultiply(&pEnemy->mtxWorld, &pEnemy->mtxWorld, &mtxRot);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pEnemy->pos.x, pEnemy->pos.y, pEnemy->pos.z);

			D3DXMatrixMultiply(&pEnemy->mtxWorld, &pEnemy->mtxWorld, &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pEnemy->mtxWorld);

			//���݂̃}�e���A��������
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^������
			pMat = (D3DXMATERIAL*)g_pBuffMatOrnamentEnemyModel[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatOrnamentEnemyModel[nCntModel]; nCntMat++)
			{
				pMat[nCntMat].MatD3D.Diffuse.r = g_enemy[nCntModel].r;
				pMat[nCntMat].MatD3D.Diffuse.g = g_enemy[nCntModel].g;
				pMat[nCntMat].MatD3D.Diffuse.b = g_enemy[nCntModel].b;
				pMat[nCntMat].MatD3D.Diffuse.a = g_enemy[nCntModel].a;

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureOrnamentEnemyModel[pEnemy->nType][nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_pMeshOrnamentEnemyModel[pEnemy->nType]->DrawSubset(nCntMat);
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}
//****************************************
// ���f���̓ǂݍ��ݏ���
//****************************************
void LoadEnemyModel(void)
{
	FILE *pFile;				// �t�@�C���|�C���^
	Enemy *pEnemy = g_enemy;
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

								// ��ޖ��̏��̃f�[�^�t�@�C�����J��
	pFile = fopen("data\\txt\\EnemyData.txt", "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (strcmp(aDataSearch, "END") == 0) { fclose(pFile); break; }	//�t�@�C�������	
		if (aDataSearch[0] == '#') { continue; }							// �܂�Ԃ�

		if (strcmp(aDataSearch, "TYPE") == 0) {
			// CHR:�G[00] �̎�ޖ��̏��̓ǂݍ��݂��J�n
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); // ����

				if (strcmp(aDataSearch, "TYPE_END") == 0) { pEnemy++; break; }										// �ǂݍ��݂��I��
				else if (strcmp(aDataSearch, "MODEL_PATH") == 0) { fscanf(pFile, "%s", &pEnemy->aModelPath); }		// ���f���̑��΃p�X
				else if (strcmp(aDataSearch, "FIGURE_TYPE") == 0) { fscanf(pFile, "%d", &pEnemy->nType); }			// �G�̎��
				else if(strcmp(aDataSearch, "MOVE_TYPE") == 0) { fscanf(pFile, "%d", &pEnemy->nType_M); }			// �G�̎��
				else if (strcmp(aDataSearch, "POS") == 0) {		// �ʒu
					fscanf(pFile, "%f", &pEnemy->pos.x);	// X
					fscanf(pFile, "%f", &pEnemy->pos.y);	// Y
					fscanf(pFile, "%f", &pEnemy->pos.z);	// Z
				}
				else if (strcmp(aDataSearch, "ROT") == 0) {		// ����
					fscanf(pFile, "%f", &pEnemy->rot.x);	// X
					fscanf(pFile, "%f", &pEnemy->rot.y);	// Y
					fscanf(pFile, "%f", &pEnemy->rot.z);	// Z
				}
			}
		}
	}
}
//****************************************
// �����蔻��
//****************************************

//�@��
void CollisionEnemy_Wall(Enemy *pEnemy, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	Wall *pWall = GetWall();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == true)
		{
			if (pEnemy->pos.x >= pWall->pos.x - (pWall->fWidth + pEnemy->fWidth) &&
				pEnemy->pos.x <= pWall->pos.x + (pWall->fWidth + pEnemy->fWidth) &&
				pEnemy->pos.z >= pWall->pos.z - (pWall->fWidth + pEnemy->fWidth) &&
				pEnemy->pos.z <= pWall->pos.z + (pWall->fWidth + pEnemy->fWidth))
			{
				if (pWall->nType == 2)
				{
					if (pWall->nCype == 0 || pWall->nCype == 1)
					{
						if (pWall->pos.z - DEFAULT_INT >= pEnemy->posOld.z + pEnemy->fWidth &&
							pWall->pos.z - DEFAULT_INT <= pEnemy->pos.z + pEnemy->fWidth)
						{
							pEnemy->pos.z = pWall->pos.z - (DEFAULT_INT + pEnemy->fWidth);
							pEnemy->bReturn = true;
							pEnemy->nCntSummon = RETURN_COUNT;
							pEnemy->nType_M = 0;
						}
						else if (pWall->pos.z + DEFAULT_INT <= pEnemy->posOld.z - pEnemy->fWidth &&
							pWall->pos.z + DEFAULT_INT >= pEnemy->pos.z - pEnemy->fWidth)
						{
							pEnemy->pos.z = pWall->pos.z + (DEFAULT_INT + pEnemy->fWidth);
							pEnemy->bReturn = true;
							pEnemy->nCntSummon = RETURN_COUNT;
							pEnemy->nType_M = 1;
						}
					}
					if (pWall->nCype == 2 || pWall->nCype == 3)
					{
						if (pWall->pos.x - DEFAULT_INT >= pEnemy->posOld.x + pEnemy->fWidth &&
							pWall->pos.x - DEFAULT_INT <= pEnemy->pos.x + pEnemy->fWidth)
						{
							pEnemy->pos.x = pWall->pos.x - (DEFAULT_INT + pEnemy->fWidth);
							pEnemy->bReturn = true;
							pEnemy->nCntSummon = RETURN_COUNT;
							pEnemy->nType_M = 2;
						}
						else if (pWall->pos.x + DEFAULT_INT <= pEnemy->posOld.x - pEnemy->fWidth &&
							pWall->pos.x + DEFAULT_INT >= pEnemy->pos.x - pEnemy->fWidth)
						{
							pEnemy->pos.x = pWall->pos.x + (DEFAULT_INT + pEnemy->fWidth);
							pEnemy->bReturn = true;
							pEnemy->nCntSummon = RETURN_COUNT;
							pEnemy->nType_M = 3;
						}
					}
				}
				else
				{
					if (pWall->nCype == 0 || pWall->nCype == 1)
					{
						if (pWall->pos.z - DECISION >= pEnemy->posOld.z + pEnemy->fWidth &&
							pWall->pos.z - DECISION <= pEnemy->pos.z + pEnemy->fWidth)
						{
							pEnemy->pos.z = pWall->pos.z - (DECISION + pEnemy->fWidth);
							pEnemy->bReturn = true;
							pEnemy->nCntSummon = RETURN_COUNT;
							pEnemy->nType_M = 0;
						}
						else if (pWall->pos.z + DECISION <= pEnemy->posOld.z - pEnemy->fWidth &&
							pWall->pos.z + DECISION >= pEnemy->pos.z - pEnemy->fWidth)
						{
							pEnemy->pos.z = pWall->pos.z + (DECISION + pEnemy->fWidth);
							pEnemy->bReturn = true;
							pEnemy->nCntSummon = RETURN_COUNT;
							pEnemy->nType_M = 1;
						}
					}
					if (pWall->nCype == 2 || pWall->nCype == 3)
					{
						if (pWall->pos.x - DECISION >= pEnemy->posOld.x + pEnemy->fWidth &&
							pWall->pos.x - DECISION <= pEnemy->pos.x + pEnemy->fWidth)
						{
							pEnemy->pos.x = pWall->pos.x - (DECISION + pEnemy->fWidth);
							pEnemy->bReturn = true;
							pEnemy->nCntSummon = RETURN_COUNT;
							pEnemy->nType_M = 2;
						}
						else if (pWall->pos.x + DECISION <= pEnemy->posOld.x - pEnemy->fWidth &&
							pWall->pos.x + DECISION >= pEnemy->pos.x - pEnemy->fWidth)
						{
							pEnemy->pos.x = pWall->pos.x + (DECISION + pEnemy->fWidth);
							pEnemy->bReturn = true;
							pEnemy->nCntSummon = RETURN_COUNT;
							pEnemy->nType_M = 3;
						}
					}
				}
			}
		}
	}

}

// �v���C���[
void CollisionEnemy_Player(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	for (int nCntFigure = 0; nCntFigure < NUM_MODEL; nCntFigure++)
	{
		if (g_enemy[nCntFigure].bDraw == true)
		{
			if (pPos->x >= g_enemy[nCntFigure].pos.x - (g_enemy[nCntFigure].fWidth + SIZE_WIDTH) &&
				pPos->x <= g_enemy[nCntFigure].pos.x + (g_enemy[nCntFigure].fWidth + SIZE_WIDTH) &&
				pPos->z >= g_enemy[nCntFigure].pos.z - (g_enemy[nCntFigure].fHight + SIZE_HEIGHT) &&
				pPos->z <= g_enemy[nCntFigure].pos.z + (g_enemy[nCntFigure].fHight + SIZE_HEIGHT))
			{
				if (g_enemy[nCntFigure].posOld.z - g_enemy[nCntFigure].fHight >= pPosOld->z + SIZE_HEIGHT &&
					g_enemy[nCntFigure].pos.z - g_enemy[nCntFigure].fHight <= pPos->z + SIZE_HEIGHT)
				{
					pPos->z = g_enemy[nCntFigure].pos.z - (g_enemy[nCntFigure].fHight + SIZE_HEIGHT);
				}
				else if (g_enemy[nCntFigure].posOld.z + g_enemy[nCntFigure].fHight <= pPosOld->z - SIZE_HEIGHT &&
					g_enemy[nCntFigure].pos.z + g_enemy[nCntFigure].fHight >= pPos->z - SIZE_HEIGHT)
				{
					pPos->z = g_enemy[nCntFigure].pos.z + (g_enemy[nCntFigure].fHight + SIZE_HEIGHT);
				}

				else if (g_enemy[nCntFigure].posOld.x - g_enemy[nCntFigure].fWidth >= pPosOld->x + SIZE_WIDTH &&
					g_enemy[nCntFigure].pos.x - g_enemy[nCntFigure].fWidth <= pPos->x + SIZE_WIDTH)
				{
					pPos->x = g_enemy[nCntFigure].pos.x - (g_enemy[nCntFigure].fWidth + SIZE_WIDTH);
				}
				else if (g_enemy[nCntFigure].posOld.x + g_enemy[nCntFigure].fWidth <= pPosOld->x - SIZE_WIDTH &&
					g_enemy[nCntFigure].pos.x + g_enemy[nCntFigure].fWidth >= pPos->x - SIZE_WIDTH)
				{
					pPos->x = g_enemy[nCntFigure].pos.x + (g_enemy[nCntFigure].fWidth + SIZE_WIDTH);
				}
			}
		}
	}
}

//****************************************
// HIT����
//****************************************
void HitEnemy(int nCntFigure, int nDamage)
{
	if (g_enemy[nCntFigure].bUse == true)
	{
		g_enemy[nCntFigure].nLife -= nDamage;

		if (g_enemy[nCntFigure].nLife <= 0)//�G�̗̑͂��Ȃ��Ȃ���
		{
			g_enemy[nCntFigure].bUse = false;
			g_enemy[nCntFigure].bDraw = false;
			SetParticle(g_enemy[nCntFigure].pos, 0, 10, 30.0f, 1, 0);

			AddScore(g_enemy[nCntFigure].nScore);
		}
		else
		{
			for (int nCntModel = nCntFigure; nCntModel < (nCntFigure + 1); nCntModel++)
			{

				g_enemy[nCntFigure].r = 0.5f;
				g_enemy[nCntFigure].g = 0.0f;
				g_enemy[nCntFigure].b = 0.0f;
				g_enemy[nCntFigure].a = 1.0f;

				g_enemy[nCntFigure].nCntDamage = DAMEGE_COUNT;
			}
		}
	}
	SetParticle(g_enemy[nCntFigure].pos, 0, 10, 5.0f, 1, 0);
}
//****************************************
// ���̎擾
//****************************************
Enemy *GetEnemy(void)
{
	return &g_enemy[0];
}