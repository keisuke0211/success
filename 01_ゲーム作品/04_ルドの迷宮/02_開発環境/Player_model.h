//****************************************
//	Play_model.h
//	Author:��a�c��
//****************************************
#ifndef _PLAYER_MODEL_H_
#define _PLAYER_MODEL_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define MODEL_SPEED			(10)	//�ړ����x
#define SIZE_WIDTH			(20)	//���̃T�C�Y
#define SIZE_HEIGHT			(20)	//�c�̃T�C�Y
//****************************************
// �\���̂̒�`
//****************************************

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3		pos;					// ���݂̈ʒu
	D3DXVECTOR3		posOld;					// �O��̈ʒu
	D3DXVECTOR3		move;					// �ʒu�̈ړ���
	D3DXVECTOR3		moveRot;				// �����̈ړ���
	D3DXVECTOR3		vecMove;				// �ړ��x�N�g��
	D3DXVECTOR3		relativePosR;			// �����_�̑��Έʒu
	D3DXVECTOR3		targetPosR;				// �ڕW�̒����_�̑��Έʒu

	D3DXVECTOR3		rot;					// ����
	D3DXMATRIX		mtxWorld;				// ���[���h�}�g���b�N�X
	int				nIdxShadow = -1;		// �Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
	int				nIdxTorch = 1;			// �Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
	int nCntAction;							// �����ړ��̈ړ�����
	float fWidht;

	bool bAction;							// �v���C���[�̑���̉\���s�\��
}Player;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitPlayerModel(void);
void UninitPlayerModel(void);
void UpdatPlayerModel(void);
void DrawPlayerModel(void);
Player *GetPlayer(void);

#endif