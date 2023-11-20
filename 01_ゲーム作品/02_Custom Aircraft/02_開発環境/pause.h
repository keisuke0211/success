//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@pause.h           �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"main.h"

//��==================��
//�b�@ �񋓌^�\���� �@�b
//��==================��

//po�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	//�Q�[���ɖ߂�
	PAUSE_MENU_RETRY,			//�Q�[������蒼��
	PAUSE_MENU_QUIT,			//�^�C�g����ʂɖ߂�
	PAUSE_MENU_MAX
}PAUSE_MENU;

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif