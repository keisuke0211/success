//****************************************
//
//	���f���i�u���j�̏���
//	Author:��a�c��
//
//****************************************
#include "jewel.h"
#include "Player_model.h"
#include "camera.h"
#include "particle.h"
#include "score.h"
#include "sound.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPD3DXMESH g_pMeshOrnamentModel_Jewel[NUM_JEWEL] = {};					//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatOrnamentModel_Jewel[NUM_JEWEL] = {};				//�}�e���A���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureOrnamentModel_Jewel[NUM_JEWEL][1] = {};	//�e�N�X�`���ւ̃|�C���^
DWORD g_dwNumMatOrnamentModel_Jewel[NUM_JEWEL] = {};					//�}�e���A���̐�
D3DXMATRIX  g_mtxWoridFigureModel_Jewel[NUM_JEWEL];						//���[���h�}�g���b�N�X

Jewel g_jewel[NUM_JEWEL];
//****************************************
// ���f���̏���������
//****************************************
void InitJewel(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

	for (int nCntType = 0; nCntType < NUM_JEWEL; nCntType++)
	{
		g_jewel[nCntType].pos = D3DXVECTOR3(g_jewel[nCntType].pos.x, g_jewel[nCntType].pos.y, g_jewel[nCntType].pos.z);
		g_jewel[nCntType].rot = DEFAULT_D3DXVECTOR3;

		g_jewel[nCntType].r = 0.0f;
		g_jewel[nCntType].b = 0.8f;
		g_jewel[nCntType].g = 0.0f;
		g_jewel[nCntType].a = 1.0f;

		g_jewel[nCntType].fHight = 15.0f;
		g_jewel[nCntType].fWidth = 15.0f;

		g_jewel[nCntType].bUse = true;
	}

	for (int nCntType = 0; nCntType < NUM_JEWEL; nCntType++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\Diamondo.x",/*�ǂݍ��ރt�@�C����*/
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatOrnamentModel_Jewel[nCntType],
			NULL,
			&g_dwNumMatOrnamentModel_Jewel[nCntType],
			&g_pMeshOrnamentModel_Jewel[nCntType]);

		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatOrnamentModel_Jewel[nCntType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatOrnamentModel_Jewel[nCntType]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

			 //���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureOrnamentModel_Jewel[nCntType][nCntMat]);
			}
		}
	}
}
//****************************************
// ���f���̏I������
//****************************************
void UninitJewel(void)
{
	//�T�E���h�̒�~
	StopSound();

	for (int nCntType = 0; nCntType < NUM_JEWEL; nCntType++)
	{
		//���b�V���̔j��
		if (g_pMeshOrnamentModel_Jewel[nCntType] != NULL)
		{
			g_pMeshOrnamentModel_Jewel[nCntType]->Release();
			g_pMeshOrnamentModel_Jewel[nCntType] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatOrnamentModel_Jewel[nCntType] != NULL)
		{
			g_pBuffMatOrnamentModel_Jewel[nCntType]->Release();
			g_pBuffMatOrnamentModel_Jewel[nCntType] = NULL;
		}
	}
}
//****************************************
// ���f���̍X�V����
//****************************************
void UpdateJewel(void)
{
	for (int nCntModel = 0; nCntModel < NUM_JEWEL; nCntModel++)
	{
		if (g_jewel[nCntModel].bUse == true)
		{
			g_jewel[nCntModel].rot.y += 0.025f;
		}
	}
}
//****************************************
// ���f���̕`�揈��
//****************************************
void DrawJewel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̏���
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	Jewel *pFigure = g_jewel;

	for (int nCntModel = 0; nCntModel < NUM_JEWEL; nCntModel++, pFigure++)
	{
		if (g_jewel[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWoridFigureModel_Jewel[nCntModel]);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pFigure->rot.y, pFigure->rot.x, pFigure->rot.z);

			D3DXMatrixMultiply(&g_mtxWoridFigureModel_Jewel[nCntModel], &g_mtxWoridFigureModel_Jewel[nCntModel], &mtxRot);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pFigure->pos.x, pFigure->pos.y, pFigure->pos.z);

			D3DXMatrixMultiply(&g_mtxWoridFigureModel_Jewel[nCntModel], &g_mtxWoridFigureModel_Jewel[nCntModel], &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWoridFigureModel_Jewel[nCntModel]);

			//���݂̃}�e���A��������
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^������
			pMat = (D3DXMATERIAL*)g_pBuffMatOrnamentModel_Jewel[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatOrnamentModel_Jewel[pFigure->nType]; nCntMat++)
			{
				pMat[nCntMat].MatD3D.Diffuse.r = g_jewel[nCntModel].r;
				pMat[nCntMat].MatD3D.Diffuse.g = g_jewel[nCntModel].g;
				pMat[nCntMat].MatD3D.Diffuse.b = g_jewel[nCntModel].b;
				pMat[nCntMat].MatD3D.Diffuse.a = g_jewel[nCntModel].a;

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureOrnamentModel_Jewel[pFigure->nType][nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_pMeshOrnamentModel_Jewel[pFigure->nType]->DrawSubset(nCntMat);
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}
//****************************************
// ���f���̓ǂݍ��ݏ���
//****************************************
void LoadJewel(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int row = 0;//�s���𐔂���ϐ�

	char aData[500];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data\\csv\\JewelData.csv", "r");

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
		case 1:		g_jewel[row].nType = atoi(aData);			break;	//�@��ځF�摜���
		case 2:		g_jewel[row].pos.x = (float)(atoi(aData));	break;	//�@��ځFX���W
		case 3:		g_jewel[row].pos.y = (float)(atoi(aData));	break;	//�@��ځFY���W
		case 4:		g_jewel[row].pos.z = (float)(atoi(aData));	break;	//�@��ځFZ���W
		}
		//�o�b�t�@��������
		memset(aData, 0, sizeof(aData));

		//�񐔂𑫂�
		column++;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			column = 1;
			row++;
		}
	}
	//�t�@�C�������
	fclose(pFile);
}
//****************************************
// �����蔻��
//****************************************

