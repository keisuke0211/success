//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�{�X�̏���        �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include"game.h"
#include"bullet.h"
#include"explosion.h"
#include"score.h"
#include"sound.h"
#include"player.h"
#include"enemy_bullet.h"
#include"boss.h"
#include"particle.h"
#include"player.h"
#include"Summon.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define MAX_LIFE (100)  //HP�̍ő吔
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void CollisionBoss(Boss *pBoss);
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DTEXTURE9 g_pTextureBoss[NUM_BOSS] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;		//���_�o�b�t�@�|�C���^
Boss g_aBoss[NUM_BOSS];								//�G�̏��

int g_nNumBoss;										//�G�̑���
int g_Count1;										//�o�ߎ���
int g_nCntWhile;									//��莞��
int g_nCount3;										//��莞��
int nCntStop;										//��~�J�E���g
int nCntMove;										//�^�񒆂ɖ߂鎞��
int nCntpat;										//���[�v��̃J�E���g
int g_inCnt;										//�o���J�E���g
int nCntPlaterMove;									//�Ō�̃{�X������ł���v���C���[�������J�E���g
int nCntMachineGun;									//�@�֏e�̃J�E���g
int nCntCharge;										//�`���[�W����
int nCharge;										//�`���[�W��

bool nStop;											//��~�t���O
bool Reversal1 = false;								//�ړ�����
bool bBonus = false;
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�G�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��============================��
//�b�@�@�@ �{�X�̏����������@�@ �b
//��============================��
void InitBoss(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntBoss;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\boss1.png",
		&g_pTextureBoss[0]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy3.png",
		&g_pTextureBoss[1]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy3-1.png",
		&g_pTextureBoss[2]);
	
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy3-2.png",
		&g_pTextureBoss[3]);

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BOSS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void **)&pVtx, 0);

	nCntMove = 0;
	nCntpat  = 0;
	g_inCnt  = 0;
	nCntPlaterMove = 800;
	nCntMachineGun = 0;
	nCntCharge = 361;
	nCharge = 0;
	//�G�̏��̏���������
	for (nCntBoss = 0; nCntBoss < NUM_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].move.x = 0.3f;
		g_aBoss[nCntBoss].nBullet = 0;
		g_aBoss[nCntBoss].curt_nLife = 1;
		g_aBoss[nCntBoss].state_pattern = 0;
		g_aBoss[nCntBoss].nCounterState = 0;
		g_aBoss[nCntBoss].stand_time = 150;
		g_aBoss[nCntBoss].nReset = 0;

		g_aBoss[nCntBoss].bUse = false;
		g_aBoss[nCntBoss].bDrw = false;
		g_aBoss[nCntBoss].bHit = false;
		g_aBoss[nCntBoss].bTime = false;
		g_aBoss[nCntBoss].bSummon = false;

		nStop = false;
		Reversal1 = false;

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

	g_nNumBoss = 0;	//�G�̑������N���A
	g_Count1 = 0;	//�o�ߎ��Ԃ��N���A
	g_nCntWhile = 0;//��莞�Ԃ��N���A
	nCntStop = 0;	//��~���Ԃ��N���A
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBoss->Unlock();

	LoadBoss();
}
//��==========================��
//�b�@�@�@ �{�X�̏I�������@ �@�b
//��==========================��
void UninitBoss(void)
{
	int nCntBoss;
	//�T�E���h�̒�~
	StopSound();
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntBoss = 0; nCntBoss < NUM_BOSS; nCntBoss++)
	{
		if (g_pTextureBoss[nCntBoss] != NULL)
		{
			g_pTextureBoss[nCntBoss]->Release();
			g_pTextureBoss[nCntBoss] = NULL;
		}
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}
//��==========================��
//�b�@�@�@ �{�X�̍X�V�����@ �@�b
//��==========================��
void UpdateBoss(void)
{
	int nCntEnemy;		//�{�X�J�E���^
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	Player *pPlayer = Getplayer();	//�v���C���[�̏��ւ̃|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void **)&pVtx, 0);

	//g_Count1 = GetCunt();
	g_Count1++;
	for (nCntEnemy = 0; nCntEnemy < NUM_BOSS; nCntEnemy++, pVtx += 4)
	{
		//��ԑJ�ڏ���
		if (g_aBoss[nCntEnemy].bUse == true)
		{
			CollisionBoss(&g_aBoss[nCntEnemy]);

			D3DXVECTOR3 movevec;

			if (g_aBoss[1].curt_nLife <= g_aBoss[1].init_nLife / 2 && g_aBoss[1].bDrw == true)
			{
				SetParticle(D3DXVECTOR3(g_aBoss[1].pos.x + 0.0f, g_aBoss[1].pos.y + 15.0f, 0.0f), 6, 2, 15.0f, 7, 6);
			}

				switch (g_aBoss[nCntEnemy].m_pattern)
				{
				case 0:
					//�o�ė��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
					if (g_aBoss[nCntEnemy].in_time < g_Count1 && g_Count1 < g_aBoss[nCntEnemy].stop_time)
					{
						g_aBoss[nCntEnemy].pos.y += 2;
					}
					else if (g_Count1 > g_aBoss[nCntEnemy].out_time)
					{
						g_aBoss[nCntEnemy].m_pattern = 91;
						g_aBoss[nCntEnemy].bHit = true;
					}
					break;
				case 91:

					if (g_aBoss[nCntEnemy].curt_nLife <= 100)
					{
						if (nStop == false)
						{
							if (Reversal1 == false)
							{
								g_aBoss[nCntEnemy].pos.x -= 1.5;
								if (g_aBoss[nCntEnemy].pos.x < 110)
								{
									g_aBoss[nCntEnemy].pos.x = 110;
									nStop = true;
								}
							}
							else if (Reversal1 == true)
							{
								g_aBoss[nCntEnemy].pos.x += 1.5;
								if (g_aBoss[nCntEnemy].pos.x > 860)
								{
									g_aBoss[nCntEnemy].pos.x = 860;
									nStop = true;
								}
							}
						}
						else if (nStop == true)
						{
							nCntStop++;
							if (nCntStop == 20)
							{
								if (Reversal1 == false)
								{
									Reversal1 = true;
								}
								else if (Reversal1 == true)
								{
									Reversal1 = false;
								}
								nStop = false;
								nCntStop = 0;
							}
						}
					}
					break;
				case 98:
					g_aBoss[nCntEnemy].pos.x += 0;
					g_aBoss[nCntEnemy].pos.y += 0;
					break;
				case 99:
					//�^�񒆂ɖ߂鏈��

					//if (g_aBoss[nCntEnemy].pos.x >= 500.0f - 1 &&
					//	g_aBoss[nCntEnemy].pos.x <= 500.0f + 1)
					//{
					//	bMove = true;
					//	g_aBoss[nCntEnemy].m_pattern = 98;
					//}
					//else if (bMove == false)
					//{
					//	movevec = D3DXVECTOR3(500.0f, 115.0f, 0.0f) - g_aBoss[nCntEnemy].pos;//�e����v���C���[�܂ł̕����x�N�g�������߂�
					nCntMove++;
					if (g_aBoss[nCntEnemy].pos == D3DXVECTOR3(500.0f, 115.0f, 0.0f))
					{
						nCntpat++;
						if (nCntpat == 1)
						{
							if (g_aBoss[nCntEnemy].state_pattern == 1)
							{
								SetParticle(g_aBoss[0].pos, 1, 30, 90.0f, 1,0);
							}
							else if (g_aBoss[nCntEnemy].state_pattern == 2)
							{
								SetParticle(g_aBoss[0].pos, 1, 30, 90.0f, 0,0);
							}
						}
						else if (nCntpat >= 2)
						{
							g_aBoss[nCntEnemy].pos.x += 0;
							g_aBoss[nCntEnemy].pos.y += 0;
							g_aBoss[nCntEnemy].bTime = true;
						}
					}
					else
					{
						g_aBoss[nCntEnemy].pos = (g_aBoss[nCntEnemy].pos * (1.0f - (nCntMove / 60)) + (D3DXVECTOR3(500.0f, 115.0f, 0.0f) *(nCntMove / 60)));//�J�E���g�̑O��(float)������
					}
					break;
				}

			//��ʂ���͂ݏo������G���\���ɂ���
			if (g_aBoss[nCntEnemy].pos.x < 0 || g_aBoss[nCntEnemy].pos.x > SCREEN_WIDTH - 320)
			{
				//X���W���͈͊O�̏ꍇ
				g_aBoss[nCntEnemy].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}
			if (g_aBoss[nCntEnemy].pos.y < -100 || g_aBoss[nCntEnemy].pos.y > SCREEN_HEIGHT)
			{
				//Y���W���͈͊O�̏ꍇ
				g_aBoss[nCntEnemy].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}

			//�ҋ@����

			if (g_aBoss[nCntEnemy].bTime == true)
			{
				g_aBoss[nCntEnemy].stand_time--;
				
				if (g_aBoss[nCntEnemy].stand_time <= 0)
				{
					g_aBoss[nCntEnemy].bTime = false;
					//g_aBoss[nCntEnemy].stand_time = 30;

					if (g_inCnt == 1)
					{
						g_aBoss[1].bHit = true;	//�{�X�̓����蔻��ON
						g_aBoss[1].m_pattern = 91;
					}
					else if (g_inCnt == 2)
					{
						g_aBoss[2].bHit = true;//�{�X�̓����蔻��ON
						g_Count1 = 3;
					}
					else if (g_inCnt == 2 && g_aBoss[3].bTime == true && g_aBoss[4].bTime == true && g_aBoss[5].bTime == true)
					{
						g_aBoss[3].bHit = true;
						g_aBoss[4].bHit = true;
						g_aBoss[5].bHit = true;
					}
				}
				else if (g_aBoss[nCntEnemy].stand_time == 1)
				{
					if (g_inCnt == 1)
					{
						g_aBoss[1].m_pattern = 98;
					}
					else if (g_inCnt == 2)
					{
						g_aBoss[2].m_pattern = 98;
					}
				}
				else if (g_aBoss[nCntEnemy].stand_time <= 20)
				{
					if (g_inCnt == 1)
					{
						g_aBoss[1].bDrw = true;
					}
					else if (g_inCnt == 2)
					{
						g_aBoss[2].bDrw = true;
					}
					else if (g_inCnt == 2 && g_aBoss[3].bTime == true && g_aBoss[4].bTime == true && g_aBoss[5].bTime == true)
					{
						g_aBoss[3].bDrw = true;
						g_aBoss[4].bDrw = true;
						g_aBoss[5].bDrw = true;
					}
				}
				else if (g_aBoss[nCntEnemy].stand_time == 60)
				{
					if (g_inCnt == 1)
					{
						PlaySound(SOUND_LABEL_SE_SUMMON);
						SetParticle(g_aBoss[1].pos, 1, 30, 90.0f, 1,0);
					}
					else if (g_inCnt == 2)
					{
						PlaySound(SOUND_LABEL_SE_SUMMON);
						SetParticle(g_aBoss[2].pos, 1, 30, 90.0f, 0,0);
					}
					else if (g_inCnt == 2 && g_aBoss[3].bTime == true && g_aBoss[4].bTime == true && g_aBoss[5].bTime == true)
					{
						bBonus = true;
						PlaySound(SOUND_LABEL_SE_SUMMON);
						SetParticle(g_aBoss[3].pos, 1, 30, 90.0f, 0, 0);
						SetParticle(g_aBoss[4].pos, 1, 30, 90.0f, 0, 0);
						SetParticle(g_aBoss[5].pos, 1, 30, 90.0f, 0, 0);
					}
				}
			}
			if (g_aBoss[nCntEnemy].bHit == true)
			{
				switch (g_aBoss[nCntEnemy].state)
				{
				case BOSSSTATE_NORMAL:
					break;

				case BOSSSTATE_DAMAGE:
					g_aBoss[nCntEnemy].nCounterState--;


					if (g_aBoss[nCntEnemy].nCounterState <= 0)
					{
						g_aBoss[nCntEnemy].state = BOSSSTATE_NORMAL;
						g_aBoss[nCntEnemy].bDrw = true;
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
						g_aBoss[nCntEnemy].bDrw = g_aBoss[nCntEnemy].bDrw ? false : true;
					}
					break;
				}
			}

			//g_aBoss[nCntBoss].pos.y += g_aBoss[nCntBoss].move.y;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aBoss[nCntEnemy].pos.x - SIZE_BOSS * 1;
			pVtx[0].pos.y = g_aBoss[nCntEnemy].pos.y - SIZE_BOSS * 1;
			pVtx[0].pos.z = 0;
			pVtx[1].pos.x = g_aBoss[nCntEnemy].pos.x + SIZE_BOSS * 1;
			pVtx[1].pos.y = g_aBoss[nCntEnemy].pos.y - SIZE_BOSS * 1;
			pVtx[1].pos.z = 0;
			pVtx[2].pos.x = g_aBoss[nCntEnemy].pos.x - SIZE_BOSS * 1;
			pVtx[2].pos.y = g_aBoss[nCntEnemy].pos.y + SIZE_BOSS * 1;
			pVtx[2].pos.z = 0;
			pVtx[3].pos.x = g_aBoss[nCntEnemy].pos.x + SIZE_BOSS * 1;
			pVtx[3].pos.y = g_aBoss[nCntEnemy].pos.y + SIZE_BOSS * 1;
			pVtx[3].pos.z = 0;

			if (g_aBoss[nCntEnemy].bHit == true)
			{
				if (g_aBoss[2].nReset == 1)
				{
					nCntCharge = 361;
					nCharge = 0;
					g_aBoss[nCntEnemy].s_pattern = BULLETTYPE_E_CHARGE;

					g_aBoss[2].nReset = 0;
				}

				switch (g_aBoss[nCntEnemy].s_pattern)
				{
				case BULLETTYPE_E_LINE:
					g_aBoss[nCntEnemy].nBullet++;//�J�E���^�[�����Z
					if ((g_aBoss[nCntEnemy].nBullet % 40) == 0)
					{
						g_aBoss[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
						SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_LINE, g_aBoss[nCntEnemy].sType);
					}
					break;
				case BULLETTYPE_E_AIM:
					g_aBoss[nCntEnemy].nBullet++;//�J�E���^�[�����Z
					if ((g_aBoss[nCntEnemy].nBullet % 30) == 0)
					{
						g_aBoss[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
						SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(0.0f, 13.0f, 0.0f), BULLETTYPE_E_AIM, g_aBoss[nCntEnemy].sType);
					}
					break;
				case BULLETTYPE_E_HOMING:
					g_aBoss[nCntEnemy].nBullet++;//�J�E���^�[�����Z
					if ((g_aBoss[nCntEnemy].nBullet % 60) == 0)
					{
						g_aBoss[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
						SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 5.0f, 0.0f), D3DXVECTOR3(0.0f, 5, 0.0f), BULLETTYPE_E_HOMING, g_aBoss[nCntEnemy].sType);

					}
					break;
				case BULLETTYPE_E_3_SHOT:
					g_aBoss[nCntEnemy].nBullet++;//�J�E���^�[�����Z

					if ((g_aBoss[nCntEnemy].nBullet % 30) == 0)
					{
						SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_3_SHOT, g_aBoss[nCntEnemy].sType);
						SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.1)* SPEED, cosf(D3DX_PI * 0.1)* 5.0f, 0.0f), BULLETTYPE_E_3_SHOT, g_aBoss[nCntEnemy].sType);
						SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.1)* SPEED, cosf(D3DX_PI  * 0.1)* 5.0f, 0.0f),BULLETTYPE_E_3_SHOT, g_aBoss[nCntEnemy].sType);
					}
					break;
				case BULLETTYPE_S_1_SUMMON:
					if (g_aBoss[1].bSummon == true)
					{
						EnemySummon(0);
						g_aBoss[1].s_pattern = 0;
						g_aBoss[1].sType = 0;
						g_aBoss[1].bSummon = false;
						PlaySound(SOUND_LABEL_SE_SUMMON);
					}
					break;
				case BULLETTYPE_S_2_SUMMON:
					if (g_aBoss[2].bSummon == true)
					{
						EnemySummon(1);
						g_aBoss[2].s_pattern = BULLETTYPE_E_CHARGE;
						g_aBoss[2].sType = 1;
						g_aBoss[2].bSummon = false;
						PlaySound(SOUND_LABEL_SE_SUMMON);
					}
					break;
				case BULLETTYPE_E_CHARGE:

					g_aBoss[nCntEnemy].nBullet++;//�J�E���^�[�����Z

					if (g_aBoss[2].curt_nLife <= g_aBoss[2].init_nLife / 2)
					{
						if ((g_aBoss[nCntEnemy].nBullet % 60) == 0)
						{
							SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_3_SHOT2, g_aBoss[nCntEnemy].sType);
							SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.1)* SPEED, cosf(D3DX_PI * 0.1)* 5.0f, 0.0f), BULLETTYPE_E_3_SHOT2, g_aBoss[nCntEnemy].sType);
							SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.1)* SPEED, cosf(D3DX_PI  * 0.1)* 5.0f, 0.0f), BULLETTYPE_E_3_SHOT2, g_aBoss[nCntEnemy].sType);
						}
						//�`���[�W��ԂȂ�J�E���g�����炷
						if (nCntCharge <= 0)
						{
							g_aBoss[nCntEnemy].s_pattern = BULLETTYPE_E_MACHINEGUN;
							nCntMachineGun = 0;
						}
						else if (nCntCharge == 301)
						{
							nCntCharge--;
							PlaySound(SOUND_LABEL_SE_CHARG);
						}
						else if (nCntCharge <= 60)
						{
							nCntCharge--;
							nCharge++;
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 3);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 31);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 32);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 42);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 42);
						}
						else if (nCntCharge <= 120 && nCntCharge >= 61)
						{
							nCntCharge--;
							nCharge++;
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 3);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 31);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
						}
						else if (nCntCharge <= 300 && nCntCharge >= 121)
						{
							nCntCharge--;
							nCharge++;
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 3);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
						}
						else
						{
							nCntCharge--;
						}
					}
					else
					{
						if ((g_aBoss[nCntEnemy].nBullet % 90) == 0)
						{
							SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_3_SHOT2, g_aBoss[nCntEnemy].sType);
							SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.1)* SPEED, cosf(D3DX_PI * 0.1)* 5.0f, 0.0f), BULLETTYPE_E_3_SHOT2, g_aBoss[nCntEnemy].sType);
							SetEnemyBullet(g_aBoss[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.1)* SPEED, cosf(D3DX_PI  * 0.1)* 5.0f, 0.0f), BULLETTYPE_E_3_SHOT2, g_aBoss[nCntEnemy].sType);
						}
						//�`���[�W��ԂȂ�J�E���g�����炷
						if (nCntCharge <= 0)
						{
							g_aBoss[nCntEnemy].s_pattern = BULLETTYPE_E_MACHINEGUN;
							nCntMachineGun = 0;
						}
						else if (nCntCharge == 301)
						{
							nCntCharge--;
							PlaySound(SOUND_LABEL_SE_CHARG);
						}
						else if (nCntCharge <= 60)
						{
							nCntCharge--;
							nCharge++;
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 42);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 42);
						}
						else if (nCntCharge <= 300 && nCntCharge >= 60)
						{
							nCntCharge--;
							nCharge++;
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
						}
						else
						{
							nCntCharge--;
						}
					}

						break;
				case BULLETTYPE_E_MACHINEGUN:

					g_aBoss[nCntEnemy].nBullet++;//�J�E���^�[�����Z

					if (g_aBoss[2].curt_nLife <= g_aBoss[2].init_nLife / 2)
					{
						if ((g_aBoss[nCntEnemy].nBullet % 60) == 0)
						{
							SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_MACHINEGUN, g_aBoss[nCntEnemy].sType);
							SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x - 50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_MACHINEGUN, g_aBoss[nCntEnemy].sType);
						}
						if (nCntMachineGun <= 310)
						{
							nCntMachineGun++; //�J�E���g�����Z
							nCharge--;

							//20��Ɉ�񔭎ˁB310�܂łȂ̂�15�����ˁB
							if ((nCntMachineGun % 20) == 0)
							{

								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_MACHINEGUN, g_aBoss[nCntEnemy].sType);
							}
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 3);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 31);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 0.0f, g_aBoss[nCntEnemy].pos.y + 60.0f, 0.0f), 3, 2, 5.0f, 0, 32);

						}
						else
						{
							nCntCharge = 361;
							nCharge = 0;
							g_aBoss[nCntEnemy].s_pattern = BULLETTYPE_E_CHARGE;
						}
					}
					else
					{
						if (nCntMachineGun <= 310)
						{
							nCntMachineGun++; //�J�E���g�����Z
							nCharge--;

							//20��Ɉ�񔭎ˁB310�܂łȂ̂�15�����ˁB
							if ((nCntMachineGun % 30) == 0)
							{

								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_MACHINEGUN, g_aBoss[nCntEnemy].sType);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x - 50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_E_MACHINEGUN, g_aBoss[nCntEnemy].sType);
							}
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 2);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 41);

							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + 53.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 42);
							SetParticle(D3DXVECTOR3(g_aBoss[nCntEnemy].pos.x + -50.0f, g_aBoss[nCntEnemy].pos.y + 70.0f, 0.0f), 3, 2, 5.0f, 1, 42);
						}
						else
						{
							nCntCharge = 361;
							nCharge = 0;
							g_aBoss[nCntEnemy].s_pattern = BULLETTYPE_E_CHARGE;
						}
					}

					break;
				}
			}
		}
		if (g_aBoss[2].bUse == false)
		{
			nCntPlaterMove--;
			if (nCntPlaterMove == 0)
			{
				nCntPlaterMove = 0;
				pPlayer->bUse = false;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBoss->Unlock();
}
//��==========================��
//�b�@�@ �{�X�̕`�揈���@�@ �@�b
//��==========================��
void DrawBoss(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntBoss;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntBoss = 0; nCntBoss < NUM_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bDrw == true)
		{//�G���g�p����Ă���

			pDevice->SetTexture(0, g_pTextureBoss[g_aBoss[nCntBoss].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBoss * 4, 2);

		}
	}
}

