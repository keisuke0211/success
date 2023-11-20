//��====================��
//�b�@�@  �@�@�@�@�@�@�@�b
//�b�@�Q�[����ʂ̏����@�b
//�b�@Author:��a�c��   �b
//�b                    �b
//��====================��
#include "game.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "sound.h"
#include "text.h"
#include "enemy_bullet.h"
#include "boss.h"
#include "fade.h"
#include "effect.h"
#include "pause.h"
#include "particle.h"
#include "frame.h"
#include "life.h"
#include "ranking_bg.h"
#include "boss_hp.h"
#include "Summon.h"
#include "aura_effect.h"
#include "TopSource.h"
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffGame = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureGame = NULL;			//�e�N�X�`���ւ̃|�C���^

GAMESTATE g_gameState = GAMESTATE_NONE;					//�Q�[���̏��
int g_nCounterGameState = 0;							//��ԊǗ��J�E���^�[
bool g_bPause = false;									//�|�[�Y��Ԃ�ON/OFF
bool bswitch = true;									//�Ȑ؂�ւ�
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�Q�[���E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��====================================��
//�b�@�@�@ �Q�[����ʂ̏����������@�@ �@�b
//��====================================��
void InitGame(void)
{

	g_gameState = GAMESTATE_NONE;
	g_nCounterGameState = 0;
	g_bPause = false;//�|�[�Y����

     //�w�i�̏���������
	InitBg();

	//�X�R�A�̏���������
	InitScore();

	//�g�b�v�X�R�A�̏���������
	InitTopScore();

	//���C�t�̏���������
	InitLife();

	//�e�L�X�g�̏���������
	InitText();

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�I�[���G�t�F�N�g����������
	InitAuraEffect();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//�G�̒e����������
	InitEnemyBullet();

	//�����̏���������
	InitExplosion();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//�����̏���������
	InitSummon();

	//�{�X�̏���������
	InitBoss();

	//HP�Q�[�W�̏���������
	InitBosshp();

	//�g�̏���������
	InitFrame();

	//�|�[�Y�̏���������
	InitPause();

	PlaySound(SOUND_LABEL_BGM001); //���Đ��������T�E���h���w��

	//SetEnemy(D3DXVECTOR3(150, 0, 0), 2);//�y�ʒu,��ށz�C�ӂ̐������ݒ肷��
	//SetEnemy(D3DXVECTOR3(150, -70, 0), 1);//�y�ʒu,��ށz�C�ӂ̐������ݒ肷��
	//SetEnemy(D3DXVECTOR3(150, -140, 0), 2);//�y�ʒu,��ށz�C�ӂ̐������ݒ肷��
	//SetEnemy(D3DXVECTOR3(150, -210, 0), 1);//�y�ʒu,��ށz�C�ӂ̐������ݒ肷��
	//SetEnemy(D3DXVECTOR3(150, -280, 0), 2);//�y�ʒu,��ށz�C�ӂ̐������ݒ肷��

	
}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̏I�������@�@ �@�b
//��==================================��
void UninitGame(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�|���S���̏I������
	UninitBg();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�I�[���G�t�F�N�g�̏I������
	UninitAuraEffect();

	//�e�̏I������
	UninitBullet();

	//�G�̒e�I������
	UninitEnemyBullet();

	//�����̏I������
	UninitExplosion();

	//�e�L�X�g�̏I������
	UninitText();

	//�X�R�A�̏I������
	UninitScore();

	//�g�b�v�X�R�A�̏I������
	UninitTopScore();

	//���C�t�̏I������
	UninitLife();

	//�v���C���[�̏I������
	UninitPlayer();

	//�G�̏I������
	UninitEnemy();

	//�����̏I������
	UninitSummon();

	//�{�X�̏I������
	UninitBoss();

	//HP�Q�[�W�̏���������
	UninitBosshp();

	//�g�̏I������
	UninitFrame();

	//�|�[�Y�̏I������
	UninitPause();

}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̍X�V�����@�@ �@�b
//��==================================��
void UpdateGame(void)
{
	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^
	Player *pPlayer = Getplayer();	//�v���C���[�̏��ւ̃|�C���^

	if (GetKeyboardTrigger(DIK_P) == true && pPlayer->bUse == true && GetFade() == FADE_NONE)
	{//�|�[�Y�L�[(P�L�[)�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	else
	{//�|�[�Y���łȂ����
	 //�w�i�̍X�V����
		UpdateBg();

		//�e�L�X�g�̍X�V����
		UpdateText();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�g�b�v�X�R�A�̍X�V����
		UpdateTopScore();

		//���C�t�̍X�V����
		UpdateLife();

		//�e�̍X�V����
		UpdateBullet();

		//�����̍X�V����
		UpdateExplosion();

		//�G�̒e�X�V����
		UpdateEnemyBullet();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�{�X�̍X�V����
		UpdateBoss();

		//�����̍X�V����
		UpdateSummon();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�I�[���G�t�F�N�g�̍X�V����
		UpdateAuraEffect();

		//HP�Q�[�W�̍X�V����
		UpdateBosshp();

		//�g�̍X�V����
		UpdateFrame();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL://�ʏ���
			break;
		case GAMESTATE_END1://�I����ԁE�G�S��
			g_nCounterGameState--;
			if (g_nCounterGameState == 0)
			{
				g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�

				//���[�h�̐ݒ�(���U���g��ʂɈڍs)
				SetFade(MODE_GAME_CLEAR);

			}
			break;
		case GAMESTATE_END2://�I����ԁE�v���C���[��
			g_nCounterGameState--;
			if (g_nCounterGameState == 0)
			{
				g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�

				 //���[�h�̐ݒ�(���U���g��ʂɈڍs)
				SetFade(MODE_GAME_OVER);

			}
			break;
		}
	}
}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̕`�揈���@�@ �@�b
//��==================================��
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBg();
	
	//�G�̕`�揈��
	DrawEnemy();

	//�I�[���G�t�F�N�g�̕`�揈��
	DrawAuraEffect();

	//�{�X�̕`�揈��
	DrawBoss();

	//�����̕`�揈��
	DrawSummon();
	
	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�e�̕`�揈��
	DrawBullet();

	//�G�̒e�`�揈��
	DrawEnemyBullet();

	//�����̕`�揈��
  	DrawExplosion();

	//HP�Q�[�W�̕`�揈��
	//DrawBosshp();

	//�g�̕`�揈��
	DrawFrame();

	//�e�L�X�g�̏���������
	DrawaText();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�g�b�v�X�R�A�̕`�揈��
	DrawTopScore();

	//���C�t�̕`�揈��
	DrawLife();

	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		UpdatePause();
	}

}

//�|�[�Y�̗L�������ݒ�
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}
//��================================��
//�b�@�@�@ �Q�[���̏�Ԃ̐ݒ�@�@ �@�b
//��================================��
void SetGameState(GAMESTATE state, int nCounter)
{
	g_gameState = state;
	g_nCounterGameState = nCounter;
}
//��================================��
//�b�@�@�@ �Q�[���̏�Ԃ̏����@�@ �@�b
//��================================��
GAMESTATE GetGameState(void)
{
	return g_gameState;
}