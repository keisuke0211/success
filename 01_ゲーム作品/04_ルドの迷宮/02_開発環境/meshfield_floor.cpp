//��====================================��
//�b�@�@�@�@�@�@�@�@�@�@				�b
//�b�@���b�V���t�B�[���h�̏���          �b
//�b�@Author:��a�c��@					�b
//�b									�b
//��====================================��
#include "meshfield_floor.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DTEXTURE9		g_pTextureMeshfield_Floor = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield_Floor = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield_Floor = NULL;			//���_�o�b�t�@�|�C���^
D3DXMATRIX g_mtxWorldMeshfield_Floor;//���[���h�}�g���b�N�X

MeshFloor g_MeshFloor[NUM_MESHI];
//****************************************
// ����������
//****************************************
void InitMeshField_Floor(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\stone brick.png",
		&g_pTextureMeshfield_Floor);

	g_MeshFloor[0].pos = D3DXVECTOR3(0.0f,0.0f,100.0f);
	g_MeshFloor[0].rot = DEFAULT_D3DXVECTOR3;
	g_MeshFloor[0].fWidhtX = 50;
	g_MeshFloor[0].fWidhtZ = 50;
	g_MeshFloor[0].nBlock_X = 30;
	g_MeshFloor[0].nBlock_Z = 30;
	g_MeshFloor[0].nVertex = (g_MeshFloor[0].nBlock_Z + 1) * (g_MeshFloor[0].nBlock_X + 1);
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_MeshFloor[0].nVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield_Floor,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield_Floor->Lock(0, 0, (void **)&pVtx, 0);

	// ���_���W/�@���x�N�g��/�e�N�X�`�����W�̐ݒ�	

	for (int nCntHeight = 0; nCntHeight < g_MeshFloor[0].nBlock_X + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < g_MeshFloor[0].nBlock_Z + 1; nCntWidth++)
		{
			pVtx[(nCntHeight * (g_MeshFloor[0].nBlock_Z + 1)) + nCntWidth].pos
				= D3DXVECTOR3(
					((float)nCntHeight - (float)g_MeshFloor[0].nBlock_X / 2) * g_MeshFloor[0].fWidhtX,
					0.0f,
					((float)nCntWidth - (float)g_MeshFloor[0].nBlock_Z / 2) * g_MeshFloor[0].fWidhtZ);

			pVtx[(nCntHeight * (g_MeshFloor[0].nBlock_Z + 1)) + nCntWidth].nor
				= D3DXVECTOR3(
					0.0f,
					1.0f,
					0.0f);

			pVtx[(nCntHeight * (g_MeshFloor[0].nBlock_Z + 1)) + nCntWidth].tex
				= D3DXVECTOR2(
					nCntHeight * ((float)g_MeshFloor[0].nBlock_Z / (float)g_MeshFloor[0].nBlock_Z),
					nCntWidth * ((float)g_MeshFloor[0].nBlock_X / (float)g_MeshFloor[0].nBlock_X));
		}
	}

	for (int nCntVtx = 0; nCntVtx < ((g_MeshFloor[0].nBlock_Z + 1) * (g_MeshFloor[0].nBlock_X + 1)); nCntVtx++)
	{
		// ���_�J���[�̐ݒ�
		pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshfield_Floor->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((g_MeshFloor[0].nBlock_X * 2 * (g_MeshFloor[0].nBlock_Z + 1)) + ((g_MeshFloor[0].nBlock_X - 1) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield_Floor,
		NULL);

	WORD *pIdx;//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N�������_�ԍ��f�[�^�ւ̃|�C���^������
	g_pIdxBuffMeshfield_Floor->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdx = 0;	// �C���f�b�N�X�̃J�E���g

	//���_�ԍ��f�[�^�̐ݒ�
	for (int nCntDepth = 0; nCntDepth < g_MeshFloor[0].nBlock_X; nCntDepth++)
	{
		for (int nCntWidth = 0; nCntWidth < g_MeshFloor[0].nBlock_Z + 1; nCntWidth++)
		{
			pIdx[nCntIdx] = (nCntWidth + ((g_MeshFloor[0].nBlock_Z + 1) * (nCntDepth + 1)));
			pIdx[nCntIdx + 1] = nCntWidth + ((g_MeshFloor[0].nBlock_Z + 1) * nCntDepth);
			nCntIdx += 2;
		}

		if (nCntDepth < g_MeshFloor[0].nBlock_X - 1)
		{
			pIdx[nCntIdx] = ((g_MeshFloor[0].nBlock_Z + 1) * (nCntDepth + 1)) - 1;
			pIdx[nCntIdx + 1] = (g_MeshFloor[0].nBlock_Z + 1) * (nCntDepth + 2);
			nCntIdx += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshfield_Floor->Unlock();
}
//****************************************
// �I������
//****************************************
void UninitMeshField_Floor(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield_Floor != NULL)
	{
		g_pTextureMeshfield_Floor->Release();
		g_pTextureMeshfield_Floor = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield_Floor != NULL)
	{
		g_pVtxBuffMeshfield_Floor->Release();
		g_pVtxBuffMeshfield_Floor = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshfield_Floor != NULL)
	{
		g_pIdxBuffMeshfield_Floor->Release();
		g_pIdxBuffMeshfield_Floor = NULL;
	}
}
//****************************************
// �X�V����
//****************************************
void UpdateMeshField_Floor(void)
{

}
//****************************************
// �`�揈��
//****************************************
void DrawMeshField_Floor(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

												//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfield_Floor);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshFloor[0].rot.y,
		g_MeshFloor[0].rot.x, g_MeshFloor[0].rot.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshfield_Floor, &g_mtxWorldMeshfield_Floor, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshFloor[0].pos.x, g_MeshFloor[0].pos.y, g_MeshFloor[0].pos.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshfield_Floor, &g_mtxWorldMeshfield_Floor, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield_Floor);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield_Floor, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshfield_Floor);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield_Floor);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		g_MeshFloor[0].nVertex,//�p�ӂ������_�̐�
		0,
		((g_MeshFloor[0].nBlock_Z * g_MeshFloor[0].nBlock_X) * 2) + (4 * (g_MeshFloor[0].nBlock_X - 1)));//�`�悷��v���~�e�B�u�̐�
}