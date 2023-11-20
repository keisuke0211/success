//****************************************
//	camera.h
//	Author:��a�c��
//****************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

//****************************************
// �\���̂̒�`
//****************************************

// �J�����̏��\����
typedef struct
{
	D3DXVECTOR3 posV;				// ���݂̎��_
	D3DXVECTOR3 posR;				// ���݂̒����_
	D3DXVECTOR3 posOldV;			// �O��̎��_
	D3DXVECTOR3 posOldR;			// �O��̒����_
	D3DXVECTOR3 vecU;				// ������x�N�g��
	D3DXMATRIX mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;				// �r���[�}�g���b�N�X
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 spin;				// ��]��
	D3DVIEWPORT9 viewport;			// �r���[�|�[�g
									   
	float length;					// ����
									   
	bool bUse;						// �g���Ă��邩
	bool bFog;						// ���̗L��
}Camera;
//****************************************
// �}�N����`
//****************************************
#define CAMERA_SPEED			(5)			// �ړ����x�iX�EZ���W�j
#define CAMERA_SPEED1			(2)			// �ړ����x�iY���W�j
#define ROT_SPEED				(0.015f)	// ��]�X�s�[�h
#define MAX_CAMERA				(3)			// �ő�J������
#define SPIN_DAMP				(0.9f)		// ��]�̌�����
#define ROT_CURSOR	(D3DXVECTOR3(0.0005f,0.00075f,0.0f))// �J�����̃J�[�\���̉�]��
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nldx); 
Camera *Getcamara(int nCntCamara);

#endif