//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@score.h �@�@�@�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _SCORE_H_  //���̃}�N����`������ĂȂ�������
#define _SCORE_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

//�X�R�A�̐ݒ�Ɖ��Z
void SetScore(int nScore);
void AddScore(int nValue);

int GetScore(void);
#endif
