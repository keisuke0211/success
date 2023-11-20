//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@title.h           �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"
#include"input.h"

//��==================��
//�b�@ �񋓌^�\���� �@�b
//��==================��

//�����̏��
typedef enum
{
	TITLESTATE_NORMAL = 0,	//�ʏ���
	TITLESTATE_FLASHING, 	//�_�ŏ��
	TITLESTATE_MAX
}TITLESTATE;

//��====================��
//�b �@�@���\���� �@�@�b
//��====================��
typedef struct
{
	
	TITLESTATE state;	//���
	int nCounterState;	//��ԊǗ��J�E���^�[
	bool bUse;			//�g�p���Ă��邩�ǂ���

}TITLE;
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif