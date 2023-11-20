//****************************************
//	Play_model.h
//	Author:��a�c��
//****************************************
#ifndef _TORCH_H_
#define _TORCH_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define NUM_TORCH			(100)	//����̍ő吔
//****************************************
// �\���̂̒�`
//****************************************

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3		pos;		// ���݂̈ʒu
	D3DXVECTOR3		rot;		//����
	D3DXMATRIX		mtxWorld;	//���[���h�}�g���b�N�X
	int				aColor;		//�e�̃��l
	float			fRadius;	//���a
	bool			bSet;		// �����̐ݒ肪�o������
	bool			bUse;		// �g�p���Ă��邩�ǂ���
}Torch;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitTorch(void);
void UninitTorch(void);
void UpdatTorch(void);
void DrawTorch(void);

int SetTorch(void);
void SetPositionTorch(int nIdxTorch, D3DXVECTOR3 pos, float fRadius);
//void DeleteTorch(int nIdxTorch);
#endif