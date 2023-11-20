//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@sgadow.h          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define MAX_SHADOW		(512)							//�e�̍ő吔

//****************************************
// �\���̂̒�`
//****************************************
//�e�̍\����
typedef struct
{
	D3DXVECTOR3		pos;		//�ʒu
	D3DXVECTOR3		rot;		//����
	D3DXMATRIX		mtxWorld;	//���[���h�}�g���b�N�X
	int				aColor;		//�e�̃��l
	float			fWidhtX;	//�c��
	float			fWidhtZ;	//����
	bool			bSet;		//�e�̐ݒ肪�o������
	bool			bUse;		//�g�p���Ă��邩�ǂ���
}Shadow;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(void);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, float fWidht,float fHight);
void DeleteShadow(int nIdxShadow);

#endif