//��==========================��
//�b�@�@�@�{�X�̔��菈���@�@�@�b
//��==========================��

//�{�X�̓����蔻��
void CollisionBoss(Boss *pBoss)
{
	int nCntEnemy;

	Player *pPlayer = Getplayer(); //�v���C���[�̏��ւ̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < NUM_BOSS; nCntEnemy++, pBoss++)
	{
		if (pBoss->bUse == true && pBoss->bHit == true && pPlayer->bUse == true)
		{//�G���g�p����Ă���
			if (pBoss->pos.x >= pPlayer->pos.x - 80
				&& pBoss->pos.x <= pPlayer->pos.x + 80
				&& pBoss->pos.y >= pPlayer->pos.y - 80
				&& pBoss->pos.y <= pPlayer->pos.y + 80)
			{//�G�ƒe����������
				HitPlayer(nCntEnemy, 1);
			}
		}
	}
}
//��============================��
//�b�@�@ �{�X�̃q�b�g�����@�@ �@�b
//��============================��
void HitBoss(int nCntBoss, int nDamage)
{
	g_aBoss[nCntBoss].curt_nLife -= nDamage;

	if (g_aBoss[nCntBoss].curt_nLife <= 0)//�G�̗̑͂��Ȃ��Ȃ���
	{
		//�����̐ݒ�
		if (g_aBoss[0].curt_nLife == 0 && g_aBoss[0].bUse == true)
		{
			SetParticle(g_aBoss[0].pos, 1, 30, 90.0f, 0,0);
			g_aBoss[0].bUse = false;
			g_aBoss[0].bHit = false;
			g_aBoss[0].bDrw = false;
		}
		else if (g_aBoss[1].curt_nLife == 0 && g_aBoss[1].bUse == true)
		{
			SetParticle(g_aBoss[1].pos, 1, 30, 90.0f, 0,0);
			g_aBoss[1].bUse = false;
			g_aBoss[1].bHit = false;
			g_aBoss[1].bDrw = false;
		}
		else if (g_aBoss[2].curt_nLife == 0 && g_aBoss[2].bUse == true)
		{
			SetParticle(g_aBoss[2].pos, 2, 30, 90.0f, 2,0);
			g_aBoss[2].bUse = false;
			g_aBoss[2].bHit = false;
			g_aBoss[2].bDrw = false;
		}
		//SetExplosion(g_aBoss[nCntBoss].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION); //���Đ��������T�E���h���w��

		//�X�R�A�����Z
		AddScore(g_aBoss[nCntBoss].score);

		

		g_nNumBoss--; //�G�̑��������炷

		if (g_nNumBoss <= 0)
		{
			//��Ԃ̐ݒ�
			SetGameState(GAMESTATE_END1, 450);
		}
		else if (g_nNumBoss == 2)
		{
			if (g_inCnt == 0)
			{
				g_inCnt++;
				g_aBoss[1].bTime = true;
				g_aBoss[1].bSummon = true;
			}
		}
		else if (g_nNumBoss == 1)
		{
			if (g_inCnt == 1)
			{
				g_inCnt++;
				g_aBoss[2].bTime = true;
				g_aBoss[2].bSummon = true;
			}

			//g_aBoss[2].bTime = true;

			//g_aBoss[1].bUse = true; //�{�X���g�p���Ă����Ԃɂ���
			//g_aBoss[1].bDrw = true;
			//g_aBoss[1].bHit = false;	//�{�X�̓����蔻��ON
		}
	}

	else
	{
		/*if (g_aBoss[nCntBoss].state_pattern == 0)
		{
			if (g_aBoss[nCntBoss].curt_nLife <= g_aBoss[nCntBoss].init_nLife / 2 && g_aBoss[nCntBoss].curt_nLife >= g_aBoss[nCntBoss].init_nLife / 4)
			{
				if (g_aBoss[nCntBoss].state_pattern == 0)
				{
					g_aBoss[nCntBoss].bHit = false;
					g_aBoss[nCntBoss].bDrw = false;

					SetParticle(g_aBoss[nCntBoss].pos, 1, 30, 90.0f, 1);

					g_aBoss[nCntBoss].m_pattern = 99;
					g_aBoss[nCntBoss].state_pattern++;
				}
			}
		}
		else if (g_aBoss[nCntBoss].state_pattern == 1)
		{
			if (g_aBoss[nCntBoss].curt_nLife <= g_aBoss[nCntBoss].init_nLife / 4)
			{
				if (g_aBoss[nCntBoss].state_pattern == 1)
				{
					g_aBoss[nCntBoss].bHit = false;
					g_aBoss[nCntBoss].bDrw = false;

					g_nCntMove = 0;
					nCntpat = 0;
					SetParticle(g_aBoss[nCntBoss].pos, 1, 30, 90.0f, 0);

					g_aBoss[nCntBoss].m_pattern = 99;
					g_aBoss[nCntBoss].state_pattern++;
				}
			}
		}*/

		if (g_aBoss[nCntBoss].state == BOSSSTATE_NORMAL)
		{
			g_aBoss[nCntBoss].state = BOSSSTATE_DAMAGE;
			g_aBoss[nCntBoss].nCounterState = 6; //�_���[�W��ۂ��Ԃ�ݒ�
		}

		/*if (g_aBoss[nCntBoss].state_pattern == 0)
		{
			if (g_aBoss[nCntBoss].curt_nLife <= g_aBoss[nCntBoss].init_nLife / 2 && g_aBoss[nCntBoss].curt_nLife >= g_aBoss[nCntBoss].init_nLife / 4)
			{
				if (g_aBoss[nCntBoss].state_pattern == 0)
				{
					g_aBoss[nCntBoss].bHit = false;
					g_aBoss[nCntBoss].bDrw = false;

					SetParticle(g_aBoss[nCntBoss].pos, 1, 30, 90.0f, 1);

					g_aBoss[nCntBoss].m_pattern = 99;
					g_aBoss[nCntBoss].state_pattern++;
				}
			}
		}
		else if (g_aBoss[nCntBoss].state_pattern == 1)
		{
			if (g_aBoss[nCntBoss].curt_nLife <= g_aBoss[nCntBoss].init_nLife / 4)
			{
				if (g_aBoss[nCntBoss].state_pattern == 1)
				{
					g_aBoss[nCntBoss].bHit = false;
					g_aBoss[nCntBoss].bDrw = false;

					nCntMove = 0;
					nCntpat = 0;
					SetParticle(g_aBoss[nCntBoss].pos, 1, 30, 90.0f, 0);

					g_aBoss[nCntBoss].m_pattern = 99;
					g_aBoss[nCntBoss].state_pattern++;
				}
			}
		}*/

		if (g_aBoss[1].curt_nLife <= g_aBoss[1].init_nLife / 2)
		{
			g_aBoss[1].s_pattern = BULLETTYPE_E_3_SHOT;
			PlaySound(SOUND_LABEL_SE_SUMMON);
		}
		else if (g_aBoss[2].curt_nLife <= g_aBoss[2].init_nLife / 2)
		{
			g_aBoss[2].s_pattern = BULLETTYPE_E_CHARGE;
			PlaySound(SOUND_LABEL_SE_SUMMON);
		}
		PlaySound(SOUND_LABEL_SE_HIT); //���Đ��������T�E���h���w��



		VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

		//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		g_pVtxBuffBoss->Lock(0, 0, (void **)&pVtx, 0);



		pVtx += nCntBoss * 4;

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffBoss->Unlock();
	}
}
//��======================��
//�b�@�@ �{�X�̏����@�@ �@�b
//��======================��
Boss *GetBoss(void)
{
	return &g_aBoss[0];//�G�̏��̐擪�A�h���X��Ԃ�
}
//��============================��
//�b�@�@ �{�X�̑����̏����@�@ �@�b
//��============================��
int GetNumBoss(void)
{
	return g_nNumBoss;
}
//��============================��
//�b�@�@ �`���[�W���̏����@�@ �@�b
//��============================��
int GetnCharge(void)
{
	return nCharge;
}
//��==============================��
//�b�@�@ �o���J�E���g�̏����@�@ �@�b
//��==============================��
int GetinCnt(void)
{
	return g_inCnt;
}
//��============================��
//�b�@�@�@ �f�[�^�ǂݍ��݁@�@ �@�b
//��============================��
void LoadBoss(void)
{
	int c = 0;
	int column = 1;//�s���𐔂���ϐ�
	int line = 0;//�񐔂𐔂���ϐ�
	int nCntBoss; //�J�E���g�ϐ�

	char aData[100];
	FILE *pFile;

	memset(aData, 0, sizeof(aData));
	pFile = fopen("data/csv/boosdata.csv", "r");

	if (pFile == NULL)
	{
		/*printf("�t�@�C���I�[�v���G���[\n");*/
	}

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
		case 1:		g_aBoss[line].nType = atoi(aData);			break;		//�P��ځF�G�E���
		case 2:		g_aBoss[line].sType = atoi(aData);			break;		//  ��ځF�e�E���
		case 3:		g_aBoss[line].m_pattern = atoi(aData);		break;		//�@��ځF�ړ��p�^�[��
		case 4:		g_aBoss[line].s_pattern = atoi(aData);		break;		//�@��ځF���˃p�^�[��
		case 5:		g_aBoss[line].in_time = atoi(aData);		break;		//�@��ځF�o������
		case 6:		g_aBoss[line].stop_time = atoi(aData);		break;		//�@��ځF��~����
		case 7:		g_aBoss[line].shot_time = atoi(aData);		break;		//�@��ځF�e ���ˎ���
		case 8:		g_aBoss[line].out_time = atoi(aData);		break;		//��~����(���̍s������)
		case 9:		g_aBoss[line].pos.x = (float)(atoi(aData));	break;		//�@��ځFX���W
		case 10:	g_aBoss[line].pos.y = (float)(atoi(aData));	break;		//�@��ځFY���W
		case 11:	g_aBoss[line].curt_nLife = atoi(aData);					//�@��ځF�̗́@�i�\���́@���݂̗̑́j
					g_aBoss[line].init_nLife = atoi(aData);		break;		//				�i�\���́@�����̗́j
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

	//�{�X�N���X�̐���

	for (nCntBoss = 0; nCntBoss < 3; nCntBoss++)
	{
		SetBoss(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x, g_aBoss[nCntBoss].pos.y, 0), nCntBoss);
		g_aBoss[nCntBoss].bUse = true;	//�{�X���g�p���Ă����Ԃɂ���
		g_nNumBoss++;						//�G�̑��������Z����
	}
	g_aBoss[0].bDrw = true;
}
//��==========================��
//�b�@�@�@ �G�̐ݒ菈��2�@ �@�b
//��==========================��
void SetBoss(D3DXVECTOR3 pos, int nCntBoss)
{
	if (g_aBoss[nCntBoss].nType == 1)
	{
		g_aBoss[nCntBoss].score = 1000;
	}
	else if (g_aBoss[nCntBoss].nType == 2)
	{
		g_aBoss[nCntBoss].score = 2000;
	}
	else if (g_aBoss[nCntBoss].nType == 3)
	{
		g_aBoss[nCntBoss].score = 3000;
	}
	else if (g_aBoss[nCntBoss].nType == 4)
	{
		g_aBoss[nCntBoss].score = 2000;
	}
	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBoss->Lock(0, 0, (void **)&pVtx, 0);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - SIZE_BOSS / 2, g_aBoss[nCntBoss].pos.y - SIZE_BOSS / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + SIZE_BOSS / 2, g_aBoss[nCntBoss].pos.y - SIZE_BOSS / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - SIZE_BOSS / 2, g_aBoss[nCntBoss].pos.y + SIZE_BOSS / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + SIZE_BOSS / 2, g_aBoss[nCntBoss].pos.y + SIZE_BOSS / 2, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBoss->Unlock();
}