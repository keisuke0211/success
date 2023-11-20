//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@���̏���		    �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "floor.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFloor = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureFloor = NULL;			//�e�N�X�`���ւ̃|�C���^
Floor g_floor[MAX_FLOOR];
float g_GroundMoveX1;
float g_GroundMoveY1;
//****************************************
// ����������
//****************************************
void InitFloor(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\floor002.png",
		&g_pTextureFloor);

	LoadFloor();

	for (int nCntFloar = 0; nCntFloar < MAX_FLOOR; nCntFloar++)
	{
		if (g_floor[nCntFloar].nCype == 0)
		{
			g_floor[nCntFloar].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else if (g_floor[nCntFloar].nCype == 1)
		{
			g_floor[nCntFloar].rot = D3DXVECTOR3(0.0f, 0.0f, 3.141592f);
		}

		//�e�N�X�`���̕��������v�Z
		g_floor[nCntFloar].nSplitX = g_floor[nCntFloar].fWidth / 25;
		g_floor[nCntFloar].nSplitY = g_floor[nCntFloar].fHight / 25;
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\��	
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FLOOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFloor,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFloor->Lock(0, 0, (void **)&pVtx, 0);

	for (int nCntFloor = 0; nCntFloor < MAX_FLOOR; nCntFloor++, pVtx += 4)
	{
		if (g_floor[nCntFloor].nCype == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_floor[nCntFloor].fWidth, g_floor[nCntFloor].pos.y, +g_floor[nCntFloor].fHight);
			pVtx[1].pos = D3DXVECTOR3(+g_floor[nCntFloor].fWidth, g_floor[nCntFloor].pos.y, +g_floor[nCntFloor].fHight);
			pVtx[2].pos = D3DXVECTOR3(-g_floor[nCntFloor].fWidth, g_floor[nCntFloor].pos.y, -g_floor[nCntFloor].fHight);
			pVtx[3].pos = D3DXVECTOR3(+g_floor[nCntFloor].fWidth, g_floor[nCntFloor].pos.y, -g_floor[nCntFloor].fHight);
		}
		else if (g_floor[nCntFloor].nCype == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(-g_floor[nCntFloor].fWidth, -g_floor[nCntFloor].pos.y, +g_floor[nCntFloor].fHight);
			pVtx[1].pos = D3DXVECTOR3(+g_floor[nCntFloor].fWidth, -g_floor[nCntFloor].pos.y, +g_floor[nCntFloor].fHight);
			pVtx[2].pos = D3DXVECTOR3(-g_floor[nCntFloor].fWidth, -g_floor[nCntFloor].pos.y, -g_floor[nCntFloor].fHight);
			pVtx[3].pos = D3DXVECTOR3(+g_floor[nCntFloor].fWidth, -g_floor[nCntFloor].pos.y, -g_floor[nCntFloor].fHight);
		}
		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̂̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + g_floor[nCntFloor].nSplitX, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f + g_floor[nCntFloor].nSplitY);
		pVtx[3].tex = D3DXVECTOR2(0.0f + g_floor[nCntFloor].nSplitX, 0.0f + g_floor[nCntFloor].nSplitY);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffFloor->Unlock();
}
//****************************************
// �I������
//****************************************
void UninitFloor(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureFloor != NULL)
	{
		g_pTextureFloor->Release();
		g_pTextureFloor = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffFloor != NULL)
	{
		g_pVtxbuffFloor->Release();
		g_pVtxbuffFloor = NULL;
	}
}
//****************************************
// �X�V����
//****************************************
void UpdateFloor(void)
{
	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFloor->Lock(0, 0, (void **)&pVtx, 0);

	g_GroundMoveX1 += 1.0f;
	g_GroundMoveY1 += 1.0f;

	for (int nCntFloor = 0; nCntFloor < MAX_FLOOR; nCntFloor++, pVtx += 4)
	{
		pVtx[0].tex.x = g_GroundMoveX1;
		pVtx[1].tex.x = g_GroundMoveX1 + g_floor[nCntFloor].nSplitX;
		pVtx[2].tex.x = g_GroundMoveX1;
		pVtx[3].tex.x = g_GroundMoveX1 + g_floor[nCntFloor].nSplitX;

		pVtx[0].tex.y = g_GroundMoveY1;
		pVtx[1].tex.y = g_GroundMoveY1;
		pVtx[2].tex.y = g_GroundMoveY1 + g_floor[nCntFloor].nSplitY;
		pVtx[3].tex.y = g_GroundMoveY1 + g_floor[nCntFloor].nSplitY;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffFloor->Unlock();
}
//****************************************
// �`�揈��
//****************************************
void DrawFloor(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCntFloor = 0; nCntFloor < MAX_FLOOR; nCntFloor++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_floor[nCntFloor].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_floor[nCntFloor].rot.y,g_floor[nCntFloor].rot.x, g_floor[nCntFloor].rot.z);

		D3DXMatrixMultiply(&g_floor[nCntFloor].mtxWorld, &g_floor[nCntFloor].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_floor[nCntFloor].pos.x, g_floor[nCntFloor].pos.y, g_floor[nCntFloor].pos.z);

		D3DXMatrixMultiply(&g_floor[nCntFloor].mtxWorld, &g_floor[nCntFloor].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_floor[nCntFloor].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxbuffFloor, 0, sizeof(VERTEX_3D));

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b���_�t�H�[�}�b�g�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pDevice->SetFVF(FVF_VERTEX_3D);


		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�e�N�X�`���̐ݒ�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		pDevice->SetTexture(0, g_pTextureFloor);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		//���_���\���̂̃T�C�Y
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFloor * 4, 2);
	}
}
//****************************************
// �ݒ菈��
//****************************************
void LoadFloor(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int row = 0;//�s���𐔂���ϐ�

	char aData[300];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data/csv/FloorData.csv", "r");

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
		case 1:		g_floor[row].nCype  = atoi(aData);			break;	//�P��ځF���
		case 2:		g_floor[row].pos.x  = (float)(atoi(aData));	break;	//�@��ځFX���W
		case 3:		g_floor[row].pos.y  = (float)(atoi(aData));	break;	//�@��ځFY���W
		case 4:		g_floor[row].pos.z  = (float)(atoi(aData));	break;	//�@��ځFZ���W
		case 5:		g_floor[row].fHight = (float)(atoi(aData));	break;	//�@��ځF����
		case 6:		g_floor[row].fWidth = (float)(atoi(aData));	break;	//�@��ځF����
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
// ���̎擾
//****************************************
Floor *GetFloor(void)
{
	return &g_floor[0];
}
