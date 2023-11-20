//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�G�̏���          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include"game.h"
#include"enemy.h"
#include"bullet.h"
#include"explosion.h"
#include"score.h"
#include"sound.h"
#include"player.h"
#include"enemy_bullet.h"
#include"particle.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_ENEMY (5) //�G�̎��

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void CollisionEnemy(Enemy *pEnemy);
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DTEXTURE9 g_pTextureEnemy[NUM_ENEMY] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//���_�o�b�t�@�|�C���^
Enemy g_aEnemy[MAX_ENEMY];							//�G�̏��

int g_CntTime;										//�o�ߎ���
int g_nCount;										//��莞��
int g_nCntSkip;										//�X�L�b�v���Ă���̊Ԃ̎���
int g_nNumEnemy;									//���݂���G�̐�
int g_nTotalEnemy;									//�G�̑���
int g_nArrivalEnemy;								//�o�������G�̐�

bool SkipType;										//�X�L�b�v���
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�G�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��============================��
//�b�@�@�@ �G�̏����������@�@ �@�b
//��============================��
void InitEnemy(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnemy;
	SkipType = false;
	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\ghost.png",
		&g_pTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy_a.png",
		&g_pTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy2.png",
		&g_pTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy3b.png",
		&g_pTextureEnemy[3]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Enemy4.png",
		&g_pTextureEnemy[4]);

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

	//�G�̏��̏���������
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(1000.0f, 500.0f, 0.0f);
		g_aEnemy[nCntEnemy].move.x = 0.3f;
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����������������(Z�l���g�p)
		g_aEnemy[nCntEnemy].nBullet = 0;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].time = 1;
		g_aEnemy[nCntEnemy].Tracking = 90;
		g_aEnemy[nCntEnemy].nCntMove = 0;
		g_aEnemy[nCntEnemy].stand_time = 62;
		g_aEnemy[nCntEnemy].score = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].Reversal = false;
		g_aEnemy[nCntEnemy].m_switch = false;
		g_aEnemy[nCntEnemy].bHit = false;
		g_aEnemy[nCntEnemy].bDrw = false;
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

	g_CntTime = 0;		//�o�ߎ��Ԃ��N���A
	g_nCount = 0;		//��莞�Ԃ��N���A
	g_nCntSkip = 15;	//�X�L�b�v���Ă���̊Ԃ̎���
	g_nNumEnemy = 0;	//���݂���G�̐�
	g_nTotalEnemy = 0;	//�G�̑���
	g_nArrivalEnemy = 0;	//
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();

	//�G����ǂݍ���
	LoadEnemy();
}
//��==========================��
//�b�@�@�@ �G�̏I�������@�@ �@�b
//��==========================��
void UninitEnemy(void)
{
	int nCntEnemy;
	//�T�E���h�̒�~
	StopSound();
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//��==========================��
//�b�@�@�@ �G�̍X�V�����@�@ �@�b
//��==========================��
void UpdateEnemy(void)
{
	int nCntEnemy;		//�G�J�E���^
	Player *pPlayer = Getplayer();	//�v���C���[�̏��ւ̃|�C���^

	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

	if (g_nNumEnemy <= 0)
	{
		if (SkipType == false)
		{
			g_CntTime = g_aEnemy[0].in_time;
			SkipType = true;
		}
		else if (SkipType == true)
		{
			g_CntTime = g_aEnemy[g_nArrivalEnemy + 1].in_time;
		}
	}
	else
	{
		g_CntTime++;
	}
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pVtx += 4)
	{
		//��ԑJ�ڏ���
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			CollisionEnemy(&g_aEnemy[nCntEnemy]);

			D3DXVECTOR3 movevec;
			switch (g_aEnemy[nCntEnemy].m_pattern)
			{
				//=============================
				//�ォ��o������ړ��p�^�[��
				//=============================

			case 0:
				//�o�ė��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
				if (g_aEnemy[nCntEnemy].in_time < g_CntTime && g_CntTime < g_aEnemy[nCntEnemy].stop_time)
				{
					g_aEnemy[nCntEnemy].pos.y += 2;
				}
				else if (g_CntTime == g_aEnemy[nCntEnemy].stop_time)
				{
					SetEnemyBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5, 0.0f), BULLETTYPE_E_LINE, g_aEnemy[nCntEnemy].sType);
				}
				//�A�Ҏ��Ԃ��߂�����߂�
				else if (g_CntTime > g_aEnemy[nCntEnemy].out_time)
				{
					g_aEnemy[nCntEnemy].pos.y -= 2;
				}
				break;

				//�~�܂炸���ɂ����p�^�[��
			case 1:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					g_aEnemy[nCntEnemy].pos.y += 2;
				}
				break;

				//���������Ɉړ����Ȃ�������Ă���
			case 2:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					g_aEnemy[nCntEnemy].pos.y += 2;
					if (g_nCount % 10 == 0)
					{
						g_aEnemy[nCntEnemy].pos.x -= 1;
					}
				}
				break;

				//�������E�Ɉړ����Ȃ�������Ă���
			case 3:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					g_aEnemy[nCntEnemy].pos.y += 2;
					if (g_nCount % 10 == 0)
					{
						g_aEnemy[nCntEnemy].pos.x += 1;
					}
				}
				break;

				//���������Ɉړ����r���ŋA�҂���
			case 4:
				if (g_aEnemy[nCntEnemy].in_time < g_CntTime && g_CntTime < g_aEnemy[nCntEnemy].stop_time)
				{
					if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
					{
						g_aEnemy[nCntEnemy].pos.y += 2;
						if (g_nCount % 10 == 0)
						{
							g_aEnemy[nCntEnemy].pos.x -= 1;
						}
					}
				}
				//�������Ɉړ�����
				else if (g_aEnemy[nCntEnemy].stop_time < g_CntTime && g_CntTime < g_aEnemy[nCntEnemy].out_time)
				{
					g_aEnemy[nCntEnemy].pos.x += 2;
				}
				//�A�Ҏ��Ԃ��߂�����߂�
				else if (g_CntTime > g_aEnemy[nCntEnemy].out_time)
				{
					g_aEnemy[nCntEnemy].pos.y -= 2;
					if (g_nCount % 10 == 0)
					{
						g_aEnemy[nCntEnemy].pos.x += 1;
					}
				}
				break;

				//�������E�Ɉړ����r���ŋA�҂���
			case 5:
				if (g_aEnemy[nCntEnemy].in_time < g_CntTime && g_CntTime < g_aEnemy[nCntEnemy].stop_time)
				{
					if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
					{
						g_aEnemy[nCntEnemy].pos.y += 2;
						if (g_nCount % 10 == 0)
						{
							g_aEnemy[nCntEnemy].pos.x += 1;
						}
					}
				}
				//�������Ɉړ�����
				else if (g_aEnemy[nCntEnemy].stop_time < g_CntTime && g_CntTime < g_aEnemy[nCntEnemy].out_time)
				{
					g_aEnemy[nCntEnemy].pos.x -= 2;
				}
				//�A�Ҏ��Ԃ��߂�����߂�
				else if (g_CntTime > g_aEnemy[nCntEnemy].out_time)
				{
					g_aEnemy[nCntEnemy].pos.y -= 2;
					if (g_nCount % 10 == 0)
					{
						g_aEnemy[nCntEnemy].pos.x -= 1;
					}
				}
				break;

				//�v���C���[�̕����Ɉړ�����
			case 6:
				//�o�ė��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
				if (g_aEnemy[nCntEnemy].in_time < g_CntTime && g_CntTime < g_aEnemy[nCntEnemy].stop_time)
				{
					g_aEnemy[nCntEnemy].pos.y += 2;
				}
				//��~���ԉ߂�����v���C���[�̕����Ɉړ�����
				else if (g_aEnemy[nCntEnemy].stop_time < g_CntTime)
				{
					if (g_aEnemy[nCntEnemy].time >= 1 && pPlayer->bUse == true)
					{
						movevec = pPlayer->pos - g_aEnemy[nCntEnemy].pos;	//�G�l�~�[����v���C���[�܂ł̕����x�N�g�������߂�

						D3DXVec3Normalize(&movevec, &movevec);				//�x�N�g���𐳋K������(�x�N�g�����P�ɂ���) (�������@, ����������O)

						movevec = movevec * 10;								//�������������Ɉړ��ʂ�^����

						g_aEnemy[nCntEnemy].pos += movevec;					//�e�̈ʒu���X�V����
						g_aEnemy[nCntEnemy].move = movevec;
						g_aEnemy[nCntEnemy].time--;
					}
					else if (pPlayer->bUse == false)
					{
						g_aEnemy[nCntEnemy].pos.y += 2;
					}
					else
					{
						//�e�̈ʒu�X�V
						g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
						g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
					}
				}
				break;
				//�W�O�U�O�Ɉړ�
			case 7:
					//�o�ė��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
					if (g_aEnemy[nCntEnemy].in_time < g_CntTime)
					{
						g_aEnemy[nCntEnemy].nCntMove++;

							if (g_aEnemy[nCntEnemy].Reversal == false)
							{
								g_aEnemy[nCntEnemy].pos.x -= 3;
								g_aEnemy[nCntEnemy].pos.y += 2;
								if (g_aEnemy[nCntEnemy].pos.x < 10)
								{
									g_aEnemy[nCntEnemy].Reversal = true;
									g_aEnemy[nCntEnemy].nCntMove = 0;

								}
								else if (g_aEnemy[nCntEnemy].nCntMove >= 120)
								{
									g_aEnemy[nCntEnemy].Reversal = true;
									g_aEnemy[nCntEnemy].nCntMove = 0;
								}
							}
							else if (g_aEnemy[nCntEnemy].Reversal == true)
							{
								g_aEnemy[nCntEnemy].pos.x += 3;
								g_aEnemy[nCntEnemy].pos.y += 2;

								if (g_aEnemy[nCntEnemy].pos.x > 950)
								{
									g_aEnemy[nCntEnemy].Reversal = false;
									g_aEnemy[nCntEnemy].nCntMove = 0;
								}
								else if (g_aEnemy[nCntEnemy].nCntMove >= 120)
								{
									g_aEnemy[nCntEnemy].Reversal = false;
									g_aEnemy[nCntEnemy].nCntMove = 0;
								}
							}
					}
					break;
			case 71:
				//�o�ė��Ă���~�܂鎞�Ԃ܂ł̊ԂȂ牺�Ɉړ�
				if (g_aEnemy[nCntEnemy].in_time < g_CntTime)
				{
					g_aEnemy[nCntEnemy].nCntMove++;

					if (g_aEnemy[nCntEnemy].Reversal == false)
					{
						g_aEnemy[nCntEnemy].pos.x += 3;
						g_aEnemy[nCntEnemy].pos.y += 2;
						if (g_aEnemy[nCntEnemy].pos.x < 10)
						{
							g_aEnemy[nCntEnemy].Reversal = true;
							g_aEnemy[nCntEnemy].nCntMove = 0;

						}
						else if (g_aEnemy[nCntEnemy].nCntMove >= 120)
						{
							g_aEnemy[nCntEnemy].Reversal = true;
							g_aEnemy[nCntEnemy].nCntMove = 0;
						}
					}
					else if (g_aEnemy[nCntEnemy].Reversal == true)
					{
						g_aEnemy[nCntEnemy].pos.x -= 3;
						g_aEnemy[nCntEnemy].pos.y += 2;

						if (g_aEnemy[nCntEnemy].pos.x > 950)
						{
							g_aEnemy[nCntEnemy].Reversal = false;
							g_aEnemy[nCntEnemy].nCntMove = 0;
						}
						else if (g_aEnemy[nCntEnemy].nCntMove >= 120)
						{
							g_aEnemy[nCntEnemy].Reversal = false;
							g_aEnemy[nCntEnemy].nCntMove = 0;
						}
					}
				}
				break;
				//==============================
				//������o������ړ��p�^�[��
				//=============================

				//�~�܂炸���Ɉړ�����(������E)
			case 8:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					g_aEnemy[nCntEnemy].pos.x += 2;
				}
				break;
				//�V�i�E���獶�j
			case 9:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					g_aEnemy[nCntEnemy].pos.x -= 2;
				}
				break;
				//�v���C���[��X������v����܂ŉ��Ɉړ�����(��)
			case 10:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					if (g_aEnemy[nCntEnemy].m_switch == false)
					{
						g_aEnemy[nCntEnemy].nBullet++;//�J�E���^�[�����Z
						if ((g_aEnemy[nCntEnemy].nBullet % 60) == 0)
						{
							g_aEnemy[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
							SetEnemyBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5, 0.0f), BULLETTYPE_E_LINE, g_aEnemy[nCntEnemy].sType);
						}
						g_aEnemy[nCntEnemy].pos.x += 2;

						if (pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x - 32 &&
							pPlayer->pos.x <= g_aEnemy[nCntEnemy].pos.x + 32
							&& pPlayer->bUse == true)
						{
							g_aEnemy[nCntEnemy].m_switch = true;
						}
					}
					//��v�����牺�Ɉړ�����
					else if (g_aEnemy[nCntEnemy].m_switch == true)
					{
						g_aEnemy[nCntEnemy].pos.y += 15;
					}
				}
				break;
				//�v���C���[��X������v����܂ŉ��Ɉړ�����(�E)
			case 11:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					if (g_aEnemy[nCntEnemy].m_switch == false)
					{
						g_aEnemy[nCntEnemy].nBullet++;//�J�E���^�[�����Z
						if ((g_aEnemy[nCntEnemy].nBullet % 60) == 0)
						{
							g_aEnemy[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
							SetEnemyBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5, 0.0f), BULLETTYPE_E_LINE, g_aEnemy[nCntEnemy].sType);
						}
						g_aEnemy[nCntEnemy].pos.x -= 2;

						if (pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x - 32 &&
							pPlayer->pos.x <= g_aEnemy[nCntEnemy].pos.x + 32
							&& pPlayer->bUse == true)
						{
							g_aEnemy[nCntEnemy].m_switch = true;
						}
					}
					//��v�����牺�Ɉړ�����
					else if (g_aEnemy[nCntEnemy].m_switch == true)
					{
						g_aEnemy[nCntEnemy].pos.y += 15;
					}
				}
				break;
				//�v���C���[��X������v����܂ŉ��Ɉړ�����(��)
			case 12:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					if (g_aEnemy[nCntEnemy].m_switch == false)
					{
						g_aEnemy[nCntEnemy].nBullet++;//�J�E���^�[�����Z
						if ((g_aEnemy[nCntEnemy].nBullet % 60) == 0)
						{
							g_aEnemy[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
							SetEnemyBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5, 0.0f), BULLETTYPE_E_LINE, g_aEnemy[nCntEnemy].sType);
						}
						g_aEnemy[nCntEnemy].pos.x += 2;

						if (pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x - 64 &&
							pPlayer->pos.x <= g_aEnemy[nCntEnemy].pos.x + 64
							&& pPlayer->bUse == true)
						{
							g_aEnemy[nCntEnemy].m_switch = true;
						}
					}
					//��v������1�����ǔ����邷��
					else if (g_aEnemy[nCntEnemy].m_switch == true)
					{
						if (g_aEnemy[nCntEnemy].Tracking >= 1)
						{
							movevec = pPlayer->pos - g_aEnemy[nCntEnemy].pos;	//�e����v���C���[�܂ł̕����x�N�g�������߂�

							D3DXVec3Normalize(&movevec, &movevec);				//�x�N�g���𐳋K������(�x�N�g�����P�ɂ���) (�������@, ����������O)

							movevec = movevec * 5;								//�������������Ɉړ��ʂ�^����

							g_aEnemy[nCntEnemy].pos += movevec;					//�e�̈ʒu���X�V����
							g_aEnemy[nCntEnemy].move = movevec;
							g_aEnemy[nCntEnemy].Tracking--;
						}
						//�O�b�ɂȂ����璼�i����
						else if (g_aEnemy[nCntEnemy].Tracking == 0)
						{
							//�e�̈ʒu�X�V
							g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
							g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
						}
					}
				}
				break;
				//�v���C���[��X������v����܂ŉ��Ɉړ�����(�E)
			case 13:
				if (g_aEnemy[nCntEnemy].in_time <= g_CntTime)
				{
					if (g_aEnemy[nCntEnemy].m_switch == false)
					{
						g_aEnemy[nCntEnemy].nBullet++;//�J�E���^�[�����Z
						if ((g_aEnemy[nCntEnemy].nBullet % 60) == 0)
						{
							g_aEnemy[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
							SetEnemyBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5, 0.0f), BULLETTYPE_E_LINE, g_aEnemy[nCntEnemy].sType);
						}
						g_aEnemy[nCntEnemy].pos.x -= 2;

						if (pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x - 64 &&
							pPlayer->pos.x <= g_aEnemy[nCntEnemy].pos.x + 64
							&& pPlayer->bUse == true)
						{
							g_aEnemy[nCntEnemy].m_switch = true;
						}
					}
					//��v�����牺�Ɉړ�����
					else if (g_aEnemy[nCntEnemy].m_switch == true)
					{
						if (g_aEnemy[nCntEnemy].Tracking >= 1)
						{
							movevec = pPlayer->pos - g_aEnemy[nCntEnemy].pos;	//�e����v���C���[�܂ł̕����x�N�g�������߂�

							D3DXVec3Normalize(&movevec, &movevec);				//�x�N�g���𐳋K������(�x�N�g�����P�ɂ���) (�������@, ����������O)

							movevec = movevec * 5;								//�������������Ɉړ��ʂ�^����

							g_aEnemy[nCntEnemy].pos += movevec;					//�e�̈ʒu���X�V����
							g_aEnemy[nCntEnemy].move = movevec;
							g_aEnemy[nCntEnemy].Tracking--;
						}
						else if (g_aEnemy[nCntEnemy].Tracking == 0)
						{
							//�e�̈ʒu�X�V
							g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
							g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
						}
					}
				}
				break;
			}

			//��ʂ���͂ݏo������G���\���ɂ���
			if (g_aEnemy[nCntEnemy].pos.x < -30 || g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH - 220)
			{
				//X���W���͈͊O�̏ꍇ
				g_aEnemy[nCntEnemy].bDrw = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}
			if (g_aEnemy[nCntEnemy].pos.y < -45 || g_aEnemy[nCntEnemy].pos.y > SCREEN_HEIGHT)
			{
				//Y���W���͈͊O�̏ꍇ
				g_aEnemy[nCntEnemy].bDrw = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					//���\�\�\�\�\�\�\�\�\�\�\�\��
					//�b�@�@�@ ���_�J���[ �@�@�@�b
					//���\�\�\�\�\�\�\�\�\�\�\�\��
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�|���S����ʏ�F�ɖ߂�
				}
				break;
			}


			//g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - SIZE_ENEMY / 2;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - SIZE_ENEMY / 2;
			pVtx[0].pos.z = 0;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + SIZE_ENEMY / 2;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - SIZE_ENEMY / 2;
			pVtx[1].pos.z = 0;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - SIZE_ENEMY / 2;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + SIZE_ENEMY / 2;
			pVtx[2].pos.z = 0;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + SIZE_ENEMY / 2;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + SIZE_ENEMY / 2;
			pVtx[3].pos.z = 0;

			
			switch (g_aEnemy[nCntEnemy].s_pattern)
			{
			case BULLETTYPE_E_LINE:
				g_aEnemy[nCntEnemy].nBullet++;//�J�E���^�[�����Z
				if ((g_aEnemy[nCntEnemy].nBullet % 60) == 0)
				{
					g_aEnemy[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
					SetEnemyBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5, 0.0f), BULLETTYPE_E_LINE, g_aEnemy[nCntEnemy].sType);
				}
				break;

			case BULLETTYPE_E_AIM:
				g_aEnemy[nCntEnemy].nBullet++;//�J�E���^�[�����Z
				if ((g_aEnemy[nCntEnemy].nBullet % 90) == 0)
				{
					g_aEnemy[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
					SetEnemyBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5., 0.0f), BULLETTYPE_E_AIM, g_aEnemy[nCntEnemy].sType);
				}
				break;

			case BULLETTYPE_E_HOMING:
				g_aEnemy[nCntEnemy].nBullet++;//�J�E���^�[�����Z
				if ((g_aEnemy[nCntEnemy].nBullet % 90) == 0)
				{
					g_aEnemy[nCntEnemy].nBullet = 0;//�J�E���^�[�������l�ɖ߂�
					SetEnemyBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5., 0.0f), BULLETTYPE_E_HOMING, g_aEnemy[nCntEnemy].sType);
				}
				break;
			case 99:
				break;
			}
		}
		else if (g_aEnemy[nCntEnemy].bUse == false)
		{
			if (g_aEnemy[nCntEnemy].in_time == g_CntTime)
			{
				pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - SIZE_ENEMY / 2;
				pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - SIZE_ENEMY / 2;
				pVtx[0].pos.z = 0;
				pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + SIZE_ENEMY / 2;
				pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - SIZE_ENEMY / 2;
				pVtx[1].pos.z = 0;
				pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - SIZE_ENEMY / 2;
				pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + SIZE_ENEMY / 2;
				pVtx[2].pos.z = 0;
				pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + SIZE_ENEMY / 2;
				pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + SIZE_ENEMY / 2;
				pVtx[3].pos.z = 0;

				g_aEnemy[nCntEnemy].bUse = true;	//�G���g�p���Ă����Ԃɂ���
				g_aEnemy[nCntEnemy].bHit = true;	//�G�̓����蔻����I���ɂ���
				g_aEnemy[nCntEnemy].bDrw = true;	//�G��\������
				g_nNumEnemy++;						//���݂���G�̐������Z
				g_nArrivalEnemy++;					//�o�������G�̐����Z
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//��==========================��
//�b�@�@�@ �G�̕`�揈���@�@ �@�b
//��==========================��
void DrawEnemy(void)
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
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bDrw == true)
		{//�G���g�p����Ă���

			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//��==========================��
//�b�@�@�@ �G�̔��菈���@�@ �@�b
//��==========================��

//�G�̓����蔻��
void CollisionEnemy(Enemy *pEnemy)
{
	int nCntEnemy;

	Player *pPlayer = Getplayer(); //�v���C���[�̏��ւ̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bHit == true && pPlayer->bUse == true)
		{//�G���g�p����Ă���
			if (pEnemy->pos.x >= pPlayer->pos.x - 32
				&& pEnemy->pos.x <= pPlayer->pos.x + 32
				&& pEnemy->pos.y >= pPlayer->pos.y - 32
				&& pEnemy->pos.y <= pPlayer->pos.y + 32)
			{//�G�ƃv���C���[����������

				HitPlayer(nCntEnemy, 1);

			}
		}
	}
}
//��============================��
//�b�@�@�@ �G�̃q�b�g�����@�@ �@�b
//��============================��
void HitEnemy(int nCntEnemy, int nDamage)
{
	if (g_aEnemy[nCntEnemy].bHit == true)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;

		if (g_aEnemy[nCntEnemy].nLife <= 0)//�G�̗̑͂��Ȃ��Ȃ���
		{
			//�����̐ݒ�
			switch (g_aEnemy[nCntEnemy].nType)
			{
			case 0:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 20, 10.0f, 0,0);
				break;
			case 1:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 20, 10.0f, 0,0);
				break;
			case 2:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 20, 10.0f, 1,0);
				break;
			case 3:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 20, 10.0f, 4, 0);
				break;
			case 4:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 20, 10.0f, 5, 0);
				break;
			}

			//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			PlaySound(SOUND_LABEL_SE_EXPLOSION); //���Đ��������T�E���h���w��

			g_aEnemy[nCntEnemy].bUse = false;
			g_aEnemy[nCntEnemy].bDrw = false;
			g_aEnemy[nCntEnemy].bHit = false;

			g_nNumEnemy--;		//���݂̓G�̐�
			g_nTotalEnemy--;	//�G�̑��������炷
			AddScore(g_aEnemy[nCntEnemy].score);
		}

		else
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			PlaySound(SOUND_LABEL_SE_HIT); //���Đ��������T�E���h���w��
			g_aEnemy[nCntEnemy].nCounterState = 10; //�_���[�W��ۂ��Ԃ�ݒ�

			VERTEX_2D *pVtx;	//�ݒ�p�|�C���^

			//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
			g_pVtxBuffEnemy->Lock(0, 0, (void **)&pVtx, 0);

			switch (g_aEnemy[nCntEnemy].nType)
			{
			case 0:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 5, 6.0f, 0,0);
				break;
			case 1:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 5, 6.0f, 0,0);
				break;
			case 2:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 5, 6.0f, 1,0);
				break;
			case 3:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 20, 10.0f, 4, 0);
				break;
			case 4:
				SetParticle(g_aEnemy[nCntEnemy].pos, 0, 20, 10.0f, 5, 0);
				break;
			}

			pVtx += nCntEnemy * 4;
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b�@�@�@ ���_�J���[ �@�@�@�b
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f); //�|���S���̃_���[�W�F�ɐݒ�

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffEnemy->Unlock();
		}
	}
}
//��====================��
//�b�@ �G�̑����̎擾�@ �b
//��====================��
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}
//��======================��
//�b�@�@�@ �G�̏����@�@ �@�b
//��======================��
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];//�G�̏��̐擪�A�h���X��Ԃ�
}
//��================��
//�b �o�ߎ��Ԃ̏��� �b
//��================��
int GetCunt(void)
{
	return g_CntTime;
}
//��====================================��
//�b�@�@�@ �G�l�~�[�f�[�^�ǂݍ��݁@�@ �@�b
//��====================================��
void LoadEnemy(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int line   = 0;//�s���𐔂���ϐ�
	int nCntEnemy; //�J�E���g�ϐ�

	char aData[100];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data/csv/enemydata.csv", "r");

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
		case 1:		g_aEnemy[line].nType = atoi(aData);			 break;	//�P��ځF�G�E���
		case 2:		g_aEnemy[line].sType = atoi(aData);			 break;	//  ��ځF�e�E���
		case 3:		g_aEnemy[line].m_pattern = atoi(aData);		 break;	//�@��ځF�ړ��p�^�[��
		case 4:		g_aEnemy[line].s_pattern = atoi(aData);		 break;	//�@��ځF���˃p�^�[��
		case 5:		g_aEnemy[line].in_time = atoi(aData);		 break;	//�@��ځF�o������
		case 6:		g_aEnemy[line].stop_time = atoi(aData);		 break;	//�@��ځF��~����
		case 7:		g_aEnemy[line].shot_time = atoi(aData);		 break;	//�@��ځF�e ���ˎ���
		case 8:		g_aEnemy[line].out_time = atoi(aData);		 break;	//�@��ځF�A�Ҏ���
		case 9:		g_aEnemy[line].pos.x = (float)(atoi(aData)); break;	//�@��ځFX���W
		case 10:	g_aEnemy[line].pos.y = (float)(atoi(aData)); break;	//�@��ځFY���W
		case 11:	g_aEnemy[line].nLife = atoi(aData);			 break;	//�@��ځF�̗�
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
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].nType == 1)
		{
			g_aEnemy[nCntEnemy].score = 100;
		}
		else if (g_aEnemy[nCntEnemy].nType == 2)
		{

			g_aEnemy[nCntEnemy].score = 200;
		}
		else if (g_aEnemy[nCntEnemy].nType == 3)
		{
			g_aEnemy[nCntEnemy].score = 300;
		}
		else if (g_aEnemy[nCntEnemy].nType == 4)
		{
			g_aEnemy[nCntEnemy].score = 50;
		}
	}
}
//��==========================��
//�b�@�@�@ �G�̐ݒ菈��1�@ �@�b
//��==========================��
//void SetEnemy(D3DXVECTOR3 pos, int nType)
//{
//	int nCntEnemy;
//
//	//�ݒ�p�|�C���^
//	VERTEX_2D *pVtx;
//
//	//���_�o�b�t�@�̃��b�N
//	g_pVtxBuffSummon->Lock(0, 0, (void **)&pVtx, 0);
//
//	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
//	{
//		if (g_aEnemy[nCntEnemy].bUse == false)
//		{
//			g_aEnemy[nCntEnemy].pos = pos;
//			g_aEnemy[nCntEnemy].nType = nType;
//			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
//			g_aEnemy[nCntEnemy].curt_nLife = 2;
//
//			//���\�\�\�\�\�\�\�\�\�\�\�\��
//			//�b �@�@���_���W��ݒ�@�@ �b
//			//���\�\�\�\�\�\�\�\�\�\�\�\��
//
//			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - SIZE_ENEMY / 2, g_aEnemy[nCntEnemy].pos.y - SIZE_ENEMY / 2, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + SIZE_ENEMY / 2, g_aEnemy[nCntEnemy].pos.y - SIZE_ENEMY / 2, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - SIZE_ENEMY / 2, g_aEnemy[nCntEnemy].pos.y + SIZE_ENEMY / 2, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + SIZE_ENEMY / 2, g_aEnemy[nCntEnemy].pos.y + SIZE_ENEMY / 2, 0.0f);
//
//
//			g_nNumSummon++; //�G�̑��������Z����
//			g_aEnemy[nCntEnemy].bUse = true; //�e���g�p���Ă����Ԃɂ���
//
//			break;
//		}
//		pVtx += 4; //�Y���̈ʒu�܂Ői�߂�
//	}
//	//���_�o�b�t�@�̃A�����b�N
//	g_pVtxBuffSummon->Unlock();
//}