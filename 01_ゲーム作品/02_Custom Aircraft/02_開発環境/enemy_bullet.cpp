//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�@�@�G�̒e�����@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "enemy_bullet.h"
#include "effect.h"
#include"particle.h"
#include"enemy.h"
#include"boss.h"
#include"Summon.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define MAX_BULLET (800)		//�e�̍ő吔
#define BULLET_SPEED (4.0f)		//�e�̃X�s�[�h
#define MAX_ENEMY_BULLET (6)	//�e�̎��
//��==================��
//�b�@ �\���̂̒�` �@�b
//��==================��
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	float rot;			//����
	int nLife;			//����
	BULLETTYPE_E type;	//���
	int stype;			//�e�@�摜
	int speed;			//�e�X�s�[�h
	int time;			//���ԁi�ǐՎ��ԁj
	bool bUse;			//�g�p���Ă��邩�ǂ���
}eBullet;

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void CollisionPlayer(eBullet *pBullet);

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DTEXTURE9		g_pTextureEnemyBullet[MAX_ENEMY_BULLET] = {};		 //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyBullet = NULL;		 //���_�o�b�t�@�|�C���^
static eBullet g_aBullet[MAX_BULLET];//�e�̏��

//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�e�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��============================��
//�b�@�@�@ �e�̏����������@�@ �@�b
//��============================��
void InitEnemyBullet(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntBullet;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\eff_shot_001_01_red.PNG",
		&g_pTextureEnemyBullet[0]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\eff_shot_001_01_blue.PNG",
		&g_pTextureEnemyBullet[1]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\eff_shot_001_01_green.PNG",
		&g_pTextureEnemyBullet[2]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\eff_shot_001_01_yellow.PNG",
		&g_pTextureEnemyBullet[3]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\eff_shot_001_01_white.PNG",
		&g_pTextureEnemyBullet[4]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\cleanness.png",
		&g_pTextureEnemyBullet[5]);

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemyBullet,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffEnemyBullet->Lock(0, 0, (void **)&pVtx, 0);

	nCntBullet = 0;

	//�e�̏��̏���������
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = LIFE_DATA1/2;
		g_aBullet[nCntBullet].time = 10;
		g_aBullet[nCntBullet].bUse = false;


		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
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

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemyBullet->Unlock();
}
//��==========================��
//�b�@�@�@ �e�̏I�������@�@ �@�b
//��==========================��
void UninitEnemyBullet(void)
{
	int nCntBullet;

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntBullet = 0; nCntBullet < MAX_ENEMY_BULLET; nCntBullet++)
	{
		if (g_pTextureEnemyBullet[nCntBullet] != NULL)
		{
			g_pTextureEnemyBullet[nCntBullet]->Release();
			g_pTextureEnemyBullet[nCntBullet] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxBuffEnemyBullet != NULL)
	{
		g_pVtxBuffEnemyBullet->Release();
		g_pVtxBuffEnemyBullet = NULL;
	}
}
//��==========================��
//�b�@�@�@ �e�̍X�V�����@�@ �@�b
//��==========================��
void UpdateEnemyBullet(void)
{
	int nCntBullet;
	//float fRotMove, fRotDest, fRotDiff, fRotTotal;//���݂̈ړ������E�ڕW�̈ړ������E�ڕW�̈ړ������܂ł̍����E�Q�̊p�x�̍��v

	Enemy *pEnemy = GetEnemy();		//�G�̏��ւ̃|�C���^
	Player *pPlayer = Getplayer();	//�v���C���[�̏��ւ̃|�C���^

								   //�e�N�X�`�����W�̍X�V
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemyBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���

		 //�G�l�~�[�̒e
			CollisionPlayer(&g_aBullet[nCntBullet]);

			D3DXVECTOR3 movevec;

			switch (g_aBullet[nCntBullet].type)
			{
			case BULLETTYPE_E_LINE:

				//�e�̈ʒu�X�V
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				break;
			case BULLETTYPE_E_AIM:

				if (g_aBullet[nCntBullet].time >= 1 && pPlayer->bUse == true)
				{
					movevec = pPlayer->pos - g_aBullet[nCntBullet].pos;//�e����v���C���[�܂ł̕����x�N�g�������߂�

					D3DXVec3Normalize(&movevec, &movevec);				//�x�N�g���𐳋K������(�x�N�g�����P�ɂ���) (�������@, ����������O)

					movevec = movevec * BULLET_SPEED;					//�������������Ɉړ��ʂ�^����

					g_aBullet[nCntBullet].pos += movevec;				//�e�̈ʒu���X�V����
					g_aBullet[nCntBullet].move = movevec;
					g_aBullet[nCntBullet].time--;
				}
				else
				{
					//�e�̈ʒu�X�V
					g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
					g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				}
				break;
			case BULLETTYPE_E_HOMING:

				//g_aBullet[nCntBullet].time--;
				//if (g_aBullet[nCntBullet].time >= 1)
				//{
				//	fRotMove = atan2f(g_aBullet[nCntBullet].pos.x,g_aBullet[nCntBullet].pos.y);	//���݂̈ړ�����
				//	fRotDest = atan2f(g_aBullet[nCntBullet].pos.x - pPlayer->pos.x, g_aBullet[nCntBullet].pos.y - pPlayer->pos.y);	//�ڕW�̈ړ�����
				//	fRotDiff = fRotDest - fRotMove;																					//�ڕW�̈ړ������܂ł̍���
				//	if (fRotDiff >= D3DX_PI)
				//	{
				//		fRotDiff = fRotDiff - D3DX_PI * 2;
				//	}
				//	else if (fRotDiff <= -D3DX_PI)
				//	{
				//		fRotDiff = fRotDiff + D3DX_PI * 2;
				//	}
				//	fRotMove += fRotDiff * 0.5f;	//�ړ������i�p�x�j�̕␳
				//	if (fRotMove >= D3DX_PI)
				//	{
				//		fRotMove = fRotMove - D3DX_PI * 2;
				//	}
				//	else if (fRotMove <= -D3DX_PI)
				//	{
				//		fRotMove = fRotMove + D3DX_PI * 2;
				//	}
				//	g_aBullet[nCntBullet].move.x = sinf(fRotMove) * 5;
				//	g_aBullet[nCntBullet].move.y = cosf(fRotMove) * 5;
				//}
				//else if (g_aBullet[nCntBullet].time == 0)
				//{
				//	g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				//	g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				//}	


				if (g_aBullet[nCntBullet].time >= 1 && pPlayer->bUse == true)
				{
					movevec = pPlayer->pos - g_aBullet[nCntBullet].pos;//�e����v���C���[�܂ł̕����x�N�g�������߂�

					D3DXVec3Normalize(&movevec, &movevec);				//�x�N�g���𐳋K������(�x�N�g�����P�ɂ���) (�������@, ����������O)

					movevec = movevec * BULLET_SPEED;					//�������������Ɉړ��ʂ�^����

					g_aBullet[nCntBullet].pos += movevec;				//�e�̈ʒu���X�V����
					g_aBullet[nCntBullet].move = movevec;
					g_aBullet[nCntBullet].time--;
				}
				else
				{
					//�e�̈ʒu�X�V
					g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
					g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				}
				break;
			case BULLETTYPE_E_3_SHOT:
				//�e�̈ʒu�X�V
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				break;
			case BULLETTYPE_E_MACHINEGUN:

				if (g_aBullet[nCntBullet].time >= 1 && pPlayer->bUse == true)
				{
					movevec = pPlayer->pos - g_aBullet[nCntBullet].pos;//�e����v���C���[�܂ł̕����x�N�g�������߂�

					D3DXVec3Normalize(&movevec, &movevec);				//�x�N�g���𐳋K������(�x�N�g�����P�ɂ���) (�������@, ����������O)

					movevec = movevec * BULLET_SPEED * 2;				//�������������Ɉړ��ʂ�^����

					g_aBullet[nCntBullet].pos += movevec;				//�e�̈ʒu���X�V����
					g_aBullet[nCntBullet].move = movevec;
					g_aBullet[nCntBullet].stype = 5;
					g_aBullet[nCntBullet].time--;
				}
				else
				{
					//�e�̈ʒu�X�V
					g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
					g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				}
				break;
			case BULLETTYPE_E_3_SHOT2:
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				break;
			case BULLETTYPE_E_CHARGE_SHOT:
				if (g_aBullet[nCntBullet].time >= 1 && pPlayer->bUse == true)
				{
					movevec = pPlayer->pos - g_aBullet[nCntBullet].pos;//�e����v���C���[�܂ł̕����x�N�g�������߂�

					D3DXVec3Normalize(&movevec, &movevec);				//�x�N�g���𐳋K������(�x�N�g�����P�ɂ���) (�������@, ����������O)

					movevec = movevec * BULLET_SPEED * 2;				//�������������Ɉړ��ʂ�^����

					g_aBullet[nCntBullet].pos += movevec;				//�e�̈ʒu���X�V����
					g_aBullet[nCntBullet].move = movevec;
					g_aBullet[nCntBullet].stype = 5;
					g_aBullet[nCntBullet].time--;
				}
				else
				{
					//�e�̈ʒu�X�V
					g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
					g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				}
				break;
			}
			
			//���_���W�̍X�V
			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - 24 / 2;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - 24 / 2;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + 24 / 2;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - 24 / 2;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - 24 / 2;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + 24 / 2;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + 24 / 2;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + 24 / 2;

			//�e�̋O�Ղ�ݒ�
			switch (g_aBullet[nCntBullet].type)
			{
			case BULLETTYPE_E_LINE:
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 12.0f, 10, 0);
				break;
			case BULLETTYPE_E_AIM:
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 12.0f, 10, 0);
				break;
			case BULLETTYPE_E_HOMING:
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 12.0f, 10, 0);
				break;
			case BULLETTYPE_E_3_SHOT:
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 12.0f, 10, 0);
				break;
			case BULLETTYPE_E_MACHINEGUN:
				SetParticle(g_aBullet[nCntBullet].pos, 4, 2, 5.0f, 1, 4);
				break;
			case BULLETTYPE_E_3_SHOT2:
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 12.0f, 10, 0);
				break;
			case BULLETTYPE_E_CHARGE_SHOT:
				SetParticle(g_aBullet[nCntBullet].pos, 4, 2, 5.0f, 1, 4);
				break;
			}
			if (g_aBullet[nCntBullet].pos.x < 0 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH - 310)
			{//X���W���͈͊O�̏ꍇ
				g_aBullet[nCntBullet].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
				switch (g_aBullet[nCntBullet].type)
				{
				case 0:
					//�����̐ݒ�
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 0, 0);
					break;
				case 1:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 1, 0);
					break;
				case 2:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				case 3:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				case BULLETTYPE_E_MACHINEGUN:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				case BULLETTYPE_E_3_SHOT2:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				}
			}
			if (g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
			{//Y���W���͈͊O�̏ꍇ
				g_aBullet[nCntBullet].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
				switch (g_aBullet[nCntBullet].type)
				{
				case 0:
					//�����̐ݒ�
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 0, 0);
					break;
				case 1:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 1, 0);
					break;
				case 2:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				case 3:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				case BULLETTYPE_E_MACHINEGUN:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				case BULLETTYPE_E_3_SHOT2:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				}
			}

			//�����̃J�E���g�_�E��
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				switch (g_aBullet[nCntBullet].type)
				{
				case 0:
					//�����̐ݒ�
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 0,0);
					break;
				case 1:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 1,0);
					break;
				case 2:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2,0);
					break;
				case 3:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				case BULLETTYPE_E_MACHINEGUN:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				case BULLETTYPE_E_3_SHOT2:
					SetParticle(g_aBullet[nCntBullet].pos, 0, 2, 5.0f, 2, 0);
					break;
				}
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				g_aBullet[nCntBullet].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemyBullet->Unlock();
}
//��==========================��
//�b�@�@�@ �e�̕`�揈���@�@ �@�b
//��==========================��
void DrawEnemyBullet(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntBullet;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemyBullet, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			pDevice->SetTexture(0, g_pTextureEnemyBullet[g_aBullet[nCntBullet].stype]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//��==========================��
//�b�@�@�@ �e�̐ݒ菈���@�@ �@�b
//��==========================��
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE_E type,int stype)
{
	int nCntBullet;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemyBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].stype = stype;

			if (g_aBullet[nCntBullet].type == BULLETTYPE_E_MACHINEGUN)
			{
				g_aBullet[nCntBullet].nLife = LIFE_DATA1 * 4;
			}
			else
			{
				g_aBullet[nCntBullet].nLife = LIFE_DATA1 * 2;
			}

			//�G�C���ƃz�[�~���O�̒ǐՎ��Ԃ��ʂɐݒ�
			if (g_aBullet[nCntBullet].type == 1)
			{
				g_aBullet[nCntBullet].time = 1;
			}
			else if (g_aBullet[nCntBullet].type == 2)
			{
				g_aBullet[nCntBullet].time = 30;
			}
			else if (g_aBullet[nCntBullet].type == 4)
			{
				g_aBullet[nCntBullet].time = 1;
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_E_MACHINEGUN)
			{
				g_aBullet[nCntBullet].time = 1;
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_E_CHARGE_SHOT)
			{
				g_aBullet[nCntBullet].time = 1;
			}
			
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b �@�@���_���W��ݒ�@�@ �b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - SIZE_ENEMY / 3;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - SIZE_ENEMY / 3;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + SIZE_ENEMY / 3;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - SIZE_ENEMY / 3;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - SIZE_ENEMY / 3;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + SIZE_ENEMY / 3;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + SIZE_ENEMY / 3;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + SIZE_ENEMY / 3;
			g_aBullet[nCntBullet].bUse = true; //�e���g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4; //�Y���̈ʒu�܂Ői�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemyBullet->Unlock();
}
//��==========================��
//�b�@�@�@ �e�̔��菈���@�@ �@�b
//��==========================��

//�v���C���[�����蔻��
void CollisionPlayer(eBullet *pBullet)
{
	int nCntEnemy;

	Player *pPlayer = Getplayer(); //�v���C���[�̏��ւ̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < MAX_BULLET; nCntEnemy++)
	{

		if (pPlayer->bUse == true && pBullet->bUse == true)
		{
			if (pBullet->pos.x >= pPlayer->pos.x - 24 &&
				pBullet->pos.x <= pPlayer->pos.x + 24 &&
				pBullet->pos.y >= pPlayer->pos.y - 24 &&
				pBullet->pos.y <= pPlayer->pos.y + 24)
			{//�v���C���[�ƒe����������

				HitPlayer(nCntEnemy, 1);

				SetParticle(pBullet->pos, 0, 10, 10.0f, 0, 0);

				pBullet->bUse = false;

			}
		}
	}
}
