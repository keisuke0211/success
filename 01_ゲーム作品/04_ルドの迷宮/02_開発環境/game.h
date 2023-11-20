//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@game.h            �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _GAME_H_
#define _GAME_H_

#include"main.h"
#include"input.h"

//*****************************************************************************
// �Q�[���̏��
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,		//�������Ă��Ȃ����
	GAMESTATE_NORMAL,		//�ʏ��ԁE�Q�[���i�s��
	GAMESTATE_END1,			//�I����ԁE�G�S��
	GAMESTATE_END2,			//�v���C���[��
	GAMESTATE_MAX
}GAMESTATE;

typedef struct
{
	float Start;	// �J�n�ʒu
	float End;		// �I���ʒu

	bool bUse;		// �g�p���Ă��邩�ǂ���
}Fog1;
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state, int nCounter);
GAMESTATE GetGameState(void);
int GetTimeCnt(void);
Fog1 *GetFog(void);

#endif