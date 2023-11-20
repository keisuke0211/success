//****************************************
//	wall.h
//	Author:��a�c��
//****************************************
#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define MAX_WALL (150)			//�ǂ̍ő吔
//*****************************************************************************
// �ǈꗗ
//*****************************************************************************
typedef enum
{
	WALL_LABEL_ROCKS02 = 0,		// �󂹂Ȃ���
	WALL_LABEL_ROCKS00,			// ������
	WALL_LABEL_AIR,				// ��C( �N���A�̓����蔻��p )
	WALL_LABEL_MAX
}WALL_LABEL;
//****************************************
// �\���̂̒�`
//****************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3	vecLine;	//���E���x�N�g��
	D3DXVECTOR3	vecToPos;	//���E���x�N�g��

	int nCype;				//�v�Z���@
	int nType;				//�摜���
	int nSplitX;			//���̕�����
	int nSplitY;			//�c�̕�����
	int nLife;				//�ϋv��
	int nCntTime;			//�؂�ւ�����

	float fWidth;			//����
	float fHight;			//����
	float fRate;			//pos0�����_�܂ł̋���
	bool bUse;				//�g�p���Ă��邩�ǂ�
	bool bDraw;
}Wall;

typedef struct
{
	int Total;		//�󂹂�ǂ̍��v
	int Break;		//�󂵂���
	int Current;	//���݂̐�
	float Current_F;	//���݉󂵂��ǂ̃p�[�Z���g�\��
	int Pull;		//���v�l����8���������l
}BreakWall;


//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void LoadWall(void);
void CollisionWallPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

Wall *GetWall(void);
BreakWall *GetBreakWall(void);


#endif
