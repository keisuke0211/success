//****************************************
//	floar.h
//	Author:��a�c��
//****************************************
#ifndef _FLOOR_H_
#define _FLOOR_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define MAX_FLOOR (100)			//���̍ő吔
//****************************************
// �\���̂̒�`
//****************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3	vecLine;	//���E���x�N�g��
	D3DXVECTOR3	vecToPos;	//���E���x�N�g��

	int nCype;				//�v�Z���@
	int nType;				//�摜���
	int nSplitX;			//���̕�����
	int nSplitY;			//�c�̕�����

	float fWidth;			//����
	float fHight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Floor;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitFloor(void);
void UninitFloor(void);
void UpdateFloor(void);
void DrawFloor(void);
void LoadFloor(void);
Floor *GetFloor(void);

#endif