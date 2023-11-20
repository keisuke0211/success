//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@player/h          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _PLAYER_H_  //���̃}�N����`������ĂȂ�������
#define _PLAYER_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//****************************************
// �v���C���[�̏��
//****************************************

typedef enum
{
	PLAYERSTATE_APPEAR = 0,		//�o�����(�_��)
	PLAYERSTATE_NORMAL,			//�ʏ���
	PLAYERSTATE_DAMAGE,			//�_���[�W���
	PLAYERSTATE_WAIT,			//�_�ŏ��
	PLAYERSTATE_DEATH,			//���S���
	PLAYESTATE_MAX
}PLAYERSTATE;

//****************************************
// �v���C���[�̍\���̂̒�`
//****************************************

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;    //����
	D3DXVECTOR3 move;   //�ړ���
	PLAYERSTATE state;	//���
	int nCounterState;	//��ԊǗ��J�E���^�[
	int nLife;			//�̗�
	bool bUse;			//�g�p���Ă��邩�ǂ���
	bool bDrw;			//�\���@����E���Ȃ�
	bool bBeing;		//�v���C���[�̏�ԁ@�����E���S
	bool bBph;			//�R���g���[���̐U���̗L��
}Player;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void); //�S�̃f�[�^��main.cpp����ړ�
void HitPlayer(int nCntPlayer, int nDamage);
Player *Getplayer(void);
//****************************************
// �}�N����`
//****************************************
#define SIZE_WIDTH  (32.0f)
#define SIZE_HEIGHT (32.0f)
#define PLAYER_SPEED (2.0f)
#define SPEED       (12.0f)
#define UP          (0.75f)
#define DOWN        (0.25f) 

#endif