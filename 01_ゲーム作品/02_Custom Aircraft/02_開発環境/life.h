//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@life.h  �@�@�@�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _LIFE_H_  //���̃}�N����`������ĂȂ�������
#define _LIFE_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

////���C�t�̐ݒ�ƌ��Z
void SetLife(int nLife);
void AddLife(int nValue);
void DeleteLife(int nValus);

int GetLife(void);
#endif