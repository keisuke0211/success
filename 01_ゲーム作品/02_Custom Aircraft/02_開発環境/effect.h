//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@effect.h          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,int nType);

#endif