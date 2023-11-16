//========================================
// 
// �I�u�W�F�N�g�y X�t�@�C�� �z����
// 
//========================================
// *** objectX.h ***
//========================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "../main.h"
#include "object.h"

//****************************************
// �O���錾
//****************************************
class CModel;

//****************************************
// �N���X
//****************************************
class CObjectX : public CObject
{
public:

	// ***** ��` *****
	const DWORD  FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���_�t�H�[�}�b�g�y3D�z

	// ***** �֐� *****
	CObjectX(int nPriority = PRIO_OBJECT);
	virtual~CObjectX();

	/* ���C�� */
	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	static CObjectX *Create(void);	// ����

	/* �ݒ� */
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = m_posOld = pos; }	// �ʒu
	virtual void SetPosOld(D3DXVECTOR3 posOld) { m_posOld = posOld; }	// �ʒu(�ߋ�)
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = m_rotOld = rot; }	// ����
	virtual void SetRotOld(D3DXVECTOR3 rotOld) { m_rotOld = rotOld; }	// ����(�ߋ�)
	virtual void SetSize(const D3DXVECTOR3 &size) { m_size = size; }	// �����蔻��
	virtual void SetScale(D3DXVECTOR3 scale) { m_scale = scale; };		// �X�P�[��
	virtual void SetModel(int  nModelID) { m_nModelID = nModelID; }		// ���f��ID
	virtual void SetColor(D3DXCOLOR color) { m_color = color; }			// �F

	D3DXVECTOR3 GetPos() { return m_pos; }								// �ʒu
	D3DXVECTOR3 GetPosOld() { return m_posOld; }						// �ʒu(�ߋ�)
	D3DXVECTOR3 GetRot() { return m_rot; }								// ����
	D3DXVECTOR3 GetRotOld() { return m_rotOld; }						// ����(�ߋ�)
	D3DXVECTOR3 GetScale() { return m_scale; }							// �X�P�[��
	D3DXVECTOR3 GetSize() { return m_size; }							// �����蔻��
	D3DXCOLOR GetColor() { return m_color; }							// �F

	float GetWidth(void) { return m_Width; }	// ��
	float GetHeight(void) { return m_Height; }	// ����
	float GetDepth(void) { return m_Depth; }	// ���s��

private:
	// ***** �ϐ� *****
	D3DXMATRIX  m_mtxWorld;	//���[���h�}�g���b�N�X

	CModel		*m_pModel;	// ���f��
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posOld;	// �ʒu(�ߋ�)
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_rotOld;	// ����(�ߋ�)
	D3DXVECTOR3	m_size;		// �����蔻��
	D3DXVECTOR3	m_scale;	// �X�P�[��
	D3DXCOLOR m_color;		// �F
	bool m_bColor;			// �F�ύX�t���O
	int m_nModelID;			// ���f��ID
	float m_Width;
	float m_Height;
	float m_Depth;
	char m_aModelPath[TXT_MAX];

};
#endif