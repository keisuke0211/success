//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@tutorial.h        �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include"main.h"
#include"input.h"
//*****************************************************************************
// �u���b�N�ꗗ
//*****************************************************************************
typedef enum
{
	TUTORIAL_LABEL_ROCKS02 = 0,		// ��{����
	TUTORIAL_LABEL_ROCKS00,			// ���A�[�̑���
	TUTORIAL_LABEL_ROCKS01,			// ���A�[�̌�����
	TUTORIAL_LABEL_DIR,				// �t�b�N����
	TUTORIAL_LABEL_DIR1,			// �t�b�N�W�����v
	TUTORIAL_LABEL_MAX
}TUTORIAL_LABEL;
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial1(void);

#endif