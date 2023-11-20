//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@effect.h          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _GOAL_EFFECT_H_
#define _GOAL_EFFECT_H_

#include"main.h"

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitGoalEffect(void);
void UninitGoalEffect(void);
void UpdateGoalEffect(void);
void DrawGoalEffect(void);
void SetGoalEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, int nType);

#endif