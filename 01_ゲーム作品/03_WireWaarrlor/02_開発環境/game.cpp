//��====================��
//�b�@�@  �@�@�@�@�@�@�@�b
//�b�@�Q�[����ʂ̏����@�b
//�b�@Author:��a�c��   �b
//�b                    �b
//��====================��
#include "game.h"
#include "fade.h"
#include "player.h"
#include "bg.h"
#include "block.h"
#include "camera.h"
#include "lure.h"
#include "rope.h"
#include "sound.h"
#include "time.h"
#include "text.h"
#include "result ver2.h"
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffGame = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureGame = NULL;			//�e�N�X�`���ւ̃|�C���^

GAMESTATE g_gameState = GAMESTATE_NONE;					//�Q�[���̏��
int g_nCounterGameState = 0;							//��ԊǗ��J�E���^�[
bool g_bPause = false;									//�|�[�Y��Ԃ�ON/OFF
bool bswitch = true;									//�Ȑ؂�ւ�
int g_nTimeCnt;
int nCnt99;
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
	nCnt99 = 0;
	//�w�i�̏���������
	InitBg();

	//�v���C���[�̏���������
	InitPlayer();

	//���A�[�̏���������
	InitLure();

	//���[�v�̏���������
	InitRope();
	//�u���b�N�̏���������
	InitBlock();

	//�^�C�}�[�̏���������
	InitTime();
	//�e�L�X�g�̏���������
	InitText();
	//�J�����̏���������
	InitCamera();

	PlaySound(SOUND_LABEL_BGM001); //���A��BJM

	
}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̏I�������@�@ �@�b
//��==================================��
void UninitGame(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�w�i�̏I������
	UninitBg();

	//�v���C���[�̏I������
	UninitPlayer();

	//���A�[�̏I������
	UninitLure();
	//���[�v�̏I������
	UninitRope();
	//�u���b�N�̏I������
	UninitBlock();
	//�^�C�}�[�̏I������
	UninitTime();
	//�e�L�X�g�̏I������
	UninitText();
	//�J�����̏I������
	UninitCamera();

}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̍X�V�����@�@ �@�b
//��==================================��
void UpdateGame(void)
{
	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^

	if (GetTime() == 0 && nCnt99 == 0)
	{
		SetGameState(GAMESTATE_END2, 1);
		nCnt99++;
	}
	else if (GetTime() > 0)
	{
		g_nTimeCnt++;
		if (g_nTimeCnt >= 60)
		{
			g_nTimeCnt = 0;
			AddTime(-1);
		}
	}

	if (GetKeyboardTrigger(DIK_P) == true && GetFade() == FADE_NONE)
	{//�|�[�Y�L�[(P�L�[)�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	//�w�i�̍X�V����
	UpdateBg();
	//�v���C���[�̍X�V����
	UpdatePlayer();
	//���A�[�̍X�V����
	UpdateLure();
	//���[�v�̍X�V����
	UpdateRope();
	//�u���b�N�̍X�V����
	UpdateBlock();
	//�^�C�}�[�̍X�V����
	UpdateTime();
	//�e�L�X�g�̍X�V����
	UpdateText();
	//�J�����̍X�V����
	UpdateCamera();

	GetCamera()->bCamera_Y = false;
		switch (g_gameState)
		{
		case GAMESTATE_NORMAL://�ʏ���
			break;
		case GAMESTATE_END1://�I����ԁE�G�S��
			g_nCounterGameState--;
			if (g_nCounterGameState == 0)
			{
				//���[�h�̐ݒ�(���U���g��ʂɈڍs)
				SetFade(MODE_RESULY2);

				g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�
			}
			break;
		case GAMESTATE_END2://�Q�[���I�[�o�[
			g_nCounterGameState--;
			if (g_nCounterGameState == 0)
			{
				//���[�h�̐ݒ�(���U���g��ʂɈڍs)
				SetFade(MODE_RESULY1);

				g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�
			}
			break;
		}
}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̕`�揈���@�@ �@�b
//��==================================��
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBg();
	//�u���b�N�̕`�揈��
	DrawBlock();
	//���[�v�̕`�揈��
	DrawRope();
	//���A�[�̕`�揈��
	DrawLure();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	//�e�L�X�g�̕`�揈��
	DrawaText();
	//�^�C�}�[�̕`�揈��
	DrawTime();
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
int GetTimeCnt(void)
{
	return g_nTimeCnt;
}