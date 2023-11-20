//****************************************
//	input.h
//	Author:��a�c��
//****************************************
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
// �񋓌^�̒�`
//****************************************

// ���I�ȓ��͂̎��
typedef enum
{
	ACTIVE_INPUT_TYPE_KEYBOARD,
	ACTIVE_INPUT_TYPE_CONTROLLER,
	ACTIVE_INPUT_TYPE_MAX,
}ACTIVE_INPUT_TYPE;

// �}�E�X�ԍ�
typedef enum
{
	MOUSE_LEFT = 0,
	MOUSE_RIGHT,
	MOUSE_MAX,
}MOUSE;

// �X�e�b�N�ԍ�
typedef enum
{
	STICK_TYPE_LEFT = 0,
	STICK_TYPE_RIGHT,
	STICK_TYPE_MAX
}STICK_TYPE;

//****************************************
// �v���g�^�C�v�錾
//****************************************

HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);	// ���͊֘A�̏���������
void UninitInput(void);								// ���͊֘A�̏I������
void UpdateInput(void);								// ���͊֘A�̍X�V����

void UpdateKeyboard(void);							// �L�[�{�[�h�̍X�V����
void UpdateMouse(void);								// �}�E�X�̍X�V����
void UpdateCursor(void);							// �J�[�\���̍X�V����

/* �L�[�{�[�h */
bool GetKeyboardPress(int nKey);					// �L�[�{�[�h�̃v���X�����擾
bool GetKeyboardTrigger(int nKey);					// �L�[�{�[�h�̃g���K�[�����擾
bool GetKeyboardRepeat(int nKey);					// �L�[�{�[�h�̃��s�[�g�����擾
bool GetKeyboardRelease(int nKey);					// �L�[�{�[�h�̃����[�X�����擾

/* �J�[�\�� */
D3DXVECTOR3 GetCursorPosOnScreen(void);				// ��ʏ�̃J�[�\���̈ʒu���擾
D3DXVECTOR3 GetCursorMove(void);					// �J�[�\���̈ړ��ʂ��擾

/* �}�E�X */
bool GetMousePress(int nMouse);						// �}�E�X�̃v���X�����擾
bool GetMouseTrigger(int nMouse);					// �}�E�X�̃g���K�[�����擾
bool GetMouseRepeat(int nMouse);					// �}�E�X�̃��s�[�g�����擾
bool GetMouseRelease(int nMouse);					// �}�E�X�̃����[�X�����擾

XINPUT_STATE *GetXInputState(void);
STICK_INPUT GetStick(STICK_TYPE type);

#endif