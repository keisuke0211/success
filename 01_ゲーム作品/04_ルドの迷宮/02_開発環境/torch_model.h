#pragma once
//****************************************
//	figure_model.h
//	Author:��a�c��
//****************************************
#ifndef _TORCH_MODEL_H_
#define _TORCH_MODEL_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define NUM_TORCH_M			(66)			//���f���̔z�u��
#define TXT_MAX				(500)		//�ǂݍ��ޕ����̍ő吔
#define MAX_TEXTURE			(10)		//�e�N�X�`���̍ő吔
#define DAMEGE_COUNT		(10)		//�_���[�W�̂�����Ă��猳�̐F�ɖ߂�J�E���g
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
	int	nIdxTorchLight = -1;		//�Ώۂ̏Ɩ��̃C���f�b�N�X(�ԍ�)

	float fHight;
	float fWidth;
	float r, g, b, a;

	char aModelPath[TXT_MAX];	// ���f���̑��΃p�X

	bool bUse;
}Torch_Model;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitTorch_Model(void);
void UninitTorch_Model(void);
void UpdateTorch_Model(void);
void DrawTorch_Model(void);
void LoadTorch_Model(void);
void HitFigure(int nCntTorch, int nDamage);
//Torch_Model *GetTorch_Model(void);

#endif