//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@enemy.h		�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"main.h"
//****************************************
// �}�N����`
//****************************************
#define MAX_ENEMY (128) //�G�̍ő吔
#define SIZE_ENEMY (48) //�G�̑傫��

//****************************************
// �񋓌^�̒�`
//****************************************

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE, 	//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//****************************************
// �\���̂̒�`
//****************************************

//�G�\���̂̒�`
typedef struct
{
	int nType;			//�G�E���
	int sType;			//�e�E���
	int m_pattern;		//�ړ��p�^�[��
	int s_pattern;		//���˃p�^�[��
	int speed;			//�e�X�s�[�h
	int nLife;			//�̗�
	int score;			//�X�R�A

	int in_time;		//�o������
	int stop_time;		//��~����
	int shot_time;		//�e���ˎ���
	int out_time;		//�A�Ҏ���
	int nCntMove;		//�ړ��Ԋu
	int nBullet;		//�U���Ԋu
	int time;			//�v���C���[�̈ʒu���m�F���鎞��
	int Tracking;		//�ǔ����鎞��
	int stand_time;		//�ҋ@����

	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;    //����


	ENEMYSTATE state;	//���
	int nCounterState;	//��ԊǗ��J�E���^�[

	bool bUse;			//�g�p���Ă��邩�ǂ���
	bool Reversal;		//�ړ��������]
	bool m_switch;		//�s���E�؂�ւ�
	bool bTime;			//�ҋ@�̃I���E�I�t
	bool bDrw;			//�\���@����E���Ȃ�
	bool bHit;			//�����蔻��@�I���E�I�t
}Enemy;

//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void LoadEnemy(void);

//void SetEnemy(D3DXVECTOR3 pos, int nType);	//�ʒu�Ǝ��
void HitEnemy(int nCntEnemy, int nDamage);

Enemy *GetEnemy(void);
int GetNumEnemy(void);
int GetCunt(void);

#endif