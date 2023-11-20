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

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECTINPUT8 g_pInput = NULL;//DirectInout�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX]; //�L�[�{�[�h�̃g���K�[���

XINPUT_STATE xInput;
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�L�[�{�[�h�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��====================================��
//�b�@�@�@ �L�[�{�[�h�̏����������@�@ �@�b
//��====================================��
HRESULT lnitKeyboard(HINSTANCE hlnstance, HWND hWnd)
{

	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hlnstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))

	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))

	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//��==================================��
//�b�@�@�@ �L�[�{�[�h�̏I�������@�@ �@�b
//��==================================��
void UninitKeyboard(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//��==================================��
//�b�@�@�@ �L�[�{�[�h�̍X�V�����@�@ �@�b
//��==================================��
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	int nCntKey;

	xInput.dwPacketNumber = XInputGetState(xInput.dwPacketNumber, &xInput);

	//���̓f�o�C�X����f�[�^������
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];//�L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); //�L�[�{�[�h�̂ւ̃A�N�Z�X�����l��7
	}

}
//�L�[�{�[�h�̃g���K�[��������
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0X80) ? true : false;
}
//�L�[�{�[�h�̃u���X���
bool GetKeyboardPress(int nKey)
{
	//        ���R�����Z�q�@�@��������? A:B; ���������^�Ȃ�A��Ԃ��@�U�Ȃ�B��Ԃ�
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
XINPUT_STATE *GetXInputState(void)
{
	return &xInput;
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