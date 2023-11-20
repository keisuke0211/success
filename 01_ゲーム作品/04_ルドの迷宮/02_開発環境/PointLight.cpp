//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@���C�g�̏���      �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "light.h"
#include "PointLight.h"
#include "Player_model.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
D3DLIGHT9 g_PointLihgt[NUM_POINTLIGHT];//���C�g�̏��
				  //���C�g�̏��
static PointLight g_lihgtInformation[NUM_POINTLIGHT] =
{
	//{ D3DXVECTOR3(0.2f , -0.9f , 0.6f),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) },	// �O
	//{ D3DXVECTOR3(0.2f , 0.9f , -0.5f),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) },	// ���
	//{ D3DXVECTOR3(0.9f , -0.9f , 0.5f),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) },	// �E

	{D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(0.1f, 0.1f, 0.0f, 1.0f)},	// ��E�O
};

//***************************************
// ����������
//****************************************
void InitPointLight(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;//�ݒ�p�����x�N�g��

	 //���C�g�̏����N���A����
	ZeroMemory(&g_PointLihgt, sizeof(D3DLIGHT9));

	for (int nCntLight = NUM_LIGHT; nCntLight < NUM_POINTLIGHT + NUM_LIGHT; nCntLight++)
	{
		//���C�g�̎�ނ�ݒ�
		g_PointLihgt[nCntLight].Type = D3DLIGHT_POINT;

		//���C�g�̊g�U����ݒ�g_lihgtInformation[nCntLight - NUM_LIGHT].col
		g_PointLihgt[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		vecDir = g_lihgtInformation[nCntLight - NUM_LIGHT].rot;

		//�x�N�g���𐳋K��
		D3DXVec3Normalize(&vecDir, &vecDir);

		g_PointLihgt[nCntLight].Direction = vecDir;

		g_PointLihgt[nCntLight].Position = D3DXVECTOR3(0.0f,20.0f, 100.0f);

		/*g_PointLihgt[1].Position = D3DXVECTOR3(-99.0f, 170.0f, 450.0f);
		g_PointLihgt[2].Position = D3DXVECTOR3(0.0f, 170.0f, 1049.0f);*/

		g_PointLihgt[nCntLight].Range = 150.0f;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_PointLihgt[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}
//****************************************
// �I������
//****************************************
void UninitPointLight(void)
{

}
//****************************************
// �X�V����
//****************************************
void UpdatePointLight(void)
{

}