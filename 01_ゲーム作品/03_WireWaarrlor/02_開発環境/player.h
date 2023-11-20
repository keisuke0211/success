//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@player/h          �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#ifndef _PLAYER_H_  //���̃}�N����`������ĂȂ�������
#define _PLAYER_H_  //�Q�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"
#include "block.h"
//****************************************
// �v���C���[�̍\���̂̒�`
//****************************************

typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 Draepos;//�`��ʒu
	D3DXVECTOR3 rot;    //����
	D3DXVECTOR3 move;   //�ړ���

	int nType;			//�摜���
	int nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int nPatternAnim;	//�A�j���[�V�����p�^�[��No.
	int nCntReturn;		//�v���C���[���t�b�N�̏��Ɉړ�����J�E���g
	int nCntFriction;	//���C�̌����J�E���g
	int bCheckpoint;	//���Ԓn�_�ɂӂꂽ��

	float fLength;		//�v���C���[�̒���
	float fAngle;		//�v���C���[�̊p�x
	float fTwo_Range;	//�v���C���[�ƃ��A�[�̋���
	float fTwo_Angle;	//�v���C���[�ƃ��A�[�̊p�x

	//�U��q�֌W
	float fx;			//�x�_�@X���W
	float fy;			//�x�_�@Y���W
	float rot1;			//�v���C���[�̊p�x
	float rot_spd;		//�p���x(�P�t���[���Ŋp�x���ω������)
	float length;		//�R�̒���(�v��)
	float lengthFixed;	//�R�̒���(�Œ�)
	float g;			//�d�͉����x
	float rad;			//���݂̏d��̈ʒu�@����
	float px;			//		�V			X���W
	float py;			//		�V			
	float vx;			//�d�͈ړ��ʂ𔽉f�����v���C���[�̈ʒu�@�����W
	float vy;			//�@			�V						�x���W
	float t;			//
	float gx;			//�d�͈ړ��ʂ𔽉f�����v���C���[�̈ʒu�@�����W
	float gy;			//�@			�V						�x���W
	float r;			//�Q�̏d��̈ʒu�̊p�x��
	float sub;			//�v���C���[�̊p�x�ƂQ�̏d��̊p�x����������
	float friction;		//���C��

	//�������^��
	float px1;			//�d��̈ʒu�@X���W�i������₷�������ϐ����g���j
	float py1;			//	  �V	�@Y���W
	float dx;			//X�����̑��x
	float dy;			//Y�����̑��x
	float gx1;			//�d�͉����x X���W
	float gy1;			//�d�͉����x Y���W

	//bool�ꗗ
	bool bLure;
	bool bDraw;			//�\�����邩
	bool bIdle;			//�ҋ@ON�EOFF
	bool bJump;			//�W�����v�����ǂ���
	bool bSpace;		//�v���C���[�ƃ��A�[�̊Ԋu���v�Z���������ĂȂ���
	bool bCamera;		//�J�����n�m�E�n�e�e
	bool bMeasure;		//�v���������ǂ���(�U��q)
	bool bMeasure2;		//�v���������ǂ���(�������^��)
	bool bPendulum;		//�U��q����E���Ȃ�
	bool bAutoLure;		//�ŏ��̎����ړ��������ǂ���
	bool bInertia;		//�������^�����邩�ǂ���
	bool bOperation;	//����o���邩�ǂ����H
	bool bLanding;		//���n�������ǂ���;
	bool bOnce;			//�P�񂾂���������
	bool bDirection;	//�������̐i�ޕ���

	Block *pBlock;		//�Ώۃu���b�N�ւ̃|�C���^
}Player;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);	//�S�̃f�[�^��main.cpp����ړ�
void PlayerAction(void);//�v���C���[�̑���A�ړ�����
void LureAction(void);	//���A�[�̑���A�ړ�����
void Pendulum(void);	//�U��q���̏���
void PendulumEnd(void); //�U��q�I�����̏���
Player *Getplayer(void);
//****************************************
// �}�N����`
//****************************************
#define DEFAULT_INT			(0)						//int�̏����l
#define DEFAULT_FLOAT		(0.0f)					//float�̏����l
#define SIZE_WIDTH			(16.0f)					// �v���C���[�̕�
#define SIZE_HEIGHT			(26.0f)					// 	  �V      ����
#define PLAYER_SPEED		(1.5f)					// 	  �V      �ړ����x
#define PLAYER_JUMP			(18.0f)					// 	  �V      �W�����v��
#define UP					(0.75f)					// �΂ߏ�̊p�x
#define DOWN				(0.25f)					// �΂߉��̊p�x
#define MIN_STRING			(10.0f)					// �ŏ��̎��̒���
#define MAX_STRING			(350.0f)				// �ő�̎��̒���
#define AMOUNT_OF_FRICTION	(0.0005f)				// ���C��
#define MIN_FRICTION		(0.0f)					// ���C�̍ŏ��l
#define MAX_FRICTION		(3.2f)					// ���C�̍ő�l
#define MIN_GRAVITY			(0.05f)					// �ŏ��̏d��
#define MAX_GRAVITY			(1.0f)					// �ō��̏d��

#endif