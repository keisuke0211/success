//========================================
// 
// �^�C�g���w�i
// 
//========================================
// *** UI_title.h ***
//========================================
#include "UI_title.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"

//========================================
// �R���X�g���N�^
//========================================
CUiTitle::CUiTitle(int nPriority) : CObject2D(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CUiTitle::~CUiTitle()
{

}

//========================================
// ����
//========================================
CUiTitle *CUiTitle::Create(void)
{
	CUiTitle *pTitle = new CUiTitle;

	pTitle->m_Info.pos = D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,0.0f);
	pTitle->m_Info.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	pTitle->Init();

	return pTitle;
}

//========================================
// ������
//========================================
HRESULT CUiTitle::Init(void)
{
	CObject2D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BG);

	// �ݒ�
	SetPos(m_Info.pos);
	SetSize(m_Info.size.x, m_Info.size.y);
	SetColar(INIT_D3DXCOLOR);

	BindTexture(CTexture::TEX_TITLE_BG);

	return S_OK;
}

//========================================
// �I��
//========================================
void CUiTitle::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CUiTitle::Update(void)
{
	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CUiTitle::Draw(void)
{
	CObject2D::Draw();
}