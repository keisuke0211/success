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
	SOUND_LABEL_BGM001,			// BGM1�E�O
	SOUND_LABEL_BGM002,			// BGM2�E���A��
	SOUND_LABEL_BGM003,			// BGM3�E�G���f�B���O�iCLEAR�j
	SOUND_LABEL_BGM004,			// BGM4�E�G���f�B���O�iOVER�j
	SOUND_LABEL_SHOT,			//�e�̔��ˉ�
	SOUND_LABEL_DAMAGE,			//�G�̃_���[�W��
	SOUND_LABEL_BREAK,			//�ǂ����鉹
	SOUND_LABEL_JEWEL,			//�N���X�^���̊l����
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
