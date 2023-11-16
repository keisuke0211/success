//========================================
// 
// �I�u�W�F�N�g�y 2D �z����
// 
//========================================
// *** object2D.h ***
//========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "../main.h"
#include "object.h"

//****************************************
// �N���X
//****************************************
class CObject2D : public CObject
{
public:

	/* ��` */

	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���_�t�H�[�}�b�g�y2D�z

	// ***** �\���� *****

	//���_���y 2D �z
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;	//���_���W
		float rhw;			//���W�ϊ��W���i1.0f�ŌŒ�j
		D3DCOLOR col;		//���_�J���[
		D3DXVECTOR2 tex;	//�e�N�X�`�����W
	};

	// ***** �֐� *****
	CObject2D(int nPriority = PRIO_OBJECT);
	virtual~CObject2D();

	/* ���C�� */
	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	static CObject2D *Create(void);	// ����

	/* �ݒ� */
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = m_posOld = pos; }		// �ʒu
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					// ����
	virtual void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; };		// �T�C�Y
	virtual void SetColar(D3DXCOLOR color);				// �F
	void SetPtn(int nPtn) { m_nPtn = nPtn; }			// �p�^�[��
	void BindTexture(int nIdx);							// �e�N�X�`���w��
	virtual void SetTex(PositionVec4 tex);				// �e�N�X�`�����W
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	/* �擾 */
	float GetWidth(void) { return m_fWidth; }		// ��
	float GetHeight(void) { return m_fHeight; }		// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }// �ʒu(�ߋ�)
	int GetPtn(void) { return m_nPtn; }				// �p�^�[�� 
	int GetPtnWidth(void) { return m_nPtnWidth; }	// �p�^�[����
	int GetPtnHeight(void) { return m_nPtnHeight; }	// �p�^�[������

	// �p�^�[���̏��ݒ�
	void SetPtnInfo(int nPtnWidth = 1, int nPtnHeight = 1, int nPtnMax = 1, bool bPtnAnim = false, int nAnimTime = 0);

protected:
	// ***** �֐� *****
	void SetVtxPos(VERTEX_2D *pVtx);			// ���_���W�̐ݒ�
	virtual void SetTexPos(VERTEX_2D *pVtx);	// �e�N�X�`�����W�̐ݒ�
	void Animation(void);						// �A�j���[�V����

	/* �擾 */
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }	// ���_�o�b�t�@

private:
	// ***** �ϐ� *****
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_posOld;				// �ʒu(�ߋ�)
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_color;					// �F
	float m_fWidth;						// ��
	float m_fHeight;					// ����
	int m_nPtn;							// �p�^�[��
	int m_nPtnWidth;					// �p�^�[����
	int m_nPtnHeight;					// �p�^�[������
	int m_nPtnMax;						// �p�^�[���̍ő�
	bool m_bPtnAnim;					// �p�^�[���A�j���t���O
	int m_nAnimCounter;					// �A�j���J�E���^�[
	int m_nAnimTime;					// �A�j���ɂ����鎞��
};
#endif