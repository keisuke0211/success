//========================================
// 
// �t�F�[�h
// 
//========================================
// *** fade.cpp ***
//========================================
#include "fade.h"
#include "../manager.h"

CFade::FADE CFade::m_fade = FADE_NONE;
CScene::MODE CFade::m_modeNext = CScene::MODE_TITLE;

//========================================
// �R���X�g���N�^
//========================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	m_color = INIT_D3DXCOLOR;
}

//========================================
// �f�X�g���N�^
//========================================
CFade::~CFade()
{

}

//========================================
// ������
//========================================
HRESULT CFade::Init(void)
{
	CObject2D::Init();

	m_fade = FADE_IN;

	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// �����|���S��(�s����)�ɂ���

	BindTexture(-1);
	SetType(TYPE_NONE);
	SetPos(D3DXVECTOR3(640, 360, 0.0f));
	SetSize(1280, 720);
	SetColar(m_color);

	// ���[�h�ݒ�
	CManager::SetMode(m_modeNext);
	return S_OK;
}

//========================================
// �I��
//========================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�@�t�F�[�h�C��
			m_color.a -= (float)FADE_TRANSITION / 1000;

			if (m_color.a <= 0.0f)
			{// �����x��0�ȉ��̎�

				m_color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{// �t�F�[�h�A�E�g
			m_color.a += (float)FADE_TRANSITION / 1000;

			if (m_color.a > 1.0f)
			{// �����x���ő�l�����������A

				m_color.a = 1.0f;
				m_fade = FADE_IN;

				if (m_modeNext != CScene::MODE_MAX)
				{// ���̃��[�h�������łȂ���,

					CManager::SetMode(m_modeNext);
				}
			}
		}
	}

	SetColar(m_color);
	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CFade::Draw(void)
{
	CObject2D::Draw();
}

//========================================
// �ݒ�
//========================================
void CFade::SetFade(CScene::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_color = D3DXCOLOR(0, 0, 0, 0);
}