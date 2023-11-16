//========================================
// 
// ���b�V���t�B�[���h
// 
//========================================
// *** mesh_floor.h ***
//========================================
#ifndef _MESH_FLOOR_H_
#define _MESH_FLOOR_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// �N���X
//****************************************
class CFloor : public CObject
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
	CFloor(int nPriority = PRIO_OBJECT);
	~CFloor();

	/* ���C�� */
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CFloor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR color, float fWidth,float fHeight, int *nType, int nNumTex,bool bDivision, int nDivisionX, int nDivisionY, float *fTexX, float *fTexY);

	/* �ݒ� */
	/* �ʒu			*/void SetPos(D3DXVECTOR3 pos) { m_Info.pos = pos; }
	/* ����			*/void SetRot(D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* �F			*/void SetColor(const D3DXCOLOR& color) { m_Info.color = color; }

private:
	// ***** �\���� *****
	struct Multi
	{
		int	nType;			// �摜���
		float fTexX;		// �e�N�X�`�����W�̊J�n�ʒu(X��)
		float fTexY;		// �e�N�X�`�����W�̊J�n�ʒu(Y��)
		float fTexXSpeed;	// �e�N�X�`�����W�̈ړ����x(X��)
		float fTexYSpeed;	// �e�N�X�`�����W�̈ړ����x(Y��)
	};

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXCOLOR	color;	// �F
		float fWidth;		// ��
		float fHeight;		// ����
		int nNumTex;		// �摜��
		int nDivisionX;		// ������
		int nDivisionY;		// ��������
		int nNumDivisionX;	// ������X
		int nNumDivisionY;	// ������Y
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