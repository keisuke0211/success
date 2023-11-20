//****************************************
//	meshfield_wall.h
//	Author:��a�c��
//****************************************
#ifndef _MESHFIELD_WALL_H_
#define _MESHFIELD_WALL_H_
#include "main.h"

//****************************************
// �\���̂̒�`
//****************************************

//���b�V���t�B�[���h�E�ǂ̍\����
typedef struct
{
	D3DXVECTOR3		pos;		//�ʒu
	D3DXVECTOR3		rot;		//����
	D3DXMATRIX		mtxWorld;	//���[���h�}�g���b�N�X
	int	nBlock_Z;				//���̃u���b�N��
	int nBlock_X;				//�c�̃u���b�N��

	float			fWidhtX;	//�c��
	float			fWidhtZ;	//����
}MeshWall;

//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitMeshField_Wall(void);
void UninitMeshField_Wall(void);
void UpdateMeshField_Wall(void);
void DrawMeshField_Wall(void);
void CollisionMeshField_Wall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

#endif 