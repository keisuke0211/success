//****************************************
//	figure_model.h
//	Author:��a�c��
//****************************************
#ifndef _JEWEL_H_
#define _JEWEL_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define NUM_JEWEL	(116)			//���f���̔z�u��
//****************************************
// �\���̂̒�`
//****************************************

//���f���i�u���j�̍\����
typedef struct
{
	D3DXVECTOR3		pos;		//�ʒu
	D3DXVECTOR3		rot;		//����
	D3DXMATRIX		mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxModelParent;		//�e���f���̃C���f�b�N�X

	int nLife;
	int nType;
	int nCntDamage;
	int	nIdxShadow = -1;		//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

	float fHight;
	float fWidth;
	float r, g, b, a;

	bool bUse;
}Jewel;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitJewel(void);
void UninitJewel(void);
void UpdateJewel(void);
void DrawJewel(void);
void LoadJewel(void);
void CollisionJewel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
Jewel *GetJewel(void);

#endif