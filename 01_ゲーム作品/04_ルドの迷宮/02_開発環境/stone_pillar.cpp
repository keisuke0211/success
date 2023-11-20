//****************************************
//
//	�Β��̏���
//	Author:��a�c��
//
//****************************************
#include "Player_model.h"
#include "stone_pillar.h"
#include "particle.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPD3DXMESH g_pMeshOrnamentModel_P[NUM_PILLAR] = {};							//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatOrnamentModel_P[NUM_PILLAR] = {};					//�}�e���A���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureOrnamentModel_P[NUM_PILLAR][MAX_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
DWORD g_dwNumMatOrnamentModel_P[NUM_PILLAR] = {};							//�}�e���A���̐�
D3DXMATRIX  g_mtxWoridFigureModel_P[NUM_PILLAR];							//���[���h�}�g���b�N�X

Pillar g_Pillar[NUM_PILLAR];
//****************************************
// ���f���̏���������
//****************************************
void InitPillar_Model(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

	for (int nCntType = 0; nCntType < NUM_PILLAR; nCntType++)
	{
		g_Pillar[nCntType].pos = D3DXVECTOR3(g_Pillar[nCntType].pos.x, g_Pillar[nCntType].pos.y, g_Pillar[nCntType].pos.z);

		if (g_Pillar[nCntType].nType == 0)
		{
			g_Pillar[nCntType].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else if (g_Pillar[nCntType].nType == 1)
		{
			g_Pillar[nCntType].rot = D3DXVECTOR3(0.0f, 0.0f, 1.575f);
		}
		else if (g_Pillar[nCntType].nType == 2)
		{
			g_Pillar[nCntType].rot = D3DXVECTOR3(0.0f, 1.575f, 1.575f);
		}
		g_Pillar[nCntType].fHight = 15.0f;
		g_Pillar[nCntType].fWidth = 15.0f;
		g_Pillar[nCntType].r = 1.0f;
		g_Pillar[nCntType].b = 1.0f;
		g_Pillar[nCntType].g = 1.0f;
		g_Pillar[nCntType].a = 1.0f;
		g_Pillar[nCntType].bUse = true;
	}
	for (int nCntType = 0; nCntType < NUM_PILLAR; nCntType++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\stone_pillar.x",/*�ǂݍ��ރt�@�C����*/
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatOrnamentModel_P[nCntType],
			NULL,
			&g_dwNumMatOrnamentModel_P[nCntType],
			&g_pMeshOrnamentModel_P[nCntType]);

		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatOrnamentModel_P[nCntType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatOrnamentModel_P[nCntType]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

			 //���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureOrnamentModel_P[nCntType][nCntMat]);
			}
		}
	}
}
//****************************************
// ���f���̏I������
//****************************************
void UninitPillar_Model(void)
{
	for (int nCntType = 0; nCntType < NUM_PILLAR; nCntType++)
	{
		//���b�V���̔j��
		if (g_pMeshOrnamentModel_P[nCntType] != NULL)
		{
			g_pMeshOrnamentModel_P[nCntType]->Release();
			g_pMeshOrnamentModel_P[nCntType] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatOrnamentModel_P[nCntType] != NULL)
		{
			g_pBuffMatOrnamentModel_P[nCntType]->Release();
			g_pBuffMatOrnamentModel_P[nCntType] = NULL;
		}
	}
}
//****************************************
// ���f���̍X�V����
//****************************************
void UpdatePillar_Model(void)
{
	
}
//****************************************
// ���f���̕`�揈��
//****************************************
void DrawPillar_Model(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̏���
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	Pillar *pPillar = g_Pillar;

	for (int nCntModel = 0; nCntModel < NUM_PILLAR; nCntModel++, pPillar++)
	{
		if (g_Pillar[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWoridFigureModel_P[nCntModel]);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pPillar->rot.y, pPillar->rot.x, pPillar->rot.z);

			D3DXMatrixMultiply(&g_mtxWoridFigureModel_P[nCntModel], &g_mtxWoridFigureModel_P[nCntModel], &mtxRot);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pPillar->pos.x, pPillar->pos.y, pPillar->pos.z);

			D3DXMatrixMultiply(&g_mtxWoridFigureModel_P[nCntModel], &g_mtxWoridFigureModel_P[nCntModel], &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWoridFigureModel_P[nCntModel]);

			//���݂̃}�e���A��������
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^������
			pMat = (D3DXMATERIAL*)g_pBuffMatOrnamentModel_P[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatOrnamentModel_P[pPillar->nType]; nCntMat++)
			{
				pMat[nCntMat].MatD3D.Diffuse.r = g_Pillar[nCntModel].r;
				pMat[nCntMat].MatD3D.Diffuse.g = g_Pillar[nCntModel].g;
				pMat[nCntMat].MatD3D.Diffuse.b = g_Pillar[nCntModel].b;
				pMat[nCntMat].MatD3D.Diffuse.a = g_Pillar[nCntModel].a;

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureOrnamentModel_P[pPillar->nType][nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_pMeshOrnamentModel_P[pPillar->nType]->DrawSubset(nCntMat);
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}
//****************************************
// ���f���̓ǂݍ��ݏ���
//****************************************
void LoadPillar_Model(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int row = 0;//�s���𐔂���ϐ�

	char aData[500];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data\\csv\\PillarData.csv", "r");

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
		case 1:		g_Pillar[row].nType = atoi(aData);			break;	//�@��ځF�摜���
		case 2:		g_Pillar[row].pos.x = (float)(atoi(aData));	break;	//�@��ځFX���W
		case 3:		g_Pillar[row].pos.y = (float)(atoi(aData));	break;	//�@��ځFY���W
		case 4:		g_Pillar[row].pos.z = (float)(atoi(aData));	break;	//�@��ځFZ���W
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
// �����蔻�菈��
//****************************************
void CollisioPillar_Model(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	for (int nCntFigure = 0; nCntFigure < NUM_PILLAR; nCntFigure++)
	{
		if (g_Pillar[nCntFigure].bUse == true)
		{
			if (g_Pillar[nCntFigure].nType == 0)
			{
				if (pPos->x >= g_Pillar[nCntFigure].pos.x - (g_Pillar[nCntFigure].fWidth + SIZE_WIDTH) &&
					pPos->x <= g_Pillar[nCntFigure].pos.x + (g_Pillar[nCntFigure].fWidth + SIZE_WIDTH) &&
					pPos->z >= g_Pillar[nCntFigure].pos.z - (g_Pillar[nCntFigure].fWidth + SIZE_WIDTH) &&
					pPos->z <= g_Pillar[nCntFigure].pos.z + (g_Pillar[nCntFigure].fWidth + SIZE_WIDTH))
				{
					if (g_Pillar[nCntFigure].pos.z - g_Pillar[nCntFigure].fWidth >= pPosOld->z + SIZE_HEIGHT &&
						g_Pillar[nCntFigure].pos.z - g_Pillar[nCntFigure].fWidth <= pPos->z + SIZE_HEIGHT)
					{
						pPos->z = g_Pillar[nCntFigure].pos.z - (g_Pillar[nCntFigure].fWidth + SIZE_HEIGHT);
					}
					else if (g_Pillar[nCntFigure].pos.z + g_Pillar[nCntFigure].fWidth <= pPosOld->z - SIZE_HEIGHT &&
						g_Pillar[nCntFigure].pos.z + g_Pillar[nCntFigure].fWidth >= pPos->z - SIZE_HEIGHT)
					{
						pPos->z = g_Pillar[nCntFigure].pos.z + (g_Pillar[nCntFigure].fWidth + SIZE_HEIGHT);
					}

					else if (g_Pillar[nCntFigure].pos.x - g_Pillar[nCntFigure].fWidth >= pPosOld->x + SIZE_WIDTH &&
						g_Pillar[nCntFigure].pos.x - g_Pillar[nCntFigure].fWidth <= pPos->x + SIZE_WIDTH)
					{
						pPos->x = g_Pillar[nCntFigure].pos.x - (g_Pillar[nCntFigure].fWidth + SIZE_WIDTH);
					}
					else if (g_Pillar[nCntFigure].pos.x + g_Pillar[nCntFigure].fWidth <= pPosOld->x - SIZE_WIDTH &&
						g_Pillar[nCntFigure].pos.x + g_Pillar[nCntFigure].fWidth >= pPos->x - SIZE_WIDTH)
					{
						pPos->x = g_Pillar[nCntFigure].pos.x + (g_Pillar[nCntFigure].fWidth + SIZE_WIDTH);
					}

					if (g_Pillar[nCntFigure].nType == 5)
					{
						g_Pillar[nCntFigure].bUse = false;
						SetParticle(g_Pillar[nCntFigure].pos, 0, 10, 5.0f, 2, 0);
					}
				}
			}
		}
	}
}
//****************************************
// ���̎擾
//****************************************
Pillar *GetPillarl(void)
{
	return &g_Pillar[0];
}