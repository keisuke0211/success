//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@enemy.h		�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _SUMMON_H_
#define _SUMMON_H_

#include"main.h"
#include<stdio.h>
//****************************************
// �}�N����`
//****************************************
#define MAX_ENEMY (128) //�G�̍ő吔
#define SIZE_ENEMY (48) //�G�̑傫��

//****************************************
// �񋓌^�̒�`
//****************************************

//�G�̏��
typedef enum
{
	SUMMONSTATE_NORMAL = 0,	//�ʏ���
	SUMMONSTATE_DAMAGE, 	//�_���[�W���
	SUMMONSTATE_MAX
}SUMMONSTATE;

//****************************************
// �\���̂̒�`
//****************************************

//�G�\���̂̒�`
typedef struct
{
	int nType;			//�G�E���
	int sType;			//�e�E���
	int m_pattern;		//�ړ��p�^�[��
	int s_pattern;		//���˃p�^�[��
	int speed;			//�e�X�s�[�h
	int nLife;			//�̗�
	int score;			//�X�R�A

	int in_time;		//�o������
	int stop_time;		//��~����
	int shot_time;		//�e���ˎ���
	int out_time;		//�A�Ҏ���
	int nCntMove;		//�ړ��Ԋu
	int nBullet;		//�U���Ԋu
	int time;			//�v���C���[�̈ʒu���m�F���鎞��
	int Tracking;		//�ǔ����鎞��
	int nCntStop;		//��~����

	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;    //����


	SUMMONSTATE state;	//���
	int nCounterState;	//��ԊǗ��J�E���^�[

	bool bUse;			//�g�p���Ă��邩�ǂ���
	bool Reversal;		//�ړ��������]
	bool m_switch;		//�s���E�؂�ւ�
	bool bTime;			//�ҋ@�̃I���E�I�t
	bool nStop;			//��~�t���O
	bool bDrw;			//�\���@����E���Ȃ�
	bool bHit;			//�����蔻��@�I���E�I�t
}Summon;

//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitSummon(void);
void UninitSummon(void);
void UpdateSummon(void);
void DrawSummon(void);
void LoadSummon(void);

void HitSummon(int nCntEnemy, int nDamage);
void EnemySummon(int p_pattern);				//�ꏊ�E���

Summon *GetSummon(void);
int GetNumSummon(void);
int GetnCharge1(void);
int GetnCharge2(void);

#endif