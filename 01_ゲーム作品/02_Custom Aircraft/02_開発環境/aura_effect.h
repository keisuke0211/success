//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@aura_effect.h     �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _AURAEFFECT_H_
#define _AURAEFFECT_H_

#include"main.h"

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitAuraEffect(void);
void UninitAuraEffect(void);
void UpdateAuraEffect(void);
void DrawAuraEffect(void);
void SetAuraEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, int nType);

#endif