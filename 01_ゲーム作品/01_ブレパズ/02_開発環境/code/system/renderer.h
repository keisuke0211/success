//========================================
// 
// �`�揈��
// 
//========================================
// *** renderer.h ***
//========================================
#include "../main.h"

#ifndef _RENDERER_H_
#define _RENDERER_H_

//****************************************
// �N���X
//****************************************
class CRenderer
{
public:

	/* ��` */
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���_�t�H�[�}�b�g�y2D�z

	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;	//���_���W
		float rhw;			//���W�ϊ��W���i1.0f�ŌŒ�j
		D3DCOLOR col;		//���_�J���[
		D3DXVECTOR2 tex;	//�e�N�X�`�����W
	};

	// ***** �֐� *****

	CRenderer();
	~CRenderer();

	/* �����_���[ */
	HRESULT Init(HWND hWnd, BOOL bWindow);	// ������
	void Uninit(void);						// �I��
	void Update(void);						// �X�V
	void Draw(void);						// �`��

	/* �擾 */
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X

	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void);

private:

	// ***** �֐� *****
	void DrawFPS(void);		// FPS�\��

	// ***** �ϐ� *****
	D3DPRESENT_PARAMETERS m_d3dpp = {};	// �v���[���e�[�V�����p�����[�^
	LPDIRECT3D9 m_pD3D;					// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3D�f�o�C�X�ւ̃|�C���^

	static LPD3DXFONT m_pFont;			// �t�H���g�ւ̃|�C���^
};
#endif