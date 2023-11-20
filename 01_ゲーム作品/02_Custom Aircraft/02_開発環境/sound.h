//=============================================================================
//
// �T�E���h���� [sound.h]
// Author :��a�c��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0�E�I�[�v�j���O
	SOUND_LABEL_BGM001,			// BGM1�E�X�e�[�W�P
	SOUND_LABEL_BGM002,			// BGM2�E�X�e�[�W�Q
	SOUND_LABEL_BGM003,			// BGM3�E�G���f�B���O�iCLEAR�j
	SOUND_LABEL_BGM004,			// BGM4�E�G���f�B���O�iOVER�j
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_START,		//�Q�[���X�^�[�g
	SOUND_LABEL_SE_CHARG,		//�`���[�W
	SOUND_LABEL_SE_SUMMON,		//����
	SOUND_LABEL_MAX,
}SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
