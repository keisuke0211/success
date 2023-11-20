//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@bullet.h          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"
#include"explosion.h"
#include"enemy.h"
#include"player.h"
#include"boss.h"

//��==================��
//�b�@ �񋓌^�\���� �@�b
//��==================��
//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER = 0,//�v���C���[�̒e
	BULLETTYPE_ENEMY,     //�G�̒e
	BULLETTYPE_MAX
}BULLETTYPE;

//��==================��
//�b�@ �\���̂̒�` �@�b
//��==================��
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	float rot;			//����
	int nLife;			//����
	BULLETTYPE type;	//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Bullet;

//��====================��
//�b�@�v���g�^�C�v�錾�@�b
//��====================��
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float rot ,BULLETTYPE type);//pos ���ˈʒu�Fmove �ړ���
Bullet *GetBullet(void);
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define BULLET_WIDTH  (16.0f)
#define BULLET_HEIGHT (16.0f)
#define MAX_DATA		(2)
#define LIFE_DATA     (60)
#endif

