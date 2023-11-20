//****************************************
//	bullet.h
//	Author:��a�c��
//****************************************
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
//****************************************
// �}�N����`
//****************************************
#define BULLET_SIZE_WIDTH			(10)	//���̃T�C�Y
#define BULLET_SIZE_HEIGHT			(15)	//�c�̃T�C�Y
//****************************************
// ���\����
//****************************************
//�r���{�[�h�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXMATRIX mtxWorld;
	int nLife;
	int nIdxShadow;//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

	float fWidht;
	float fHight;

	bool bUse;
}Bullet;

//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Bullet *GetBullet(void);

#endif 