//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@block.h           �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _BLOCK_H_  //���̃}�N����`������ĂȂ�������
#define _BLOCK_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//*****************************************************************************
// �u���b�N�ꗗ
//*****************************************************************************
typedef enum
{
	BLOCK_LABEL_ROCKS02 = 0,		// �Â��΁i�w�i�j
	BLOCK_LABEL_ROCKS00,			// �D�F�̐�
	BLOCK_LABEL_ROCKS01,			// ���F�̐�
	BLOCK_LABEL_DIR,				// �y
	BLOCK_LABEL_BLOCK001,			// �u���b�N1
	BLOCK_LABEL_BLOCK002,			// �u���b�N2
	BLOCK_LABEL_TreasureChest,		// ��
	BLOCK_LABEL_Checkpoint1,		// ���Ԓn�_1
	BLOCK_LABEL_Checkpoint2,		// ���Ԓn�_2
	BLOCK_LABEL_MAX
}BLOCK_LABEL;

//****************************************
// �u���b�N�̍\���̂̒�`
//****************************************

//�u���b�N�\����
typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	int nType;			//���
	int nSpeed;			//�ړ���
	int nSplitX;		//���̕�����
	int nSplitY;		//�c�̕�����
	int nCounterAnim;	//�`���X�g�̃A�j���[�V�����J�E���g
	int nPatternAnim;	//�`���X�g�̃A�j���[�V�����p�^�[��
	int nCounterAnim1;	//�`���X�g�̃A�j���[�V�����J�E���g
	int nPatternAnim1;	//�`���X�g�̃A�j���[�V�����p�^�[��

	float fWidth;		//��
	float fHight;		//����

	bool bUse;			//�g�p���Ă��邩�ǂ���
	bool bClear;		//�S�[���������ǂ���
	bool bChat;			//�󔠂ɂӂꂽ���ǂ���
}Block;
//****************************************
// �}�N����`
//****************************************
#define MAX_BLOCK (256)	//�u���b�N�̍ő吔
#define NUM_BLOCK	(5) //�u���b�N�̎��
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void LoadBlock(void);

bool CollisionBlockPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool CollisionBlockLure(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool CollisionBlockAutoLure(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

bool CollisionBlockPendulumX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool CollisionBlockPendulumY(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

bool CollisionBlockParabola(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);



Block *GetBlock(void);

#endif