//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@text.h            �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _TEXT_H_  //���̃}�N����`������ĂȂ�������
#define _TEXT_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//*****************************************************************************
// �e�L�X�g�ꗗ
//*****************************************************************************
typedef enum
{
	TEXT_SCORE = 0,				// SCORE
	TEXT_TIME,					// TIME
	TEXT_DAMAGE,				// Damage
} TEXT;

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitText(void);
void UninitText(void);
void UpdateText(void);
void DrawaText(void);


#endif