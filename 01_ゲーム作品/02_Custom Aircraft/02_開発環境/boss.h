//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@boos.h  �@�@�@�@  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _BOSS_H_  //���̃}�N����`������ĂȂ�������
#define _BOSS_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define NUM_BOSS	(4)		//�G�̍ő吔
#define SIZE_BOSS	(80)	//�{�X�̑傫��
//��==================��
//�b�@ �񋓌^�\���� �@�b
//��==================��

//�{�X�̏��
typedef enum
{
	BOSSSTATE_NORMAL = 0,	//�ʏ���
	BOSSSTATE_DAMAGE, 	//�_���[�W���
	BOSSSTATE_MAX
}BOSSSTATE;

//��====================��
//�b �@�@���\���� �@�@�b
//��====================��
//�G�\���̂̒�`
typedef struct
{
	int nType;				//�G�E���
	int sType;				//�e�E���
	int score;				//�X�R�A
	int m_pattern;			//�ړ��p�^�[��
	int s_pattern;			//���˃p�^�[��
	int state_pattern;		//��Ԑ��ڂ̃p�^�[��
	int in_time;			//�o������
	int stop_time;			//��~����
	int shot_time;			//�e���ˎ���
	int out_time;			//�A�Ҏ���
	int stand_time;			//�ҋ@����

	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���

	int speed;				//�e�X�s�[�h
	int init_nLife;			//�����̗�
	int curt_nLife;			//���݂̗̑�

	BOSSSTATE state;		//���
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nBullet;			//�U���Ԋu
	int nReset;				//�`���[�W���Z�b�g
	
	bool bHit;				//�����蔻�肠��Ȃ�
	bool bTime;				//�ҋ@���Ԃ̃J�E���g�@�J�n�E�I��
	bool bUse;				//�g�p���Ă��邩�ǂ���
	bool bDrw;				//�\�����邩���Ȃ���
	bool bSummon;			//����������
}Boss;

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nCntBoss);
void HitBoss(int nCntBoss, int nDamage);
void LoadBoss(void);
Boss *GetBoss(void);

int GetNumBoss(void);
int GetnCharge(void);
int GetinCnt(void);

#endif