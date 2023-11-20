//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@���f������        �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "model.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPD3DXMESH g_pMeshModel = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;;				//�}�e���A���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureModel[2] = {};			//�e�N�X�`���ւ̃|�C���^
DWORD g_dwNumMatModel = 0;							//�}�e���A���̐�
D3DXVECTOR3 g_posModel;								//�ʒu
D3DXVECTOR3 g_rotModel;								//����
D3DXMATRIX  g_mtxWoridModel;						//���[���h�}�g���b�N�X
//****************************************
// ���f���̏���������
//****************************************
void InitModel(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posModel = DEFAULT_D3DXVECTOR3;
	g_rotModel = DEFAULT_D3DXVECTOR3;
	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/Luna.x",/*�ǂݍ��ރt�@�C����*/
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

												//�}�e���A�����ɑ΂���|�C���^������
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���

		 //���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureModel[nCntMat]);
		}
	}
}
//****************************************
// ���f���̏I������
//****************************************
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}
//****************************************
// ���f���̍X�V����
//****************************************
void UpdateModel(void)
{

}
//****************************************
// ���f���̕`�揈��
//****************************************
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̏���
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

												//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWoridModel);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y,g_rotModel.x, g_rotModel.z);

	D3DXMatrixMultiply(&g_mtxWoridModel, &g_mtxWoridModel, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);

	D3DXMatrixMultiply(&g_mtxWoridModel, &g_mtxWoridModel, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWoridModel);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^������
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureModel[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
