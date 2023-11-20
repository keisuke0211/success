//****************************************
//	enemy_model.h
//	Author:��a�c��
//****************************************
#ifndef _ENEMY_MODEL_H_
#define _ENEMY_MODEL_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define NUM_MODEL			(50)		//���f���̔z�u��
#define TXT_MAX				(500)		//�ǂݍ��ޕ����̍ő吔
#define MAX_TEXTURE			(10)		//�e�N�X�`���̍ő吔
#define DAMEGE_COUNT		(10)		//�_���[�W�̂�����Ă��猳�̐F�ɖ߂�J�E���g
#define DECISION			(50)		//�����蔻��̒ǉ����l
#define RETURN_COUNT		(40)		//�G�̃��X�|�[�����鎞��
//****************************************
// �\���̂̒�`
//****************************************

//���f���i�u���j�̍\����
typedef struct
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		posOld;		// �O��̈ʒu
	D3DXVECTOR3		Initpos;	// �����ʒu
	D3DXVECTOR3		move;		// �ړ���
	D3DXVECTOR3		rot;		// ����
	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
	int nIdxModelParent;		// �e���f���̃C���f�b�N�X

	int nLife;
	int nSpeed;
	int nScore;
	int nType;
	int nType_M;				//�ړ��p�^�[��
	int nCntSummon;
	int nCntDamage;
	int	nIdxShadow = -1;		//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)

	float fHight;
	float fWidth;

	float r, g, b, a;

	char aModelPath[TXT_MAX];	// ���f���̑��΃p�X

	bool bUse;
	bool bDraw;
	bool bMove;
	bool bReturn;
}Enemy;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitEnemyeModel(void);
void UninitEnemyeModel(void);
void UpdateEnemyeModel(void);
void DrawEnemyeModel(void);
void LoadEnemyModel(void);
void ActionMode(Enemy *pEnemy);
void HitEnemy(int nCntFigure, int nDamage);
void CollisionEnemy_Wall(Enemy *pEnemy,D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
void CollisionEnemy_Player(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
Enemy *GetEnemy(void);

#endif
