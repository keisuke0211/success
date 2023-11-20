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

//*****************************************************************************
// �^�C�g���w�i�ꗗ
//*****************************************************************************
typedef enum
{
	TITLE_BG000 = 0,	// ����
	TITLE_BG001,		// �_�P
	TITLE_MAX,
}TITLE_BG;
//��====================��
//�b �@�@���\���� �@�@�b
//��====================��
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X

	TITLESTATE state;	//���
	int nCounterState;	//��ԊǗ��J�E���^�[

	float fWidth;		//����
	float fHight;		//����

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