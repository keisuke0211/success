//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�v���C���[�̏���  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "game.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "life.h"
#include "particle.h"
#include "effect.h"
//��==============��
//�b�@�}�N����`�@�b
//��==============��
#define MAX_SPEED (65535)		//�U���̍ő�l
#define MIN_SPEED	  (0)		//�U���̍ŏ��l

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffPlayer = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^
int g_nCounterAnimPlayer;									//�A�j���[�V�����J�E���^�[���W
int g_nPatternAnimPlayer;									//�A�j���[�V�����p�^�[�� No.
Player g_Player;											//�v���C���[�̏��
float g_fLengthPlayer;									    //�Ίp���̒���
float g_fAnglePlayer;									    //�Ίp���̊p�x
int ShootMode;												//�ˌ��؂�ւ��@�@0:�P�ˁ@1:�A��
int DirectionMode;											//�e��
int nCount;
int g_nCntMove;
//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�v���C���[�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��==============================��
//�b�@�@�v���C���[�̏����������@�@�b
//��==============================��
void InitPlayer(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\fighter_a.png",
		&g_pTexturePlayer);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	g_Player.pos = D3DXVECTOR3((SCREEN_WIDTH -300) / 2, SCREEN_HEIGHT -200,0);		//�ʒu
	g_Player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);									//�ړ���
    //                                   ��-3.14f�`3.14f
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//����������������(Z�l���g�p)
	g_Player.nLife = 5;																//���C�t�̒l��ݒ�
	g_Player.state = PLAYERSTATE_NORMAL;											//�v���C���[�̏�Ԃ�������
	g_Player.nCounterState = 0;														//�v���C���[�̏�ԃJ�E���g��������
	g_Player.bUse = true;
	g_Player.bDrw = true;
	g_Player.bBeing = true;
	g_nCntMove = 0;
	//�Ίp���̒������Z�o����(p��*p��+p����*p����);
	g_fLengthPlayer = sqrtf(64*64+64*64);

	//�Ίp���̊p�x���Z�o����(p��,p����)
	g_fAnglePlayer = atan2f(64,64);


	//g_nCounterAnimPlayer = 1;					//�J�E���^�[������������
	//g_nPatternAnimPlayer = 0;					//�p�^�[��No.������

	ShootMode     = 0;							//�ˌ����[�h��������
	DirectionMode = 0;							//�e��������������
	nCount = 0;
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffPlayer,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//�@�@�@�@x                               y                     z
	//pVtx[0].pos = D3DXVECTOR3(g_posPlayer.x - SIZE_WIDTH / 2, g_posPlayer.y - SIZE_HEIGHT / 2, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_posPlayer.x + SIZE_WIDTH / 2, g_posPlayer.y - SIZE_HEIGHT / 2, 0.0f); //�E���Őݒ肷��
	//pVtx[2].pos = D3DXVECTOR3(g_posPlayer.x - SIZE_WIDTH / 2, g_posPlayer.y + SIZE_HEIGHT / 2, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_posPlayer.x + SIZE_WIDTH / 2, g_posPlayer.y + SIZE_HEIGHT / 2, 0.0f); //�����Őݒ肷��

	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@�@rhw�̐ݒ�@�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@ ���_�J���[ �@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`�����W�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffPlayer->Unlock();

	//���C�t�̒l��ݒ�
	AddLife(g_Player.nLife);
}
//��==============================��
//�b�@�@ �v���C���[�̏I�������@�@ �b
//��==============================��
void UninitPlayer(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffPlayer != NULL)
	{
		g_pVtxbuffPlayer->Release();
		g_pVtxbuffPlayer = NULL;
	}
}
//��==============================��
//�b�@�@ �v���C���[�̍X�V�����@�@ �b
//��==============================��
void UpdatePlayer(void)
{
	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^
	
	XINPUT_STATE state;							//XINPUT_STATE�^ state���쐬
	XInputGetState(0, &state);					//state�ɏK�������R���g���[���̏�Ԃ��i�[
	XINPUT_VIBRATION vibration;					//XINPUT_VIBRATION vibration���쐬

	if (g_Player.bUse == true)
	{ 
		//�R���g���[���E�X�e�B�b�N����

		if (GetStick(STICK_TYPE_LEFT).fTplDiameter > 0)
		{// ���X�e�B�b�N���|��Ă��鎞�A
			g_Player.move.x += sinf(GetStick(STICK_TYPE_LEFT).fAngle) * PLAYER_SPEED;
			g_Player.move.y += cosf(GetStick(STICK_TYPE_LEFT).fAngle) * PLAYER_SPEED;
		}
		//else if (GetStick(STICK_TYPE_RIGHT).fTplDiameter > 0)
		//{// �E�X�e�B�b�N���|��Ă��鎞�A
		//	g_Player.move.x += sinf(GetStick(STICK_TYPE_RIGHT).fAngle) * PLAYER_SPEED;
		//	g_Player.move.y += cosf(GetStick(STICK_TYPE_RIGHT).fAngle) * PLAYER_SPEED;
		//}

		//�L�[�{�[�h&�R���g���[���E�{�^���@����

		else if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true || 
			xInput->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{//A�L�[�������ꂽ

			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true ||
				xInput->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{//����ړ�
				g_Player.move.x += sinf(D3DX_PI * -0.75f) * PLAYER_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.75f) * PLAYER_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true || 
				xInput->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{//�����ړ�
				g_Player.move.x += sinf(D3DX_PI * -0.25f) * PLAYER_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.25f) * PLAYER_SPEED;
			}
			else
			{//���ړ�
				g_Player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
				g_Player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;

			}
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true || 
			xInput->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{//D�L�[�������ꂽ
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true || 
				xInput->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{//�E��ړ�
				g_Player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true || 
				xInput->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{//�E���ړ�
				g_Player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;
			}
			else
			{//�E�ړ�
				g_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
				g_Player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;

			}
		}
		else if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true || 
			xInput->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		{//W�L�[�������ꂽ
			g_Player.move.x += sinf(D3DX_PI * 1.0f) * PLAYER_SPEED;
			g_Player.move.y += cosf(D3DX_PI * 1.0f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true ||
			xInput->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{//S�L�[�������ꂽ
			g_Player.move.x += sinf(D3DX_PI * 0.0f) * PLAYER_SPEED;
			g_Player.move.y += cosf(D3DX_PI * 0.0f) * PLAYER_SPEED;
		}

		
		if (ShootMode == 0)
		{
			if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_A )
			{
				nCount++;

				if (nCount % 12 == 0)
				{
					PlaySound(SOUND_LABEL_SE_SHOT); //���Đ��������T�E���h���w��
					// A �{�^���������ꂽ
					SetBullet(D3DXVECTOR3(g_Player.pos.x + 2.0f, g_Player.pos.y - 65.0f, 0.0f), D3DXVECTOR3(0.0f, -SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				}
			}
			if (GetKeyboardPress(DIK_SPACE) == true)
			{

				nCount++;
				if (DirectionMode == 0 && nCount % 12 == 0)
				{
					PlaySound(SOUND_LABEL_SE_SHOT); //���Đ��������T�E���h���w��
					SetBullet(D3DXVECTOR3(g_Player.pos.x + 2.0f, g_Player.pos.y - 65.0f, 0.0f), D3DXVECTOR3(0.0f, -SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				}
			}
		}
		else if (ShootMode == 1)
		{
			nCount++;
			if (GetKeyboardPress(DIK_SPACE) == true && nCount % 7 == 0)
			{
				PlaySound(SOUND_LABEL_SE_SHOT); //���Đ��������T�E���h���w��

				if (DirectionMode == 0)
				{
					SetBullet(D3DXVECTOR3(g_Player.pos.x + 0.0f, g_Player.pos.y - 65.0f, 0.0f), D3DXVECTOR3(0.0f, -SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				}
				/*else if (DirectionMode == 1)
				{
				SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, -SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				SetBullet(g_Player.pos, D3DXVECTOR3(sinf(D3DX_PI * -UP)* SPEED, cosf(D3DX_PI * -UP)* SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				SetBullet(g_Player.pos, D3DXVECTOR3(sinf(D3DX_PI * UP)* SPEED, cosf(D3DX_PI * -UP)* SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				SetBullet(g_Player.pos, D3DXVECTOR3(SPEED, 0.0f, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				SetBullet(g_Player.pos, D3DXVECTOR3(-SPEED, 0.0f, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				SetBullet(g_Player.pos, D3DXVECTOR3(sinf(D3DX_PI * -DOWN)* SPEED, cosf(D3DX_PI * DOWN)* SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				SetBullet(g_Player.pos, D3DXVECTOR3(sinf(D3DX_PI * DOWN)* SPEED, cosf(D3DX_PI  * DOWN)* SPEED, 0.0f), g_Player.rot.z, BULLETTYPE_PLAYER);
				}*/
			}
		}
		//��]

		//if (GetKeyboardPress(DIK_LEFT) == true)
		//{
		//	g_Player.rot.z = (float)fmod(g_Player.rot.z + D3DX_PI + (D3DX_PI * 2) + 0.1f, D3DX_PI * 2) - D3DX_PI;	//���v����
		//}
		//else if (GetKeyboardPress(DIK_RIGHT) == true)
		//{
		//	g_Player.rot.z = (float)fmod(g_Player.rot.z + D3DX_PI + (D3DX_PI * 2) - 0.1f, D3DX_PI * 2) - D3DX_PI;	//�����v����
		//}

		//�g��E�k��

		//if (GetKeyboardPress(DIK_UP) == true)
		//{
		//	g_fLengthPlayer += 0.5f;
		//}
		//else if (GetKeyboardPress(DIK_DOWN) == true)
		//{
		//	g_fLengthPlayer -= 0.5f;
		//}
		else if (GetKeyboardPress(DIK_F2))
		{
			if (ShootMode == 0)
			{
				ShootMode++;
			}
			else if (ShootMode == 1)
			{
				ShootMode--;
			}
		}
		//else if (GetKeyboardPress(DIK_F3))
		//{
		//	if (DirectionMode == 0)
		//	{
		//		DirectionMode++;
		//	}
		//	else if (DirectionMode == 1)
		//	{
		//		DirectionMode--;
		//	}
		//}

		//�ʒu���X�V
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		//�v���C���[�̈ʒu���͈͊O�ɏo������
		if (g_Player.pos.x > 960.0f)
		{//X���W���͈͊O�̏ꍇ
			g_Player.pos.x = 960.0f;
		}
		if (g_Player.pos.x < 50.0f)
		{//X���W���͈͊O�̏ꍇ
			g_Player.pos.x = 50.0f;
		}
		if (g_Player.pos.y > 680.0f)
		{//Y���W���͈͊O�̏ꍇ
			g_Player.pos.y = 680.0f;
		}
		if (g_Player.pos.y < 45.0f)
		{//Y���W���͈͊O�̏ꍇ
			g_Player.pos.y = 45.0f;
		}
		//�ړ��ʂ��X�V(����������)
		g_Player.move.x += (0.0f - g_Player.move.x) * 0.25f;
		g_Player.move.y += (0.0f - g_Player.move.y) * 0.25f;

		////���_���W�̍Đݒ�
		//pVtx[0].pos = D3DXVECTOR3(g_posPlayer.x - SIZE_WIDTH / 2, g_posPlayer.y - SIZE_HEIGHT / 2, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(g_posPlayer.x + SIZE_WIDTH / 2, g_posPlayer.y - SIZE_HEIGHT / 2, 0.0f); //�E���Őݒ肷��
		//pVtx[2].pos = D3DXVECTOR3(g_posPlayer.x - SIZE_WIDTH / 2, g_posPlayer.y + SIZE_HEIGHT / 2, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(g_posPlayer.x + SIZE_WIDTH / 2, g_posPlayer.y + SIZE_HEIGHT / 2, 0.0f); //�����Őݒ肷��
		//�e�N�X�`�����W�̍X�V
		VERTEX_2D *pVtx;

		//���_�o�b�t�@�̃��b�N
		g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

		switch (g_Player.state)
		{
		case PLAYERSTATE_NORMAL:
			break;

		case PLAYERSTATE_DAMAGE:

			if (g_Player.nCounterState == 0)
			{
				if (g_Player.bBph == true)
				{
					vibration.wLeftMotorSpeed = MIN_SPEED;		//vibration�@�����o�[�@wLeftMotorSpeed�@�ɒl�����@���[�^�[�X�s�[�h100%
					vibration.wRightMotorSpeed = MIN_SPEED;		//�@�@�@�@ �V�@    �@�@wRightMotorSpeed �ɒl����  ���[�^�[�X�s�[�h0%
					XInputSetState(0, &vibration);				//�W���C�X�e�B�b�N�Ƀo�C�u���[�^�[�f�[�^�𑗐M
				}

				g_Player.nCounterState = 20;
				g_Player.bDrw = true;
				g_Player.state = PLAYERSTATE_WAIT;
				//���\�\�\�\�\�\�\�\�\�\�\�\��
				//�b�@�@�@ ���_�J���[ �@�@�@�b
				//���\�\�\�\�\�\�\�\�\�\�\�\��
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�|���S����ʏ�F�ɖ߂�
			}
			else
			{
				g_Player.nCounterState--;
				g_Player.bDrw = g_Player.bDrw ? false : true;
			}
			break;
		case PLAYERSTATE_WAIT:
			if (g_Player.nCounterState == 0)
			{
				g_Player.bDrw = true;
				g_Player.state = PLAYERSTATE_NORMAL;
			}
			else
			{
				g_Player.nCounterState--;
				g_Player.bDrw = g_Player.bDrw ? false : true;
			}
			break;
		case PLAYERSTATE_DEATH:
			return;
			break;
		}


		pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;
		
		//�E���_�o�b�t�@���A�����b�N
		g_pVtxbuffPlayer->Unlock();
	}
	else if (g_Player.bUse == false && g_Player.bBeing == true)
	{
		g_nCntMove++;
		g_Player.pos = (g_Player.pos * (1.0f - (float)(g_nCntMove / (float)2000)) + (D3DXVECTOR3(g_Player.pos.x, -200.0f, 0.0f) * (float)(g_nCntMove / (float)2000)));

		SetParticle(D3DXVECTOR3(g_Player.pos.x + 20, g_Player.pos.y + 0.0f, 0.0f), 3, 40, 30.0f, 3,1);
		SetParticle(D3DXVECTOR3(g_Player.pos.x - 20, g_Player.pos.y + 0.0f, 0.0f), 3, 40, 30.0f, 3,1);


		VERTEX_2D *pVtx;

		//���_�o�b�t�@�̃��b�N
		g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 - g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 + g_fAnglePlayer)) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

		//�E���_�o�b�t�@���A�����b�N
		g_pVtxbuffPlayer->Unlock();
	}
}
//��==============================��
//�b�@�@ �v���C���[�̕`�揈���@�@ �b
//��==============================��
void DrawPlayer(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffPlayer, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_Player.bDrw == true)
	{
		pDevice->SetTexture(0, g_pTexturePlayer);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		//���_���\���̂̃T�C�Y
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//��================================��
//�b�@�@ �v���C���[�̃q�b�g�����@�@ �b
//��================================��
void HitPlayer(int nCntPlayer, int nDamage)
{
	XINPUT_STATE state;							//XINPUT_STATE�^ state���쐬
	XInputGetState(0, &state);					//state�ɏK�������R���g���[���̏�Ԃ��i�[
	XINPUT_VIBRATION vibration;					//XINPUT_VIBRATION vibration���쐬

		if (g_Player.nCounterState > 0)
		{}
		else if (g_Player.state == PLAYERSTATE_NORMAL)
		{
			g_Player.nLife -= nDamage;
			DeleteLife(nDamage);
		}

	if (g_Player.nLife == 0)//�v���C���[�̗̑͂��Ȃ��Ȃ���
	{
		g_Player.state = PLAYERSTATE_DEATH;

		//�����̐ݒ�
		SetParticle(g_Player.pos, 0, 40, 30.0f,0,0);

		//SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION); //���Đ��������T�E���h���w��

		vibration.wLeftMotorSpeed = MIN_SPEED;		//vibration�@�����o�[�@wLeftMotorSpeed�@�ɒl�����@���[�^�[�X�s�[�h100%
		vibration.wRightMotorSpeed = MIN_SPEED;		//�@�@�@�@ �V�@    �@�@wRightMotorSpeed �ɒl����  ���[�^�[�X�s�[�h0%
		XInputSetState(0, &vibration);				//�W���C�X�e�B�b�N�Ƀo�C�u���[�^�[�f�[�^�𑗐M

		g_Player.bUse = false;
		g_Player.bDrw = false;
		g_Player.bBeing = false;

		//��Ԃ̐ݒ�
		SetGameState(GAMESTATE_END2, 160);
	}

	else if (g_Player.nLife > 0 && g_Player.state == PLAYERSTATE_NORMAL)
	{
		if (g_Player.state == PLAYERSTATE_NORMAL)
		{
			g_Player.state = PLAYERSTATE_DAMAGE;
			g_Player.nCounterState = 10; //�_���[�W��ۂ��Ԃ�ݒ�
		}
		PlaySound(SOUND_LABEL_SE_HIT); //HIT���𗬂�

		if (g_Player.bBph == true)
		{
			vibration.wLeftMotorSpeed = MAX_SPEED;		//vibration�@�����o�[�@wLeftMotorSpeed�@�ɒl�����@���[�^�[�X�s�[�h100%
			vibration.wRightMotorSpeed = MAX_SPEED;		//�@�@�@�@ �V�@    �@�@wRightMotorSpeed �ɒl����  ���[�^�[�X�s�[�h0%
			XInputSetState(0, &vibration);				//�W���C�X�e�B�b�N�Ƀo�C�u���[�^�[�f�[�^�𑗐M
		}
		//XInputEnable(false);						//XInput�����B		�����ꂪ�Ȃ��Ƃ����ƐU�������ςȂ��ɂȂ�B

	}

}
//��======================��
//�b�@ �v���C���[�̏����@ �b
//��======================��
Player *Getplayer(void)
{
	return &g_Player;//�G�̏��̐擪�A�h���X��Ԃ�
}
