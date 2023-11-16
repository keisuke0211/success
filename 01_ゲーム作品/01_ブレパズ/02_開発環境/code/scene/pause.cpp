//========================================
// 
// �|�[�Y
// 
//========================================
// *** pause.h ***
//========================================
#include "pause.h"
#include "../system/input.h"
#include "../scene/fade.h"
#include "../system/words/text.h"
#include "../system/sound.h"
#include "../object/BG/blackout.h"

// �ÓI�ϐ�
bool CPause::m_bPause = false;

//========================================
// �R���X�g���N�^
//========================================
CPause::CPause()
{
	m_Menu = false;
	m_nSelectMenu = 0;
	m_Blackout = NULL;

	for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
	{
		m_Text[nCnt] = NULL;
	}
}

//========================================
// �f�X�g���N�^
//========================================
CPause::~CPause()
{

}

//========================================
// ������
//========================================
HRESULT CPause::Init(void)
{

	return S_OK;
}

//========================================
// �I��
//========================================
void CPause::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CPause::Update(void)
{
	if (m_bPause)
	{
		// ���j���[����
		MenuCreate();

		// ���j���[
		Menu();
	}
}

//========================================
// �`��
//========================================
void CPause::Draw(void)
{

}

//========================================
// ����
//========================================
CPause *CPause::Create(void)
{
	CPause *pPause = new CPause;

	pPause->Init();

	return pPause;
}

//========================================
// ���j���[
//========================================
void CPause::Menu(void)
{
	CSound *pSound = CManager::GetSound();

	// �F
	for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
	{
		if (m_Text[nCnt] != NULL)
		{
			if (nCnt == m_nSelectMenu)
			{
				m_Text[nCnt]->SetBoxColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
			else
			{
				m_Text[nCnt]->SetBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
		}
	}

	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// -- ���j���[�I�� ---------------------------
	if (pInputKeyboard->GetTrigger(DIK_W) || pInputKeyboard->GetTrigger(DIK_UP) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_UP) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_UP])
	{
		m_nSelectMenu--;
		pSound->PlaySound(CSound::TYPE_SELECT);
	}
	else if (pInputKeyboard->GetTrigger(DIK_S) || pInputKeyboard->GetTrigger(DIK_DOWN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_DOWN) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_DOWN])
	{
		m_nSelectMenu++;
		pSound->PlaySound(CSound::TYPE_SELECT);
	}

	if (m_nSelectMenu > (MENU_MAX - 1))
	{// ���j���[�̍őO���Ɉړ�
		m_nSelectMenu = 0;
	}
	else if (m_nSelectMenu < 0)
	{// ���j���[�̍Ō���Ɉړ�
		m_nSelectMenu = (MENU_MAX - 1);
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pSound->PlaySound(CSound::TYPE_CYBER);

			switch (m_nSelectMenu)
			{
			case MENU_RESUME:
				m_bPause = false;
				break;
			case MENU_RESET:
				m_bPause = false;

				if (CScene::GetMode() == MODE_GAME)
				{
					CManager::GetFade()->SetFade(MODE_GAME);
				}
				else if (CScene::GetMode() == MODE_TUTORIAL)
				{
					CManager::GetFade()->SetFade(MODE_TUTORIAL);
				}
				break;
			case MENU_TITLE:
				m_bPause = false;
				CManager::GetFade()->SetFade(MODE_TITLE);
				break;
			}
		}
	}

	if (!m_bPause)
	{
		for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
		{
			if (m_Text[nCnt] != NULL)
			{
				m_Text[nCnt]->Uninit();
				m_Text[nCnt] = NULL;
			}
		}
		m_Blackout->Uninit();
		m_Blackout = NULL;

		m_Menu = false;
	}
}

//========================================
// ���j���[����
//========================================
void CPause::MenuCreate(void)
{
	FormFont pFont = {
		INIT_D3DXCOLOR,
		20.0f,
		5,
		10,
		-1
	};

	if (!m_Menu)
	{
		// �Ó]
		m_Blackout = CBlackout::Create();

		{
			m_Text[0] = CText::Create(CText::BOX_NORMAL_RECT,
				D3DXVECTOR3(640.0f, 250.0f, 0.0f),
				D3DXVECTOR2(360.0f, 100.0f),
				"�ĊJ",
				CFont::FONT_BESTTEN,
				&pFont);
			m_Text[0]->SetTetPause(true);
		}

		{
			m_Text[1] = CText::Create(CText::BOX_NORMAL_RECT,
				D3DXVECTOR3(640.0f, 400.0f, 0.0f),
				D3DXVECTOR2(360.0f, 100.0f),
				"��蒼��",
				CFont::FONT_BESTTEN,
				&pFont);
			m_Text[1]->SetTetPause(true);
		}
		{
			m_Text[2] = CText::Create(CText::BOX_NORMAL_RECT,
				D3DXVECTOR3(640.0f, 550.0f, 0.0f),
				D3DXVECTOR2(360.0f, 100.0f),
				"�^�C�g���ɖ߂�",
				CFont::FONT_BESTTEN,
				&pFont);
			m_Text[2]->SetTetPause(true);
		}
		{
			pFont = {
				INIT_D3DXCOLOR,
				40.0f,
				5,
				10,
				-1
			};

			FormShadow pShadow = {
				D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),
				true,
				D3DXVECTOR3(3.0f,3.0f,0.0f),
				D3DXVECTOR2(1.0f,1.0f)
			};

			m_Text[3] = CText::Create(CText::BOX_NORMAL_RECT,
				D3DXVECTOR3(640.0f, 100.0f, 0.0f),
				D3DXVECTOR2(360.0f, 100.0f),
				"�|�[�Y",
				CFont::FONT_BESTTEN,
				&pFont,false,&pShadow);
			m_Text[3]->SetTetPause(true);
		}

		m_Menu = true;
	}
}