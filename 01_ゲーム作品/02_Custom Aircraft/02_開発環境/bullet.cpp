//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�@�@�e�̏����@�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include"bullet.h"
#include"effect.h"
#include"particle.h"
#include"Summon.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define MAX_BULLET (400)  //�e�̍ő吔

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void CollisionEnemy	(Bullet *pBullet);
void CollisionSummon(Bullet *pBullet);
void CollisionBoss(Bullet *pBullet);
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DTEXTURE9		g_pTextureBullet[2] = {};			 //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		 //���_�o�b�t�@�|�C���^
Bullet g_aBullet[MAX_BULLET];//�e�̏��
float g_fLengthBullit;									    //�Ίp���̒���
float g_fAngleBullit;									    //�Ίp���̊p�x

//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�e�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��============================��
//�b�@�@�@ �e�̏����������@�@ �@�b
//��============================��
void InitBullet(void)
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
		".\\data\\TEXTURE\\Bullet.png",
		&g_pTextureBullet[0]);

	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Human soul.png",
		&g_pTextureBullet[1]);

	//���_�o�b�t�@�̐���                           ���K�v�Ȓ��_��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	nCntBullet = 0;

	//�e�̏��̏���������
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = LIFE_DATA;

		g_aBullet[nCntBullet].bUse = false;
		//�g�p���Ă��Ȃ���Ԃɂ���//�Ίp���̒������Z�o����(p��*p��+p����*p����);
		g_fLengthBullit = sqrtf(BULLET_WIDTH* BULLET_WIDTH + BULLET_HEIGHT * BULLET_HEIGHT);

		//�Ίp���̊p�x���Z�o����(p��,p����)
		g_fAngleBullit = atan2f(BULLET_WIDTH, BULLET_HEIGHT);

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
	g_pVtxBuffBullet->Unlock();
}
//��==========================��
//�b�@�@�@ �e�̏I�������@�@ �@�b
//��==========================��
void UninitBullet(void)
{
	int nCntBullet;

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntBullet = 0; nCntBullet < MAX_DATA; nCntBullet++)
	{
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//��==========================��
//�b�@�@�@ �e�̍X�V�����@�@ �@�b
//��==========================��
void UpdateBullet(void)
{
	int nCntBullet;

	//�e�N�X�`�����W�̍X�V
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���

			CollisionEnemy(&g_aBullet[nCntBullet]);
			CollisionBoss (&g_aBullet[nCntBullet]);
			CollisionSummon(&g_aBullet[nCntBullet]);

			//�e�̈ʒu�X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;


			SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10.0f,10,0);

			//���_���W�̍X�V

			/*pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot + (-D3DX_PI + g_fAngleBullit)) * g_fLengthBullit;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot + (-D3DX_PI + g_fAngleBullit)) * g_fLengthBullit;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot + (D3DX_PI - g_fAngleBullit)) * g_fLengthBullit;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot + (D3DX_PI - g_fAngleBullit)) * g_fLengthBullit;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot + (0 - g_fAngleBullit)) * g_fLengthBullit;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot + (0 - g_fAngleBullit)) * g_fLengthBullit;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot + (0 + g_fAngleBullit)) * g_fLengthBullit;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot + (0 + g_fAngleBullit)) * g_fLengthBullit;
			pVtx[3].pos.z = 0.0f;*/

			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - SIZE_ENEMY / 4;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - SIZE_ENEMY / 4;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + SIZE_ENEMY / 4;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - SIZE_ENEMY / 4;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - SIZE_ENEMY / 4; 
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + SIZE_ENEMY / 4;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + SIZE_ENEMY / 4;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + SIZE_ENEMY / 4;
			

			//SetParticle(g_aBullet[nCntBullet].pos,0);


			//�e�̈ʒu���͈͊O�ɏo������
			if (g_aBullet[nCntBullet].pos.x < 0 || g_aBullet[nCntBullet].pos.x > 1000)
			{//X���W���͈͊O�̏ꍇ
				g_aBullet[nCntBullet].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}
			if (g_aBullet[nCntBullet].pos.y < 5 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
			{//Y���W���͈͊O�̏ꍇ
				g_aBullet[nCntBullet].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}

			//�����̃J�E���g�_�E��
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife == 0)
			{
				//�����̐ݒ�
				SetParticle(g_aBullet[nCntBullet].pos, 0, 5, 6.0f,0,0);

				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				/*g_aBullet[nCntBullet].pos*/
				g_aBullet[nCntBullet].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
			}
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}
//��==========================��
//�b�@�@�@ �e�̕`�揈���@�@ �@�b
//��==========================��
void DrawBullet(void)
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
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	for (nCntBullet = 0; nCntBullet < MAX_DATA; nCntBullet++)
	{
		pDevice->SetTexture(0, g_pTextureBullet[nCntBullet]);

		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{
			if (g_aBullet[nCntBullet].bUse == true)
			{//�e���g�p����Ă���
				
			 //�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
			}
		}
	}
}

