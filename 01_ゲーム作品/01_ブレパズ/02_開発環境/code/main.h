//========================================
// *** main.h ***
//========================================

#ifndef _MAIN_H_
#define _MAIN_H_             

#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include <assert.h>
#include"XInput.h"
#include <iostream>	// �O���̑��u�Ɠ��o��
#include <fstream>	// �t�@�C�� �̓��o��
#include <vector>
#include <string>
#include <sstream>	// �J���}�ŋ�؂邽�߂ɕK�v

using namespace std;
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include"d3dx9.h"  //�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0X0800) //�r���h���̌x���Ώ��p�̃}�N��
#include"dinput.h"//���͏����ɕK�v//�Q�d�C���N���[�h�X�q�̃}�N�����`����

//#ifdef _DEBUG
//#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif
//========================================
// ���C�u����
//========================================

#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�����������ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	//���͏����ɕK�v
#pragma comment(lib,"Opengl32.lib")	//�t�H�O�����ɕK�v
#include"xaudio2.h"					//�T�E���h�����ɕK�v
//========================================
// �}�N����`
//========================================
#define SCREEN_WIDTH		(1280.0f)														// �E�C���h�E�̕�
#define SCREEN_HEIGHT		(720.0f)														// �E�C���h�E�̍���
#define SWITCH_TIME			(600)															// �؂�ւ�鎞��(1�b = 60)
#define INIT_FLOAT			(0.0f)															// float�̏����l
#define INIT_VEC			D3DXVECTOR3(0.0f,1.0f,0.0f)										// VEC�̏�����
#define INIT_D3DXVECTOR2	D3DXVECTOR2(0.0f,0.0f)											// D3DXVECTOR2�̏����l
#define INIT_D3DXVECTOR3	D3DXVECTOR3(0.0f,0.0f,0.0f)										// D3DXVECTOR3�̏����l
#define INIT_POSITIONVEC4	PositionVec4(0.0f,1.0f,0.0f,1.0f)								// PositionVec4�̏����l
#define INIT_D3DXCOLOR		D3DXCOLOR(1,1,1,1)												// D3DXCOLOR�̏����l
#define TXT_MAX				(256)															// ������̍ő吔(�ėp)


#ifdef _DEBUG

#define WINDOW_MODE			(false)								// �E�C���h�E���[�h�̐؂�ւ�

#else

#define WINDOW_MODE			(true)								// �E�C���h�E���[�h�̐؂�ւ�

#endif // _DEBUG
//========================================
// ���\����
//========================================

struct PositionVec4
{
	float     P0, P1, P2, P3;
	constexpr PositionVec4() : P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f) { }
	constexpr PositionVec4(float _P0, float _P1, float _P2, float _P3) : P0(_P0), P1(_P1), P2(_P2), P3(_P3) { }
};

// ���C�������̏��\����
typedef struct
{
	HWND				hWnd;		// �E�C���h�E�n���h��(���ʎq)
	HINSTANCE			hinstance;	// �C���X�^���X�n���h��
	D3DXVECTOR3			windowPos;	// �ʒu
}Main;

//========================================
// �v���g�^�C�v�錾
//========================================

/* �E�C���h�E�̃��[�h	*/void WindowMode(bool bScreen);
/* �E�C���h�E�n���h��	*/HWND *GetWindowHandle(void);
/* �C���X�^���X�n���h��	*/HINSTANCE *GetHinstance(void);
/* �E�C���h�E�ʒu		*/D3DXVECTOR3 GetWindowPos(void);
/* FPS					*/int GetFps(void);
#endif