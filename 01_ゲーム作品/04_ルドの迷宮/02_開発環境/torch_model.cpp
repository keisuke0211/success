//****************************************
//
//	�����̏���
//	Author:��a�c��
//
//****************************************
#include "torch_model.h"
#include "torch.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPD3DXMESH g_pMeshOrnamentModel_T[NUM_TORCH_M] = {};							//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatOrnamentModel_T[NUM_TORCH_M] = {};						//�}�e���A���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureOrnamentModel_T[NUM_TORCH_M][MAX_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
DWORD g_dwNumMatOrnamentModel_T[NUM_TORCH_M] = {};								//�}�e���A���̐�
D3DXMATRIX  g_mtxWoridFigureModel_T[NUM_TORCH_M];								//���[���h�}�g���b�N�X

Torch_Model g_Torch[NUM_TORCH_M];
//****************************************
// ���f���̏���������
//****************************************
void InitTorch_Model(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

	for (int nCntType = 0; nCntType < NUM_TORCH_M; nCntType++)
	{
		g_Torch[nCntType].pos = D3DXVECTOR3(g_Torch[nCntType].pos.x, g_Torch[nCntType].pos.y, g_Torch[nCntType].pos.z);

		if (g_Torch[nCntType].nType == 0)
		{
			g_Torch[nCntType].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else if (g_Torch[nCntType].nType == 1)
		{
			g_Torch[nCntType].rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
		}
		else if (g_Torch[nCntType].nType == 2)
		{
			g_Torch[nCntType].rot = D3DXVECTOR3(0.0f, 1.575f, 0.0f);
		}
		else if (g_Torch[nCntType].nType == 3)
		{
			g_Torch[nCntType].rot = D3DXVECTOR3(0.0f, -1.575f, 0.0f);
		}

		g_Torch[nCntType].fHight = 0.0f;
		g_Torch[nCntType].fWidth = 0.0f;
		g_Torch[nCntType].r = 1.0f;
		g_Torch[nCntType].b = 1.0f;
		g_Torch[nCntType].g = 1.0f;
		g_Torch[nCntType].a = 1.0f;
		g_Torch[nCntType].bUse = true;

		g_Torch[nCntType].nIdxTorchLight = SetTorch();
	}
	for (int nCntType = 0; nCntType < NUM_TORCH_M; nCntType++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\torch.x",/*�ǂݍ��ރt�@�C����*/
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatOrnamentModel_T[nCntType],
			NULL,
			&g_dwNumMatOrnamentModel_T[nCntType],
			&g_pMeshOrnamentModel_T[nCntType]);

		//�}�e���A�����ɑ΂���|�C���^������
		pMat = (D3DXMATERIAL*)g_pBuffMatOrnamentModel_T[nCntType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatOrnamentModel_T[nCntType]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���

			 //���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_pTextureOrnamentModel_T[nCntType][nCntMat]);
			}
		}
	}
}
//****************************************
// ���f���̏I������
//****************************************
void UninitTorch_Model(void)
{
	for (int nCntType = 0; nCntType < NUM_TORCH_M; nCntType++)
	{
		//���b�V���̔j��
		if (g_pMeshOrnamentModel_T[nCntType] != NULL)
		{
			g_pMeshOrnamentModel_T[nCntType]->Release();
			g_pMeshOrnamentModel_T[nCntType] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatOrnamentModel_T[nCntType] != NULL)
		{
			g_pBuffMatOrnamentModel_T[nCntType]->Release();
			g_pBuffMatOrnamentModel_T[nCntType] = NULL;
		}
	}
}
//****************************************
// ���f���̍X�V����
//****************************************
void UpdateTorch_Model(void)
{
	for (int nCntModel = 0; nCntModel < NUM_TORCH_M; nCntModel++)
	{
		SetPositionTorch(nCntModel, D3DXVECTOR3(g_Torch[nCntModel].pos.x + g_Torch[nCntModel].fWidth, g_Torch[nCntModel].pos.y, g_Torch[nCntModel].pos.z + g_Torch[nCntModel].fHight), 150);
	}
}
//****************************************
// ���f���̕`�揈��
//****************************************
void DrawTorch_Model(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̏���
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	Torch_Model *pTorch = g_Torch;

	for (int nCntModel = 0; nCntModel < NUM_TORCH_M; nCntModel++, pTorch++)
	{
		if (g_Torch[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWoridFigureModel_T[nCntModel]);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pTorch->rot.y, pTorch->rot.x, pTorch->rot.z);

			D3DXMatrixMultiply(&g_mtxWoridFigureModel_T[nCntModel], &g_mtxWoridFigureModel_T[nCntModel], &mtxRot);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pTorch->pos.x, pTorch->pos.y, pTorch->pos.z);

			D3DXMatrixMultiply(&g_mtxWoridFigureModel_T[nCntModel], &g_mtxWoridFigureModel_T[nCntModel], &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWoridFigureModel_T[nCntModel]);

			//���݂̃}�e���A��������
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^������
			pMat = (D3DXMATERIAL*)g_pBuffMatOrnamentModel_T[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatOrnamentModel_T[pTorch->nType]; nCntMat++)
			{
				pMat[nCntMat].MatD3D.Diffuse.r = g_Torch[nCntModel].r;
				pMat[nCntMat].MatD3D.Diffuse.g = g_Torch[nCntModel].g;
				pMat[nCntMat].MatD3D.Diffuse.b = g_Torch[nCntModel].b;
				pMat[nCntMat].MatD3D.Diffuse.a = g_Torch[nCntModel].a;

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureOrnamentModel_T[pTorch->nType][nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_pMeshOrnamentModel_T[pTorch->nType]->DrawSubset(nCntMat);
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}
//****************************************
// ���f���̓ǂݍ��ݏ���
//****************************************
void LoadTorch_Model(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int row = 0;//�s���𐔂���ϐ�

	char aData[500];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data\\csv\\TorchData.csv", "r");

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
		case 1:		g_Torch[row].nType = atoi(aData);			break;	//�@��ځF�摜���
		case 2:		g_Torch[row].pos.x = (float)(atoi(aData));	break;	//�@��ځFX���W
		case 3:		g_Torch[row].pos.y = (float)(atoi(aData));	break;	//�@��ځFY���W
		case 4:		g_Torch[row].pos.z = (float)(atoi(aData));	break;	//�@��ځFZ���W
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