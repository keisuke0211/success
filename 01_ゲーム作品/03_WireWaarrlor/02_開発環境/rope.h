//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@rope.h            �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _ROPE_H_  //���̃}�N����`������ĂȂ�������
#define _ROPE_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"
//****************************************
// ���A�[�̍\���̂̒�`
//****************************************

typedef struct
{
	D3DXVECTOR3 posA;	//���݂̈ʒu
	D3DXVECTOR3 posB;	//���݂̈ʒu
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;    //����

	float Length;
	float Angle;

	bool bUse;			//�g�p���Ă��邩�ǂ���
}Rope;
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��

void InitRope(void);
void UninitRope(void);
void UpdateRope(void);
void DrawRope(void);
Rope *GetRope(void);

//****************************************
// �}�N����`
//****************************************
#define SIZE_ROPE_WIDTH  (5.0f)
#define SIZE_ROPE_HEIGHT (5.0f)

#endif