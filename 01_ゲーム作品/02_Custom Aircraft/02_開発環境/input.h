//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@input.h           �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//****************************************
// �X�e�B�b�N���͂̏��\����
//****************************************

// �X�e�B�b�N�̓��͏��\����
typedef struct
{
	float fTplDiameter;	// �X�e�B�b�N�̓|���
	float fAngle;		// �X�e�B�b�N�̊p�x
}STICK_INPUT;
//****************************************
// �X�e�B�b�N�ԍ��̒�`
//****************************************

typedef enum
{
	STICK_TYPE_LEFT = 0,
	STICK_TYPE_RIGHT,
	STICK_TYPE_MAX
}STICK_TYPE;

//****************************************
// �v���g�^�C�v�錾
//****************************************
HRESULT lnitKeyboard(HINSTANCE hlnstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
void UpdateButton(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetButtonPress(int nButton);
bool GetButtonTrigger(int nButton);
XINPUT_STATE *GetXInputState(void);
STICK_INPUT GetStick(STICK_TYPE type);

#endif