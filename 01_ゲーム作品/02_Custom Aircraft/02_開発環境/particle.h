//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@particle.h        �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include"main.h"

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nType, int nLife, float fRadius,int cType, int pType);

#endif
