//========================================
// 
// �I�u�W�F�N�g�y 3D �z����
// 
//========================================
// *** object3D.cpp ***
//========================================
#include "../manager.h"
#include "object3D.h"
#include "../system/renderer.h"
#include "../system/texture.h"

//========================================
// �R���X�g���N�^
//========================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	// �l���N���A����
	m_pos = INIT_D3DXVECTOR3;		// �ʒu
	m_posOld = INIT_D3DXVECTOR3;	// �ʒu(�ߋ�)
	m_rot = INIT_D3DXVECTOR3;		// ����
	m_color = INIT_D3DXCOLOR;		// �F
	m_fHeight = INIT_FLOAT;			// ����
	m_fWidth = INIT_FLOAT;			// ��
	m_nPtn = 0;						// �p�^�[��
	m_nPtnWidth = 0;				// �p�^�[����
	m_nPtnHeight = 0;				// �p�^�[������
	m_nPtnMax = 0;					// �p�^�[���̍ő�
	m_bPtnAnim = false;				// �p�^�[���A�j���t���O
	m_nAnimCounter = 0;				// �A�j���J�E���^�[
	m_nAnimTime = 0;				// �A�j���ɂ����鎞��
}

//========================================
// �f�X�g���N�^
//========================================
CObject3D::~CObject3D()
{

}

//========================================
// ��������
//========================================
CObject3D *CObject3D::Create(void)
{
	CObject3D *pObj3D = NULL;

	if (pObj3D != NULL)
	{
		return pObj3D;
	}

	// �I�u�W�F�N�g3D�̐���
	pObj3D = new CObject3D;

	// ����������
	pObj3D->Init();

	return pObj3D;
}

//========================================
// ����������
//========================================
HRESULT CObject3D::Init(void)
{
	m_nPtn = 0;					// �p�^�[��
	m_nPtnWidth = 1;			// �p�^�[����
	m_nPtnHeight = 1;			// �p�^�[������
	m_nPtnMax = 1;				// �p�^�[���̍ő�
	m_bPtnAnim = false;			// �p�^�[���A�j���t���O
	m_nAnimCounter = 0;			// �A�j���J�E���^�[
	m_nAnimTime = 0;			// �A�j���ɂ����鎞��

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// ���_���W�̐ݒ�
	SetVtxPos(pVtx);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�̔j��
	m_pVtxBuff->Unlock();

	return S_OK;
}

//========================================
// �I������
//========================================
void CObject3D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//========================================
// �X�V����
//========================================
void CObject3D::Update(void)
{
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	SetTexPos(pVtx);

	// ���_���W�̐ݒ�
	SetVtxPos(pVtx);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//========================================
// �`�揈��
//========================================
void CObject3D::Draw(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;										//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================================
// ���_���W�̐ݒ菈��
//========================================
void CObject3D::SetVtxPos(VERTEX_3D *pVtx)
{
	// �Ίp���̒���
	float fLength = sqrtf((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight)) * 0.5f;
	// �Ίp���̊p�x
	float fAngle = atan2f(m_fWidth, m_fHeight);

	// ���_���W��ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.y - (D3DX_PI - fAngle)) * fLength;
	pVtx[0].pos.y = m_pos.y;
	pVtx[0].pos.z = m_pos.z + cosf(m_rot.y - (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.y + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = m_pos.y;
	pVtx[1].pos.z = m_pos.z + cosf(m_rot.y - (D3DX_PI - fAngle)) * fLength;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.y - fAngle) * fLength;
	pVtx[2].pos.y = m_pos.y ;
	pVtx[2].pos.z = m_pos.z + cosf(m_rot.y - fAngle) * fLength;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.y + fAngle) * fLength;
	pVtx[3].pos.y = m_pos.y;
	pVtx[3].pos.z = m_pos.z + cosf(m_rot.y - fAngle) * fLength;
}

//========================================
// �F�ݒ�
//========================================
void CObject3D::SetColor(const D3DXCOLOR& color)
{
	// �T�C�Y�̑��
	m_color = color;

	// �ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[1].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[2].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[3].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);

	// ���_�o�b�t�@�̔j��
	m_pVtxBuff->Unlock();
}

//========================================
// �p�^�[�����ݒ�
//========================================
void CObject3D::SetPtnInfo(int nPtnWidth, int nPtnHeight, int nPtnMax, bool bPtnAnim, int nAnimTime)
{
	m_nPtnWidth = nPtnWidth;	// �p�^�[����
	m_nPtnHeight = nPtnHeight;	// �p�^�[������
	m_nPtnMax = nPtnMax;		// �p�^�[���̍ő�
	m_bPtnAnim = bPtnAnim;	 	// �p�^�[���A�j���t���O
	m_nAnimCounter = 0;			// �A�j���J�E���^�[(������)
	m_nAnimTime = nAnimTime;	// �A�j���ɂ����鎞��
}

//========================================
// �A�j���[�V��������
//========================================
void CObject3D::Animation(void)
{
	// �p�^�[���A�j���t���O���^�̎��A
	if (m_bPtnAnim)
	{
		if (++m_nAnimCounter % m_nAnimTime == 0)
		{// �A�j���J�E���^�[�����Z���Ă����鎞�ԂŊ���؂ꂽ��A
			m_nAnimCounter = 0;
			m_nPtn = (m_nPtn + 1) % m_nPtnMax;	// �p�^�[�������Z���A�ő�ŏ�]�Z
		}
	}
}

//========================================
// �e�N�X�`�����W�̐ݒ菈��
//========================================
void CObject3D::SetTexPos(VERTEX_3D *pVtx)
{
	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((m_nPtn % m_nPtnWidth) * (1.0f / m_nPtnWidth), ((m_nPtn / m_nPtnWidth) % m_nPtnHeight) * (1.0f / m_nPtnHeight));
	pVtx[1].tex = D3DXVECTOR2((m_nPtn % m_nPtnWidth) * (1.0f / m_nPtnWidth) + (1.0f / m_nPtnWidth), ((m_nPtn / m_nPtnWidth) % m_nPtnHeight) * (1.0f / m_nPtnHeight));
	pVtx[2].tex = D3DXVECTOR2((m_nPtn % m_nPtnWidth) * (1.0f / m_nPtnWidth), (((m_nPtn / m_nPtnWidth) % m_nPtnHeight) * (1.0f / m_nPtnHeight)) + (1.0f / m_nPtnHeight));
	pVtx[3].tex = D3DXVECTOR2((m_nPtn % m_nPtnWidth) * (1.0f / m_nPtnWidth) + (1.0f / m_nPtnWidth), (((m_nPtn / m_nPtnWidth) % m_nPtnHeight) * (1.0f / m_nPtnHeight)) + (1.0f / m_nPtnHeight));
}

//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CObject3D::BindTexture(int nIdx)
{
	CTexture *pTexture = CManager::GetTexture();

	m_pTexture = pTexture->GetAddress(nIdx);
}

//========================================
// �e�N�X�`���ݒ�
//========================================
void CObject3D::SetTex(PositionVec4 tex)
{
	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

	 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(tex.P0, tex.P2);
	pVtx[1].tex = D3DXVECTOR2(tex.P1, tex.P2);
	pVtx[2].tex = D3DXVECTOR2(tex.P0, tex.P3);
	pVtx[3].tex = D3DXVECTOR2(tex.P1, tex.P3);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}