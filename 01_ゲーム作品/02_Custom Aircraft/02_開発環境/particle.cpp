//��======================��
//�b�@�@�@�@�@�@�@�@�@�@  �b
//�b�@�p�[�e�B�N������	  �b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include"particle.h"
#include"effect.h"
#include"boss.h"
#include"Summon.h"
#include"aura_effect.h"
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

	Boss *pBoss = GetBoss(); //�G�̏��ւ̃|�C���^

	//�G�t�F�N�g�ݒ�p
	D3DXVECTOR3 pos;	//�ʒu
	float fRot;			//�p�x
	float fSpeed;		//�ړ����x
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 movevec;
	D3DXCOLOR col;		//�F
	float fRadius = 0;		//���a
	int nLife = 0;			//����
	float rRot;			//���S�_����p�x�����߂�
	//float rRange;		//���S�_���狗�������߂�

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
				g_aParticle[nCntParticle].nCntForm = 5;
				break;
			case 2:
				nForm = GetnCharge();
				g_aParticle[nCntParticle].nCntForm = 0 + (nForm / 3);
				break;
			case 3:
				g_aParticle[nCntParticle].nCntForm = 10;
				break;
			case 4:
				g_aParticle[nCntParticle].nCntForm = 5;
				break;
			case 5:
				nForm = GetnCharge1();
				g_aParticle[nCntParticle].nCntForm = 0 + (nForm / 3);
				break;
			case 6:
				g_aParticle[nCntParticle].nCntForm = 20;
				break;

			case 31:
				g_aParticle[nCntParticle].nCntForm = 10;
				break;
			case 32:
				g_aParticle[nCntParticle].nCntForm = 10;
				break;
			case 41:
				g_aParticle[nCntParticle].nCntForm = 10;
				break;
			case 42:
				g_aParticle[nCntParticle].nCntForm = 10;
				break;
			case 51:
				nForm1 = GetnCharge2();
				g_aParticle[nCntParticle].nCntForm = 0 + (nForm / 2);
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
					break;
				case 1:
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;
					//�ړ��ʂ̐ݒ�
					fRot = 0.0f;
					fSpeed = 0.0f;
					move.x = sinf(fRot) * fSpeed;
					move.y = cosf(fRot) * fSpeed;
					break;
				case 2:
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					fSpeed = (float)(rand() % (2 * 50)) / 50 + 2;
					move.x = sinf(fRot) * fSpeed;
					move.y = cosf(fRot) * fSpeed;
					break;
				case 3:
					rRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;

					pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + sinf(rRot) * 30,
									  g_aParticle[nCntParticle].pos.y + cosf(rRot) * 30, 0.0f);

					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					move.x = sinf(fRot) * 0;
					move.y = cosf(fRot) * 0;
					break;
				case 4:
					pos = g_aParticle[nCntParticle].pos;
					fRot = 0.0f;
					fSpeed = 0.0f;
					move.x = sinf(fRot) * fSpeed;
					move.y = cosf(fRot) * fSpeed;
					break;
				case 5:
					//�ʒu�̐ݒ�
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					fSpeed = (float)(rand() % (2 * 50)) / 50 + 2;
					move.x = sinf(fRot) * fSpeed;
					move.y = cosf(fRot) * fSpeed;
					break;
				case 6:

					pos = D3DXVECTOR3(pBoss->pos.x + 0.0f, pBoss->pos.y + 15.0f, 0.0f);

					rRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;

					pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + sinf(rRot) * 90,
						g_aParticle[nCntParticle].pos.y + cosf(rRot) * 90, 0.0f);

					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					move.x = sinf(3) * 3;
					move.y = cosf(3) * 3;
					break;

				case 31:
					rRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;

					pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + sinf(rRot) * 40,
						g_aParticle[nCntParticle].pos.y + cosf(rRot) * 40, 0.0f);

					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					move.x = sinf(fRot) * 0;
					move.y = cosf(fRot) * 0;
					break;
				case 32:
					rRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;

					pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + sinf(rRot) * 50,
						g_aParticle[nCntParticle].pos.y + cosf(rRot) * 50, 0.0f);

					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					move.x = sinf(fRot) * 0;
					move.y = cosf(fRot) * 0;
					break;
				case 41:
					rRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;

					pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + sinf(rRot) * 20,
						g_aParticle[nCntParticle].pos.y + cosf(rRot) * 20, 0.0f);

					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					move.x = sinf(fRot) * 0;
					move.y = cosf(fRot) * 0;
					break;
				case 42:
					rRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;

					pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + sinf(rRot) * 30,
						g_aParticle[nCntParticle].pos.y + cosf(rRot) * 30, 0.0f);

					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					move.x = sinf(fRot) * 0;
					move.y = cosf(fRot) * 0;
					break;
				case 51:
					pos = g_aParticle[nCntParticle].pos;

					//�ړ��ʂ̐ݒ�
					fRot = (float)(rand() % ((int)(100 * 2 * D3DX_PI) + 1) - (int)(D3DX_PI * 100)) / (float)100;
					fSpeed = (float)(rand() % (2 * 50)) / 50 + 2;
					move.x = sinf(fRot) * fSpeed;
					move.y = cosf(fRot) * fSpeed;
					break;
				}

				switch (g_aParticle[nCntParticle].cType)
				{
				case 0:
					//�F
					col = D3DXCOLOR(1.0f, 0.2f, 0.3f, 1.0f);
					break;
				case 1:
					col = D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f);
					break;
				case 2:
					col = D3DXCOLOR(0.5f, 0.5f, 0.2f, 1.0f);
					break;
				case 3:
					col = D3DXCOLOR(0.5f, 0.2f, 0.3f, 1.0f);
					break;
				case 4:
					col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					break;
				case 5:
					col = D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f);
					break;
				case 6:
					col = D3DXCOLOR(0.1f, 1.0f, 0.3f, 1.0f);
					break;
				case 7:
					col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
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
					fRadius = 90;
					break;
				case 3:
					fRadius = 5;
					break;
				case 4:
					fRadius = 12;
					break;
				case 6:
					fRadius = 10;
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
					//����
					nLife = 30;
					break;
				case 3:
					//����
					nLife = 10;
					break;
				case 4:
					nLife = 10;
					break;
				case 6:
					nLife = 15;
					break;
				}
				
				if (g_aParticle[nCntParticle].pType == 6 && g_aParticle[nCntParticle].nType == 6)
				{
					//�G�t�F�N�g�ݒ�
					SetAuraEffect(pos, move, col, fRadius, nLife, 0);
				}
				else
				{
					//�G�t�F�N�g�ݒ�
					SetEffect(pos, move, col, fRadius, nLife, 0);
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