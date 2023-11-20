//��====================��
//�b�@�@  �@�@�@�@�@�@�@�b
//�b�@�Q�[����ʂ̏����@�b
//�b�@Author:��a�c��   �b
//�b                    �b
//��====================��
#include "game.h"
#include "fade.h"

//UI
#include "frame.h"
#include "score.h"
#include "text.h"
#include "time.h"
#include "damage.h"
// ���C�g
#include "PointLight.h"
// ���f��
#include "stone_pillar.h"
#include "Player_model.h"
#include "torch_model.h"
#include "enemy_model.h"
#include "figure_model.h"
#include "jewel.h"
// ���o
#include "camera.h"
#include "effect.h"
#include "Goal_effect.h"
#include "particle.h"
#include "shadow.h"
#include "sound.h"
#include "torch.h"

// �n�`
#include "floor.h"
#include "meshfield_floor.h"
#include "meshfield_wall.h"
#include "wall.h"

// ���̑�
#include "bullet.h"
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffGame = NULL;			// ���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureGame = NULL;			// �e�N�X�`���ւ̃|�C���^

GAMESTATE g_gameState = GAMESTATE_NONE;					// �Q�[���̏��
Fog1 g_aFog;											// ���̏��
int g_nCounterGameState = 0;							// ��ԊǗ��J�E���^�[
bool g_bPause;											// �|�[�Y��Ԃ�ON/OFF
bool g_dMap;											// �~�j�}�b�v�̂n�m�E�n�e�e
int g_nTimeCnt;
int nCnt99;
int nScore;