//��==========================��
//�b�@�@�@ �e�̐ݒ菈���@�@ �@�b
//��==========================��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot,BULLETTYPE type)
{
	int nCntBullet;

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].nLife = LIFE_DATA*2;
			//���\�\�\�\�\�\�\�\�\�\�\�\��
			//�b �@�@���_���W��ݒ�@�@ �b
			//���\�\�\�\�\�\�\�\�\�\�\�\��

				/*pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot + (-D3DX_PI + g_fAngleBullit)) * g_fLengthBullit;
				pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot + (-D3DX_PI + g_fAngleBullit)) * g_fLengthBullit;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot + (D3DX_PI - g_fAngleBullit)) * g_fLengthBullit;
				pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot + (D3DX_PI - g_fAngleBullit)) * g_fLengthBullit;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot + (0 - g_fAngleBullit)) * g_fLengthBullit;
				pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot + (0 - g_fAngleBullit)) * g_fLengthBullit;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + sinf(g_aBullet[nCntBullet].rot + (0 + g_fAngleBullit)) * g_fLengthBullit;
				pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + cosf(g_aBullet[nCntBullet].rot + (0 + g_fAngleBullit)) * g_fLengthBullit;
				pVtx[3].pos.z = 0.0f;
*/
				pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - SIZE_ENEMY / 4;
				pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - SIZE_ENEMY / 4;
				pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + SIZE_ENEMY / 4;
				pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - SIZE_ENEMY / 4;
				pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - SIZE_ENEMY / 4;
				pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + SIZE_ENEMY / 4;
				pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + SIZE_ENEMY / 4;
				pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + SIZE_ENEMY / 4;
			g_aBullet[nCntBullet].bUse = true; //�e���g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4; //�Y���̈ʒu�܂Ői�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//��==========================��
//�b�@�@�@ �e�̔��菈���@�@ �@�b
//��==========================��

//�G�̓����蔻��
void CollisionEnemy(Bullet *pBullet)
{
	int nCntEnemy;

	Enemy *pEnemy = GetEnemy(); //�G�̏��ւ̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{//�G���g�p����Ă���
			if (pBullet->pos.x >= pEnemy->pos.x - 32
				&& pBullet->pos.x <= pEnemy->pos.x + 32
				&& pBullet->pos.y >= pEnemy->pos.y - 32
				&& pBullet->pos.y <= pEnemy->pos.y + 32)
			{//�G�ƒe����������

				HitEnemy(nCntEnemy, 1);

				pBullet->bUse = false;

			}
		}
	}
}
//�����̓G�̓����蔻��
void CollisionSummon(Bullet *pBullet)
{
	int nCntEnemy;

	Summon *pSummon = GetSummon(); //�G�̏��ւ̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < 60; nCntEnemy++, pSummon++)
	{
		if (pSummon->bUse == true)
		{//�G���g�p����Ă���

			if (pSummon->nType == 5)
			{
				if    (pBullet->pos.x >= pSummon->pos.x - 80
					&& pBullet->pos.x <= pSummon->pos.x + 80
					&& pBullet->pos.y >= pSummon->pos.y - 80
					&& pBullet->pos.y <= pSummon->pos.y + 80)
				{//�G�ƒe����������

					HitSummon(nCntEnemy, 1);

					pBullet->bUse = false;
				}
			}
			else
			{
				if (pBullet->pos.x >= pSummon->pos.x - 32
					&& pBullet->pos.x <= pSummon->pos.x + 32
					&& pBullet->pos.y >= pSummon->pos.y - 32
					&& pBullet->pos.y <= pSummon->pos.y + 32)
				{//�G�ƒe����������

					HitSummon(nCntEnemy, 1);

					pBullet->bUse = false;
				}
			}
		}
	}
}
//�{�X�̓����蔻��
void CollisionBoss(Bullet *pBullet)
{
	int nCntEnemy;

	Boss *pBoss = GetBoss(); //�G�̏��ւ̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < 3; nCntEnemy++, pBoss++)
	{
		if (pBoss->bUse == true && pBoss->bHit == true)
		{//�G���g�p����Ă���
			if (pBullet->pos.x >= pBoss->pos.x - 80
				&& pBullet->pos.x <= pBoss->pos.x + 80
				&& pBullet->pos.y >= pBoss->pos.y - 80
				&& pBullet->pos.y <= pBoss->pos.y + 80)
			{//�G�ƒe����������

				HitBoss(nCntEnemy, 1);

				SetParticle(pBullet->pos, 0, 10, 10.0f, 0,0);

				pBullet->bUse = false;

			}
		}
	}
}
//��=============��
//�b�@�e�̏����@ �b
//��=============��
Bullet *GetBullet(void)
{
	return &g_aBullet[0];//�G�̏��̐擪�A�h���X��Ԃ�
}