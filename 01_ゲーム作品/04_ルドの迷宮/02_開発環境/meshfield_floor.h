//****************************************
//	meshfield_floor.h
//	Author:��a�c��
//****************************************
#ifndef _MESHFIELD_FLOOR_H_
#define _MESHFIELD_FLOOR_H_
#include "main.h"

//****************************************
// �}�N����`
//****************************************
#define NUM_MESHI			(3)			//���b�V���̔z�u��
//****************************************
// �\���̂̒�`
//****************************************

//���b�V���t�B�[���h�E���̍\����
typedef struct
{
	D3DXVECTOR3		pos;		//�ʒu
	D3DXVECTOR3		rot;		//����
	D3DXMATRIX		mtxWorld;	//���[���h�}�g���b�N�X
	int	nBlock_Z;				//���̃u���b�N��
	int nBlock_X;				//�c�̃u���b�N��
	int nVertex;				//���_��
	int nIdx;					//�C���f�b�N�X��
	int nPolygon;				//�|���S����

	float			fWidhtX;	//�c��
	float			fWidhtZ;	//����
}MeshFloor;

//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitMeshField_Floor(void);
void UninitMeshField_Floor(void);
void UpdateMeshField_Floor(void);
void DrawMeshField_Floor(void);

#endif 