//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@topscore.h �@ �@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _TOPSCORE_H_  //���̃}�N����`������ĂȂ�������
#define _TOPSCORE_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

void InitTopScore(void);
void UninitTopScore(void);
void UpdateTopScore(void);
void DrawTopScore(void);

//�X�R�A�̐ݒ�Ɖ��Z
void SetTopScore(int nScore);
//void AddTopScore(int nValue);
int GetTopScore(void);

#endif
