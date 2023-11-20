//****************************************
//	figure_model.h
//	Author:��a�c��
//****************************************
#ifndef _FIGURE_MODEL_H_
#define _FIGURE_MODEL_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define NUM_FIGURE_MODEL	(7)			//���f���̔z�u��
#define TXT_MAX				(500)		//�ǂݍ��ޕ����̍ő吔
#define MAX_TEXTURE			(10)		//�e�N�X�`���̍ő吔
#define DAMEGE_COUNT		(10)		//�_���[�W�̂�����Ă��猳�̐F�ɖ߂�J�E���g
//****************************************
// �\���̂̒�`
//****************************************

//���f���i�u���j�̍\����
typedef struct
{
	D3DXVECTOR3		pos;		//�ʒu
	D3DXVECTOR3		rot;		//����
	D3DXMATRIX		mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxModelParent;		//�e���f���̃C���f�b�N�X

	int nLife;
	int nType;
	int nCntDamage;
	int	nIdxShadow = -1;		//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

	float fHight;
	float fWidth;
	float r,g,b,a;

	char aModelPath[TXT_MAX];	// ���f���̑��΃p�X
	
	bool bUse;
	bool bDraw;
}Figure;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitFigureModel(void);
void UninitFigureModel(void);
void UpdateFigureModel(void);
void DrawFigureModel(void);
void LoadFigureModel(void);
void HitFigure(int nCntFigure, int nDamage);
void CollisionFigurePlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
Figure *GetFigure(void);

#endif