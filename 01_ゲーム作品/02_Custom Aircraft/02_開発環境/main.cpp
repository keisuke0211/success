//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@���C���̏���      �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��

//�Q�[���� 
//Custom Aircraft(�J�X�^���@�G�A�N���t�g)

//��========================��
//�b�@�C���N���[�h�t�@�C���@�b
//��========================��
#include "main.h"			//�쐬�����@main.h ���C���N���[�h����
#include "sound.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result ver1.h"
#include "result ver2.h"
#include "ranking_bg.h"
#include "ranking_score.h"
#include "fade.h"
#include "enemy.h"
#include <stdio.h>
#include "tutorial.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define CLASS_NAME    "WindowClass"        //�E�C���h�E�N���X�̖��O
#define WINDOW_NAME   "Custom Aircraft"  //�E�C���h�E�̖��O(�L���v�V�����ɕ\��)
#define IDI_ICON1 (126)
#define IDI_ICON2 (125)

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3D9		  g_pD3D = NULL;			    //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		    //Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;						//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;							//FPS�J�E���^
int DisplayMode = 0;							//������@�\���@ON/OFF

MODE g_mode = MODE_TITLE;						//���݂̃��[�h


//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y���C���E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��==========================��
//�b�@�@�@�@���C���֐��@�@�@�@�b
//��==========================��
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hinstancePrev, LPSTR lpCmdLine, int nCmdShow)
{

	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�E�C���h�E�N���X�̍\���́@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						  //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,								  //�E�C���h�E�̃X�^�C��
		WindowProc,								  //�E�C���h�E�v���V�[�W��
		0,										  //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,										  //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hinstance,								  //�C���X�^���X�n���h��
		LoadIcon(NULL,((LPCSTR)IDI_ICON2)),		  //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),				  //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),				  //�N���C�A���g�̈�̔w�i�F
		NULL,									  //���j���[�o�[
		CLASS_NAME,								  //�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,((LPCSTR)IDI_ICON2)),		  //�t�@�C���̃A�C�R��
	};
	HWND hWnd;									  //�E�C���h�E�n���h��(���ʎq)
	MSG msg;									  //���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//��ʃT�C�Y�̍\����
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@ �E�C���h�E�N���X�̓o�^�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��

	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@�E�C���h�E�̐����@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	hWnd = CreateWindowEx(0, //�g���E�B���h�E�X�^�C��
		CLASS_NAME,          //�E�C���h�E�N���X�̖��O
		WINDOW_NAME,         //�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW, //�E�C���h�E�X�^�C��
		CW_USEDEFAULT,       //�E�C���h�E�̍���X���W
		CW_USEDEFAULT,       //�E�C���h�E�̍���Y���W
		SCREEN_WIDTH,        //�E�C���h�E�̕�
		SCREEN_HEIGHT,       //�E�C���h�E�̍���
		NULL,                //�e�E�C���h�E�̃n���h��
		NULL,                //���j���[�n���h���܂��͎q�E�C���h�EID
		hinstance,           //�C���X�^���X�n���h��
		NULL);               //�E�C���h�E�쐬�f�[

	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCount;		//�t���[���J�E���g
	DWORD dwFPSLastTime;	//�Ō��FPS���v����������

	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@ �@���������� �@�@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (FAILED(Init(hinstance, hWnd, TRUE)))
	{//�����������Ɏ��s�����ꍇ
		return -1;
	}
	//����\��ݒ�
	timeBeginPeriod(1);

	 dwCurrentTime = 0;					//����������
	 dwExecLastTime = timeGetTime();	//���ݎ���������
	 dwFrameCount = 0;					//����������
	 dwFPSLastTime = timeGetTime();		//���ݎ���������
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@�E�C���h�E�̕\���@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	ShowWindow(hWnd, nCmdShow);  //�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);          //�N���C�A���g�̈���X�V

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

			    //�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;//�t���[���J�E���g�����Z
			}
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//��==========================��
//�b�@�E�C���h�E�v���V�[�W���@�b
//��==========================��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;


	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^

	

	switch (uMsg)
	{
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
//��==========================��
//�b�@�@�@�f�o�C�X�̏����@�@�@�b
//��==========================��
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�yDirect3D�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��==================��
//�b�@�@�����������@�@�b
//��==================��
HRESULT Init(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow)//TRUE:�E�C���h�E/FALSE:�t���X�N���[��
{
	D3DDISPLAYMODE d3ddm;        //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp; //�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));   //�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;                          //�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                        //�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;                         //�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;                                     //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                      //�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;                           //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                     //�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;                                      //�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;    //���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;      //�C���^�[�o��

	//Direct3D�f�o�C�X������
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,                     //�`�揈��
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,//���_����
		&d3dpp,
		&g_pD3DDevice)))                    //�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL                     ,//�`�揈��
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,//���_����
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,                     //�`�揈��
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,//���_����
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PALETTE,
		"Terminal", &g_pFont);

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏���������
	if (FAILED(lnitKeyboard(hlnstance, hWnd)))
	{
		return E_FAIL;
	}

	//�T�E���h�̏���������
	InitSound(hWnd);

	//�t�F�[�h�̐ݒ�
	lnitFade(g_mode);

	//���[�h�̐ݒ�
	SetMode(g_mode);

	//�e��I�u�W�F�N�g�̏���������
	return S_OK;
}
//��==================��
//�b�@ �@�I�������@ �@�b
//��==================��
void Uninit(void)
{
	//����������������������������������
	//�@�@�e��I�u�W�F�N�g�̏I������
	//����������������������������������

	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@�@�@�I�������@�@�@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��

	//�T�E���h�̏I������
	StopSound();

	UninitSound();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�^�C�g����ʂ̏I������
	UninitTitle();

	//�`���[�g���A����ʂ̏I������
	UninitTutorial();

	//�Q�[����ʂ̏I������
	UninitGame();

	//���U���g��ʂP�̏I������
	UninitResult1();

	//���U���g��ʂQ�̏I������
	UninitResult2();

	//�����L���O��ʂ̏I������
	UninitRanking();

	//Xinput�����
	XInputEnable(false);

	//�t�F�[�h�̏I������
	UninitFade();

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@ �f�o�C�X�̔j���@ �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@�I�u�W�F�N�g�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\��
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//��==================��
//�b�@�@ �X�V�����@�@ �b
//��==================��
void Update(void)
{
	//����������������������������������
	//�@�@�e��I�u�W�F�N�g�̍X�V����
	//����������������������������������

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		UpdateTitle();
		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����
		UpdateTutorial();
		break;

	case MODE_GAME:			//�Q�[�����
		UpdateGame();
		break;

	case MODE_GAME_OVER:	//���U���g��ʁE�Q�[���I�[�o�[
		UpdateResult1();
		break;

	case MODE_GAME_CLEAR:	//���U���g��ʁE�Q�[���N���A
		UpdateResult2();
		break;

	case MODE_RANKING:		//�����L���O���
		UpdateRanking();
		break;
	}
	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//��==================��
//�b�@�@ �`�揈���@�@ �b
//��==================��
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	
	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

	 //����������������������������������
	 //�@�@�e��I�u�W�F�N�g�̕`�揈��
	 //����������������������������������

		switch (g_mode)
		{
		case MODE_TITLE:		//�^�C�g�����
			DrawTitle();
			break;

		case MODE_TUTORIAL:		//�`���[�g���A�����
			DrawTutorial1();
			break;

		case MODE_GAME:			//�Q�[�����
			DrawGame();
			break;

		case MODE_GAME_OVER:	//���U���g��ʁE�Q�[���I�[�o�[
			DrawResult1();
			break;

		case MODE_GAME_CLEAR:	//���U���g��ʁE�Q�[���N���A
			DrawResult2();
			break;

		case MODE_RANKING:		//�����L���O���
			DraeRanking();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�e�L�X�g�̕`�揈��
		RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		RECT rect1 = { 0,250,SCREEN_WIDTH,SCREEN_HEIGHT };

		char aStr[500];
		char aStr2[500];

		if (GetKeyboardTrigger(DIK_F1) == true)
		{
			if (DisplayMode == 0)
			{
				DisplayMode++;
			}
			else if (DisplayMode == 1)
			{
				DisplayMode--;
			}
		}
		if (DisplayMode == 1)
		{
			//������ɑ��
			wsprintf(&aStr[0], "\n �y ������@ �z \n���\�\�\�\�\�\�\��\n�b��ړ��F  [W] �b\n�b���ړ��F  [S] �b\n�b���ړ��F  [A] �b\n�b�E�ړ��F  [D] �b\n�b����]�F  [��]�b\n�b�E��]�F  [��]�b\n�b�g��@�F  [��]�b\n�b�k���@�F  [��]�b\n�b�e�@�@:[SPACE]�b\n���\�\�\�\�\�\�\��\n");
			wsprintf(&aStr2[0], "\n   �y �U�� �z   \n���\�\�\�\�\�\�\��\n�b�؊��@�F [F2] �b\n�b�e��  �F [F3] �b\n���\�\�\�\�\�\�\��\n");

			//�e�L�X�g�̕`��
			g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
			g_pFont->DrawText(NULL, &aStr2[0], -1, &rect1, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
#ifdef _DEBUG

		//FPS�̕\��
		DrawFPS();

#endif // _DEBUG

	    //�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//��==================��
//�b�@�@ FPS�����@ �@ �b
//��==================��
void DrawFPS(void)
{
	RECT rect = { 0,250,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	sprintf(&aStr[0], "FPS:%d\n�p�x:%f\n�o������:%d", g_nCountFPS, GetStick(STICK_TYPE_LEFT).fAngle, GetCunt());

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//��=================��
//�b�@���[�h�̐ݒ�@ �b
//��=================��
void SetMode(MODE mode)
{
	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		UninitTitle();
		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����
		UninitTitle();
		break;

	case MODE_GAME:			//�Q�[�����
		UninitGame();
		break;

	case MODE_GAME_OVER:	//���U���g��ʁE�Q�[���I�[�o�[
		UninitResult1();
		break;

	case MODE_GAME_CLEAR:	//���U���g��ʁE�Q�[���N���A
		UninitResult2();
		break;

	case MODE_RANKING:		//�����L���O���
		UninitRanking();
		break;
	}

	//�V������ʂ̏���������
	switch (mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		InitTitle();
		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����
		InitTutorial();
		break;

	case MODE_GAME:			//�Q�[�����
		InitGame();
		break;

	case MODE_GAME_OVER:	//���U���g��ʁE�Q�[���I�[�o�[
		InitResult1();
		break;

	case MODE_GAME_CLEAR:	//���U���g��ʁE�Q�[���N���A
		InitResult2();
		break;

	case MODE_RANKING:		//�����L���O���
		InitRanking();
		break;
	}

	g_mode = mode; //���݂̉�ʂɐ؂�ւ���
}

//��=================��
//�b�@���[�h�̏����@ �b
//��=================��
MODE GetMode(void)
{
	return g_mode;
}