//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@camera.h          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _CAMERA_H_  //���̃}�N����`������ĂȂ�������
#define _CAMERA_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//****************************************
// �\���̂̒�`
//****************************************

// �J�����̏��\����
typedef struct
{
	// �ʒu�֘A
	D3DXVECTOR3 pos;				// �ʒu
	float fWidth;					// ���̒��S�_
	float fHeighy;					// �c�̒��S�_

	bool bCamera_Y;
}Camera;


//****************************************
// �v���g�^�C�v�錾
//****************************************

void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

// �J�����̏����擾
Camera *GetCamera(void);

// �J�����̈ʒu�ɍ��킹��
void CameraPosition(D3DXVECTOR3 *pDrawPos);

#endif