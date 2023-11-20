//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@lure.h            �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _LURE_H_  //���̃}�N����`������ĂȂ�������
#define _LURE_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"
//****************************************
// ���A�[�̍\���̂̒�`
//****************************************

typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 move;   //�ړ���
	D3DXVECTOR3 rot;    //����

	int nCntReturn;		//�v���C���[�̏ꏊ�ɖ߂�J�E���g
	int nLife;			//����

	float Length;
	float Angle;
	bool bUse;			//�g�p���Ă��邩�ǂ���
	bool bReturn;		//���A�[��߂�
	bool bStab;			//�ǂɓ����������ǂ���
	bool bWireA;		//���C���A�N�V����A�@�t�b�N�̏��Ɉړ�����E���Ȃ�
	bool bRope;			//���[�v�̒����ݒ�@�Œ�or����
}Lure;
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitLure(void);
void UninitLure(void);
void UpdateLure(void);
void DrawLure(void);
void SetLure(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);
Lure *GetLure(void);
//****************************************
// �}�N����`
//****************************************
#define SIZE_LURE_WIDTH  (5.0f)
#define SIZE_LURE_HEIGHT (5.0f)

#endif