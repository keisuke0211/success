//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@�r���{�[�h�̏���  �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include "billboard.h"
//****************************************
// �O���[�o���ϐ�
//****************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBillboard = NULL;			//���_�o�b�t�@�|�C���^
LPDIRECT3DTEXTURE9		g_pTextureBillboard = NULL;			//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posBillboard;//�ʒu
D3DXMATRIX g_mtxWorldBillboard;//���[���h�}�g���b�N�X

//****************************************
// ����������
//****************************************
void InitBilldoard(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�e�N�X�`���̓ǂݍ��݁@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	D3DXCreateTextureFromFile(pDevice,
		".\\data\\TEXTURE\\Rocks00.png",
		&g_pTextureBillboard);

	g_posBillboard = D3DXVECTOR3(50, 50, 50);
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@  ���_�o�b�t�@  �@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBillboard,
		NULL);

	//�ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	g_pVtxbuffBillboard->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posBillboard.x - 50, g_posBillboard.y+50, g_posBillboard.z);
	pVtx[1].pos = D3DXVECTOR3(g_posBillboard.x + 50, g_posBillboard.y+50, g_posBillboard.z);
	pVtx[2].pos = D3DXVECTOR3(g_posBillboard.x - 50, g_posBillboard.y-50, g_posBillboard.z);
	pVtx[3].pos = D3DXVECTOR3(g_posBillboard.x + 50, g_posBillboard.y-50, g_posBillboard.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̂̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxbuffBillboard->Unlock();
}
//****************************************
// �I������
//****************************************
void UninitBilldoard(void)
{
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@���_�o�b�t�@�̔j���@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\�\��
	if (g_pVtxbuffBillboard != NULL)
	{
		g_pVtxbuffBillboard->Release();
		g_pVtxbuffBillboard = NULL;
	}
}
//****************************************
// �X�V����
//****************************************
void UpdateBilldoard(void)
{

}
//****************************************
// �`�揈��
//****************************************
void DrawBilldoard(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;					//�r���[�}�g���b�N�X�擾�p

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);//Z�e�X�g�̐ݒ�,��r���@
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);//Z�o�b�t�@�X�V�̗L�������ݒ�,�L��������

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);//�A���t�@�e�X�g�̗L�������ݒ�A�L���E�����ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);//�A���t�@�e�X�g�̐ݒ�,��r���@
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);//�A���t�@�e�X�g�̎Q�ƒl�ݒ�i0�`255�j

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);//�t�s������߂�
	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);

	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxbuffBillboard, 0, sizeof(VERTEX_3D));

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b���_�t�H�[�}�b�g�̐ݒ�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�e�N�X�`���̐ݒ�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	pDevice->SetTexture(0, g_pTextureBillboard);

	//���\�\�\�\�\�\�\�\�\�\�\�\��
	//�b�@�@�|���S���̕`��@�@�@�b
	//���\�\�\�\�\�\�\�\�\�\�\�\��

	//���_���\���̂̃T�C�Y
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//Z�e�X�g�̐ݒ�,��r���@
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);//Z�o�b�t�@�X�V�̗L�������ݒ�,�L��������

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//�A���t�@�e�X�g�̗L�������ݒ�A�L���E�����ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_ALWAYS);//�A���t�@�e�X�g�̐ݒ�,��r���@
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);//�A���t�@�e�X�g�̎Q�ƒl�ݒ�i0�`255�j
}