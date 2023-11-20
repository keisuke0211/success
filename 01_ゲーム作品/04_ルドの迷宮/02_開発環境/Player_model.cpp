//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@���f������        �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "Player_model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "wall.h"
#include "effect.h"
#include "torch.h"
#include "figure_model.h"
#include "stone_pillar.h"
#include "meshfield_wall.h"
#include "enemy_model.h"
#include "jewel.h"
#include "sound.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPD3DXMESH g_pMeshHammerModel = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatHammerModel = NULL;					//�}�e���A���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureHammerModel[2] = {};			//�e�N�X�`���ւ̃|�C���^
DWORD g_dwNumHammerMatModel = 0;							//�}�e���A���̐�
Player		g_player;										//�v���C���[�̏��
//****************************************
// ���f���̏���������
//****************************************
void InitPlayerModel(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(Getcamara(0)->posV.x,5.0f, Getcamara(0)->posV.z); //x,y,z+250
	g_player.posOld = DEFAULT_D3DXVECTOR3;
	g_player.move = DEFAULT_D3DXVECTOR3;
	g_player.vecMove = DEFAULT_D3DXVECTOR3;
	g_player.relativePosR = D3DXVECTOR3(0.0f,15.0f,0.0f);
	g_player.targetPosR = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 3.125f, 0.0f);
	g_player.nCntAction = 30;
	g_player.fWidht = 25.0f;
	g_player.bAction = true;
	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/Luna.x",/*�ǂݍ��ރt�@�C����*/
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatHammerModel,
		NULL,
		&g_dwNumHammerMatModel,
		&g_pMeshHammerModel);

	D3DXMATERIAL *pMat;							//�}�e���A���ւ̃|�C���^

	//�}�e���A�����ɑ΂���|�C���^������
	pMat = (D3DXMATERIAL*)g_pBuffMatHammerModel->GetBufferPointer();

	for (int nCntMat = 0;nCntMat < (int)g_dwNumHammerMatModel;nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���

			//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_pTextureHammerModel[nCntMat]);
		}
	}

	//�e�̐ݒ�
	g_player.nIdxShadow = SetShadow();
	//g_player.nIdxShadow = SetTorch();
}
//****************************************
// ���f���̏I������
//****************************************
void UninitPlayerModel(void)
{
	//�T�E���h�̒�~
	StopSound();

	//���b�V���̔j��
	if (g_pMeshHammerModel != NULL)
	{
		g_pMeshHammerModel->Release();
		g_pMeshHammerModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatHammerModel != NULL)
	{
		g_pBuffMatHammerModel->Release();
		g_pBuffMatHammerModel = NULL;
	}
}
//****************************************
// ���f���̍X�V����
//****************************************
void UpdatPlayerModel(void)
{
	//�O��̈ʒu���X�V����
	g_player.posOld = g_player.pos;

	if(g_player.bAction == true)
	{
		//git�����g����悤�ɂȂ���
		if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[�������ꂽ

			if (GetKeyboardPress(DIK_W) == true)
			{//W�L�[�������ꂽ
				g_player.moveRot.y = -0.75 - (Getcamara(0)->rot.z * D3DX_PI);
				g_player.rot.y = 2.25f - (Getcamara(0)->rot.z * D3DX_PI);

				g_player.move.x += sinf(g_player.moveRot.y) * MODEL_SPEED;
				g_player.move.z += cosf(g_player.moveRot.y) * MODEL_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//S�L�[�������ꂽ
				g_player.moveRot.y = -2.25 - (Getcamara(0)->rot.z * D3DX_PI);
				g_player.rot.y = 0.75f - (Getcamara(0)->rot.z * D3DX_PI);

				g_player.move.x += sinf(g_player.moveRot.y) * MODEL_SPEED;
				g_player.move.z += cosf(g_player.moveRot.y) * MODEL_SPEED;
			}
			else
			{
				g_player.moveRot.y = -1.570796f - (Getcamara(0)->rot.z * D3DX_PI);
				g_player.rot.y = 1.570796f - (Getcamara(0)->rot.z * D3DX_PI);


				g_player.move.x += sinf(g_player.moveRot.y) * MODEL_SPEED;
				g_player.move.z += cosf(g_player.moveRot.y) * MODEL_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[�������ꂽ

			if (GetKeyboardPress(DIK_W) == true)
			{//W�L�[�������ꂽ
				g_player.moveRot.y = 0.75 - (Getcamara(0)->rot.z * D3DX_PI);
				g_player.rot.y = -2.25f - (Getcamara(0)->rot.z * D3DX_PI);

				g_player.move.x += sinf(g_player.moveRot.y) * MODEL_SPEED;
				g_player.move.z += cosf(g_player.moveRot.y) * MODEL_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//S�L�[�������ꂽ
				g_player.moveRot.y = 2.25 - (Getcamara(0)->rot.z * D3DX_PI);
				g_player.rot.y = -7.5 - (Getcamara(0)->rot.z * D3DX_PI);


				g_player.move.x += sinf(g_player.moveRot.y) * MODEL_SPEED;
				g_player.move.z += cosf(g_player.moveRot.y) * MODEL_SPEED;
			}
			else
			{
				g_player.moveRot.y = 1.570796f - (Getcamara(0)->rot.z * D3DX_PI);
				g_player.rot.y = -1.570796f - (Getcamara(0)->rot.z * D3DX_PI);

				g_player.move.x += sinf(g_player.moveRot.y) * MODEL_SPEED;
				g_player.move.z += cosf(g_player.moveRot.y) * MODEL_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[�������ꂽ
			g_player.moveRot.y = 0.0f - (Getcamara(0)->rot.z * D3DX_PI);
			g_player.rot.y = 3.1425f - (Getcamara(0)->rot.z * D3DX_PI);

			// �ړ��ʂ��X�V
			g_player.move.x += sinf(g_player.moveRot.y) * MODEL_SPEED;
			g_player.move.z += cosf(g_player.moveRot.y) * MODEL_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[�������ꂽ
			g_player.moveRot.y = 3.1425f - (Getcamara(0)->rot.z * D3DX_PI);
			g_player.rot.y = 0.0f - (Getcamara(0)->rot.z * D3DX_PI);

			g_player.move.x += sinf(g_player.moveRot.y) * MODEL_SPEED;
			g_player.move.z += cosf(g_player.moveRot.y) * MODEL_SPEED;
		}

		if (GetKeyboardPress(DIK_J) == true)
		{//DIK_LSHIFT �L�[�������ꂽ

			//g_player.rot.y -= 0.03125f;
			Getcamara(0)->rot.z += ROT_SPEED;
		}
		else if (GetKeyboardPress(DIK_L) == true)
		{//DIK_RSHIFT �L�[�������ꂽ

			//g_player.rot.y += 0.03125f;
			Getcamara(0)->rot.z -= ROT_SPEED;
		}

		
		for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
		{
			if (nCntCamera < 2)
			{
				Getcamara(nCntCamera)->posR.x = g_player.pos.x + sinf(D3DX_PI * (1.0f - g_player.rot.y));
				Getcamara(nCntCamera)->posR.z = g_player.pos.z + cosf(D3DX_PI * (1.0f - g_player.rot.y));

				Getcamara(nCntCamera)->posV.x = Getcamara(nCntCamera)->posR.x + sinf(D3DX_PI * (1.0f - Getcamara(nCntCamera)->rot.z)) * Getcamara(nCntCamera)->length;
				Getcamara(nCntCamera)->posV.z = Getcamara(nCntCamera)->posR.z + cosf(D3DX_PI * (1.0f - Getcamara(nCntCamera)->rot.z)) * Getcamara(nCntCamera)->length;
			}
		}

		//�ړ��ʂ��X�V

		//// ���_���璍���_�܂ł̊p�x�����߁A�ړ������ɉ��Z
		//g_player.moveRot.y += FindAngle(
		//	D3DXVECTOR3(posV.x, posV.z, 0.0f),
		//	D3DXVECTOR3(posR.x, posR.z, 0.0f));

		//// ����/�ړ�����/�ڕW�����𐧌�
		//RotControl(&g_player.rot);
		//RotControl(&g_player.moveRot);
		//RotControl(&g_player.targetRot);

		//// �p�x��ڕW�p�x�Ɍ����Đ��ڂ���
		//g_player.rot.y += AngleDifference(g_player.rot.y, g_player.targetRot.y) * CHR_PLAYER_00_ROT_DIAMETER;

		//// �ړ��ʂ��X�V
		//g_player.move.x += sinf(g_player.moveRot.y) * fMove;
		//g_player.move.z += cosf(g_player.moveRot.y) * fMove;

		g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
		g_player.move.z += (0.0f - g_player.move.z) * 0.5f;

		//�ʒu���X�V
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;
		g_player.pos.z += g_player.move.z;

		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 25.0f, g_player.pos.z), g_player.rot);
			PlaySound(SOUND_LABEL_SHOT); //�e�̔��ˉ�
		}
	}
	else if (g_player.bAction == false)
	{

	}

	//�ǂƂ̓����蔻��i�|���S���j
	CollisionWallPlayer(&g_player.pos, &g_player.posOld, &g_player.move);

	//�ǂƂ̓����蔻��i���b�V���j
	//CollisionMeshField_Wall(&g_player.pos, &g_player.posOld, &g_player.move);

	//�u���Ƃ̓����蔻��
	CollisionFigurePlayer(&g_player.pos,&g_player.posOld,&g_player.move);
	
	//�G�Ƃ̓����蔻��
	CollisionEnemy_Player(&g_player.pos, &g_player.posOld, &g_player.move);

	//�Β��Ƃ̓����蔻��
	CollisioPillar_Model(&g_player.pos, &g_player.posOld, &g_player.move);

	//��΂Ƃ̓����蔻��
	CollisionJewel(&g_player.pos, &g_player.posOld, &g_player.move);

	//�v���C���[�̉e�`��
	SetPositionShadow(g_player.nIdxShadow, g_player.pos,g_player.fWidht,g_player.fWidht);
}
//****************************************
// ���f���̕`�揈��
//****************************************
void DrawPlayerModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̏���
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	
	//D3DXMATRIX mtxShadow;						//�V���h�E�}�g���b�N�X
	//D3DLIGHT9 light;							//���C�g���
	//D3DXVECTOR4 posLight;						//���C�g�̈ʒu
	//D3DXVECTOR3 pos, normal;					//���ʏ�̔C�ӂ̓_�A�@���x�N�g��
	//D3DXPLANE plane;							//���ʏ��

	////���C�g�̈ʒu�����
	//pDevice->GetLight(0, &light);
	//posLight = D3DXVECTOR4(0, 100, 100, 0.0f);

	////���ʏ��𐶐�
	//pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y, g_player.pos.z);
	//normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//D3DXPlaneFromPointNormal(&plane, &pos, &normal);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	////�V���h�E�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&mtxShadow);

	////�V���h�E�}�g���b�N�X�̍쐬
	//D3DXMatrixShadow(&mtxShadow, &posLight, &plane);
	//D3DXMatrixMultiply(&mtxShadow, &g_player.mtxWorld, &mtxShadow);

	////�V���h�E�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y,
		g_player.rot.x, g_player.rot.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^������
	pMat = (D3DXMATERIAL*)g_pBuffMatHammerModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumHammerMatModel; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
		pMat[nCntMat].MatD3D.Diffuse.b = 1.0f;
		pMat[nCntMat].MatD3D.Diffuse.g = 1.0f;
		pMat[nCntMat].MatD3D.Diffuse.r = 1.0f;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureHammerModel[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshHammerModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//****************************************
// �v���C���[�̏��
//****************************************
Player *GetPlayer(void)
{
	return &g_player;
}