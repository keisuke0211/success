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
	TEXT_TOP = 0,				// �s�n�o
	TEXT_SCORE,					// �r�b�n�q�d
	TEXT_LIFE,					//  L I F E
} TEXT;

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitText(void);
void UninitText(void);
void UpdateText(void);
void DrawaText(void);


#endif