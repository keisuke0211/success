//========================================
// 
// ���͏���
// 
//========================================
// *** input.h ***
//========================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "../main.h"
#include "physics.h"

//****************************************
// �N���X
//****************************************

// ����
class CInput : public CPhysics
{
public:
	// ***** ��` *****
	static const int REPEATE_INTERVAL = 160;	// ���s�[�g�Ԋu

	// ***** �֐� *****
	CInput();
	virtual~CInput();

	/* ���C�� */
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	virtual void Uninit(void);								// �I��
	virtual void Update(void) = 0;							// �X�V

protected:
	// �L�[�{�[�h
	static LPDIRECTINPUT8 m_pInput;		// DirectInout�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;		// ���̓f�o�C�X�ւ̃|�C���^

	// �}�E�X
	static LPDIRECTINPUT8 m_pMouswInput;
	LPDIRECTINPUTDEVICE8 m_pDeviceMouse;

private:

};

// �L�[�{�[�h
class CKeyboard : public CInput
{
public:

	// ***** �֐� *****
	CKeyboard();
	virtual~CKeyboard();

	/* ���C�� */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V
	bool GetPress(int nKey);						// �v���X���
	bool GetTrigger(int nKey);						// �g���K�[�����擾
	bool GetRepeat(int nKey);						// ���s�[�g�����擾
	bool GetRelease(int nKey);						// �����[�X�����擾

private:
	// ***** ��` *****
	static const int NUM_KEY_MAX = 256;		// �L�[�̍ő吔

	// ***** �ϐ� *****
	BYTE  m_aKeyState[NUM_KEY_MAX];
	BYTE  m_aKeyStateTrigger[NUM_KEY_MAX];			// �L�[�{�[�h�̃g���K�[���
	BYTE  m_aKeyStateRepeat[NUM_KEY_MAX];			// �L�[�{�[�h�̃��s�[�g���
	BYTE  m_aKeyStateRelease[NUM_KEY_MAX];			// �L�[�{�[�h�̃����[�X���
	DWORD m_aKeyCurrentTime[NUM_KEY_MAX];			// �L�[�{�[�h�̌��݂̎���
	DWORD m_aKeyExecLastTime[NUM_KEY_MAX];			// �L�[�{�[�h�̍Ō�ɐ^��Ԃ�������
};

// �}�E�X
class CMouse : public CInput
{
public:
	// ***** �񋓌^ *****

	//�L�[���
	enum MOUSE
	{
		MOUSE_LEFT = 0,		//�}�E�X���{�^��
		MOUSE_RIGHT,		//�}�E�X�E�{�^��
		MOUSE_MIDDLE,		//�}�E�X�����{�^��
		MOUSE_4,			//�}�E�X�{�^��4
		MOUSE_5,			//�}�E�X�{�^��5
		MOUSE_6,			//�}�E�X�{�^��6
		MOUSE_7,			//�}�E�X�{�^��7
		MOUSE_8,			//�}�E�X�{�^��8
		MOUSE_MAX
	};

	// ***** �֐� *****
	CMouse();
	virtual~CMouse();

	/* ���C�� */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);				// ������
	void Uninit(void);											// �I��
	void Update(void);											// �X�V
	bool GetPress(MOUSE Mouse);									// �v���X�����擾
	bool GetTrigger(MOUSE Mouse);								// �g���K�[�����擾
	bool GetRepeat(MOUSE Mouse);								// ���s�[�g�����擾
	bool GetRelease(MOUSE Mouse);								// �����[�X�����擾
	D3DXVECTOR3 GetPos(void);									// ��ʓ��̈ʒu
	D3DXVECTOR3 GetCursorMove(void) { return m_MouseMove; }		// �J�[�\���̈ړ���
	int GetWheel(void);											// �z�C�[���̓�������

private:
	// ***** ��` *****
	static const int MOUSE_KEY_MAX = 8;		// �L�[�̍ő吔

	// ***** �ϐ� *****
	DIMOUSESTATE2	m_aMouseState;					// �v���X���
	DIMOUSESTATE2	m_aMouseStateTrigger;			// �g���K�[���
	DIMOUSESTATE2	m_aMouseStateRelease;			// �����[�X���
	DIMOUSESTATE2	m_aMouseStateRepeat;			// ���s�[�g���
	DIMOUSESTATE2	m_aMouseCurrentTime;			// ���݂̎���
	DIMOUSESTATE2	m_aMouseExecLastTime;			// �Ō�ɐ^��Ԃ�������
	HWND m_hMouseWnd;								// �E�B���h�E�n���h��

	D3DXVECTOR3 g_MousePosTemp;		// �ʒu�ۑ��p
	D3DXVECTOR3 m_MouseMove;
};

// �W���C�p�b�g
class CJoypad : public CInput
{
public:	

	// ***** �񋓌^ *****

	//�L�[���
	enum JOYKEY
	{
		JOYKEY_UP = 0,				//�\���{�^����
		JOYKEY_DOWN,				//�\���{�^����
		JOYKEY_LEFT,				//�\���{�^����
		JOYKEY_RIGHT,				//�\���{�^���E
		JOYKEY_START,				//�X�^�[�g�{�^��
		JOYKEY_BACK,				//�o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
		JOYKEY_A,					//A�{�^��
		JOYKEY_B,					//B�{�^��
		JOYKEY_X,					//X�{�^��
		JOYKEY_Y,					//Y�{�^��
		JOYKEY_MAX
	};

	// �X�e�b�N�ԍ�
	enum STICK_TYPE
	{
		STICK_TYPE_LEFT = 0,
		STICK_TYPE_RIGHT,
		STICK_TYPE_MAX
	};

	// �X�e�B�b�N�̕���
	enum STICK_ANGLE
	{
		STICK_ANGLE_UP = 0,
		STICK_ANGLE_DOWN,
		STICK_ANGLE_LEFT,
		STICK_ANGLE_RIGHT,
		STICK_ANGLE_MAX,
	};

	// ***** �\���� *****

	// �X�e�B�b�N�̓��͏��
	typedef struct
	{
		float aTplDiameter[STICK_TYPE_MAX];						// �X�e�B�b�N�̓|���
		float aAngle[STICK_TYPE_MAX];							// �X�e�B�b�N�̊p�x
		bool aAnglePress[STICK_TYPE_MAX][STICK_ANGLE_MAX];		// �X�e�B�b�N�̕����v���X���
		bool aAngleTrigger[STICK_TYPE_MAX][STICK_ANGLE_MAX];	// �X�e�B�b�N�̕����g���K�[���
		bool aAngleRepeat[STICK_TYPE_MAX][STICK_ANGLE_MAX];		// �X�e�B�b�N�̕������s�[�g���
		bool aAngleRelease[STICK_TYPE_MAX][STICK_ANGLE_MAX];	// �X�e�B�b�N�̕��������[�X���
	}STICK_INPUT;


	// ***** �֐� *****
	CJoypad();
	virtual~CJoypad();

	/* ���C�� */
	HRESULT Init(void);											// ������
	void Uninit(void);											// �I��
	void Update(void);											// �X�V(�{�^��)
	void UpdateStick(void);										// �X�V(�X�e�B�b�N)
	bool GetPress(JOYKEY Key, int nPatNum = 0);					// �v���X�����擾
	bool GetTrigger(JOYKEY Key, int nPatNum = 0);				// �g���K�[�����擾
	bool GetRelese(JOYKEY Key, int nPatNum = 0);				// �����[�X�����擾
	bool GetRepeat(JOYKEY Key, int nPatNum = 0);				// ���s�[�g�����擾

	int GetTriggerPedal(JOYKEY Key, int nPatNum = 0);					// �g���K�[�y�_�������擾
	void Vibration(int nTime, WORD nStrength, int nPatNum = 0);			// �R���g���[���[�̐U������
	STICK_INPUT GetStick(int nPatNum = 0) { return m_stick[nPatNum]; }	// �X�e�B�b�N�̓��͏����擾
	XINPUT_STATE *GetXInputState(void);									// �W���C�p�b�g�̓��͏��̎擾

private:
	// ***** ��` *****
	static const int MAX_PAT = 4;		// �R���g���[���̍ő吔

	// ***** �ϐ� *****
	STICK_INPUT m_stick[MAX_PAT];					// �X�e�B�b�N�̓��͏��
	XINPUT_STATE m_JoyKeyState[MAX_PAT];			// �v���X���
	XINPUT_STATE m_JoyKeyStateTrigger[MAX_PAT];		// �g���K�[���
	XINPUT_STATE m_JoyKeyStateRelease[MAX_PAT];		// �����[�X���
	XINPUT_STATE m_aJoyKeyStateRepeat[MAX_PAT];		// ���s�[�g���
	XINPUT_STATE m_aJoyKeyCurrentTime[MAX_PAT];		// ���݂̎���
	XINPUT_STATE m_aJoyKeyExecLastTime[MAX_PAT];	// �Ō�ɐ^��Ԃ�������
	D3DXVECTOR3 m_JoyStickPos[MAX_PAT];				// �W���C�X�e�B�b�N�̌X��
	XINPUT_VIBRATION m_JoyMoter[MAX_PAT];			// �W���C�p�b�h�̃��[�^�[
	int m_nTime[MAX_PAT];							// �U����������
	WORD m_nStrength[MAX_PAT];						// �U���̋��� (0 - 65535)
	XINPUT_STATE m_xInput;							// ���͏��

	bool m_bAngle[MAX_PAT][STICK_TYPE_MAX][STICK_ANGLE_MAX];				// �X�e�B�b�N�̓��͏��
	DWORD m_aStickCurrentTime[MAX_PAT][STICK_TYPE_MAX][STICK_ANGLE_MAX];	// �X�e�B�b�N�̌��݂̎���
	DWORD m_aStickExecLastTime[MAX_PAT][STICK_TYPE_MAX][STICK_ANGLE_MAX];	// �X�e�B�b�N�̌��݂̎���

};
#endif