//�v���C���[
void CollisionJewel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	for (int nCntFigure = 0; nCntFigure < NUM_JEWEL; nCntFigure++)
	{
		if (g_jewel[nCntFigure].bUse == true)
		{
			if (pPos->x >= g_jewel[nCntFigure].pos.x - (g_jewel[nCntFigure].fWidth + SIZE_WIDTH) &&
				pPos->x <= g_jewel[nCntFigure].pos.x + (g_jewel[nCntFigure].fWidth + SIZE_WIDTH) &&
				pPos->z >= g_jewel[nCntFigure].pos.z - (g_jewel[nCntFigure].fHight + SIZE_HEIGHT) &&
				pPos->z <= g_jewel[nCntFigure].pos.z + (g_jewel[nCntFigure].fHight + SIZE_HEIGHT))
			{
				if (g_jewel[nCntFigure].pos.z - g_jewel[nCntFigure].fHight >= pPosOld->z + SIZE_HEIGHT &&
					g_jewel[nCntFigure].pos.z - g_jewel[nCntFigure].fHight <= pPos->z + SIZE_HEIGHT)
				{
					g_jewel[nCntFigure].bUse = false;
					SetParticle(g_jewel[nCntFigure].pos, 0, 10, 5.0f, 1, 2);
					PlaySound(SOUND_LABEL_JEWEL); //�l����
					AddScore(50);
				}
				else if (g_jewel[nCntFigure].pos.z + g_jewel[nCntFigure].fHight <= pPosOld->z - SIZE_HEIGHT &&
					g_jewel[nCntFigure].pos.z + g_jewel[nCntFigure].fHight >= pPos->z - SIZE_HEIGHT)
				{
					g_jewel[nCntFigure].bUse = false;
					SetParticle(g_jewel[nCntFigure].pos, 0, 10, 5.0f, 1, 2);
					PlaySound(SOUND_LABEL_JEWEL); //�l����
					AddScore(50);
				}

				else if (g_jewel[nCntFigure].pos.x - g_jewel[nCntFigure].fWidth >= pPosOld->x + SIZE_WIDTH &&
					g_jewel[nCntFigure].pos.x - g_jewel[nCntFigure].fWidth <= pPos->x + SIZE_WIDTH)
				{
					g_jewel[nCntFigure].bUse = false;
					SetParticle(g_jewel[nCntFigure].pos, 0, 10, 5.0f, 1, 2);
					PlaySound(SOUND_LABEL_JEWEL); //�l����
					AddScore(50);
				}
				else if (g_jewel[nCntFigure].pos.x + g_jewel[nCntFigure].fWidth <= pPosOld->x - SIZE_WIDTH &&
					g_jewel[nCntFigure].pos.x + g_jewel[nCntFigure].fWidth >= pPos->x - SIZE_WIDTH)
				{
					g_jewel[nCntFigure].bUse = false;
					SetParticle(g_jewel[nCntFigure].pos, 0, 10, 5.0f, 1, 2);
					PlaySound(SOUND_LABEL_JEWEL); //�l����
					AddScore(50);
				}
			}
		}
	}
}
//���̎擾
Jewel *GetJewel(void)
{
	return &g_jewel[0];
}
