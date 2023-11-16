//========================================
// 
// �����ݒ�
// 
//========================================
// *** words.h ***
//========================================
#ifndef _WORDS_H_
#define _WORDS_H_

#include "../../main.h"
#include "../../object/object.h"
#include "font.h"

//****************************************
// �N���X
//****************************************
class CWords : public CObject
{
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���_�t�H�[�}�b�g�y2D�z

																					// �e���_�̉����l
	const D3DXVECTOR3 CWords::m_Vtx[4] =
	{
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	};

public:

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
	CWords(int nPriority = PRIO_TEXT);
	~CWords() override;

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	//--------------------------------------------------
	// ��������
	// ����1  : const char *Text    / ����
	// ����2  : D3DXVECTOR3 pos     / �ʒu
	// ����3  : D3DXVECTOR2 size    / �T�C�Y
	// ����4  : CFont::FONT Type�@�@/ �t�H���g���
	// ����5  : D3DXCOLOR col		/ �����̐F
	//--------------------------------------------------
	static CWords *CWords::Create(const char *Text, D3DXVECTOR3 pos, D3DXVECTOR3 Size, CFont::FONT Type, D3DXCOLOR col);

	// -- �ݒ� ------------------------------------------
	/* �ʒu		*/virtual void SetPos(const D3DXVECTOR3 &pos);
	/* �ړ���	*/virtual void SetMove(const D3DXVECTOR3 &move);
	/* �����F	*/void SetColar(D3DXCOLOR Collar);
	/* �T�C�Y	*/void SetSize(D3DXVECTOR3 Size) { m_Info.size = Size; };
	/* ����		*/void SetRot(D3DXVECTOR3 Rot) { m_Info.rot = Rot; };
	/* �ړ���	*/void SetMoveRot(D3DXVECTOR3 inMoveRot) { m_Info.moveRot = inMoveRot; };

	// -- �擾 ------------------------------------------
	/* �ʒu			*/virtual D3DXVECTOR3 GetPos() { return m_Info.pos; }
	/* �����F		*/D3DXCOLOR GetColar() { return m_Info.col; };
	/* �T�C�Y		*/D3DXVECTOR3 GetSize() { return m_Info.size; };
	/* �ړ���		*/D3DXVECTOR3 &GetMove() { return m_Info.move; };
	/* ���_�o�b�t�@	*/LPDIRECT3DVERTEXBUFFER9 &GetVtx() { return m_pVtxBuff; };

private:
	// ***** �\���� *****

	// �������
	struct Info
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXVECTOR3 size;
		D3DXVECTOR3 move;
		D3DXVECTOR3 moveRot;
		D3DXCOLOR col;

		bool bDisp;			// �\���t���O
	};

	// ***** �֐� *****
	/* �����̐ݒ�	*/void SetWords(const char*Text, CFont::FONT Type);


	/* �ϐ�	*/
	Info m_Info;
	LPDIRECT3DTEXTURE9 m_pTex;					// �e�N�X�`�����
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	// ���_�o�b�t�@
};

#endif