//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@ranking.h �@�@�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _RANKING_SCORE_H_  //���̃}�N����`������ĂȂ�������
#define _RANKING_SCORE_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

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
void InitRankingScore(void);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);

void LoadRanking(void);
void SaveRanking(void);
void SetRanking(D3DXVECTOR3 pos,int nRanking);

#endif