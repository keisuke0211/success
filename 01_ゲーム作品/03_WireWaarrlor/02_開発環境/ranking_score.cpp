//��======================��
//�b�@�@�@�@�@�@�@  �@�@�@�b
//�b�@�����L���O�̏���    �b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include "ranking_score.h"
#include "time.h"
//�}�N����`
#define NUM_PLASE		(3)	//�����L���O����
#define NUM_RANKING		(6)	//�����L���O�̐�
#define NUM_RANKING1	(5)	//�����L���O�̐�
#define MAX_RANKING		(5)	//�����L���O�������ʂT
LPDIRECT3DTEXTURE9 g_pTextureRanking[NUM_RANKING] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;
Ranking g_aRanking[NUM_RANKING];
int g_nRanking;
int g_aData[NUM_RANKING];

//===================================================
//�����L���O�̏���������
//===================================================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	int nCntRanking;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,"data/texture/number001.png",&g_pTextureRanking[0]);
	D3DXCreateTextureFromFile(pDevice,"data/texture/number002.png",&g_pTextureRanking[1]);
	D3DXCreateTextureFromFile(pDevice,"data/texture/number003.png",&g_pTextureRanking[2]);
	D3DXCreateTextureFromFile(pDevice,"data/texture/number004.png",&g_pTextureRanking[3]);
	D3DXCreateTextureFromFile(pDevice,"data/texture/number004.png",&g_pTextureRanking[4]);
	D3DXCreateTextureFromFile(pDevice,"data/texture/number005.png",&g_pTextureRanking[5]);


	g_aData[0] = 5000;
	g_aData[1] = 4950;
	g_aData[2] = 4900;
	g_aData[3] = 4800;
	g_aData[4] = 2000;
	g_aData[5] = 10;

	for (nCntRanking = 0; nCntRanking < NUM_PLASE; nCntRanking++)
	{
		g_aRanking[nCntRanking].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCntRanking].bUse = false;
		g_nRanking = 0;

	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLASE * NUM_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRanking = 0; nCntRanking < NUM_PLASE * NUM_RANKING; nCntRanking++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f	+ nCntRanking * 34.0f, 180.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(30.0f + nCntRanking * 34.0f, 180.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f	+ nCntRanking * 34.0f, 240.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(30.0f + nCntRanking * 34.0f, 240.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();
}
//================================================
//�����L���O�I������
//=================================================
void UninitRankingScore(void)
{
	int nRanking;

	for (nRanking = 0; nRanking < NUM_RANKING; nRanking++)
	{
		if (g_pTextureRanking[nRanking] != NULL)
		{
			g_pTextureRanking[nRanking]->Release();
			g_pTextureRanking[nRanking] = NULL;
		}
	}
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}
//=========================================================
//�����L���O�X�V����
//=========================================================
void UpdateRankingScore(void)
{
	int g_nRankUpdate = -1;
	int Score;
	int nCount1;
	int nCount2;
	int nMax;
	bool bRankUpdate = false;
	Score = GetInitTime() - GetTime();

	FILE *pFile;	//�t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen("data\\ranking.bin", "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�t�@�C������f�[�^������������
		fread(&g_aData[0], sizeof(int), 5, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		g_aData[0] = 150;
		g_aData[1] = 180;
		g_aData[2] = 200;
		g_aData[3] = 220;
		g_aData[4] = 230;
		g_aData[5] = 250;
	}

	if (Score < g_aData[NUM_RANKING - 1])
	{//�ł��������l���}������l���傫��������

	 //�ł��������l�ɑ}������l��������
		g_aData[NUM_RANKING - 1] = Score;

		g_nRankUpdate = NUM_RANKING - 1;
	}

	//�\�[�g�̏���
	for (nCount1 = 0; nCount1 < NUM_RANKING - 1; nCount1++)
	{
		//���ёւ�������
		for (nCount2 = nCount1 + 1; nCount2 < NUM_RANKING; nCount2++)
		{
			if (g_aData[nCount1] > g_aData[nCount2])
			{//��r���Ă鐔��

			 //���݂̔�r���Ă��鐔��ۑ�
				nMax = g_aData[nCount1];

				//�ő�l�ɒu��������
				g_aData[nCount1] = g_aData[nCount2];

				//�ύX�������l�����ɖ߂�
				g_aData[nCount2] = nMax;
			}
		}
	}

	// �t�@�C�����J��
	pFile = fopen("data\\ranking.bin", "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�t�@�C������f�[�^������������
		fwrite(&g_aData[0], sizeof(int), 5, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	
	SetRanking(D3DXVECTOR3(490.0f, 180.0f, 0.0f), g_aData[0]);
	SetRanking(D3DXVECTOR3(490.0f, 265.0f, 0.0f), g_aData[1]);
	SetRanking(D3DXVECTOR3(490.0f, 350.0f, 0.0f), g_aData[2]);
	SetRanking(D3DXVECTOR3(490.0f, 435.0f, 0.0f), g_aData[3]);
	SetRanking(D3DXVECTOR3(490.0f, 515.0f, 0.0f), g_aData[4]);
	SetRanking(D3DXVECTOR3(490.0f, 615.0f, 0.0f), Score);
}
//======================================================
//�����L���O�`�揈��
//======================================================
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRanking;
	int nCnt;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < NUM_RANKING; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureRanking[nCnt]);

		for (nCntRanking = 0; nCntRanking < NUM_PLASE * NUM_RANKING; nCntRanking++)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCnt * NUM_PLASE + nCntRanking )*4, 2);
		}
	}
}
//==================================================
//�����L���O�Z�b�g����
//==================================================
void SetRanking(D3DXVECTOR3 pos, int nRanking)
{
	int aTexU[NUM_PLASE];
	int nCntRanking;
	int nCntNumber;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		if (g_aRanking[nCntRanking].bUse == false)
		{
			g_nRanking = nRanking;

			aTexU[0] = g_nRanking % 1000 / 100;
			aTexU[1] = g_nRanking % 100 / 10;
			aTexU[2] = g_nRanking % 10 / 1;

			for (nCntNumber = 0; nCntNumber < NUM_PLASE; nCntNumber++, pVtx += 4)
			{
				g_aRanking[nCntNumber].pos = pos;

				pVtx[0].pos = D3DXVECTOR3(g_aRanking[nCntNumber].pos.x - 24.0f + (nCntNumber * 85.0f), g_aRanking[nCntNumber].pos.y - 35.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aRanking[nCntNumber].pos.x + 24.0f + (nCntNumber * 85.0f), g_aRanking[nCntNumber].pos.y - 35.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aRanking[nCntNumber].pos.x - 24.0f + (nCntNumber * 85.0f), g_aRanking[nCntNumber].pos.y + 35.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aRanking[nCntNumber].pos.x + 24.0f + (nCntNumber * 85.0f), g_aRanking[nCntNumber].pos.y + 35.0f, 0.0f);

				pVtx[0].tex = D3DXVECTOR2(0.01f + (aTexU[nCntNumber] * 0.1f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntNumber] * 0.1f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.01f + (aTexU[nCntNumber] * 0.1f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntNumber] * 0.1f), 1.0f);
			}

			g_aRanking[nCntRanking].bUse = true;

			break;
		}
		else
		{
			pVtx += 4 * NUM_PLASE;
		}
	}

	//���_�o�b�t�@�����b�N
	g_pVtxBuffRanking->Unlock();
}
