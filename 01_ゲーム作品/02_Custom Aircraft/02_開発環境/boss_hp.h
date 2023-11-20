//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@boss_hp.h         �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _BOSS_HP_H_
#define _BOSS_HP_H_

#include"main.h"

//��==================��
//�b�@ �\���̂̒�` �@�b
//��==================��
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//���_�J���[
	int nType;
	int init_nLife;		//�����̗�
	int curt_nLife;		//���݂̗̑�
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Bosshp;

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitBosshp(void);
void UninitBosshp(void);
void UpdateBosshp(void);
void DrawBosshp(void);

#endif