//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�Q�[���E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��====================================��
//�b�@�@�@ �Q�[����ʂ̏����������@�@ �@�b
//��====================================��
void InitGame(void)
{
	Camera *pCamera = Getcamara(0);

	g_aFog.Start = 1.0f;
	g_aFog.End = 2500.0f;
	g_aFog.bUse = true;

	g_gameState = GAMESTATE_NONE;
	g_nCounterGameState = 0;
	g_bPause = false;//�|�[�Y����
	g_dMap = true;
	nCnt99 = 0;

	//�G�l�~�[�@�ǂݍ��ݏ���
	LoadEnemyModel();
	//�����@�ǂݍ��ݏ���
	LoadTorch_Model();
	//���f���E�u���@�ǂݍ��ݏ���
	LoadFigureModel();
	//�Β�
	LoadPillar_Model();
	//���
	LoadJewel();

	//�J����
	InitCamera();
	//��
	InitFloor();
	//��
	InitWall();

	//���f��
	InitPlayerModel();
	//�G�l�~�[
	InitEnemyeModel();
	//���f���E�u��
	InitFigureModel();
	//�����E���f��
	InitTorch_Model();
	//�Β�
	InitPillar_Model();
	//���
	InitJewel();
	//�e
	InitBullet();
	//����
	InitTorch();
	//�G�t�F�N�g
	InitEffect();
	//�S�[���G�t�F�N�g
	InitGoalEffect();
	//�p�[�e�B�N��
	InitParticle();
	//�e
	InitShadow();
	//�g
	InitFrame();
	//SCORE
	InitScore();
	//�e�L�X�g
	InitText();
	//�^�C��
	InitTime();
	//�_���[�W
	InitDamage();

	pCamera[1].bUse = true;

	PlaySound(SOUND_LABEL_BGM002); //���A��BJM
}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̏I�������@�@ �@�b
//��==================================��
void UninitGame(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�|�C���g���C�g
	UninitPointLight();
	//���f��
	UninitPlayerModel();
	//�G�l�~�[
	UninitEnemyeModel();
	//���f���E�u��
	UninitFigureModel();
	//�����E���f��
	UninitTorch_Model();
	//�Β�
	UninitPillar_Model();
	//���
	UninitJewel();
	//�e
	UninitBullet();
	//����
	UninitTorch();
	//�G�t�F�N�g
	UninitEffect();
	//�S�[���G�t�F�N�g
	UninitGoalEffect();
	//�p�[�e�B�N��
	UninitParticle();
	//�e
	UninitShadow();
	//�g
	UninitFrame();
	//SCORE
	UninitScore();
	//�e�L�X�g
	UninitText();
	//�^�C��
	UninitTime();
	//�_���[�W
	UninitDamage();
	//��
	UninitFloor();
	//��
	UninitWall();
	//���b�V���t�B�[���h�E��
	UninitMeshField_Floor();
	//���b�V���t�B�[���h�E��
	UninitMeshField_Wall();

}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̍X�V�����@�@ �@�b
//��==================================��
void UpdateGame(void)
{
	Camera *pCamera = Getcamara(0);
	Player *pPlayer = GetPlayer();

	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^

#ifdef _DEBUG
	//�@�~�j�}�b�v�̂n�m�E�n�e�e
	if (GetKeyboardTrigger(DIK_I) == true)
	{
		if (pCamera[2].bUse == false)
		{
			if (pCamera[1].bUse == true)
			{
				pCamera[1].bUse = false;
				g_dMap = false;
			}
			else if (pCamera[1].bUse == false)
			{
				pCamera[1].bUse = true;
				g_dMap = true;
			}
		}
	}
#endif // _DEBUG

	//�@�S�̃}�b�v�̂n�m�E�n�e�e
	if (GetKeyboardTrigger(DIK_M) == true)
	{
		if (pCamera[2].bUse == true)
		{
			if (g_dMap == true)
			{
				pCamera[1].bUse = true;
			}
			pCamera[2].bUse = false;
			g_aFog.bUse = true;
			pPlayer->bAction = true;

		}
		else if (pCamera[2].bUse == false)
		{
			if (g_dMap == true)
			{
				pCamera[1].bUse = false;
			}
			pCamera[2].bUse = true;
			g_aFog.bUse = false;
			pPlayer->bAction = false;
		}
	}

#ifdef _DEBUG

	if (GetKeyboardTrigger(DIK_P) == true && GetFade() == FADE_NONE)
	{//�|�[�Y�L�[(P�L�[)�������ꂽ
		g_bPause = g_bPause ? false : true;
	}
#endif // _DEBUG

	if (g_bPause == false)
	{
		if (pCamera[2].bUse == false)
		{
			if (g_gameState == GAMESTATE_NONE)
			{
				if (GetTime() == 0 && nCnt99 == 0)
				{
					SetGameState(GAMESTATE_END1, 1);
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
			}

			//���f��
			UpdatPlayerModel();
			//�G�l�~�[
			UpdateEnemyeModel();
			//���f���E�u��
			UpdateFigureModel();
			//�����E���f��
			UpdateTorch_Model();
			//�Β�
			UpdatePillar_Model();
			//���
			UpdateJewel();
			//�e
			UpdateBullet();
			//����
			UpdatTorch();
			//�G�t�F�N�g
			UpdateEffect();
			//�S�[���G�t�F�N�g
			UpdateGoalEffect();
			//�p�[�e�B�N��
			UpdateParticle();
			//�e
			UpdateShadow();
			
			//SCORE
			UpdateScore();
			//�^�C��
			UpdateTime();
			//�e�L�X�g
			UpdateText();
			//�_���[�W
			UpdateDamage();
			//��
			UpdateFloor();
			//��
			UpdateWall();

			switch (g_gameState)
			{
			case GAMESTATE_NORMAL://�ʏ���
				break;
			case GAMESTATE_END1://�I����ԁE�G�S��
				g_nCounterGameState--;
				if (g_nCounterGameState == 0)
				{
					//���[�h�̐ݒ�(���U���g��ʂɈڍs)
					SetFade(MODE_RESULY1);

					g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�
					pCamera[1].bUse = false;
					pCamera[2].bUse = false;
					g_aFog.End = 2500.0f;
				}
				break;
			case GAMESTATE_END2://�Q�[���N���A
				g_nCounterGameState--;
				if (g_nCounterGameState == 0)
				{
					nScore = 90 - (90 - GetTime());

					nScore = nScore * 50;

					AddScore(nScore);

					//���[�h�̐ݒ�(���U���g��ʂɈڍs)
					SetFade(MODE_RESULY2);

					g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�

					pCamera[1].bUse = false;
					pCamera[2].bUse = false;
					g_aFog.End = 2500.0f;
				}
				break;
			}
		}
		//�g
		UpdateFrame();
	}
}
//��==================================��
//�b�@�@�@ �Q�[����ʂ̕`�揈���@�@ �@�b
//��==================================��
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;

	Camera *pCamera = Getcamara(0);
	Fog1 *pFog = GetFog();

	pDevice->SetRenderState(D3DRS_FOGENABLE, pFog->bUse);				// ���̗L����
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(0, 0, 0, 0));	// ���̐F
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);			// ���_���[�h
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&pFog->Start));	// �J�n�ʒu
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&pFog->End));		// �I���ʒu

	//��
	DrawFloor();
	//��
	DrawWall();
	//�e
	DrawBullet();
	//�e
	DrawShadow();
	//����
	DrawTorch();
	//�G�l�~�[
	DrawEnemyeModel();
	//���f���E�u��
	DrawFigureModel();
	//�����E���f��
	DrawTorch_Model();
	//�Β�
	DrawPillar_Model();
	//���
	DrawJewel();
	if (pCamera[2].bUse == false)
	{
		//�G�t�F�N�g
		DrawEffect();
	}
	//�S�[���G�t�F�N�g
	DrawGoalEffect();
	//�p�[�e�B�N��
	DrawParticle();
	//���f��
	DrawPlayerModel();

	if (pCamera[2].bUse == false)
	{
		//SCORE
		DrawScore();
		//�e�L�X�g
		DrawaText();
		//�^�C��
		DrawTime();
		//�_���[�W
		DrawDamage();
	}
	//�g
	DrawaFrame();
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

Fog1 *GetFog(void)
{
	return &g_aFog;
}