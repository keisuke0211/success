#pragma once
//****************************************
//	stone_pillar_model.h
//	Author:��a�c��
//****************************************
#ifndef _PILLAR_MODEL_H_
#define _PILLAR_MODEL_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define NUM_PILLAR			(421)		//���f���̔z�u��
#define TXT_MAX				(500)		//�ǂݍ��ޕ����̍ő吔
#define MAX_TEXTURE			(10)		//�e�N�X�`���̍ő吔
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

	int nType;

	float fHight;
	float fWidth;
	float r, g, b, a;

	char aModelPath[TXT_MAX];	// ���f���̑��΃p�X

	bool bUse;
}Pillar;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitPillar_Model(void);
void UninitPillar_Model(void);
void UpdatePillar_Model(void);
void DrawPillar_Model(void);
void LoadPillar_Model(void);
void CollisioPillar_Model(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

Pillar *GetPillarl(void);

#endif