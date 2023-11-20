//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�v���C���[�̏���  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "player.h"
#include "game.h"
#include "input.h"
#include "camera.h"
#include "lure.h"
#include "rope.h"
#include "sound.h"
#include "time.h"
//****************************************
// �O���[�o���ϐ�
//****************************************

LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffPlayer = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^

int nCnt;
Player g_Player;											//�v���C���[�̏��
//****************************************
// �v���C���[�̏���������
//****************************************
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
		".\\data\\TEXTURE\\player01.png",
		&g_pTexturePlayer);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@ �A�j���[�V���� �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	g_Player.pos			= D3DXVECTOR3(100, SCREEN_HEIGHT - 150,0);						//���݂̈ʒu
	g_Player.posOld			= D3DXVECTOR3(100, SCREEN_HEIGHT - 150, 0);						//�O��̈ʒu
	g_Player.move			= D3DXVECTOR3(0.0f,0.0f,0.0f);									//�ړ���
	g_Player.Draepos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//�`��ʒu
	g_Player.rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//����������������(Z�l���g�p)
	g_Player.fLength	    = sqrtf(SIZE_WIDTH*SIZE_WIDTH+SIZE_HEIGHT*SIZE_HEIGHT);			//�v���C���[�ƃt�b�N�Ƃ̋���
	g_Player.fAngle			= atan2f(SIZE_WIDTH, SIZE_HEIGHT);								//���݂̃v���C���[�ƃt�b�N�Ƃ̊p�x
	g_Player.fTwo_Range		= sqrtf(0*0 + 0*0);												//�v���C���[�ƃt�b�N�Ƃ̋���
	g_Player.fTwo_Angle		= atan2f(0, 0);													//���݂̃v���C���[�ƃt�b�N�Ƃ̊p�x
	g_Player.nCounterAnim	= DEFAULT_INT;													//�A�j���[�V�����J�E���^�[����������
	g_Player.nPatternAnim	= DEFAULT_INT;													//�A�j���[�V�����p�^�[��������������
	g_Player.nCntReturn		= DEFAULT_INT;													//�v���C���[���t�b�N�̈ʒu�Ɉړ�����J�E���g
	g_Player.nCntFriction	= DEFAULT_INT;													//���C�̌����J�E���g
	g_Player.bCheckpoint	= DEFAULT_INT;

	//�U��q�Ɏg���ϐ�
	g_Player.fx				= DEFAULT_FLOAT;
	g_Player.fy				= DEFAULT_FLOAT;
	g_Player.rot1			= DEFAULT_FLOAT;
	g_Player.rot_spd		= DEFAULT_FLOAT;
	g_Player.lengthFixed	= DEFAULT_FLOAT;
	g_Player.g				= DEFAULT_FLOAT;
	g_Player.px				= DEFAULT_FLOAT;
	g_Player.py				= DEFAULT_FLOAT;
	g_Player.vx				= DEFAULT_FLOAT;
	g_Player.vy				= DEFAULT_FLOAT;
	g_Player.t				= DEFAULT_FLOAT;
	g_Player.gx				= DEFAULT_FLOAT;
	g_Player.gy				= DEFAULT_FLOAT;
	g_Player.r				= DEFAULT_FLOAT;
	g_Player.sub			= DEFAULT_FLOAT;
	g_Player.friction		= MAX_FRICTION;
	g_Player.length			= DEFAULT_FLOAT;

	//�������^���Ɏg���ϐ�
	g_Player.px1			= DEFAULT_FLOAT;
	g_Player.py1			= DEFAULT_FLOAT;
	g_Player.dx				= DEFAULT_FLOAT;
	g_Player.dy				= DEFAULT_FLOAT;
	g_Player.gx1			= DEFAULT_FLOAT;
	g_Player.gy1			= DEFAULT_FLOAT;

	//bool�^
	g_Player.bJump		= false;
	g_Player.bDraw		= true;
	g_Player.bCamera	= true;
	g_Player.bLure		= false;
	g_Player.bSpace		= false;
	g_Player.bIdle		= false;
	g_Player.bMeasure	= false;
	g_Player.bMeasure2  = false;
	g_Player.bPendulum	= false;
	g_Player.bInertia	= false;
	g_Player.bAutoLure	= true;
	g_Player.bOperation = true;
	g_Player.bOnce		= false;
	g_Player.bDirection = false;

	nCnt = 0;
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

	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (-D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 - g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (0 + g_Player.fAngle)) * g_Player.fLength;

	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (-D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 - g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (0 + g_Player.fAngle)) * g_Player.fLength;

	pVtx[0].pos.z = DEFAULT_FLOAT;
	pVtx[1].pos.z = DEFAULT_FLOAT;
	pVtx[2].pos.z = DEFAULT_FLOAT;
	pVtx[3].pos.z = DEFAULT_FLOAT;

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
	pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffPlayer->Unlock();
}
//****************************************
// �v���C���[�̏I������
//****************************************
void UninitPlayer(void)
{
	//�T�E���h�̒�~
	StopSound();

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
//****************************************
// �v���C���[��	�X�V����
//****************************************
void UpdatePlayer(void)
{
	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^

	XINPUT_STATE state;							//XINPUT_STATE�^ state���쐬
	XInputGetState(0, &state);					//state�ɏK�������R���g���[���̏�Ԃ��i�[

	Lure *pLure = GetLure();
	Rope *pRope = GetRope();
	Block *pBlock = GetBlock();
	//�e�N�X�`�����W�̍X�V
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxbuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

	g_Player.posOld = g_Player.pos;		//�O��̈ʒu��ۑ�

	//�R���g���[���E�X�e�B�b�N����
	if (GetStick(STICK_TYPE_LEFT).fTplDiameter > 0)
	{// ���X�e�B�b�N���|��Ă��鎞�A
		g_Player.move.x += sinf(GetStick(STICK_TYPE_LEFT).fAngle) * PLAYER_SPEED;
		g_Player.move.y += cosf(GetStick(STICK_TYPE_LEFT).fAngle) * PLAYER_SPEED;
	}
	//����o���邩
	if (g_Player.bOperation == true)
	{
		//�v���C���[�̑���E�ړ�����
		PlayerAction();

		//���A�[�̑���E�ړ�����
		LureAction();

	}
		//�ʒu���X�V
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

	//�d�͏���
	if (g_Player.bLure == false)
	{
		if (g_Player.bJump == false)
		{
			if (g_Player.move.y <= 0)
			{
				g_Player.move.y += MAX_GRAVITY;
			}
			else if (g_Player.move.y >= 1)
			{
				g_Player.move.y += (MAX_GRAVITY + MIN_GRAVITY);
			}
		}
		else if (g_Player.bJump == true)
		{
			if (g_Player.move.y <= 0)
			{
				if (g_Player.bPendulum == false)
				{
					g_Player.move.y += MAX_GRAVITY;
				}
				else if (g_Player.bPendulum == true && g_Player.bPendulum == true && g_Player.pos.y >= pLure->pos.y)
				{
					g_Player.move.y = MAX_GRAVITY;
				}
				else if (g_Player.bPendulum == true && g_Player.bPendulum == true && g_Player.pos.y <= pLure->pos.y)
				{
					g_Player.move.y += MAX_GRAVITY;
				}
			}
			else if (g_Player.move.y >= 1)
			{
				if (GetLure()->bStab == true)
				{
					g_Player.bPendulum = true;
				}

				if (g_Player.bPendulum == false)
				{
					g_Player.move.y += (MAX_GRAVITY + MIN_GRAVITY);
				}
				else if (g_Player.bPendulum == true && g_Player.bPendulum == true && g_Player.pos.y >= pLure->pos.y)
				{
					g_Player.move.y = MAX_GRAVITY;
				}
				else if (g_Player.bPendulum == true && g_Player.bPendulum == true && g_Player.pos.y <= pLure->pos.y)
				{
					g_Player.move.y += (MAX_GRAVITY + MIN_GRAVITY);
				}
			}
		}
	}
	else if (g_Player.bLure == true)
	{
		if (g_Player.bJump == false)
		{
			if (g_Player.move.y <= 0)
			{
				g_Player.move.y += MAX_GRAVITY;
			}
			else if (g_Player.move.y >= 1)
			{
				g_Player.move.y += (MAX_GRAVITY + MIN_GRAVITY);
			}
		}
		else if (g_Player.bJump == true)
		{
			if (g_Player.bPendulum == true && g_Player.pos.y <= pLure->pos.y)
			{
				if (g_Player.move.y <= 0)
				{
					g_Player.move.y += MAX_GRAVITY;
				}
				else if (g_Player.move.y >= 1)
				{
					g_Player.move.y += (MAX_GRAVITY + MIN_GRAVITY);
				}
			}
			else if (pLure->bWireA == true)
			{

			}
			/*else
			{
				if (g_Player.move.y <= 0)
				{
					g_Player.move.y += MAX_GRAVITY;
				}
				else if (g_Player.move.y >= 1)
				{
					g_Player.move.y += (MAX_GRAVITY + MIN_GRAVITY);
				}
			}*/
		}
	}
	//�v���C���[�̈ʒu���͈͊O�ɏo������
	if (g_Player.pos.x >11500.0f)
	{//X���W���͈͊O�̏ꍇ
		g_Player.pos.x = 24800.0f;
	}
	else if (g_Player.pos.x > 90.0f && g_Player.pos.x < 10050.0f)
	{
		g_Player.bCamera = true;
	}
	else if (g_Player.pos.x > -359.0f && g_Player.pos.x < 90.0f)
	{
		g_Player.bCamera = false;
	}
	else if (g_Player.pos.x < -360.0f)
	{//X���W���͈͊O�̏ꍇ
		g_Player.pos.x = -360.0f;
	}
	else if (g_Player.pos.x > 10050.0f)
	{
		g_Player.bCamera = false;
	}
	
	if (g_Player.pos.y >= 720.0f &&g_Player.pos.y <= 1199.0f)
	{
		pLure->bUse			= false;
		pRope->bUse			= false;
		g_Player.bOperation = false;
		g_Player.bCamera	= false;
	}
	else if (g_Player.pos.y > 1200.0f)
	{//Y���W���͈͊O�̏ꍇ
		if (nCnt == 5)
		{
			if (g_Player.bCheckpoint == 0)
			{
				g_Player.pos = D3DXVECTOR3(100, 615, 0);
			}
			if (g_Player.bCheckpoint == 1)
			{
				g_Player.pos = D3DXVECTOR3(4230, 515, 0);
			}
			else if (g_Player.bCheckpoint == 2)
			{
				g_Player.pos = D3DXVECTOR3(7600, 565, 0);
			}
			g_Player.nCntFriction	= DEFAULT_INT;
			g_Player.nCntReturn		= DEFAULT_INT;
			pLure->nLife			= DEFAULT_INT;
			pLure->nCntReturn		= DEFAULT_INT;

			g_Player.fx				= DEFAULT_FLOAT;
			g_Player.fy				= DEFAULT_FLOAT;
			g_Player.rot1			= DEFAULT_FLOAT;
			g_Player.rot_spd		= DEFAULT_FLOAT;
			g_Player.lengthFixed	= DEFAULT_FLOAT;
			g_Player.g				= DEFAULT_FLOAT;
			g_Player.vx				= DEFAULT_FLOAT;
			g_Player.vy				= DEFAULT_FLOAT;
			g_Player.t				= DEFAULT_FLOAT;
			g_Player.gx				= DEFAULT_FLOAT;
			g_Player.gy				= DEFAULT_FLOAT;
			g_Player.r				= DEFAULT_FLOAT;
			g_Player.sub			= DEFAULT_FLOAT;
			g_Player.px1			= DEFAULT_FLOAT;
			g_Player.py1			= DEFAULT_FLOAT;
			g_Player.dx				= DEFAULT_FLOAT;
			g_Player.dy				= DEFAULT_FLOAT;
			g_Player.gx1			= DEFAULT_FLOAT;
			g_Player.gy1			= DEFAULT_FLOAT;

			g_Player.friction		= MAX_FRICTION;

			g_Player.bCamera	= true;
			g_Player.bMeasure	= false;
			g_Player.bMeasure2	= false;
			g_Player.bOnce		= false;
			g_Player.bPendulum	= false;
			g_Player.bLure		= false;
			g_Player.bSpace		= false;
			g_Player.bAutoLure	= true;
			g_Player.bOperation = true;
			g_Player.bInertia	= false;
			g_Player.bDirection = false;
			pLure->bReturn		= false;
			pLure->bStab		= false;
			pLure->bWireA		= false;

			nCnt = 0;
		}
		else
		{
			nCnt++;
		}
	}

	if (g_Player.pos.y < -100.0f)
	{//Y���W���͈͊O�̏ꍇ
		g_Player.pos.y = -100.0f;
	}

	//�ړ��ʂ��X�V(����������)
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.25f;


	//�u���b�N�Ƃ̓����蔻��
	if (CollisionBlockPlayer(&g_Player.pos, &g_Player.posOld, &g_Player.move) == true)
	{
		g_Player.bJump = false;
		g_Player.bPendulum = false;
		g_Player.bInertia = false;
	}

	//�������^�����Ă��Ȃ�������f�[�^������������
	if (g_Player.bInertia == false)
	{
		g_Player.px1 = DEFAULT_FLOAT;
		g_Player.py1 = DEFAULT_FLOAT;
		g_Player.dx	 = DEFAULT_FLOAT;
		g_Player.dy	 = DEFAULT_FLOAT;
		g_Player.gx1 = DEFAULT_FLOAT;
		g_Player.gy1 = DEFAULT_FLOAT;
		g_Player.bOnce = false;
	}
	//�v���C���[�𒆐S�ɉ�ʂ𓮂���
	D3DXVECTOR3 drawPos = g_Player.pos;

	CameraPosition(&drawPos);

	pVtx[0].pos.x = drawPos.x - SIZE_WIDTH;
	pVtx[0].pos.y = drawPos.y - SIZE_HEIGHT;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = drawPos.x + SIZE_WIDTH;
	pVtx[1].pos.y = drawPos.y - SIZE_HEIGHT;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = drawPos.x - SIZE_WIDTH;
	pVtx[2].pos.y = drawPos.y + SIZE_HEIGHT;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = drawPos.x + SIZE_WIDTH;
	pVtx[3].pos.y = drawPos.y + SIZE_HEIGHT;
	pVtx[3].pos.z = 0.0f;

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`�����W�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((g_Player.nPatternAnim % 5)* 0.2f), 0.0f	 + ((g_Player.nPatternAnim / 5)* 0.125f));
	pVtx[1].tex = D3DXVECTOR2(0.2f + ((g_Player.nPatternAnim % 5)* 0.2f), 0.0f	 + ((g_Player.nPatternAnim / 5)* 0.125f));
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((g_Player.nPatternAnim % 5)* 0.2f), 0.125f + ((g_Player.nPatternAnim / 5)* 0.125f));
	pVtx[3].tex = D3DXVECTOR2(0.2f + ((g_Player.nPatternAnim % 5)* 0.2f), 0.125f + ((g_Player.nPatternAnim / 5)* 0.125f));

	//���_�o�b�t�@���A�����b�N
	g_pVtxbuffPlayer->Unlock();
}
//****************************************
// �v���C���[�̕`�揈��
//****************************************
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
	if (g_Player.bDraw == true)
	{
		pDevice->SetTexture(0, g_pTexturePlayer);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�@�|���S���̕`��@�@�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��

		//���_���\���̂̃T�C�Y
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//****************************************
// �v���C���[�̑���E�ړ�����
//****************************************
void PlayerAction(void)
{
	//�L�[�{�[�h&�R���g���[���E�{�^���@����
	if (g_Player.bPendulum == false)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[�������ꂽ

			g_Player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;

			if (g_Player.bJump == false)
			{
				if (g_Player.nPatternAnim >= 0 && g_Player.nPatternAnim <= 10)
				{
					g_Player.nPatternAnim = 11;
				}
				if (g_Player.nPatternAnim >= 24 && g_Player.nPatternAnim <= 35)
				{
					g_Player.nPatternAnim = 11;
				}

				g_Player.nCounterAnim++;

				if (g_Player.nCounterAnim % 4 == 0)
				{
					if (g_Player.nPatternAnim >= 11 && g_Player.nPatternAnim <= 20)
					{
						g_Player.nPatternAnim++;
					}
					else if (g_Player.nPatternAnim == 21)
					{
						g_Player.nPatternAnim = 12;
					}
				}
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[�������ꂽ
			g_Player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;

			if (g_Player.bJump == false)
			{
				if (g_Player.nPatternAnim >= 11 && g_Player.nPatternAnim <= 21)
				{
					g_Player.nPatternAnim = 0;
				}
				if (g_Player.nPatternAnim >= 24 && g_Player.nPatternAnim <= 35)
				{
					g_Player.nPatternAnim = 0;
				}

				g_Player.nCounterAnim++;

				if (g_Player.nCounterAnim % 4 == 0)
				{
					if (g_Player.nPatternAnim >= 0 && g_Player.nPatternAnim <= 9)
					{
						g_Player.nPatternAnim++;
					}
					else if (g_Player.nPatternAnim == 10)
					{
						g_Player.nPatternAnim = 1;
					}
				}
			}
		}

		else if (GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false)
		{
			if (g_Player.nPatternAnim >= 11 && g_Player.nPatternAnim <= 21)
			{
				g_Player.nPatternAnim = 30;
			}
			else if (g_Player.nPatternAnim >= 0 && g_Player.nPatternAnim <= 10)
			{
				g_Player.nPatternAnim = 24;
			}
		}

		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{//�r�o�`�b�d�������ꂽ/\

			if (g_Player.bJump == false && g_Player.bLure == false)
			{
				PlaySound(SOUND_LABEL_SE_JUMP); //�W�����v�̌��ʉ�

				g_Player.bJump = true;
				g_Player.move.y = -PLAYER_JUMP;
			}
		}
	}

	if (g_Player.bJump == true)
	{
		//�v���C���[���O�����Ă��鎞
		if (g_Player.nPatternAnim >= 0 && g_Player.nPatternAnim <= 10)
		{
			g_Player.nPatternAnim = 22;
		}
		else if (g_Player.nPatternAnim >= 24 && g_Player.nPatternAnim <= 29)
		{
			g_Player.nPatternAnim = 22;
		}

		//�v���C���[���������Ă��鎞
		else if (g_Player.nPatternAnim >= 11 && g_Player.nPatternAnim <= 21)
		{
			g_Player.nPatternAnim = 23;
		}
		else if (g_Player.nPatternAnim >= 30 && g_Player.nPatternAnim <= 35)
		{
			g_Player.nPatternAnim = 23;
		}
	}
	else if (g_Player.bJump == false)
	{
		//�W�����v���[�V�����@�O��
		if (g_Player.nPatternAnim == 22)
		{
			g_Player.nPatternAnim = 24;
		}
		//�W�����v���[�V�����@���
		else if (g_Player.nPatternAnim == 23)
		{
			g_Player.nPatternAnim = 30;
		}
		//�ҋ@���[�V�����O��

		if (g_Player.nPatternAnim >= 24 && g_Player.nPatternAnim <= 35)
		{
			g_Player.nCounterAnim++;

			if (g_Player.nCounterAnim % 12 == 0)
			{
				if (g_Player.nPatternAnim >= 24 && g_Player.nPatternAnim <= 28)
				{
					g_Player.nPatternAnim++;
				}
				else if (g_Player.nPatternAnim == 29)
				{
					g_Player.nPatternAnim = 25;
				}
				else if (g_Player.nPatternAnim >= 30 && g_Player.nPatternAnim <= 34)
				{
					g_Player.nPatternAnim++;
				}
				else if (g_Player.nPatternAnim == 35)
				{
					g_Player.nPatternAnim = 30;
				}
			}
		}
	}

	if (g_Player.bPendulum == true && GetLure()->bStab == true)
	{
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_Player.length -= 5.0f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_Player.length += 5.0f;
		}

		//���̒����̌��E�l��ݒ�
		if (g_Player.length <= MIN_STRING)
		{
			g_Player.length = MIN_STRING;
		}
		else if (g_Player.length >= MAX_STRING)
		{
			g_Player.length = MAX_STRING;
		}
	}
}
//****************************************
// ���A�[�̑���E�ړ�����
//****************************************
void LureAction(void)
{
	Lure *pLure = GetLure();
	Rope *pRope = GetRope();

	if (pLure->bStab == false)
	{
		//�t�b�N���o��
		if (pLure->bUse == false)
		{
			//�w�肵�������Ƀt�b�N������
			if (GetKeyboardPress(DIK_W) == true && GetKeyboardPress(DIK_D) == true && GetKeyboardTrigger(DIK_P) == true)
			{
				g_Player.rot.z = -45.0f;
				SetLure(g_Player.pos, D3DXVECTOR3(20.0f, -20.0f, 0.0f), g_Player.rot);
			}
			else if (GetKeyboardPress(DIK_W) == true && GetKeyboardPress(DIK_A) == true && GetKeyboardTrigger(DIK_P) == true)
			{
				g_Player.rot.z = 45.0f;
				SetLure(g_Player.pos, D3DXVECTOR3(-20.0f, -20.0f, 0.0f), g_Player.rot);
			}
			else if (GetKeyboardPress(DIK_W) == true && GetKeyboardTrigger(DIK_P) == true)
			{
				g_Player.rot.z = 0.0f;
				SetLure(g_Player.pos, D3DXVECTOR3(0.0f, -20.0f, 0.0f), g_Player.rot);
			}
			else if (GetKeyboardPress(DIK_A) == true && GetKeyboardTrigger(DIK_P) == true)
			{

				g_Player.rot.z = 190.0f;
				SetLure(g_Player.pos, D3DXVECTOR3(-20.0f, 0.0f, 0.0f), g_Player.rot);
			}
			else if (GetKeyboardPress(DIK_D) == true && GetKeyboardTrigger(DIK_P) == true)
			{
				g_Player.rot.z = -190.0f;
				SetLure(g_Player.pos, D3DXVECTOR3(20.0f, 0.0f, 0.0f), g_Player.rot);
			}
			else if (GetKeyboardTrigger(DIK_P) == true)
			{
				if (g_Player.nPatternAnim >= 24 && g_Player.nPatternAnim <= 28)
				{
					g_Player.rot.z = -190.0f;
					SetLure(g_Player.pos, D3DXVECTOR3(20.0f, 0.0f, 0.0f), g_Player.rot);
				}
				else if (g_Player.nPatternAnim >= 30 && g_Player.nPatternAnim <= 34)
				{
					g_Player.rot.z = 190.0f;
					SetLure(g_Player.pos, D3DXVECTOR3(-20.0f, 0.0f, 0.0f), g_Player.rot);
				}
			}
			PlaySound(SOUND_LABEL_SE_EXPLOSION); //�t�b�N���ˉ�
		}
	}

	if (pLure->bStab == true && g_Player.bAutoLure == true)
	{
		pLure->bWireA = true;
		g_Player.bJump = true;
		if (g_Player.bJump == true)
		{
			g_Player.bLure = true;
		}
		//�t�b�N���ǂɓ��������玩���ł��̏ꏊ�Ɉړ�����
		if (g_Player.bLure == true && pLure->bWireA == true && g_Player.bAutoLure == true)
		{
			g_Player.pos = (g_Player.pos * (1.0f - (float)(g_Player.nCntReturn / (float)75)) + ((pLure->pos) *(float)(g_Player.nCntReturn / (float)75)));//�J�E���g�̑O��(float)������

			if (g_Player.pos.x >= pLure->pos.x - SIZE_LURE_WIDTH	* 8 &&
				g_Player.pos.x <= pLure->pos.x + SIZE_LURE_WIDTH	* 8 &&
				g_Player.pos.y >= pLure->pos.y - SIZE_LURE_HEIGHT	* 8 &&
				g_Player.pos.y <= pLure->pos.y + SIZE_LURE_HEIGHT	* 8)
			{
				StopSound(SOUND_LABEL_SE_EXPLOSION); //�t�b�N��߂�

				//pLure->bUse = false;
				g_Player.bAutoLure = false;
				g_Player.bPendulum = true;
				pLure->bWireA = false;
			}
			else
			{
				g_Player.nCntReturn++;

				if (CollisionBlockAutoLure(&g_Player.pos, &g_Player.posOld, &g_Player.move) == true)
				{
					pLure->bReturn = true;
				}
			}
		}
	}

	if (pLure->bStab == true && g_Player.bAutoLure == false)
	{
		if (pLure->bStab == true && g_Player.bJump == false)
		{
			//�v���C���[�ƃt�b�N�̋����𒲂ׂ�
			g_Player.length = sqrtf(pow(fabs(pLure->pos.x - g_Player.posOld.x), 2)
				+ pow(fabs(pLure->pos.y - g_Player.posOld.y), 2));

			//���̌��E�n��ݒ�
			if (g_Player.length >= MAX_STRING)
			{
				g_Player.length = MAX_STRING;
				g_Player.nCntReturn = 500;
				pLure->bReturn = true;
			}

			g_Player.bCamera = true;

			if (pLure->bWireA == false)
			{
				g_Player.bLure = false;
			}

			//�v���C���[�ƃt�b�N�̊p�x�����߂�
			/*g_Player.fTwo_Angle = atan2f(((pLure->pos.x - SIZE_LURE_WIDTH) - (g_Player.pos.x - SIZE_WIDTH))
				+ ((pLure->pos.x - SIZE_LURE_WIDTH) + (g_Player.pos.x - SIZE_WIDTH))
				, ((pLure->pos.y - SIZE_LURE_HEIGHT) - (g_Player.pos.y - SIZE_HEIGHT))
				+ ((pLure->pos.y - SIZE_LURE_HEIGHT) + (g_Player.pos.y - SIZE_HEIGHT)));*/

		}

		//�U��q
		Pendulum();

		//�t�b�N�����܂�
		if (GetKeyboardTrigger(DIK_P) == true && pLure->bReturn == false)
		{
			PlaySound(SOUND_LABEL_SE_START1); //�t�b�N��߂�

			g_Player.nCntReturn = 30;
			pLure->bReturn = true;
			g_Player.bPendulum = false;

		}

		if (GetKeyboardTrigger(DIK_SPACE) == true && pLure->bReturn == false)
		{
			g_Player.nCntReturn = 30;
			pLure->bReturn = true;
			g_Player.bPendulum = false;

			if (g_Player.rot_spd >= 0.02f || g_Player.rot_spd <= -0.02f)
			{
				//�������^�����n�߂�
				if (g_Player.bOnce == false)
				{
					g_Player.bInertia = true;
					g_Player.bMeasure2 = false;
					g_Player.px1 = g_Player.px;
					g_Player.py1 = g_Player.py;

					g_Player.bOnce = true;
				}
			}
		}

		//�U��q���̓����蔻��
		if (CollisionBlockPendulumX(&g_Player.pos, &g_Player.posOld, &g_Player.move) == true)
		{
			g_Player.rot_spd = DEFAULT_FLOAT;
		}
		if (CollisionBlockPendulumY(&g_Player.pos, &g_Player.posOld, &g_Player.move) == true)
		{
			pLure->bReturn = true;
		}
	}

	//�t�b�N���A�҂��鏈��
	if (pLure->bReturn == true)
	{
		pLure->nCntReturn++;
		pLure->pos = (pLure->pos * (1.0f - (float)(pLure->nCntReturn / (float)25)) + ((Getplayer()->pos) *(float)(pLure->nCntReturn / (float)25)));//�J�E���g�̑O��(float)������

		if (g_Player.pos.x >= pLure->pos.x - SIZE_LURE_WIDTH  * 2 &&
			g_Player.pos.x <= pLure->pos.x + SIZE_LURE_WIDTH  * 2 &&
			g_Player.pos.y >= pLure->pos.y - SIZE_LURE_HEIGHT * 2 &&
			g_Player.pos.y <= pLure->pos.y + SIZE_LURE_HEIGHT * 2)
		{
			pLure->bUse = false;
		}
	}

	//���A�[�𗣂������̏���
	if (g_Player.bInertia == true)
	{
		PendulumEnd();
	}

	//�t�b�N���g�p����Ă��Ȃ���ԂɂȂ�����@���C���[�֘A�̏���S�ď���������
	if (pLure->bUse == false && pLure->bReturn == true)
	{
		StopSound(SOUND_LABEL_SE_START1); //�t�b�N��߂�

		g_Player.nCntFriction		= DEFAULT_INT;
		g_Player.nCntReturn			= DEFAULT_INT;
		pLure->nLife				= DEFAULT_INT;
		pLure->nCntReturn			= DEFAULT_INT;

		g_Player.fx					= DEFAULT_FLOAT;
		g_Player.fy					= DEFAULT_FLOAT;
		g_Player.rot1				= DEFAULT_FLOAT;
		g_Player.rot_spd			= DEFAULT_FLOAT;
		g_Player.lengthFixed		= DEFAULT_FLOAT;
		g_Player.g					= DEFAULT_FLOAT;
		g_Player.vx					= DEFAULT_FLOAT;
		g_Player.vy					= DEFAULT_FLOAT;
		g_Player.t					= DEFAULT_FLOAT;
		g_Player.gx					= DEFAULT_FLOAT;
		g_Player.gy					= DEFAULT_FLOAT;
		g_Player.r					= DEFAULT_FLOAT;
		g_Player.sub				= DEFAULT_FLOAT;

		g_Player.friction			= MAX_FRICTION;
		
		g_Player.bCamera	= true;
		g_Player.bMeasure	= false;
		g_Player.bPendulum	= false;
		g_Player.bLure		= false;
		g_Player.bSpace		= false;
		g_Player.bAutoLure	= true;
		pLure->bReturn		= false;
		pLure->bStab		= false;
		pLure->bWireA		= false;
		pRope->bUse			= false;
	}
}
//****************************************
// �U��q�̏���
//****************************************
void Pendulum(void)
{
	Lure *pLure = GetLure();

	if (g_Player.bPendulum == true && g_Player.pos.y >= pLure->pos.y)
	{
		//g_Player.bCamera = false;
		//if (g_Player.fTwo_Angle <= 1.6f)
		//{
		//	g_Player.bIdle = false;
		//}
		//else if (g_Player.fTwo_Angle >= 2.4f)
		//{
		//	g_Player.bIdle = true;
		//}
		////fAngle�i�p�x�j�Ɉړ��ʂ�����
		//if (g_Player.bIdle == false)
		//{
		//	g_Player.fTwo_Angle += 0.02f;
		//}
		//if (g_Player.bIdle == true)
		//{
		//	g_Player.fTwo_Angle -= 0.02f;
		//}
		////�P��t�b�N�̈ʒu�Ƀv���C���[�𓮂���
		//g_Player.pos = pLure->pos;
		//g_Player.fTwo_Range -= 0.5;
		//g_Player.move.x = sinf(D3DX_PI * g_Player.fTwo_Angle) * g_Player.lengthFixed;
		//g_Player.move.y = cosf(D3DX_PI * g_Player.fTwo_Angle) * g_Player.lengthFixed;
		//

		//�P�񂾂��v�Z����
		if (g_Player.bMeasure == false)
		{
			GetLure()->rot.z = 0.0f;

			g_Player.g = 1.0f;

			//�v���C���[�ƃt�b�N�̋����𒲂ׂ�
			g_Player.length = sqrtf(pow(fabs(pLure->pos.x - g_Player.posOld.x), 2)
				+ pow(fabs(pLure->pos.y - g_Player.posOld.y), 2));

			//�v���C���[�ƃt�b�N�̋����𒲂ׂ�
			g_Player.rot1 = atan2f(g_Player.pos.y - pLure->pos.y, g_Player.pos.x - pLure->pos.x) * 180 / D3DX_PI;

			//�t�b�N�̍��W��������
			g_Player.fx = pLure->pos.x;
			g_Player.fy = pLure->pos.y;

			//���̌��E�n��ݒ�
			if (g_Player.length >= MAX_STRING)
			{
				g_Player.length = MAX_STRING;
			}
			g_Player.bMeasure = true;
		}
		//���̒������Œ�
		g_Player.lengthFixed = g_Player.length;

		//�@���݂̏d��̈ʒu
		g_Player.rad = g_Player.rot1 * D3DX_PI / 180;
		g_Player.px = g_Player.fx + cosf(g_Player.rad) * g_Player.lengthFixed;
		g_Player.py = g_Player.fy + sinf(g_Player.rad) * g_Player.lengthFixed;

		//�@�d�͂̈ړ��ʂ𔽉f�����d��̈ʒu
		g_Player.vx = g_Player.px - g_Player.fx;
		g_Player.vy = g_Player.py - g_Player.fy;
		g_Player.t = -(g_Player.vy * g_Player.g) / (g_Player.vx + g_Player.vy * g_Player.vy);
		g_Player.gx = g_Player.px + g_Player.t * g_Player.vx;
		g_Player.gy = g_Player.py + g_Player.g + g_Player.t * g_Player.vy;

		//�Q�̏d��̈ʒu�̊p�x��
		g_Player.r = atan2f(g_Player.gy - g_Player.fy, g_Player.gx - g_Player.fx) * 180 / D3DX_PI;

		//�p�x���������x�ɉ��Z
		g_Player.sub = g_Player.r - g_Player.rot1;
		g_Player.sub -= floorf(g_Player.sub / 360.0) * 360.0;
		if (g_Player.sub < -180.0) g_Player.sub += 360.0;
		if (g_Player.sub > 180.0) g_Player.sub -= 360.0;
		g_Player.rot_spd += g_Player.sub;

		//���C(�l�𑝂₷�Ɖ�]�X�s�[�h���オ��)
		g_Player.rot_spd += AMOUNT_OF_FRICTION;

		//�U��q��Ԃ̎��@��]�X�s�[�h�� A & D �ŏグ��
		if (GetKeyboardPress(DIK_A) == true)
		{
			if (g_Player.rot_spd >= MIN_FRICTION && g_Player.rot_spd <= MAX_FRICTION / 2)
			{
				g_Player.rot_spd += AMOUNT_OF_FRICTION * 100;
				g_Player.friction += 0.1f;
			}
		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			if (g_Player.rot_spd <= MIN_FRICTION && g_Player.rot_spd >= -MAX_FRICTION / 2)
			{
				g_Player.rot_spd -= AMOUNT_OF_FRICTION * 100;
				g_Player.friction += 0.1f;
			}
		}

		//�U�蕝�̌��E�l�̐ݒ�
		if (g_Player.friction >= MAX_FRICTION)
		{
			g_Player.friction = MAX_FRICTION;
		}
		else if (g_Player.friction <= -MAX_FRICTION)
		{
			g_Player.friction = -MAX_FRICTION;
		}

		//���C�̌��E�l��ݒ�
		if (g_Player.rot_spd >= g_Player.friction)
		{
			g_Player.rot_spd = g_Player.friction;
		}
		else if (g_Player.rot_spd <= -g_Player.friction)
		{
			g_Player.rot_spd = -g_Player.friction;
		}

		//���C�̌��E�l�����X�Ɍ��炷
		g_Player.nCntFriction++;

		if (g_Player.nCntFriction % 10 == 0)
		{
			g_Player.friction -= 0.1f;
		}

		//���E�l��0�ȉ��ɍs���Ȃ��悤�ɂ���
		if (g_Player.friction <= 0.0f)
		{
			g_Player.friction = 0.0f;
		}

		//�p�x�Ɋp���x�����Z
		g_Player.rot1 += g_Player.rot_spd;

		//�V�����d��̈ʒu
		g_Player.rad = g_Player.rot1 * D3DX_PI / 180;
		g_Player.px = g_Player.fx + cosf(g_Player.rad) * g_Player.lengthFixed;
		g_Player.py = g_Player.fy + sinf(g_Player.rad) * g_Player.lengthFixed;

		//�d��̍��W
		g_Player.pos.x = g_Player.px;
		g_Player.pos.y = g_Player.py;
	}

}
//****************************************
// �������^��
//****************************************
void PendulumEnd(void)
{
	Lure *pLure = GetLure();

	if (g_Player.bMeasure2 == false)
	{
		// X ���W�̑��x��ݒ�
		g_Player.dx = ((g_Player.pos.x - pLure->pos.x) / 12.5);

		// �x���W�̑��x��ݒ�
		g_Player.dy = ((pLure->pos.y - g_Player.pos.y) / 12.5);

		//�d�͉����x�̐ݒ�@X���W
		g_Player.gx1 = ((g_Player.pos.x - pLure->pos.x) / 1000);

		//�d�͉����x�̐ݒ�
		g_Player.gy1 = 1.0f;
		
		g_Player.bMeasure2 = true;
	}

	// X �������x�ɏd�͉����x�����Z
	g_Player.dx -= g_Player.gx1;
	// Y �������x�ɏd�͉����x�����Z
	g_Player.dy += g_Player.gy1;

	// ���W�ɑ��x�����Z
	g_Player.px1 += g_Player.dx;
	g_Player.py1 += g_Player.dy;

	// ���W���C���X�^���X�̍��W�ɔ��f
	g_Player.pos.x = g_Player.px1;
	g_Player.pos.y = g_Player.py1;

	// �n�ʁE�ǂɓ���������������^������߂�
	if (CollisionBlockParabola(&g_Player.pos, &g_Player.posOld, &g_Player.move) == true)
	{
		g_Player.bInertia = false;
	}
}
//****************************************
// �v���C���[�̏���
//****************************************
Player *Getplayer(void)
{
	return &g_Player;
}