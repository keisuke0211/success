//��======================��
//�b�@�@�@�@�@�@�@�@�@�@  �b
//�b�@�p�[�e�B�N������	  �b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include"particle.h"
#include"effect.h"
#include "Goal_effect.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define MAX_PARTICLE	(2560)	//�p�[�e�B�N������
//��====================��
//�b �@�@���\���� �@�@�b
//��====================��

//�p�[�e�B�N���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�i�����ʒu�j
	int  nLife;			//�����i�������ԁj
	int nType;			//���
	int cType;			//�F���
	int pType;			//�p�[�e�B�N�����
	int nCntForm;		//��x�ɐ�������p�[�e�B�N����
	float fRadius;		//���a�i�傫���j
	bool bUse;			//�g�p���Ă��邩�ǂ���
} Particle;

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
Particle g_aParticle[MAX_PARTICLE];
int nForm;
int nForm1;
//��====================================��
//�b�@�@ �p�[�e�B�N���̏����������@�@ �@�b
//��====================================��
void InitParticle(void)
{
	int nCntParticle;

	nForm = 0;
	nForm1 = 0;
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].nCntForm = 0;
		g_aParticle[nCntParticle].bUse = false;
	}
}
//��==================================��
//�b�@�@ �p�[�e�B�N���̏I�������@�@ �@�b
//��==================================��
void UninitParticle(void)
{

}
//��==================================��
//�b�@�@ �p�[�e�B�N���̍X�V�����@�@ �@�b
//��==================================��
void UpdateParticle(void)
{
	int nCntParticle;	//�J�E���^

	//�G�t�F�N�g�ݒ�p
	D3DXVECTOR3 pos;	//�ʒu
	float fRot;			//�p�x
	float fSpeed;		//�ړ����x
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 movevec;
	D3DXCOLOR col;		//�F
	float fRadius = 0;	//���a
	int nLife = 0;		//����

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse)
		{
			//�p�[�e�B�N���̔���
			int nCntAppear;

			switch (g_aParticle[nCntParticle].pType)
			{
			case 0:
				g_aParticle[nCntParticle].nCntForm = 20;
				break;
			case 1:
				g_aParticle[nCntParticle].nCntForm = 1;
				break;
			case 2:
				g_aParticle[nCntParticle].nCntForm = 5;
				break;
			}

			for (nCntAppear = 0; nCntAppear < g_aParticle[nCntParticle].nCntForm; nCntAppear++)
			{
				switch (g_aParticle[nCntParticle].pType)
				{
				case 0:
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;
					//�ړ��ʂ̐ݒ�
					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					fSpeed = (float)(rand() % (2 * 100)) / 100 + 2;
					move.x = sinf(fRot) * fSpeed;
					move.y = cosf(fRot) * fSpeed;
					move.z = sinf(fRot) * fSpeed;
					break;
				case 1:
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;
					//�ړ��ʂ̐ݒ�
					fRot = 0.0f;
					fSpeed = 0.0f;
					move.x = sinf(fRot) * fSpeed;
					move.y = cosf(fRot) * fSpeed;
					move.z = sinf(fRot) * fSpeed;
					break;
				case 2:
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;
					//�ړ��ʂ̐ݒ�
					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					fSpeed = (float)(rand() % (2 * 100)) / 100 + 2;
					move.x = sinf(fRot) * fSpeed;
					move.y = cosf(fRot) * fSpeed;
					move.z = sinf(fRot) * fSpeed;
					break;
				}

				switch (g_aParticle[nCntParticle].cType)
				{
				case 0:
					//�F
					col = D3DXCOLOR(0.0f, 1.0f, 0.1f, 1.0f);
					break;
				case 1:
					col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
					break;
				case 2:
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					break;
				case 3:
					col = D3DXCOLOR(0.1f, 0.3f, 0.1f, 1.0f);
					break;
				}

				switch (g_aParticle[nCntParticle].nType)
				{
				case 0:
					//���a
					fRadius = 5;
					break;
				case 1:
					fRadius = 30;
					break;
				case 2:
					fRadius = 20;
					break;
				case 3:
					fRadius = 80;
					break;
				}

				switch (g_aParticle[nCntParticle].nType)
				{
				case 0:
					//����
					nLife = 30;
					break;
				case 1:
					//����
					nLife = 30;
					break;
				case 2:
					nLife = 20;
					break;
				case 3:
					nLife = 50;
					break;
				}

				//�G�t�F�N�g�ݒ�
				if (g_aParticle[nCntParticle].pType == 1)
				{
					SetGoalEffect(pos, move, col, fRadius, nLife, g_aParticle[nCntParticle].pType);
				}
				else
				{
					SetEffect(pos, move, col, fRadius, nLife, g_aParticle[nCntParticle].pType);
				}
			}
				

			//�����̌���
			g_aParticle[nCntParticle].nLife--;
			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}
//��==================================��
//�b�@�@ �p�[�e�B�N���̕`�揈���@�@ �@�b
//��==================================��
void DrawParticle(void)
{
	
}

//��==================================��
//�b�@�@ �p�[�e�B�N���̐ݒ菈���@�@ �@�b
//��==================================��
void SetParticle(D3DXVECTOR3 pos, int nType, int nLife, float fRadius,int cType,int pType)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nType = nType;
			g_aParticle[nCntParticle].cType = cType;
			g_aParticle[nCntParticle].pType = pType;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].fRadius = fRadius;
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
	}
}