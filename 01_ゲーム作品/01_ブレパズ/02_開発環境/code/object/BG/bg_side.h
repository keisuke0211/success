//========================================
// 
// �w�i(����)�y 3D_MULTI �z����
// 
//========================================
// *** bg_side.h ***
//========================================
#ifndef _BG_SIDE_H_
#define _BG_SIDE_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// �N���X
//****************************************
class CBgSide : public CObject
{
public:
	// ***** �\���� *****

	// ���_���[3D_MULTI]�̍\���̂��`
	struct VERTEX_3D_MULTI
	{
		D3DXVECTOR3 pos;	// ���_���W
		D3DXVECTOR3 nor;	// �@���x�N�g��
		D3DCOLOR	col;	// ���_�J���[
		D3DXVECTOR2 tex1;	// �e�N�X�`�����W1
		D3DXVECTOR2 texM;	// �e�N�X�`�����W2
		D3DXVECTOR2 texM2;	// �e�N�X�`�����W3
	};

	// ***** �֐� *****
	CBgSide(int nPriority = PRIO_OBJECT);
	~CBgSide();

	/* ���C�� */
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CBgSide *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR color, float fHeight, float fRadius, int *nType, int nNumTex, int nDivisionX, int nDivisionY, float *fTexV);

	/* �ݒ� */
	/* �ʒu			*/void SetPos(D3DXVECTOR3 pos) { m_Info.pos = pos; }	
	/* ����			*/void SetRot(D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* �F			*/void SetColor(const D3DXCOLOR& color) { m_Info.color = color; }

private:
	// ***** �\���� *****
	struct Multi
	{
		int	nType;			// �摜���
		float fTexV;		// �e�N�X�`�����W�̊J�n�ʒu(X��)
		float fTexVSpeed;	// �e�N�X�`�����W�̈ړ����x(X��)
	};

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXCOLOR	color;	// �F
		float fHeight;		// ����
		float fRadius;		// ���a
		int nNumTex;		// �摜��
		int nDivisionX;		// ������
		int nDivisionY;		// ��������
		Multi *pMulti;		// �}���`���
	};

	// ***** �ϐ� *****
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield1;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield2;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield3;		// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxWorld;							// ���[���h�}�g���b�N�X

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�����i�[
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuf;	//�C���f�b�N�X�����i�[

	Info m_Info;	// ���ʏ��
};
#endif