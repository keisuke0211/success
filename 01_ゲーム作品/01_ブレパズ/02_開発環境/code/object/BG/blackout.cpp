//========================================
// 
// �Ó]
// 
//========================================
// *** blackout.cpp ***
//========================================
#include "blackout.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"

//========================================
// �R���X�g���N�^
//========================================
CBlackout::CBlackout(int nPriority) : CObject2D(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR2;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CBlackout::~CBlackout()
{

}

//========================================
// ����
//========================================
CBlackout *CBlackout::Create(void)
{
	CBlackout *pObj = new CBlackout;

	pObj->m_Info.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	pObj->m_Info.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	pObj->Init();

	return pObj;
}

//========================================
// ������
//========================================
HRESULT CBlackout::Init(void)
{
	CObject2D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BG);

	// �ݒ�
	SetPos(m_Info.pos);
	SetSize(m_Info.size.x, m_Info.size.y);
	SetColar(D3DXCOLOR(0,0,0,0.7f));

	BindTexture(-1);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBlackout::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CBlackout::Update(void)
{
	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CBlackout::Draw(void)
{
	CObject2D::Draw();
}