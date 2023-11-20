//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@fade.h		�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//��==================��
//�b�@ �񋓌^�\���� �@�b
//��==================��

//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,//�������Ă��Ȃ����
	FADE_IN,//�t�F�[�h�C�����
	FADE_OUT,//�t�F�[�h�A�E�g���
	FADE_MAX,
}FADE;
//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��

//�v���g�^�C�v�錾
void lnitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(MODE modeNext);
FADE GetFade(void);

#endif