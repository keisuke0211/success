//��======================��
//�b�@�@�@�@�@�@�@  �@�@�@�b
//�b�@�����L���O�̏���    �b
//�b�@Author:��a�c��@   �b
//�b                      �b
//��======================��
#include"ranking_bg.h"
#include"ranking_score.h"
#include"input.h"
#include"fade.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffRankingBG;		//�w�i�̒��_�o�b�t

LPDIRECT3DTEXTURE9 g_apTextureRankingBG;			//�X�R�A�̃e�N�X�`���|�C���^

int g_nTimerRanking;			//�����L���O��ʕ\���^�C�}�[

int g_nCntTime3;				//��莞�Ԍo�߂ŉ�ʐ��ڂ��鏈���Ɏg��

//��============================��
//�b�@ �����L���O�̏����������@ �b
//��============================��
void InitRanking(void)
{
	g_nCntTime3 = 0;//�^�C�}�[��������
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�w�i�̃e�N�X�`���̓ǂݍ���

	D3DXCreateTextureFromFile(pDevice, ".\\data\\TEXTURE\\bg010.png", &g_apTextureRankingBG);

	//���_�o�b�t�@�̐���(�w�i)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffRankingBG,
		NULL);
	

	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffRankingBG->Lock(0, 0, (void **)&pVtx, 0);

		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b �@�@���_���W��ݒ�@�@ �b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		//�b�@�e�N�X�`�����W�̐ݒ�@�b
		//���\�\�\�\�\�\�\�\�\�\�\�\��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@�̃A�����b�N
		g_pVtxbuffRankingBG->Unlock();

		//�X�R�A�̏���������
		InitRankingScore();
		//�X�R�A�̍X�V����
		UpdateRankingScore();
}
//��==========================��
//�b�@ �����L���O�̏I�������@ �b
//��==========================��
void UninitRanking(void)
{

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	
	//�w�i
	if (g_apTextureRankingBG != NULL)
	{
		g_apTextureRankingBG->Release();
		g_apTextureRankingBG = NULL;
	}

	
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��

	//�w�i
	if (g_pVtxbuffRankingBG != NULL)
	{
		g_pVtxbuffRankingBG->Release();
		g_pVtxbuffRankingBG = NULL;
	}

	//�X�R�A�̏I������
	UninitRankingScore();

}
//��==========================��
//�b�@ �����L���O�̍X�V�����@ �b
//��==========================��
void UpdateRanking(void)
{
	XINPUT_STATE *xInput = GetXInputState();	//�v���C���[�̏��ւ̃|�C���^

	//��ʐ��ځi�����L���O �� �^�C�g���j
	if (GetKeyboardTrigger(DIK_RETURN) == true && GetFade() == FADE_NONE)
	{// ����L�[ [ ENTER�L�[ ] �������ꂽ

	 //���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_START && GetFade() == FADE_NONE)
	{
		//���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (xInput->Gamepad.wButtons & XINPUT_GAMEPAD_A&& GetFade() == FADE_NONE)
	{
		//���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (GetFade() == FADE_NONE && g_nCntTime3 == SWITCH_TIME)
	{//���U���g��ʂɗ��Ă���10�b��������^�C�g����ʂɐ؂�ւ��

	 //���[�h�̐ݒ�
		SetFade(MODE_TITLE);
	}
	else if (GetFade() == FADE_NONE)
	{
		g_nCntTime3++;		//�t�F�[�h�� FADE_NONE �̏�ԂɂȂ�����1�t���[�����J�E���g����
	}
}
//��==========================��
//�b�@ �����L���O�̕`�揈���@ �b
//��==========================��
void DraeRanking(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffRankingBG, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->SetTexture(0, g_apTextureRankingBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�X�R�A�̕`�揈��
	DrawRankingScore();
}