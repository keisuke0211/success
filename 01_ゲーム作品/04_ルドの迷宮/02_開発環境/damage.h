//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@damage.h �@�@ �@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _DAMAGE_H_  //���̃}�N����`������ĂȂ�������
#define _DAMAGE_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

void InitDamage(void);
void UninitDamage(void);
void UpdateDamage(void);
void DrawDamage(void);

//�X�R�A�̐ݒ�Ɖ��Z
void SetDamage(int nScore);
void AddDamage(int nValue);

int GetDamage(void);
#endif