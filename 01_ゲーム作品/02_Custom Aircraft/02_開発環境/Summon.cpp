//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�G�̏���          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include"game.h"
#include"Summon.h"
#include"bullet.h"
#include"score.h"
#include"sound.h"
#include"player.h"
#include"enemy_bullet.h"
#include"particle.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_ENEMY	  (7) //�G�̎��
#define MAX_SUMMON	(128) //������
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void CollisionSummon(Summon *pSummon);
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DTEXTURE9 g_pTextureSummon[NUM_ENEMY] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSummon = NULL;		//���_�o�b�t�@�|�C���^
Summon g_aSummon[MAX_SUMMON];							//�G�̏��

int g_nCount10;											//��莞��
int g_nNumSummon;										//���݂���G�̐�
int g_nTotalSummon;										//�G�̑���
int g_CntTime10;
int p_summon;											//�������
int stand_time;											//�ҋ@����

int b_summon;
int nCntCharge1;										//�`���[�W����
int nCharge1;											//�`���[�W��
int nCntCharge2;										//�`���[�W����2
int nCharge2;											//�`���[�W��2
int nCntChargeShot;										//�`���[�W�V���b�g�̃J�E���g
int nCntMachineGun1;									//�@�֏e�̃J�E���g
int m_boss;

bool bswich;
bool bswich1;
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�G�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��============================��
//�b�@�@�@ �G�̏����������@�@ �@�b
//��============================��
void InitSummon(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnemy;
	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\ghost.png",
		&g_pTextureSummon[0]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy_a.png",
		&g_pTextureSummon[1]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy2.png",
		&g_pTextureSummon[2]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy3b.png",
		&g_pTextureSummon[3]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy4.png",
		&g_pTextureSummon[4]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy5.png",
		&g_pTextureSummon[5]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy6.png",
		&g_pTextureSummon[6]);

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SUMMON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSummon,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffSummon->Lock(0, 0, (void **)&pVtx, 0);

	//�G�̏��̏���������
	for (nCntEnemy = 0; nCntEnemy < MAX_SUMMON; nCntEnemy++)
	{
		g_aSummon[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSummon[nCntEnemy].move.x = 0.3f;
		g_aSummon[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����������������(Z�l���g�p)
		g_aSummon[nCntEnemy].nBullet = 0;
		g_aSummon[nCntEnemy].nLife = 1;
		g_aSummon[nCntEnemy].time = 1;
		g_aSummon[nCntEnemy].Tracking = 90;
		g_aSummon[nCntEnemy].nCntMove = 0;
		g_aSummon[nCntEnemy].nCntStop = 0;
		g_aSummon[nCntEnemy].bUse = false;
		g_aSummon[nCntEnemy].nStop = false;
		g_aSummon[nCntEnemy].Reversal = false;
		g_aSummon[nCntEnemy].m_switch = false;
		g_aSummon[nCntEnemy].bHit = false;
		g_aSummon[nCntEnemy].bDrw = false;
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(16.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(16.0f, 50.0f, 0.0f);
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�@�@rhw�̐ݒ�@�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�@ ���_�J���[ �@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	p_summon = 10;
	b_summon = 0;
	g_nNumSummon = 0;	//���݂���G�̐�
	g_nTotalSummon = 0;	//�G�̑���
	g_CntTime10 = 0;
	stand_time = 62;

	nCntMachineGun1 = 0;
	nCntCharge1 = 361;
	nCharge1 = 0;
	nCntCharge2 = 300;
	nCharge2 = 0;
	nCntChargeShot = 0;

	m_boss = 0;
	bswich = true;
	bswich1 = true;
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSummon->Unlock();

	//�G����ǂݍ���
	LoadSummon();
}
//��==========================��
//�b�@�@�@ �G�̏I�������@�@ �@�b
//��==========================��
void UninitSummon(void)
{
	int nCntEnemy;
	//�T�E���h�̒�~
	StopSound();
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_pTextureSummon[nCntEnemy] != NULL)
		{
			g_pTextureSummon[nCntEnemy]->Release();
			g_pTextureSummon[nCntEnemy] = NULL;
		}
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxBuffSummon != NULL)
	{
		g_pVtxBuffSummon->Release();
		g_pVtxBuffSummon = NULL;
	}
}
//��==========================��
//�b�@�@�@ �G�̍X�V�����@�@ �@�b
//��==========================��
void UpdateSummon(void)
{
	int nCntEnemy;		//�G�J�E���^
	Boss *pBoss = GetBoss(); //�G�̏��ւ̃|�C���^

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffSummon->Lock(0, 0, (void **)&pVtx, 0);

	g_nCount10++;
	for (nCntEnemy = 0; nCntEnemy < MAX_SUMMON; nCntEnemy++, pVtx += 4)
	{
		//��ԑJ�ڏ���
		if (g_aSummon[nCntEnemy].bUse == true)
		{
			CollisionSummon(&g_aSummon[nCntEnemy]);

			switch (g_aSummon[nCntEnemy].m_pattern)
			{
				//=============================
				//�ォ��o������ړ��p�^�[��
				//=============================

			case 0:
				if (g_aSummon[nCntEnemy].nStop == false)
				{
					if (g_aSummon[nCntEnemy].Reversal == false)
					{
						g_aSummon[nCntEnemy].pos.x -= 2;
						if (g_aSummon[nCntEnemy].pos.x < 200)
						{
							g_aSummon[nCntEnemy].pos.x = 200;
							g_aSummon[nCntEnemy].nStop = true;
						}
					}
					else if (g_aSummon[nCntEnemy].Reversal == true)
					{
						g_aSummon[nCntEnemy].pos.x += 2;
						if (g_aSummon[nCntEnemy].pos.x > 800)
						{
							g_aSummon[nCntEnemy].pos.x = 800;
							g_aSummon[nCntEnemy].nStop = true;
						}
					}
				}
				else if (g_aSummon[nCntEnemy].nStop == true)
				{
					g_aSummon[nCntEnemy].nCntStop++;
					if (g_aSummon[nCntEnemy].nCntStop == 10)
					{
						if (g_aSummon[nCntEnemy].Reversal == false)
						{
							g_aSummon[nCntEnemy].Reversal = true;
						}
						else if (g_aSummon[nCntEnemy].Reversal == true)
						{
							g_aSummon[nCntEnemy].Reversal = false;
						}
						g_aSummon[nCntEnemy].nStop = false;
						g_aSummon[nCntEnemy].nCntStop = 0;
					}
				}
				break;
			case 1:
				if (g_aSummon[nCntEnemy].nStop == false)
				{
					if (g_aSummon[nCntEnemy].Reversal == false)
					{
						g_aSummon[nCntEnemy].pos.y -= 2;
						if (g_aSummon[nCntEnemy].pos.y < 100)
						{
							g_aSummon[nCntEnemy].pos.y = 102;
							g_aSummon[nCntEnemy].nStop = true;
						}
					}
					else if (g_aSummon[nCntEnemy].Reversal == true)
					{
						g_aSummon[nCntEnemy].pos.y += 2;
						if (g_aSummon[nCntEnemy].pos.y > 600)
						{
							g_aSummon[nCntEnemy].pos.y = 598;
							g_aSummon[nCntEnemy].nStop = true;
						}
					}
				}
				else if (g_aSummon[nCntEnemy].nStop == true)
				{
					g_aSummon[nCntEnemy].nCntStop++;
					if (g_aSummon[nCntEnemy].nCntStop == 10)
					{
						if (g_aSummon[nCntEnemy].Reversal == false)
						{
							g_aSummon[nCntEnemy].Reversal = true;
						}
						else if (g_aSummon[nCntEnemy].Reversal == true)
						{
							g_aSummon[nCntEnemy].Reversal = false;
						}
						g_aSummon[nCntEnemy].nStop = false;
						g_aSummon[nCntEnemy].nCntStop = 0;
					}
				}
					break;
			case 2:
				if (g_aSummon[nCntEnemy].Reversal == false)
				{
					g_aSummon[nCntEnemy].pos.x -= 2;
					if (g_aSummon[nCntEnemy].pos.x< 100)
					{
						g_aSummon[nCntEnemy].pos.x= 101;
						g_aSummon[nCntEnemy].Reversal = true;
					}
				}
				else if (g_aSummon[nCntEnemy].Reversal == true)
				{
					g_aSummon[nCntEnemy].pos.x += 2;
					if (g_aSummon[nCntEnemy].pos.x > 300)
					{
						g_aSummon[nCntEnemy].pos.x = 299;
						g_aSummon[nCntEnemy].Reversal = false;
					}
				}
				break;
			case 3:
				if (g_aSummon[nCntEnemy].Reversal == false)
				{
					g_aSummon[nCntEnemy].pos.x -= 2;
					if (g_aSummon[nCntEnemy].pos.x< 700)
					{
						g_aSummon[nCntEnemy].pos.x = 701;
						g_aSummon[nCntEnemy].Reversal = true;
					}
				}
				else if (g_aSummon[nCntEnemy].Reversal == true)
				{
					g_aSummon[nCntEnemy].pos.x += 2;
					if (g_aSummon[nCntEnemy].pos.x > 900)
					{
						g_aSummon[nCntEnemy].pos.x = 899;
						g_aSummon[nCntEnemy].Reversal = false;
					}
				}
				break;
			case 99:
				g_aSummon[nCntEnemy].pos.x += 0;
				g_aSummon[nCntEnemy].pos.y += 0;
				break;
			}

			//��ʂ���͂ݏo������G���\���ɂ���
			if (g_aSummon[nCntEnemy].pos.x < -30 || g_aSummon[nCntEnemy].pos.x > SCREEN_WIDTH - 220)
			{
				//X���W���͈͊O�̏ꍇ
				g_aSummon[nCntEnemy].bDrw = false; //�g�p���Ă��Ȃ���Ԃɂ���
				g_aSummon[nCntEnemy].bHit = false;
				g_aSummon[nCntEnemy].bUse = false;
			}
			if (g_aSummon[nCntEnemy].pos.y < -45 || g_aSummon[nCntEnemy].pos.y > SCREEN_HEIGHT)
			{
				//Y���W���͈͊O�̏ꍇ
				g_aSummon[nCntEnemy].bDrw = false; //�g�p���Ă��Ȃ���Ԃɂ���
				g_aSummon[nCntEnemy].bHit = false;
				g_aSummon[nCntEnemy].bUse = false;
			}

			switch (g_aSummon[nCntEnemy].state)
			{
			case SUMMONSTATE_NORMAL:
				break;

			case ENEMYSTATE_DAMAGE:
				g_aSummon[nCntEnemy].nCounterState--;

				if (g_aSummon[nCntEnemy].nCounterState <= 0)
				{
					g_aSummon[nCntEnemy].state = SUMMONSTATE_NORMAL;

					if (g_aSummon[16].bHit == true && g_aSummon[17].bHit == true)
					{
						g_aSummon[16].bDrw = true;
						g_aSummon[17].bDrw = true;
					}
					else
					{
						g_aSummon[nCntEnemy].bDrw = true;
					}
					//���\�\�\�\�\�\�\�\�\�\�\�\��
					//�b�@�@�@ ���_�J���[ �@�@�@�b
					//���\�\�\�\�\�\�\�\�\�\�\�\��
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�|���S����ʏ�F�ɖ߂�
				}
				else
				{
					if(g_aSummon[16].bHit == true && g_aSummon[17].bHit == true)
					{
						g_aSummon[16].bDrw = g_aSummon[16].bDrw ? false : true;
						g_aSummon[17].bDrw = g_aSummon[17].bDrw ? false : true;
					}
					else
					{
						g_aSummon[nCntEnemy].bDrw = g_aSummon[nCntEnemy].bDrw ? false : true;
					}
				}
				break;
			}


			//g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			if (g_aSummon[nCntEnemy].nType == 5)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos.x = g_aSummon[nCntEnemy].pos.x - SIZE_BOSS;
				pVtx[0].pos.y = g_aSummon[nCntEnemy].pos.y - SIZE_BOSS;
				pVtx[0].pos.z = 0;
				pVtx[1].pos.x = g_aSummon[nCntEnemy].pos.x + SIZE_BOSS;
				pVtx[1].pos.y = g_aSummon[nCntEnemy].pos.y - SIZE_BOSS;
				pVtx[1].pos.z = 0;
				pVtx[2].pos.x = g_aSummon[nCntEnemy].pos.x - SIZE_BOSS;
				pVtx[2].pos.y = g_aSummon[nCntEnemy].pos.y + SIZE_BOSS;
				pVtx[2].pos.z = 0;
				pVtx[3].pos.x = g_aSummon[nCntEnemy].pos.x + SIZE_BOSS;
				pVtx[3].pos.y = g_aSummon[nCntEnemy].pos.y + SIZE_BOSS;
				pVtx[3].pos.z = 0;
			}
			else if (g_aSummon[nCntEnemy].nType == 6)
			{
				pVtx[0].pos.x = g_aSummon[nCntEnemy].pos.x - SIZE_ENEMY;
				pVtx[0].pos.y = g_aSummon[nCntEnemy].pos.y - SIZE_ENEMY;
				pVtx[0].pos.z = 0;
				pVtx[1].pos.x = g_aSummon[nCntEnemy].pos.x + SIZE_ENEMY;
				pVtx[1].pos.y = g_aSummon[nCntEnemy].pos.y - SIZE_ENEMY;
				pVtx[1].pos.z = 0;
				pVtx[2].pos.x = g_aSummon[nCntEnemy].pos.x - SIZE_ENEMY;
				pVtx[2].pos.y = g_aSummon[nCntEnemy].pos.y + SIZE_ENEMY;
				pVtx[2].pos.z = 0;
				pVtx[3].pos.x = g_aSummon[nCntEnemy].pos.x + SIZE_ENEMY;
				pVtx[3].pos.y = g_aSummon[nCntEnemy].pos.y + SIZE_ENEMY;
				pVtx[3].pos.z = 0;
			}
			else
			{
				//���_���W�̐ݒ�
				pVtx[0].pos.x = g_aSummon[nCntEnemy].pos.x - SIZE_ENEMY / 2;
				pVtx[0].pos.y = g_aSummon[nCntEnemy].pos.y - SIZE_ENEMY / 2;
				pVtx[0].pos.z = 0;
				pVtx[1].pos.x = g_aSummon[nCntEnemy].pos.x + SIZE_ENEMY / 2;
				pVtx[1].pos.y = g_aSummon[nCntEnemy].pos.y - SIZE_ENEMY / 2;
				pVtx[1].pos.z = 0;
				pVtx[2].pos.x = g_aSummon[nCntEnemy].pos.x - SIZE_ENEMY / 2;
				pVtx[2].pos.y = g_aSummon[nCntEnemy].pos.y + SIZE_ENEMY / 2;
				pVtx[2].pos.z = 0;
				pVtx[3].pos.x = g_aSummon[nCntEnemy].pos.x + SIZE_ENEMY / 2;
				pVtx[3].pos.y = g_aSummon[nCntEnemy].pos.y + SIZE_ENEMY / 2;
				pVtx[3].pos.z = 0;
			}

			if (g_aSummon[nCntEnemy].bHit == true)
			{
				switch (g_aSummon[nCntEnemy].s_pattern)
				{
				case BULLETTYPE_E_LINE:
					g_aSummon[nCntEnemy].nBullet++;//�J�E���^�[�����Z
					if ((g_aSummon[nCntEnemy].nBullet % 60) == 0)
					{
						SetEnemyBullet(g_aSummon[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_LINE, g_aSummon[nCntEnemy].sType);
					}
					break;

				case BULLETTYPE_E_AIM:
					g_aSummon[nCntEnemy].nBullet++;//�J�E���^�[�����Z
					if ((g_aSummon[nCntEnemy].nBullet % 90) == 0)
					{
						SetEnemyBullet(g_aSummon[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_AIM, g_aSummon[nCntEnemy].sType);
					}
					break;

				case BULLETTYPE_E_HOMING:
					g_aSummon[nCntEnemy].nBullet++;//�J�E���^�[�����Z
					if ((g_aSummon[nCntEnemy].nBullet % 90) == 0)
					{
						SetEnemyBullet(g_aSummon[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_HOMING, g_aSummon[nCntEnemy].sType);
					}
					break;
				case BULLETTYPE_E_CHARGE:

					//�`���[�W��ԂȂ�J�E���g�����炷
					if (nCntCharge1 <= 0)
					{
						g_aSummon[nCntEnemy].s_pattern = BULLETTYPE_E_MACHINEGUN;
						nCntMachineGun1 = 0;
					}
					else if (nCntCharge1 <= 60)
					{
						nCntCharge1--;
						nCharge1++;
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 5);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 32);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 31);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 3);
					}
					else if (nCntCharge1 <= 120 && nCntCharge1 >= 61)
					{
						nCntCharge1--;
						nCharge1++;
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 5);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 31);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 3);

					}
					else if (nCntCharge1 <= 300 && nCntCharge1 >= 121)
					{
						nCntCharge1--;
						nCharge1++;
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 5);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 3);
					}
					else
					{
						nCntCharge1--;
					}

					break;
				case BULLETTYPE_E_MACHINEGUN:

					if (nCntMachineGun1 <= 310)
					{
						nCntMachineGun1++; //�J�E���g�����Z
						nCharge1--;

						//30��Ɉ�񔭎ˁB310�܂łȂ̂�10�����ˁB
						if ((nCntMachineGun1 % 30) == 0)
						{
							if (bswich == false)
							{
								bswich = true;
								SetEnemyBullet(D3DXVECTOR3(g_aSummon[16].pos.x + 0.0f, g_aSummon[16].pos.y + 60.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_MACHINEGUN, g_aSummon[16].sType);
							}
							else if (bswich == true)
							{
								bswich = false;
								SetEnemyBullet(D3DXVECTOR3(g_aSummon[17].pos.x + 0.0f, g_aSummon[17].pos.y + 60.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_MACHINEGUN, g_aSummon[17].sType);
							}
						}
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 5);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 3);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 31);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 7, 32);
					}
					else
					{
						nCntCharge1 = 461;
						nCharge1 = 0;
						g_aSummon[nCntEnemy].s_pattern = BULLETTYPE_E_CHARGE;
					}
					break;
				case BULLETTYPE_E_CHARGE1:
					if (nCntCharge2 <= 0)
					{
						g_aSummon[nCntEnemy].s_pattern = BULLETTYPE_E_CHARGE_SHOT;
						nCntChargeShot = 0;
					}
					else if (nCntCharge2 <= 30)
					{
						nCntCharge2--;
						nCharge2++;

						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 51);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 31);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 32);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 3);
					}
					else if (nCntCharge2 <= 60 && nCntCharge2 >= 31)
					{
						nCntCharge2--;
						nCharge2++;

						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 51);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 31);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 3);
					}
					else if(nCntCharge2 <= 180 && nCntCharge2 >= 61)
					{
						nCntCharge2--;
						nCharge2++;
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 51);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 3);
					}
					else
					{
						nCntCharge2--;
					}
					break;
				case BULLETTYPE_E_CHARGE_SHOT:

					//�`���[�W��ԂȂ�J�E���g�����炷
					if (nCntChargeShot <= 120)
					{
						nCharge2--;
						nCntChargeShot++;
						if ((nCntChargeShot % 30) == 0)
						{
							if (bswich1 == false)
							{
								if (g_aSummon[21].bHit == true)
								{
									bswich1 = true;
								}
								SetEnemyBullet(D3DXVECTOR3(g_aSummon[20].pos.x + 0.0f, g_aSummon[20].pos.y + 60.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_CHARGE_SHOT, g_aSummon[20].sType);
							}
							else if (bswich1 == true)
							{
								if (g_aSummon[20].bHit == true)
								{
									bswich1 = false;
								}
								SetEnemyBullet(D3DXVECTOR3(g_aSummon[21].pos.x + 0.0f, g_aSummon[21].pos.y + 60.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_CHARGE_SHOT, g_aSummon[21].sType);
							}
						}
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 51);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 3);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 31);
						SetParticle(D3DXVECTOR3(g_aSummon[nCntEnemy].pos.x + 0.0f, g_aSummon[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 1, 32);

					}
					else
					{
						nCntCharge2 = 300;
						nCharge1 = 0;
						g_aSummon[nCntEnemy].s_pattern = BULLETTYPE_E_CHARGE1;
					}
					break;
				case 99:
					break;
				}
			}
			if (g_aSummon[nCntEnemy].bTime == true)
			{
				stand_time--;
				if (stand_time <= 0)
				{
					if (p_summon == 0)
					{
						g_aSummon[0].bHit = true; g_aSummon[0].bTime = false;
						g_aSummon[1].bHit = true; g_aSummon[1].bTime = false;
						g_aSummon[2].bHit = true; g_aSummon[2].bTime = false;
						g_aSummon[3].bHit = true; g_aSummon[3].bTime = false;

						g_aSummon[0].m_pattern = 1;
						g_aSummon[1].m_pattern = 1;
						g_aSummon[2].m_pattern = 0;
						g_aSummon[3].m_pattern = 0;

					}
					else if (p_summon == 1)
					{
						g_aSummon[7]. bHit = true; g_aSummon[7]. bTime = false;
						g_aSummon[8]. bHit = true; g_aSummon[8]. bTime = false;
						g_aSummon[9]. bHit = true; g_aSummon[9]. bTime = false;
						g_aSummon[10].bHit = true; g_aSummon[10].bTime = false;
						g_aSummon[11].bHit = true; g_aSummon[11].bTime = false;
						g_aSummon[12].bHit = true; g_aSummon[12].bTime = false;
						g_aSummon[13].bHit = true; g_aSummon[13].bTime = false;
						g_aSummon[14].bHit = true; g_aSummon[14].bTime = false;
						g_aSummon[15].bHit = true; g_aSummon[15].bTime = false;


						g_aSummon[14].m_pattern = 2;
						g_aSummon[15].m_pattern = 3;
					}
					else if (p_summon == 2)
					{
						g_aSummon[7].bHit = true; g_aSummon[7].bTime = false;g_aSummon[7].nLife = 15;
						g_aSummon[8].bHit = true; g_aSummon[8].bTime = false;g_aSummon[8].nLife = 15;
						g_aSummon[9].bHit = true; g_aSummon[9].bTime = false;g_aSummon[9].nLife = 15;
						g_aSummon[18].bHit = true; g_aSummon[18].bTime = false;
						g_aSummon[19].bHit = true; g_aSummon[19].bTime = false;
						g_aSummon[20].bHit = true; g_aSummon[20].bTime = false;
						g_aSummon[21].bHit = true; g_aSummon[21].bTime = false;
					}
					else if (p_summon == 3)
					{
						g_aSummon[16].bHit = true; g_aSummon[16].bTime = false;
						g_aSummon[17].bHit = true; g_aSummon[17].bTime = false;

						nCntCharge1 = 541;
						nCharge1 = 0;
					}

				}
				else if (stand_time <= 10)
				{
					if (p_summon == 0)
					{
						g_aSummon[0].bDrw = true;
						g_aSummon[1].bDrw = true;
						g_aSummon[2].bDrw = true;
						g_aSummon[3].bDrw = true;
					}
					else if (p_summon == 1)
					{
						g_aSummon[7]. bDrw = true; 
						g_aSummon[8]. bDrw = true; 
						g_aSummon[9]. bDrw = true; 
						g_aSummon[10].bDrw = true;
						g_aSummon[11].bDrw = true;
						g_aSummon[12].bDrw = true;
						g_aSummon[13].bDrw = true;
						g_aSummon[14].bDrw = true;
						g_aSummon[15].bDrw = true;
					}
					else if (p_summon == 2)
					{
						g_aSummon[7].bDrw = true;
						g_aSummon[8].bDrw = true;
						g_aSummon[9].bDrw = true;
						g_aSummon[18].bDrw = true;
						g_aSummon[19].bDrw = true;
						g_aSummon[20].bDrw = true;
						g_aSummon[21].bDrw = true;
					}
					else if (p_summon == 3)
					{
						g_aSummon[16].bDrw = true;
						g_aSummon[17].bDrw = true;
					}
				}
				else if (stand_time == 60)
				{
					if (p_summon == 0)
					{
						SetParticle(g_aSummon[0].pos, 1, 30, 90.0f, 1, 0);
						SetParticle(g_aSummon[1].pos, 1, 30, 90.0f, 1, 0);
						SetParticle(g_aSummon[2].pos, 1, 30, 90.0f, 1, 0);
						SetParticle(g_aSummon[3].pos, 1, 30, 90.0f, 1, 0);
					}
					else if (p_summon == 1)
					{
						SetParticle(g_aSummon[7]. pos, 1, 30, 90.0f, 5, 0);
						SetParticle(g_aSummon[8]. pos, 1, 30, 90.0f, 5, 0);
						SetParticle(g_aSummon[9]. pos, 1, 30, 90.0f, 5, 0);
						SetParticle(g_aSummon[10].pos, 1, 30, 90.0f, 5, 0);
						SetParticle(g_aSummon[11].pos, 1, 30, 90.0f, 5, 0);
						SetParticle(g_aSummon[12].pos, 1, 30, 90.0f, 1, 0);
						SetParticle(g_aSummon[13].pos, 1, 30, 90.0f, 1, 0);
						SetParticle(g_aSummon[14].pos, 1, 30, 90.0f, 1, 0);
						SetParticle(g_aSummon[15].pos, 1, 30, 90.0f, 1, 0);
					}
					else if (p_summon == 2)
					{
						SetParticle(g_aSummon[7].pos, 1, 30, 90.0f, 5, 0);
						SetParticle(g_aSummon[8].pos, 1, 30, 90.0f, 5, 0);
						SetParticle(g_aSummon[9].pos, 1, 30, 90.0f, 5, 0);
						SetParticle(g_aSummon[18].pos, 1, 30, 90.0f, 2, 0);
						SetParticle(g_aSummon[19].pos, 1, 30, 90.0f, 2, 0);
						SetParticle(g_aSummon[20].pos, 1, 30, 90.0f, 1, 0);
						SetParticle(g_aSummon[21].pos, 1, 30, 90.0f, 1, 0);
					}
					else if (p_summon == 3)
					{
						SetParticle(g_aSummon[16].pos, 1, 30, 90.0f, 4, 0);
						SetParticle(g_aSummon[17].pos, 1, 30, 90.0f, 4, 0);
					}
				}
		}

			if (b_summon >= 2 && b_summon <= 6)
			{
				if (g_aSummon[10].bUse == true)
				{
					SetParticle(g_aSummon[10].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[10].bHit = false; g_aSummon[10].bTime = false; g_aSummon[10].bDrw = false; g_aSummon[10].bUse = false;
					AddScore(g_aSummon[10].score * (int)1.5f);
				}
				if (g_aSummon[11].bUse == true)
				{
					SetParticle(g_aSummon[11].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[11].bHit = false; g_aSummon[11].bTime = false; g_aSummon[11].bDrw = false; g_aSummon[11].bUse = false;
					AddScore(g_aSummon[11].score * (int)1.5f);
				}
				if (g_aSummon[12].bUse == true)
				{
					SetParticle(g_aSummon[12].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[12].bHit = false; g_aSummon[12].bTime = false; g_aSummon[12].bDrw = false; g_aSummon[12].bUse = false;
					AddScore(g_aSummon[12].score * (int)1.5f);
				}
				if (g_aSummon[13].bUse == true)
				{
					SetParticle(g_aSummon[13].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[13].bHit = false; g_aSummon[13].bTime = false; g_aSummon[13].bDrw = false; g_aSummon[13].bUse = false;
					AddScore(g_aSummon[13].score * (int)1.5f);
				}
				if (g_aSummon[14].bUse == true)
				{
					SetParticle(g_aSummon[14].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[14].bHit = false; g_aSummon[14].bTime = false; g_aSummon[14].bDrw = false; g_aSummon[14].bUse = false;
					AddScore(g_aSummon[14].score * (int)1.5f);
				}
				if (g_aSummon[15].bUse == true)
				{
					SetParticle(g_aSummon[15].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[15].bHit = false; g_aSummon[15].bTime = false; g_aSummon[15].bDrw = false; g_aSummon[15].bUse = false;
					AddScore(g_aSummon[15].score * (int)1.5f);
				}

				if (g_aSummon[10].bUse == false && g_aSummon[11].bUse == false && 
					g_aSummon[12].bUse == false && g_aSummon[13].bUse == false && 
					g_aSummon[14].bUse == false && g_aSummon[15].bUse == false)
				{
					pBoss[2].nReset = 1;
					EnemySummon(2);
					b_summon = 7;
				}
			}
			else if (b_summon >= 9 && b_summon <= 14)
			{
				if (g_aSummon[7].bUse == true)
				{
					SetParticle(g_aSummon[7].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[7].bHit = false; g_aSummon[7].bTime = false; g_aSummon[7].bDrw = false; g_aSummon[7].bUse = false;
					AddScore(g_aSummon[7].score * (int)1.5f);
				}
				if (g_aSummon[8].bUse == true)
				{
					SetParticle(g_aSummon[8].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[8].bHit = false; g_aSummon[8].bTime = false; g_aSummon[8].bDrw = false; g_aSummon[8].bUse = false;
					AddScore(g_aSummon[8].score * (int)1.5f);
				}
				if (g_aSummon[9].bUse == true)
				{
					SetParticle(g_aSummon[9].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[9].bHit = false; g_aSummon[9].bTime = false; g_aSummon[9].bDrw = false; g_aSummon[9].bUse = false;
					AddScore(g_aSummon[9].score * (int)1.5f);
				}
				if (g_aSummon[18].bUse == true)
				{
					SetParticle(g_aSummon[18].pos, 1, 30, 90.0f, 2, 0);
					g_aSummon[18].bHit = false; g_aSummon[18].bTime = false; g_aSummon[18].bDrw = false; g_aSummon[18].bUse = false;
					AddScore(g_aSummon[18].score * (int)1.5f);
				}
				if (g_aSummon[19].bUse == true)
				{
					SetParticle(g_aSummon[19].pos, 1, 30, 90.0f, 2, 0);
					g_aSummon[19].bHit = false; g_aSummon[19].bTime = false; g_aSummon[19].bDrw = false; g_aSummon[19].bUse = false;
					AddScore(g_aSummon[19].score * (int)1.5f);
				}
				if (g_aSummon[20].bUse == true)
				{
					SetParticle(g_aSummon[20].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[20].bHit = false; g_aSummon[20].bTime = false; g_aSummon[20].bDrw = false; g_aSummon[20].bUse = false;
					AddScore(g_aSummon[20].score * (int)1.5f);
				}
				if (g_aSummon[21].bUse == true)
				{
					SetParticle(g_aSummon[21].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[21].bHit = false; g_aSummon[21].bTime = false; g_aSummon[21].bDrw = false; g_aSummon[21].bUse = false;
					AddScore(g_aSummon[21].score * (int)1.5f);
				}


				if (g_aSummon[7].bUse == false && g_aSummon[8].bUse == false && 
					g_aSummon[9].bUse == false && g_aSummon[18].bUse == false &&
					g_aSummon[19].bUse == false && g_aSummon[20].bUse == false && 
					g_aSummon[21].bUse == false)
				{
					pBoss[2].nReset = 1;
					EnemySummon(3);
					b_summon = 15;
				}
			}

			if (GetNumBoss() == 1)
			{
				PlaySound(SOUND_LABEL_SE_SUMMON);

				if (g_aSummon[0].bUse == true)
				{
					SetParticle(g_aSummon[0].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[0].bHit = false; g_aSummon[0].bTime = false; g_aSummon[0].bDrw = false; g_aSummon[0].bUse = false;
					AddScore(g_aSummon[0].score * (int)1.5f);
				}
				else if (g_aSummon[1].bUse == true)
				{
					SetParticle(g_aSummon[1].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[1].bHit = false; g_aSummon[1].bTime = false; g_aSummon[1].bDrw = false; g_aSummon[1].bUse = false;
					AddScore(g_aSummon[1].score * (int)1.5f);
				}
				else if (g_aSummon[2].bUse == true)
				{
					SetParticle(g_aSummon[2].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[2].bHit = false; g_aSummon[2].bTime = false; g_aSummon[2].bDrw = false; g_aSummon[2].bUse = false;
					AddScore(g_aSummon[2].score * (int)1.5f);
				}
				else if (g_aSummon[3].bUse == true)
				{
					SetParticle(g_aSummon[3].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[3].bHit = false; g_aSummon[3].bTime = false; g_aSummon[3].bDrw = false; g_aSummon[3].bUse = false;
					AddScore(g_aSummon[3].score * (int)1.5f);
				}
				else if (g_aSummon[4].bUse == true)
				{
					SetParticle(g_aSummon[4].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[4].bHit = false; g_aSummon[4].bTime = false; g_aSummon[4].bDrw = false; g_aSummon[4].bUse = false;
					AddScore(g_aSummon[4].score * (int)1.5f);
				}
				else if (g_aSummon[5].bUse == true)
				{
					SetParticle(g_aSummon[5].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[5].bHit = false; g_aSummon[5].bTime = false; g_aSummon[5].bDrw = false; g_aSummon[5].bUse = false;
					AddScore(g_aSummon[5].score * (int)1.5f);
				}
				else if (g_aSummon[6].bUse == true)
				{
					SetParticle(g_aSummon[6].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[6].bHit = false; g_aSummon[6].bTime = false; g_aSummon[6].bDrw = false; g_aSummon[6].bUse = false;
					AddScore(g_aSummon[6].score * (int)1.5f);
				}
			}
			else if (GetNumBoss() == 0)
			{
				PlaySound(SOUND_LABEL_SE_SUMMON);

				if (g_aSummon[7].bUse == true)
				{
					SetParticle(g_aSummon[7].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[7].bHit = false; g_aSummon[7].bTime = false; g_aSummon[7].bDrw = false; g_aSummon[7].bUse = false;
					AddScore(g_aSummon[7].score * (int)1.5f);
				}
				else if (g_aSummon[8].bUse == true)
				{
					SetParticle(g_aSummon[8].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[8].bHit = false; g_aSummon[8].bTime = false; g_aSummon[8].bDrw = false; g_aSummon[8].bUse = false;
					AddScore(g_aSummon[8].score * (int)1.5f);
				}
				else if (g_aSummon[9].bUse == true)
				{
					SetParticle(g_aSummon[9].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[9].bHit = false; g_aSummon[9].bTime = false; g_aSummon[9].bDrw = false; g_aSummon[9].bUse = false;
					AddScore(g_aSummon[9].score * (int)1.5f);
				}
				else if (g_aSummon[10].bUse == true)
				{
					SetParticle(g_aSummon[10].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[10].bHit = false; g_aSummon[10].bTime = false; g_aSummon[10].bDrw = false; g_aSummon[10].bUse = false;
					AddScore(g_aSummon[10].score * (int)1.5f);
				}
				else if (g_aSummon[11].bUse == true)
				{
					SetParticle(g_aSummon[11].pos, 1, 30, 90.0f, 5, 0);
					g_aSummon[11].bHit = false; g_aSummon[11].bTime = false; g_aSummon[11].bDrw = false; g_aSummon[11].bUse = false;
					AddScore(g_aSummon[11].score * (int)1.5f);
				}
				else if (g_aSummon[12].bUse == true)
				{
					SetParticle(g_aSummon[12].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[12].bHit = false; g_aSummon[12].bTime = false; g_aSummon[12].bDrw = false; g_aSummon[12].bUse = false;
					AddScore(g_aSummon[12].score * (int)1.5f);
				}
				else if (g_aSummon[13].bUse == true)
				{
					SetParticle(g_aSummon[13].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[13].bHit = false; g_aSummon[13].bTime = false; g_aSummon[13].bDrw = false; g_aSummon[13].bUse = false;
					AddScore(g_aSummon[13].score * (int)1.5f);
				}
				else if (g_aSummon[14].bUse == true)
				{
					SetParticle(g_aSummon[14].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[14].bHit = false; g_aSummon[14].bTime = false; g_aSummon[14].bDrw = false; g_aSummon[14].bUse = false;
					AddScore(g_aSummon[14].score * (int)1.5f);
				}
				else if (g_aSummon[15].bUse == true)
				{
					SetParticle(g_aSummon[15].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[15].bHit = false; g_aSummon[15].bTime = false; g_aSummon[15].bDrw = false; g_aSummon[15].bUse = false;
					AddScore(g_aSummon[15].score * (int)1.5f);
				}
				else if (g_aSummon[16].bUse == true)
				{
					SetParticle(g_aSummon[16].pos, 1, 30, 90.0f, 4, 0);
					g_aSummon[16].bHit = false; g_aSummon[16].bTime = false; g_aSummon[16].bDrw = false; g_aSummon[16].bUse = false;
					AddScore(g_aSummon[16].score * (int)1.5f);
				}
				else if (g_aSummon[17].bUse == true)
				{
					SetParticle(g_aSummon[17].pos, 1, 30, 90.0f, 4, 0);
					g_aSummon[17].bHit = false; g_aSummon[17].bTime = false; g_aSummon[17].bDrw = false; g_aSummon[17].bUse = false;
					AddScore(g_aSummon[17].score * (int)1.5f);
				}
				else if (g_aSummon[18].bUse == true)
				{
					SetParticle(g_aSummon[18].pos, 1, 30, 90.0f, 2, 0);
					g_aSummon[18].bHit = false; g_aSummon[18].bTime = false; g_aSummon[18].bDrw = false; g_aSummon[18].bUse = false;
					AddScore(g_aSummon[18].score * (int)1.5f);
				}
				else if (g_aSummon[19].bUse == true)
				{
					SetParticle(g_aSummon[19].pos, 1, 30, 90.0f, 2, 0);
					g_aSummon[19].bHit = false; g_aSummon[19].bTime = false; g_aSummon[19].bDrw = false; g_aSummon[19].bUse = false;
					AddScore(g_aSummon[19].score * (int)1.5f);
				}
				else if (g_aSummon[20].bUse == true)
				{
					SetParticle(g_aSummon[20].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[20].bHit = false; g_aSummon[20].bTime = false; g_aSummon[20].bDrw = false; g_aSummon[20].bUse = false;
					AddScore(g_aSummon[20].score * (int)1.5f);
				}
				else if (g_aSummon[21].bUse == true)
				{
					SetParticle(g_aSummon[21].pos, 1, 30, 90.0f, 1, 0);
					g_aSummon[21].bHit = false; g_aSummon[21].bTime = false; g_aSummon[21].bDrw = false; g_aSummon[21].bUse = false;
					AddScore(g_aSummon[21].score * (int)1.5f);
				}
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSummon->Unlock();
}
//��==========================��
//�b�@�@�@ �G�̕`�揈���@�@ �@�b
//��==========================��
void DrawSummon(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnemy;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSummon, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntEnemy = 0; nCntEnemy < MAX_SUMMON; nCntEnemy++)
	{
		if (g_aSummon[nCntEnemy].bDrw == true)
		{//�G���g�p����Ă���

			pDevice->SetTexture(0, g_pTextureSummon[g_aSummon[nCntEnemy].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//��==========================��
//�b�@�@�@ �G�̔��菈���@�@ �@�b
//��==========================��

//�G�̓����蔻��
void CollisionSummon(Summon *pSummon)
{
	int nCntEnemy;

	Player *pPlayer = Getplayer(); //�v���C���[�̏��ւ̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < MAX_SUMMON; nCntEnemy++, pSummon++)
	{
		if (pSummon->bHit == true)
		{//�G���g�p����Ă���
			if (pSummon->pos.x >= pPlayer->pos.x - 32
				&& pSummon->pos.x <= pPlayer->pos.x + 32
				&& pSummon->pos.y >= pPlayer->pos.y - 32
				&& pSummon->pos.y <= pPlayer->pos.y + 32)
			{//�G�ƃv���C���[����������

				HitPlayer(nCntEnemy, 1);
			}
		}
	}
}
//��============================��
//�b�@�@�@ �G�̃q�b�g�����@�@ �@�b
//��============================��
void HitSummon(int nCntSummon, int nDamage)
{
	if (g_aSummon[nCntSummon].bHit == true)
	{
		if (g_aSummon[16].bHit == true && g_aSummon[17].bHit == true)
		{
			g_aSummon[16].nLife -= nDamage;
			g_aSummon[17].nLife -= nDamage;
		}
		else
		{
			g_aSummon[nCntSummon].nLife -= nDamage;
		}

		if (g_aSummon[nCntSummon].nLife <= 0)//�G�̗̑͂��Ȃ��Ȃ���
		{
				if (g_aSummon[12].bUse == true && g_aSummon[12].nLife == 0)
				{
					if (g_aSummon[14].bUse == true)
					{
						b_summon++;
					}
					g_aSummon[12].bUse = false; g_aSummon[12].bDrw = false; g_aSummon[12].bHit = false;
				}
				if (g_aSummon[14].bUse == true && g_aSummon[14].nLife == 0)
				{
					if (g_aSummon[12].bUse == true)
					{
						b_summon++;
					}
					g_aSummon[14].bUse = false; g_aSummon[14].bDrw = false; g_aSummon[14].bHit = false;
				}

				if (g_aSummon[13].bUse == true && g_aSummon[13].nLife == 0)
				{
					if (g_aSummon[15].bUse == true)
					{
						b_summon++;
					}
					g_aSummon[13].bUse = false; g_aSummon[13].bDrw = false; g_aSummon[13].bHit = false;
				}
				if (g_aSummon[15].bUse == true && g_aSummon[15].nLife == 0)
				{
					if (g_aSummon[13].bUse == true)
					{
						b_summon++;
					}
					g_aSummon[15].bUse = false; g_aSummon[15].bDrw = false; g_aSummon[15].bHit = false;
				}

				if (g_aSummon[18].bUse == true && g_aSummon[18].nLife == 0)
				{
					if (g_aSummon[20].bUse == true)
					{
						b_summon++;
					}
					g_aSummon[18].bUse = false; g_aSummon[18].bDrw = false; g_aSummon[18].bHit = false;
				}
				if (g_aSummon[20].bUse == true && g_aSummon[20].nLife == 0)
				{
					if (g_aSummon[18].bUse == true)
					{
						b_summon++;
					}
					g_aSummon[20].bUse = false; g_aSummon[20].bDrw = false; g_aSummon[20].bHit = false;
				}

				if (g_aSummon[19].bUse == true && g_aSummon[19].nLife == 0)
				{
					if (g_aSummon[21].bUse == true)
					{
						b_summon++;
					}
					g_aSummon[19].bUse = false; g_aSummon[19].bDrw = false; g_aSummon[19].bHit = false;
				}
				if (g_aSummon[21].bUse == true && g_aSummon[21].nLife == 0)
				{
					if (g_aSummon[19].bUse == true)
					{
						b_summon++;
					}
					g_aSummon[21].bUse = false; g_aSummon[21].bDrw = false; g_aSummon[21].bHit = false;
				}
			

			if (g_aSummon[16].bUse == true && g_aSummon[17].bUse == true && g_aSummon[16].nLife == 0 && g_aSummon[17].nLife == 0)
			{
				g_aSummon[16].bUse = false;g_aSummon[16].bDrw = false;g_aSummon[16].bHit = false;SetParticle(g_aSummon[16].pos, 0, 20, 10.0f, 4, 0);
				g_aSummon[17].bUse = false;g_aSummon[17].bDrw = false;g_aSummon[17].bHit = false;SetParticle(g_aSummon[16].pos, 0, 20, 10.0f, 4, 0);
			}

			//�����̐ݒ�
			switch (g_aSummon[nCntSummon].nType)
			{
			case 0:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 0, 0);
				break;
			case 1:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 0, 0);
				break;
			case 2:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 1, 0);
				break;
			case 3:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 4, 0);
				break;
			case 4:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 5, 0);
				break;
			case 5:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 4, 0);
				break;
			case 6:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 4, 0);
				break;
			}

			//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			PlaySound(SOUND_LABEL_SE_EXPLOSION); //���Đ��������T�E���h���w��

			g_aSummon[nCntSummon].bUse = false;
			g_aSummon[nCntSummon].bDrw = false;
			g_aSummon[nCntSummon].bHit = false;

			g_nNumSummon--;		//���݂̓G�̐�
			g_nTotalSummon--;	//�G�̑��������炷
			AddScore(g_aSummon[nCntSummon].score);
		}

		else
		{
			if (g_aSummon[nCntSummon].state == SUMMONSTATE_NORMAL)
			{
				g_aSummon[nCntSummon].state = SUMMONSTATE_DAMAGE;
				g_aSummon[nCntSummon].nCounterState = 10; //�_���[�W��ۂ��Ԃ�ݒ�
			}
			PlaySound(SOUND_LABEL_SE_HIT); //���Đ��������T�E���h���w��

			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

								//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
			g_pVtxBuffSummon->Lock(0, 0, (void **)&pVtx, 0);

			switch (g_aSummon[nCntSummon].nType)
			{
			case 0:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 5, 6.0f, 0, 0);
				break;
			case 1:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 5, 6.0f, 0, 0);
				break;
			case 2:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 5, 6.0f, 1, 0);
				break;
			case 3:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 4, 0);
				break;
			case 4:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 20, 10.0f, 5, 0);
				break;
			case 5:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 5, 6.0f, 0, 0);
				break;
			case 6:
				SetParticle(g_aSummon[nCntSummon].pos, 0, 5, 6.0f, 4, 0);
				break;
			}

			pVtx += nCntSummon * 4;
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�@ ���_�J���[ �@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //�|���S���̃_���[�W�F�ɐݒ�

															 //���_�o�b�t�@���A�����b�N
			g_pVtxBuffSummon->Unlock();
		}
	}
}
//��====================��
//�b�@ �G�̑����̎擾�@ �b
//��====================��
int GetNumSummon(void)
{
	return g_nNumSummon;
}
//��======================��
//�b�@�@�@ �G�̏����@�@ �@�b
//��======================��
Summon *GetSummon(void)
{
	return &g_aSummon[0];//�G�̏��̐擪�A�h���X��Ԃ�
}
//��====================================��
//�b�@�@�@ �G�l�~�[�f�[�^�ǂݍ��݁@�@ �@�b
//��====================================��
void LoadSummon(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int line = 0;//�s���𐔂���ϐ�
	int nCntEnemy; //�J�E���g�ϐ�

	char aData[100];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data/csv/SummonData.csv", "r");

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
		case 1:		g_aSummon[line].nType = atoi(aData);			 break;	//�P��ځF�G�E���
		case 2:		g_aSummon[line].sType = atoi(aData);			 break;	//  ��ځF�e�E���
		case 3:		g_aSummon[line].m_pattern = atoi(aData);		 break;	//�@��ځF�ړ��p�^�[��
		case 4:		g_aSummon[line].s_pattern = atoi(aData);		 break;	//�@��ځF���˃p�^�[��
		case 5:		g_aSummon[line].pos.x = (float)(atoi(aData));	 break;	//�@��ځFX���W
		case 6:		g_aSummon[line].pos.y = (float)(atoi(aData));	 break;	//�@��ځFY���W
		case 7:		g_aSummon[line].nLife = atoi(aData);			 break;	//�@��ځF�̗�
		}
		//�o�b�t�@��������
		memset(aData, 0, sizeof(aData));
		//�񐔂𑫂�
		column++;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			column = 1;
			line++;
		}
	}
	//�t�@�C�������
	fclose(pFile);

	//�G�N���X�̐���
	for (nCntEnemy = 0; nCntEnemy < MAX_SUMMON; nCntEnemy++)
	{
		if (g_aSummon[nCntEnemy].nType == 1)
		{
			g_aSummon[nCntEnemy].score = 200;
		}
		else if (g_aSummon[nCntEnemy].nType == 2)
		{
			g_aSummon[nCntEnemy].score = 500;
		}
		else if (g_aSummon[nCntEnemy].nType == 3)
		{
			g_aSummon[nCntEnemy].score = 600;
		}
		else if (g_aSummon[nCntEnemy].nType == 4)
		{
			g_aSummon[nCntEnemy].score = 250;
		}
		else if (g_aSummon[nCntEnemy].nType == 5)
		{
			g_aSummon[nCntEnemy].score = 2000;
		}
		else if (g_aSummon[nCntEnemy].nType == 6)
		{
			g_aSummon[nCntEnemy].score = 1000;
		}
	}
}
//��==========================��
//�b�@�@�@ �G�̏�������  �@ �@�b
//��==========================��
void EnemySummon(int p_pattern)
{
	p_summon = p_pattern;

	switch (p_summon)
	{
	case 0:
		g_aSummon[0].bTime = true; g_aSummon[0].bUse = true;
		g_aSummon[1].bTime = true; g_aSummon[1].bUse = true;
		g_aSummon[2].bTime = true; g_aSummon[2].bUse = true;
		g_aSummon[3].bTime = true; g_aSummon[3].bUse = true;
		stand_time = 62;
		break;

	case 1:
		g_aSummon[7].bTime = true; g_aSummon[7].bUse = true;
		g_aSummon[8].bTime = true; g_aSummon[8].bUse = true;
		g_aSummon[9].bTime = true; g_aSummon[9].bUse = true;
		g_aSummon[10].bTime = true; g_aSummon[10].bUse = true;
		g_aSummon[11].bTime = true; g_aSummon[11].bUse = true;
		g_aSummon[12].bTime = true; g_aSummon[12].bUse = true;
		g_aSummon[13].bTime = true; g_aSummon[13].bUse = true;
		g_aSummon[14].bTime = true; g_aSummon[14].bUse = true;
		g_aSummon[15].bTime = true; g_aSummon[15].bUse = true;
		stand_time = 62;
		break;
	case 2:
		g_aSummon[7].bTime = true; g_aSummon[7].bUse = true;
		g_aSummon[8].bTime = true; g_aSummon[8].bUse = true;
		g_aSummon[9].bTime = true; g_aSummon[9].bUse = true;
		g_aSummon[18].bTime = true; g_aSummon[18].bUse = true;
		g_aSummon[19].bTime = true; g_aSummon[19].bUse = true;
		g_aSummon[20].bTime = true; g_aSummon[20].bUse = true;
		g_aSummon[21].bTime = true; g_aSummon[21].bUse = true;
		stand_time = 132;
		break;
	case 3:
		g_aSummon[16].bTime = true; g_aSummon[16].bUse = true;
		g_aSummon[17].bTime = true; g_aSummon[17].bUse = true;
		stand_time = 132;
		break;
	}
}
//��============================��
//�b�@�@ �`���[�W���̏����@�@ �@�b
//��============================��
int GetnCharge1(void)
{
	return nCharge1;
}
int GetnCharge2(void)
{
	return nCharge2;
}