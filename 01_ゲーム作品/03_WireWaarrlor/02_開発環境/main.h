//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@me\ain.h          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _MAIN_H_			         									    //���̃}�N����`������ĂȂ�������
#define _MAIN_H_             
//��========================��
//�b�@�C���N���[�h�t�@�C���@�b
//��========================��
#include<windows.h>//main.cpp����ړ�
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include"XInput.h"
#include"d3dx9.h"  //�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0X0800) //�r���h���̌x���Ώ��p�̃}�N��
#include"dinput.h"//���͏����ɕK�v//�Q�d�C���N���[�h�X�q�̃}�N�����`����
//��====================��
//�b�@�@���C�u�����C�@�@�b
//��====================��
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�����������ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	//���͏����ɕK�v
#include"xaudio2.h"					//�T�E���h�����ɕK�v
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define SCREEN_WIDTH     (1280.0f)											    //�E�C���h�E�̕�
#define SCREEN_HEIGHT    (720.0f)												//�E�C���h�E�̍����@��main.cpp����ړ�
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)			//���_�t�H�[�}�b�g�y2D�z
#define SWITCH_TIME		 (600)													//�؂�ւ�鎞��(1�b = 60)�@���ꕔ�̉�ʐ؂�ւ��Ɏd�l
//��====================��
//�b �@�@���\���� �@�@�b
//��====================��

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,	//�^�C�g�����
	MODE_TUTORIAL,	//�`���[�g���A�����
	MODE_GAME,		//�Q�[�����
	MODE_RESULY1,	//�Q�[���I�[�o�[
	MODE_RESULY2,	//�Q�[���N���A
	MODE_RANKING,	//�����L���O���
	MODE_MAX
} MODE;
//���_���y2D�z�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��W���i1.0f�ŌŒ�j
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
LPDIRECT3DDEVICE9 GetDevice(void);
void Position(D3DXVECTOR3 *pDrawPos, D3DXVECTOR3 basePos);	// �`��ʒu����ɍ��킹��
void SetMode(MODE mode);
MODE GetMode(void);
#endif