//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@taime.h �@�@�@�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _TIME_H_  //���̃}�N����`������ĂȂ�������
#define _TIME_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);

//�X�R�A�̐ݒ�Ɖ��Z
void SetTime(int nScore);
void AddTime(int nValue);

int GetTime(void);
#endif