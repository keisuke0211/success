//****************************************
//	PointLight.h
//	Author:��a�c��
//****************************************
#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include"main.h"
//****************************************
// �\���̂̒�`
//****************************************
// ���̏��
typedef struct
{
	// �ʒu�֘A
	D3DXVECTOR3	rot;	// ����
	D3DXCOLOR	col;	// �F
}PointLight;
//****************************************
// �}�N����`
//****************************************
#define NUM_POINTLIGHT			(1)		//���C�g�̐�
//****************************************
//�v���g�^�C�v�錾
//****************************************
void InitPointLight(void);
void UninitPointLight(void);
void UpdatePointLight(void);
#endif