//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@ranking.h �@�@�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _RESULT_SCORE1_H_  //���̃}�N����`������ĂȂ�������
#define _RESULT_SCORE1_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"
#include<stdio.h>

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nScore;
	int nType;
	bool bUse;
}Ranking1;

//�v���g�^�C�v�錾
void InitResulyScore1(void);
void UninitResulyScore1(void);
void UpdateResulyScore1(void);
void DrawResulyScore1(void);

void SetResult1(int nRanking);

#endif
