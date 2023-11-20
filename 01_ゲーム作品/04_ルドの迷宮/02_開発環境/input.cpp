//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�L�[�{�[�h�̏���  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include"input.h"

//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_KEY_MAX (256)		//�L�[�̍ő吔
#define NUM_BUTTON_MAX (14)		//�{�^���̍ő吔
#define REPEATE_INTERVAL	(160)

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECTINPUT8 g_pInput = NULL;				//DirectInout�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^

/* �L�[�{�[�h */
BYTE  g_aKeyStatePress[NUM_KEY_MAX];		// �L�[�{�[�h�̃v���X���
BYTE  g_aKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[���
BYTE  g_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g���
BYTE  g_aKeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̃����[�X���
DWORD g_aKeyCurrentTime[NUM_KEY_MAX];		// �L�[�{�[�h�̌��݂̎���
DWORD g_aKeyExecLastTime[NUM_KEY_MAX];		// �L�[�{�[�h�̍Ō�ɐ^��Ԃ�������

/* �J�[�\�� */
D3DXVECTOR3	g_cursorPosTemp;				// �J�[�\���̈ʒu��ۑ�
D3DXVECTOR3	g_cursorMove;					// �J�[�\���̈ړ���

/* �}�E�X */
BYTE	g_aMouseState[MOUSE_MAX];			// �}�E�X�̃v���X���
BYTE	g_aMouseStateTrigger[MOUSE_MAX];	// �}�E�X�̃g���K�[���
BYTE	g_aMouseStateRelease[MOUSE_MAX];	// �}�E�X�̃����[�X���
BYTE	g_aMouseStateRepeat[MOUSE_MAX];		// �}�E�X�̃��s�[�g���
DWORD	g_aMouseCurrentTime[MOUSE_MAX];		// �}�E�X�̌��݂̎���
DWORD	g_aMouseExecLastTime[MOUSE_MAX];	// �}�E�X�̍Ō�ɐ^��Ԃ�������

// �}�E�X�̃}�X�N
const int g_aMouseMask[MOUSE_MAX] =
{
	VK_LBUTTON,
	VK_RBUTTON,
};


XINPUT_STATE xInput;
ACTIVE_INPUT_TYPE	g_activeInputType;		// ���I�ȓ��͂̎��

//========== *** ��ʏ�̃J�[�\���̈ʒu���擾 ***
D3DXVECTOR3 GetCursorPosOnScreen(void)
{
	POINT cursorPos;	// �J�[�\���̈ʒu

						// �J�[�\���̌��݈ʒu���擾
	GetCursorPos(&cursorPos);

	RECT rc;	// �N���C�A���g�̈�̃T�C�Y

	// �N���C�A���g�̈�̃T�C�Y���擾
	GetClientRect(*GetWindowHandle(), &rc);

	return D3DXVECTOR3(
		(cursorPos.x - GetWindowPos().x) * (SCREEN_WIDTH / (float)rc.right),
		(cursorPos.y - GetWindowPos().y) * (SCREEN_HEIGHT / (float)rc.bottom),
		0.0f);
}

//========== *** �J�[�\���̈ړ��ʂ��擾 ***
D3DXVECTOR3 GetCursorMove(void)
{
	return g_cursorMove;
}

//========================================
// ���͊֘A�̏���������
//========================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	// �}�E�X�J�[�\����\��
	ShowCursor(false);

	// �J�[�\���ʒu��ۑ�
	/*g_cursorPosTemp = GetCursorPosOnScreen();*/

	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �����t�H�[�}�b�g
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//========================================
// ���͊֘A�̏I������
//========================================
void UninitInput(void)
{
	// XInput�����
	XInputEnable(false);

	// ���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//========================================
// ���͊֘A�̍X�V����
//========================================
void UpdateInput(void)
{
	UpdateKeyboard();	// �L�[�{�[�h

	 // �X�V����
	UpdateCursor();		// �J�[�\��
	UpdateMouse();		// �}�E�X
}

//========================================
// �L�[�{�[�h�̍X�V���� 
//========================================
void UpdateKeyboard(void)
{
	BYTE	aKeyState	// �L�[�{�[�h�̓��͏��
		[NUM_KEY_MAX];

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyStateTrigger[nCntKey] = (g_aKeyStatePress[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];

			// �L�[�{�[�h�̃����[�X����ۑ�
			g_aKeyStateRelease[nCntKey] = (g_aKeyStatePress[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];

			// ���݂̎��Ԃ��擾
			g_aKeyCurrentTime[nCntKey] = timeGetTime();

			if (aKeyState[nCntKey] && ((g_aKeyCurrentTime[nCntKey] - g_aKeyExecLastTime[nCntKey]) > REPEATE_INTERVAL))
			{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
			 // �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				g_aKeyExecLastTime[nCntKey] = g_aKeyCurrentTime[nCntKey];

				// �L�[�{�[�h�̃��s�[�g����ۑ�
				g_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
			}
			else
			{
				// �L�[�{�[�h�̃��s�[�g����ۑ�
				g_aKeyStateRepeat[nCntKey] = 0;
			}

			// �L�[�{�[�h�̃v���X����ۑ�
			g_aKeyStatePress[nCntKey] = aKeyState[nCntKey];

			if (aKeyState[nCntKey])
			{// ���͂��s��ꂽ���A
			 // ���I�ȓ��͂̎�ނ��L�[�{�[�h�ɂ���
				g_activeInputType = ACTIVE_INPUT_TYPE_KEYBOARD;
			}
		}
	}
	else
	{// ���̓f�o�C�X����f�[�^���擾�ł��Ȃ��������A
	 // �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDevKeyboard->Acquire();
	}
}
//========================================
// �J�[�\���̍X�V���� 
//========================================
void UpdateCursor(void)
{
	if (g_cursorPosTemp != GetCursorPosOnScreen())
	{// �J�[�\���̌��݈ʒu���ۑ��ʒu���قȂ鎞�A
	 // ���I�ȓ��͂̎�ނ��L�[�{�[�h�ɂ���
		g_activeInputType = ACTIVE_INPUT_TYPE_KEYBOARD;
	}

	// �J�[�\���̈ړ��ʂ�ݒ�
	g_cursorMove = GetCursorPosOnScreen() - g_cursorPosTemp;

	// �J�[�\���ʒu��ۑ�
	g_cursorPosTemp = GetCursorPosOnScreen();
}
//========================================
// �}�E�X�̍X�V���� 
//========================================
void UpdateMouse(void)
{
	for (int nCntMouse = 0; nCntMouse < MOUSE_MAX; nCntMouse++)
	{
		BYTE	mouseState	// �}�E�X�̓��͏��
			= GetKeyState(g_aMouseMask[nCntMouse]) & (0x80) ? true : false;;

		// �}�E�X�̃g���K�[����ۑ�
		g_aMouseStateTrigger[nCntMouse] = (g_aMouseState[nCntMouse] ^ mouseState)&mouseState;

		// �}�E�X�̃����[�X����ۑ�
		g_aMouseStateRelease[nCntMouse] = (g_aMouseState[nCntMouse] ^ mouseState)&~mouseState;

		// ���݂̎��Ԃ��擾
		g_aMouseCurrentTime[nCntMouse] = timeGetTime();

		if (mouseState && ((g_aMouseCurrentTime[nCntMouse] - g_aMouseExecLastTime[nCntMouse]) > REPEATE_INTERVAL))
		{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
		 // �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			g_aMouseExecLastTime[nCntMouse] = g_aMouseCurrentTime[nCntMouse];

			// �}�E�X�̃��s�[�g����ۑ�
			g_aMouseStateRepeat[nCntMouse] = mouseState;
		}
		else
		{// �L�[�����͂���Ă��Ȃ��A�������͌��݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă��Ȃ����A
		 // �}�E�X�̃��s�[�g����ۑ�
			g_aMouseStateRepeat[nCntMouse] = 0;
		}

		// �}�E�X�̃v���X����ۑ�
		g_aMouseState[nCntMouse] = mouseState;

		if (mouseState)
		{// ���͂��s��ꂽ���A
		 // ���I�ȓ��͂̎�ނ��L�[�{�[�h�ɂ���
			g_activeInputType = ACTIVE_INPUT_TYPE_KEYBOARD;
		}
	}
}


//========================================
// GetStick�֐� - �X�e�B�b�N�̓��͏����擾 -
//========================================
XINPUT_STATE *GetXInputState(void)
{
	return &xInput;
}
//========================================
// �L�[�{�[�h�̃v���X�����擾
//========================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyStatePress[nKey] & 0x80) ? true : false;
}

//========================================
// �L�[�{�[�h�̃g���K�[�����擾
//========================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================
// �L�[�{�[�h�̃��s�[�g�����擾 -
//========================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//========================================
// �L�[�{�[�h�̃����[�X�����擾
//========================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//========================================
// �}�E�X�̃v���X�����擾 -
//========================================
bool GetMousePress(int nMouse)
{
	return g_aMouseState[nMouse];
}

//========================================
// �}�E�X�̃g���K�[�����擾
//========================================
bool GetMouseTrigger(int nMouse)
{
	return g_aMouseStateTrigger[nMouse];
}

//========================================
// �}�E�X�̃��s�[�g�����擾
//========================================
bool GetMouseRepeat(int nMouse)
{
	return g_aMouseStateRepeat[nMouse];
}

//========================================
// �}�E�X�̃����[�X�����擾
//========================================
bool GetMouseRelease(int nMouse)
{
	return g_aMouseStateRelease[nMouse];
}
//========================================
// GetStick�֐� - �X�e�B�b�N�̓��͏����擾 -
//========================================
STICK_INPUT GetStick(STICK_TYPE type)
{
	STICK_INPUT stick;	// �X�e�B�b�N�̓��͏��
	float X = 0;			// �X�e�B�b�N��X��
	float Y = 0;			// �X�e�B�b�N��Y��
						// ��ނɉ������X�e�B�b�N�̎��̒l���擾
	switch (type)
	{
		//========== *** ���X�e�B�b�N ***
	case STICK_TYPE_LEFT:
		X = GetXInputState()->Gamepad.sThumbLX;
		Y = GetXInputState()->Gamepad.sThumbLY;
		break;
		//========== *** �E�X�e�B�b�N ***
	case STICK_TYPE_RIGHT:
		X = GetXInputState()->Gamepad.sThumbRX;
		Y = GetXInputState()->Gamepad.sThumbRY;
		break;
	}
	// �p�x���擾

	stick.fAngle = atan2f(-Y, -X);
	stick.fAngle -= (D3DX_PI * 0.5f);

	// �X�e�B�b�N�̓|������擾
	stick.fTplDiameter = fabsf(X);
	if (stick.fTplDiameter < fabsf(Y)) {
		stick.fTplDiameter = fabsf(Y);
	}
	stick.fTplDiameter /= 32768.0f;
	return stick;
}