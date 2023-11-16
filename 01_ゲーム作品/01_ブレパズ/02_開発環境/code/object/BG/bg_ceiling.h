//========================================
// 
// �w�i(�V��)�y 3D �z����
// 
//========================================
// *** bg_ceiling.h ***
//========================================
#ifndef _BG_CEILING_H_
#define _BG_CEILING_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// �N���X
//****************************************
class CBgCeiling : public CObject
{
public:
	// ***** �\���� *****

	//���_���y 3D �z
	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;	// ���_���W
		D3DXVECTOR3 nor;	// �@���x�N�g��
		D3DCOLOR col;		// ���_�J���[
		D3DXVECTOR2 tex;	// �e�N�X�`�����W
	};

	// ***** �֐� *****
	CBgCeiling(int nPriority = PRIO_OBJECT);
	~CBgCeiling();

	/* ���C�� */
	HRESULT Init(void);						// ������
	void Uninit(void);						// �I��
	void Update(void);						// �X�V
	void Draw(void);						// �`��
	static CBgCeiling *Create(int nType);	// ����

	/* �ݒ� */
	/* �ʒu			*/void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	/* ����			*/void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	/* �F			*/void SetColor(const D3DXCOLOR& color) { m_color = color; }

private:
	// ***** �ϐ� *****
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�����i�[
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuf;		// �C���f�b�N�X�����i�[
	LPDIRECT3DINDEXBUFFER9 m_pIdxBufLid;	// �V��̃C���f�b�N�X�����i�[

	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_color;					// �F
	int m_nStage;						// �X�e�[�W
};
#endif