//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@explosion.h       �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _EXPLOSION_H_
#define  _EXPLOSION_H_

#include"main.h"

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif