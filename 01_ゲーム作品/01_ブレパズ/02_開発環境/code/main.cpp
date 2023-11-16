//========================================
// ���C���̏���
//========================================
// *** main.cpp ***
//========================================
#include "main.h"
#include "manager.h"
//========================================
// �}�N����`
//========================================
#define CLASS_NAME    "WindowClass"		//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME   ""				//�E�C���h�E�̖��O(�L���v�V�����ɕ\��)

//========================================
// �v���g�^�C�v�錾
//========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void DrawFPS(void);

//========================================
// �O���[�o���ϐ�
//========================================
LPD3DXFONT g_pFont = NULL;						// �t�H���g�ւ̃|�C���^
int DisplayMode = 1;							// ������@�\���@ON/OFF
int g_nCountFPS = 0;							// FPS�J�E���^

Main	g_main;									// ���C�������̏��\����

CManager *g_Physics = NULL;						// �}�l�[�W���[�I�u�W�F�N�g�ւ̃|�C���^

//========== *** �E�C���h�E�n���h�����擾 ***
HWND *GetWindowHandle(void)
{
	return &g_main.hWnd;
}

//========== *** �C���X�^���X�n���h�����擾 ***
HINSTANCE *GetHinstance(void)
{
	return &g_main.hinstance;
}

//========== *** �E�C���h�E�̈ʒu���擾 ***
D3DXVECTOR3 GetWindowPos(void)
{
	return g_main.windowPos;
}

//========== *** FPS���擾 ***
int GetFps(void)
{
	return g_nCountFPS;
}

//========================================
// ���̏���
//========================================

//���C�������̏��
Main *GetMain(void)
{
	return &g_main;
}

//========================================
// ���C���֐�
//========================================
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hinstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	// ���������[�N ���O��\��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �E�C���h�E�N���X�̍\����
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),																//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,																		//�E�C���h�E�̃X�^�C��
		WindowProc,																		//�E�C���h�E�v���V�[�W��
		0,																				//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,																				//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hinstance,																		//�C���X�^���X�n���h��
		(HICON)LoadImage(NULL,"data\\ICO\\icon.ico",IMAGE_ICON,0,0,LR_SHARED | LR_LOADFROMFILE),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),														//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),														//�N���C�A���g�̈�̔w�i�F
		NULL,																			//���j���[�o�[
		CLASS_NAME,																		//�E�C���h�E�N���X�̖��O
		(HICON)LoadImage(NULL,"data\\ICO\\icon.ico",IMAGE_ICON,0,0,LR_SHARED | LR_LOADFROMFILE),	//�t�@�C���̃A�C�R��
	};
	MSG msg;									  //���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//��ʃT�C�Y�̍\����
												   // �E�C���h�E�N���X�̓o�^

	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�C���h�E�̐���
	g_main.hWnd = CreateWindowEx(0, // �g���E�B���h�E�X�^�C��
		CLASS_NAME,					// �E�C���h�E�N���X�̖��O
		WINDOW_NAME,				// �E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		// �E�C���h�E�X�^�C��
		CW_USEDEFAULT,				// �E�C���h�E�̍���X���W
		CW_USEDEFAULT,				// �E�C���h�E�̍���Y���W
		SCREEN_WIDTH,				// �E�C���h�E�̕�
		SCREEN_HEIGHT,				// �E�C���h�E�̍���
		NULL,						// �e�E�C���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�C���h�EID
		hinstance,					// �C���X�^���X�n���h��
		NULL);						// �E�C���h�E�쐬�f�[

	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCount;		//�t���[���J�E���g
	DWORD dwFPSLastTime;	//�Ō��FPS���v����������

	//�E�C���h�E���[�h�̐؂�ւ�
	WindowMode(WINDOW_MODE);

	if (g_Physics == NULL)
	{
		// �}�l�[�W���[�̐���
		g_Physics = new CManager;

		g_main.hinstance = hinstance;
		g_Physics->Init(g_main.hinstance, g_main.hWnd, TRUE);
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;				//����������
	dwExecLastTime = timeGetTime();	//���ݎ���������
	dwFrameCount = 0;				//����������
	dwFPSLastTime = timeGetTime();	//���ݎ���������

									//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���

			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); //���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);  //�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}

		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();//���ݎ���������

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//005�b�o��
			 //FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o�߂�����

				dwExecLastTime = dwCurrentTime;//�����J�n�̎���(���ݎ���)��ۑ�

				RECT rec;	// �傫�����󂯎��RECT�\����

				// �E�C���h�E�̏����擾
				GetWindowRect(g_main.hWnd, &rec);

				// �E�C���h�E�̈ʒu��ݒ�
				g_main.windowPos = D3DXVECTOR3(rec.left, rec.top, 0.0f);

				// �}�l�[�W���[�̍X�V����
				g_Physics->Update();

				// �}�l�[�W���[�̕`�揈��
				g_Physics->Draw();

				dwFrameCount++;//�t���[���J�E���g�����Z
			}
		}
	}

	if (g_Physics != NULL)
	{
		// �}�l�[�W���[�̏I������
		g_Physics->Uninit();

		delete g_Physics;
		g_Physics = NULL;
	}

	//����\��߂�
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	_CrtDumpMemoryLeaks();

	return(int)msg.wParam;
}

//========================================
// �E�C���h�E�v���V�[�W��
//========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY: //�E�C���h�E�j�������b�Z�[�W

					 //WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	//Destroy���b�Z�[�W�𑗂�
			}
			else
			{
				return 0;
			}
			break;
		}
		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	//Destroy���b�Z�[�W�𑗂�
		}
		else
		{
			return 0;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//����̏�����Ԃ�
}

//========================================
// FPS����
//========================================
void DrawFPS(void)
{
	RECT rect = { 0,230,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[521];

	//������ɑ��
	sprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//========================================
// �E�C���h�E���[�h�̐؂�ւ�
//========================================
void WindowMode(bool bScreen)
{
	HDC hDC			// �f�X�N�g�b�v�̃n���h��
		= GetDC(GetDesktopWindow());
	int nScrSizeX	// �f�X�N�g�b�v�̉�ʃT�C�YX
		= GetDeviceCaps(hDC, HORZRES);
	int nScrSizeY	// �f�X�N�g�b�v�̉�ʃT�C�YY
		= GetDeviceCaps(hDC, VERTRES);

	// �f�X�N�g�b�v�̃n���h���������
	ReleaseDC(GetDesktopWindow(), hDC);

	if (bScreen)
	{// �S��ʃt���O���^�̎��A
	 // �E�C���h�E�̈ʒu��ݒ�
		SetWindowPos(
			g_main.hWnd,
			HWND_TOP,
			0,
			0,
			nScrSizeX,
			nScrSizeY,
			SWP_SHOWWINDOW);

		// �E�C���h�E�X�^�C����ύX
		SetWindowLong(g_main.hWnd, GWL_STYLE, WS_POPUP);
	}
	else
	{// �S��ʃt���O���U�̎��A
	 // �E�C���h�E�̈ʒu��ݒ�
		SetWindowPos(
			g_main.hWnd,
			HWND_TOP,
			(nScrSizeX * 0.5f) - (SCREEN_WIDTH * 0.5f),
			(nScrSizeY * 0.5f) - (SCREEN_HEIGHT * 0.5f),
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SWP_SHOWWINDOW);

		// �E�C���h�E�X�^�C����ύX
		SetWindowLong(g_main.hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	}

	// �E�C���h�E�̕\����Ԃ�ݒ�
	ShowWindow(g_main.hWnd, SW_NORMAL);

	// �N���C�A���g�̈���X�V
	UpdateWindow(g_main.hWnd);
}
