//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@ranking.h �@�@�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _RESULT_SCORE_H_  //���̃}�N����`������ĂȂ�������
#define _RESULT_SCORE_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"
#include<stdio.h>

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nScore;
	int nType;
	bool bUse;
}Ranking;

//�v���g�^�C�v�錾
void InitResulyScore(void);
void UninitResulyScore(void);
void UpdateResulyScore(void);
void DrawResulyScore(void);

void SetResult(int nRanking);

#endif
