//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�t�F�[�h����	    �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "fade.h"

//��==================��
//�b�@�O���[�o���ϐ��@�b
//��==================��
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffFade = NULL;			//���_�o�b�t�@�|�C���^
FADE g_fade;											//�t�F�[�h�̏��
MODE g_modeNext;										//���̉��(���[�h)
D3DXCOLOR g_colorFade;									//�|���S��(�t�F�[�h)�̐F

//==============================================================================================================================================
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�b�y�t�F�[�h�E�����z�b�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//==============================================================================================================================================

//��======================================��
//�b�@�@�@ �t�F�[�h�����̏����������@�@ �@�b
//��======================================��
void lnitFade(MODE modeNext)
{

	g_fade = FADE_IN;									//�t�F�[�h�C����Ԃ�
	g_modeNext = modeNext;								//���̉��(���[�h)��ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�����|���S��(�s����)�ɂ��Ă���

	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();								//�f�o�C�X�̏���

	//���_�o�b�t�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffFade,
		NULL);
	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFade->Lock(0, 0, (void **)&pVtx, 0);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b �@�@���_���W��ݒ�@�@ �b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�@�@�@�@�@�@�@�@�@�@�@�@ x       y     z
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f); //�E���Őݒ肷��
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f); //�����Őݒ肷��

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

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffFade->Unlock();

	//���[�h�̐ݒ�
	SetMode(g_modeNext);

}
//��====================================��
//�b�@�@�@ �t�F�[�h�����̏I�������@�@ �@�b
//��====================================��
void UninitFade(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffFade != NULL)
	{
		g_pVtxbuffFade->Release();
		g_pVtxbuffFade = NULL;
	}
}
//��====================================��
//�b�@�@�@ �t�F�[�h�����̍X�V�����@�@ �@�b
//��====================================��
void UpdateFade(void)
{
	//�ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffFade->Lock(0, 0, (void **)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{

		if (g_fade == FADE_IN)
		{
			//�t�F�[�h�C�����
			g_colorFade.a -= 0.05f;//�|���S���𓧖��ɂ��Ă���

			if (g_colorFade.a <= 0.0f)
			{

				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;//�������Ă��Ȃ���Ԃɂ���
			}
		}

		else if (g_fade == FADE_OUT)
		{
			//�t�F�[�h�A�E�g
			g_colorFade.a += 0.025f; //�|���S����s�����ɂ��Ă���

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;//�t�F�[�h�C�����

				//���[�h�ݒ�
				SetMode(g_modeNext);
			}

		}
	}
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�@ ���_�J���[ �@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffFade->Unlock();
}
//��====================================��
//�b�@�@�@ �t�F�[�h�����̕`�揈���@�@ �@�b
//��====================================��
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�f�[�^�X�g���[���̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffFade, 0, sizeof(VERTEX_2D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
		pDevice->SetTexture(0, NULL);						//�e�N�X�`�����g�p���Ȃ��̂� NULL ���w��I

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�|���S���̕`��@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);
}
//��====================================��
//�b�@�@�@ �t�F�[�h�����̐ݒ菈���@�@ �@�b
//��====================================��
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;									//�t�F�[�h�A�E�g��Ԃɂ���
	g_modeNext = modeNext;								//���̉��(���[�h)��ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S����(����)�ɂ��Ă���

}
//��====================================��
//�b�@�@�@ �t�F�[�h�����̏��������@�@ �@�b
//��====================================��
FADE GetFade(void)
{
		return g_fade;
}
