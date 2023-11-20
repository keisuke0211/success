//��====================================��
//�b�@�@�@�@�@�@�@�@�@�@				�b
//�b�@���b�V���t�B�[���h�̏���          �b
//�b�@Author:��a�c��@					�b
//�b									�b
//��====================================��
#include "meshfield_wall.h"
#include "Player_model.h"
#include "camera.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DTEXTURE9		g_pTextureMeshfield_Wall = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield_Wall = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield_Wall = NULL;			//���_�o�b�t�@�|�C���^
//D3DXVECTOR3 g_posMeshfield_Wall;//�ʒu
//D3DXVECTOR3 g_rotMeshfield_Wall;//����
D3DXMATRIX g_mtxWorldMeshfield_Wall;//���[���h�}�g���b�N�X

MeshWall g_MeshWall;
//****************************************
// ����������
//****************************************
void InitMeshField_Wall(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\floor001.png",
		&g_pTextureMeshfield_Wall);

	/*g_posMeshfield_Wall = D3DXVECTOR3(0.0f, 0.0f, 750.0f);
	g_rotMeshfield_Wall = DEFAULT_D3DXVECTOR3;*/

	g_MeshWall.pos = D3DXVECTOR3(0.0f, 0.0f, 750.0f);
	g_MeshWall.rot = DEFAULT_D3DXVECTOR3;
	g_MeshWall.fWidhtX = 250;
	g_MeshWall.fWidhtZ = 500;
	g_MeshWall.nBlock_Z = g_MeshWall.nBlock_Z / 25;
	g_MeshWall.nBlock_X = g_MeshWall.nBlock_X / 25;
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield_Wall,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield_Wall->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-250, 500, 0);
	pVtx[1].pos = D3DXVECTOR3(0, 500, 0);
	pVtx[2].pos = D3DXVECTOR3(+250, 500, 0);
	pVtx[3].pos = D3DXVECTOR3(-250, 250, 0);
	pVtx[4].pos = D3DXVECTOR3(0, 250, 0);
	pVtx[5].pos = D3DXVECTOR3(+250, 250, 0);
	pVtx[6].pos = D3DXVECTOR3(-250, 0, 0);
	pVtx[7].pos = D3DXVECTOR3(0, 0, 0);
	pVtx[8].pos = D3DXVECTOR3(+250, 0, -0);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̂̐ݒ�

	//�P�����S�������ĕ\��

	/*{
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);
	}*/

	//�Z�~2�̃u���b�N���\������
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
		pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshfield_Wall->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield_Wall,
		NULL);

	WORD *pIdx;//�C���f�b�N�X���ւ̃|�C���^

			   //�C���f�b�N�X�o�b�t�@�����b�N�������_�ԍ��f�[�^�ւ̃|�C���^������
	g_pIdxBuffMeshfield_Wall->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshfield_Wall->Unlock();
}
//****************************************
// �I������
//****************************************
void UninitMeshField_Wall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield_Wall != NULL)
	{
		g_pTextureMeshfield_Wall->Release();
		g_pTextureMeshfield_Wall = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield_Wall != NULL)
	{
		g_pVtxBuffMeshfield_Wall->Release();
		g_pVtxBuffMeshfield_Wall = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshfield_Wall != NULL)
	{
		g_pIdxBuffMeshfield_Wall->Release();
		g_pIdxBuffMeshfield_Wall = NULL;
	}
}
//****************************************
// �X�V����
//****************************************
void UpdateMeshField_Wall(void)
{

}
//****************************************
// �`�揈��
//****************************************
void DrawMeshField_Wall(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

												//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfield_Wall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall.rot.y,
		g_MeshWall.rot.x, g_MeshWall.rot.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshfield_Wall, &g_mtxWorldMeshfield_Wall, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshWall.pos.x, g_MeshWall.pos.y, g_MeshWall.pos.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshfield_Wall, &g_mtxWorldMeshfield_Wall, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield_Wall);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield_Wall, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshfield_Wall);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield_Wall);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		9,//�p�ӂ������_�̐�
		0,
		12);//�`�悷��v���~�e�B�u�̐�
}
//****************************************
// �����蔻��
//****************************************
void CollisionMeshField_Wall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	for (int nCntWall = 0; nCntWall < 1; nCntWall++)
	{
		if (pPos->x >= g_MeshWall.pos.x - (g_MeshWall.fWidhtX + SIZE_WIDTH) &&
			pPos->x <= g_MeshWall.pos.x + (g_MeshWall.fWidhtX + SIZE_WIDTH) &&
			pPos->y >= g_MeshWall.pos.y - (g_MeshWall.fWidhtZ + SIZE_HEIGHT) &&
			pPos->y <= g_MeshWall.pos.y + (g_MeshWall.fWidhtZ + SIZE_HEIGHT) &&
			pPos->z >= g_MeshWall.pos.z - (g_MeshWall.fWidhtX + SIZE_WIDTH) &&
			pPos->z <= g_MeshWall.pos.z + (g_MeshWall.fWidhtX + SIZE_WIDTH))
		{
			/*if (g_Wall[nCntWall].nCype == 0 || g_Wall[nCntWall].nCype == 1)
			{*/
				if (/*g_MeshWall.pos.y + g_MeshWall.fWidhtY >= pPosOld->y + SIZE_HEIGHT &&
					g_MeshWall.pos.y - g_MeshWall.fWidhtY <= pPosOld->y - SIZE_HEIGHT &&*/
					g_MeshWall.pos.z - 2 >= pPosOld->z + SIZE_WIDTH &&
					g_MeshWall.pos.z - 2 <= pPos->z + SIZE_WIDTH)
				{
					pPos->z = g_MeshWall.pos.z - (2 + SIZE_WIDTH);

					Getcamara(0)->posV.z = pPos->z - 50;
					Getcamara(0)->posR.z = pPos->z;
				}
				else if (/*g_MeshWall.pos.y + g_MeshWall.fWidhtY >= pPosOld->y + SIZE_HEIGHT &&
						 g_MeshWall.pos.y - g_MeshWall.fWidhtY <= pPosOld->y - SIZE_HEIGHT &&*/
						 g_MeshWall.pos.z + 2 <= pPosOld->z - SIZE_WIDTH &&
						 g_MeshWall.pos.z + 2 >= pPos->z - SIZE_WIDTH)
				{
					pPos->z = g_MeshWall.pos.z + (2 + SIZE_WIDTH);

					Getcamara(0)->posV.z = pPos->z - 50;
					Getcamara(0)->posR.z = pPos->z;
				}
			//}
			/*else if (g_Wall[nCntWall].nCype == 2 || g_Wall[nCntWall].nCype == 3)
			{*/
				/*if (g_MeshWall.pos.y + g_MeshWall.fWidhtY >= pPosOld->y + SIZE_HEIGHT &&
					g_MeshWall.pos.y - g_MeshWall.fWidhtY <= pPosOld->y - SIZE_HEIGHT &&
					g_MeshWall.pos.x - 2 >= pPosOld->x + SIZE_WIDTH &&
					g_MeshWall.pos.x - 2 <= pPos->x + SIZE_WIDTH)
				{
					pPos->x = g_MeshWall.pos.x - (2 + SIZE_WIDTH);

					Getcamara()->posV.x = pPos->x;
					Getcamara()->posR.x = pPos->x;
				}
				else if (g_MeshWall.pos.y + g_MeshWall.fWidhtY >= pPosOld->y + SIZE_HEIGHT &&
					g_MeshWall.pos.y - g_MeshWall.fWidhtY <= pPosOld->y - SIZE_HEIGHT &&
					g_MeshWall.pos.x + 2 <= pPosOld->x - SIZE_WIDTH &&
					g_MeshWall.pos.x + 2 >= pPos->x - SIZE_WIDTH)
				{
					pPos->x = g_MeshWall.pos.x + (2 + SIZE_WIDTH);

					Getcamara()->posV.x = pPos->x;
					Getcamara()->posR.x = pPos->x;
				}*/
			//}
		}
	}
}