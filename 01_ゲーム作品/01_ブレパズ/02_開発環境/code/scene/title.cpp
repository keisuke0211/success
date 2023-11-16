//========================================
// 
// �^�C�g��
// 
//========================================
// *** title.cpp ***
//========================================
#include "title.h"
#include "game.h"
#include "ranking.h"
#include "../system/sound.h"
#include "../object/UI/UI_title.h"
#include "../object\model\model.h"
#include "../system/input.h"
#include "fade.h"
#include "../object/model/block.h"

#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/words/words.h"

// ��`
const char* CTitle::TEXT_FILE_PATH = "data\\GAMEDATA\\TEXT\\TITLE_DATA.txt";

// �ÓI�ϐ�
bool CTitle::m_bStart = false;
bool CTitle::m_bClear = false;

//========================================
// �R���X�g���N�^
//========================================
CTitle::CTitle()
{
	m_bStart = false;
	m_bClear = false;

	m_nTextTime = 0;
	m_nStandTime = 0;
	m_nSelectMenu = 0;

	Title = TITLE_OUTSET;

	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		m_Words[nCnt] = NULL;
		m_WordsShadow[nCnt] = NULL;
		m_bMove[nCnt] = false;
	}

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_Menu[nCnt] = NULL;
	}

}

//========================================
// �f�X�g���N�^
//========================================
CTitle::~CTitle()
{
	/*CBlock::Reset();*/
}

//========================================
// ������
//========================================
HRESULT CTitle::Init(void)
{
	m_bStart = false;
	m_bClear = false;

	CUiTitle::Create();		// �^�C�g���w�i

	// �e�L�X�g�ǂݍ���
	TextLoad();

	{
		FormFont pFont = {INIT_D3DXCOLOR,20.0f,50,1,-1};

		m_WordsShadow[0] = CWords::Create("�u", D3DXVECTOR3(443.0f, -57.0f, 0.0f), D3DXVECTOR3(52.0f, 52.0f, 0.0f), CFont::FONT_BESTTEN, D3DXCOLOR(0, 0, 0, 1));
		m_WordsShadow[1] = CWords::Create("��", D3DXVECTOR3(563.0f, -57.0f, 0.0f), D3DXVECTOR3(52.0f, 52.0f, 0.0f), CFont::FONT_BESTTEN, D3DXCOLOR(0, 0, 0, 1));
		m_WordsShadow[2] = CWords::Create("�p", D3DXVECTOR3(683.0f, -57.0f, 0.0f), D3DXVECTOR3(52.0f, 52.0f, 0.0f), CFont::FONT_BESTTEN, D3DXCOLOR(0, 0, 0, 1));
		m_WordsShadow[3] = CWords::Create("�Y", D3DXVECTOR3(803.0f, -57.0f, 0.0f), D3DXVECTOR3(52.0f, 52.0f, 0.0f), CFont::FONT_BESTTEN, D3DXCOLOR(0, 0, 0, 1));

		m_Words[0] = CWords::Create("�u", D3DXVECTOR3(440.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_BESTTEN, INIT_D3DXCOLOR);
		m_Words[1] = CWords::Create("��", D3DXVECTOR3(560.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_BESTTEN, INIT_D3DXCOLOR);
		m_Words[2] = CWords::Create("�p", D3DXVECTOR3(680.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_BESTTEN, INIT_D3DXCOLOR);
		m_Words[3] = CWords::Create("�Y", D3DXVECTOR3(800.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_BESTTEN, INIT_D3DXCOLOR);
	}
	m_bMove[0] = true;

	FormFont pFont = {
		INIT_D3DXCOLOR,
		20.0f,
		1,
		1,
		-1
	};
	m_Menu[0] = CText::Create(CText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		" ",
		CFont::FONT_BESTTEN,
		&pFont);

	pFont = {
		INIT_D3DXCOLOR,
		20.0f,
		5,
		10,
		-1
	};

	m_Menu[1] = CText::Create(CText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		"ENTER��A�{�^���������Ďn�߂Ă�!",
		CFont::FONT_BESTTEN,
		&pFont,false);

	m_nTextTime = TEXT_TIME;
	m_nStandTime = STAND_MAX;

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::TYPE_TITLE);

	return S_OK;
}

//========================================
// �I��
//========================================
void CTitle::Uninit(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();

	CObject::ReleaseAll(CObject::TYPE_BG);
	CObject::ReleaseAll(CObject::TYPE_BLOCK);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// �X�V
//========================================
void CTitle::Update(void)
{
	// �^�C�g���A�j���[�V����
	if (Title == TITLE_OUTSET)
	{
		TitleAnime();
	}
	else if (Title == TITLE_MENU)
	{
		Menu();
	}

	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g
	CSound *pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			switch (Title)
			{
			case TITLE_OUTSET:
			{
				TextClear(WORDS_MAX, 2, TITLE_MENU);

				// ���j���[����
				MenuCreate();
			}
			break;
			case TITLE_MENU:
			{
				pSound->PlaySound(CSound::TYPE_CYBER);

				switch (m_nSelectMenu)
				{
				case MENU_GAME:
					TextClear(1, MENU_MAX, TITLE_NEXT);
					CGame::Reset();
					CGame::LoodStage();
					CManager::GetFade()->SetFade(MODE_GAME);
					break;
				case MENU_TUTORIAL:
					TextClear(1, MENU_MAX, TITLE_NEXT);
					CManager::GetFade()->SetFade(MODE_TUTORIAL);
					break;
				case MENU_RANKING:
					TextClear(1, MENU_MAX, TITLE_NEXT);
					CManager::GetFade()->SetFade(MODE_RANKING);
					CRanking::SetScore11(0);
					CRanking::SetAllStage(true);
					break;
				case MENU_END:
					//�Q�[���̏I��
					PostQuitMessage(0);
					break;
				}
			}
			break;
			}
		}
	}
}

//========================================
// �`��
//========================================
void CTitle::Draw(void)
{

}

//========================================
// ����
//========================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle = new CTitle;

	pTitle->Init();

	return pTitle;
}

//========================================
// �^�C�g���A�j���[�V����
//========================================
void CTitle::TitleAnime(void)
{
	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		if (m_Words[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_Words[nCnt]->GetPos();

			if (pos.y <= 110.0f && m_bMove[nCnt])
			{
				D3DXVECTOR3 move;

				move.y = 3.0f;

				m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
				m_WordsShadow[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));

				if (pos.y >= 100.0f)
				{
					move.y = 0.0f;

					m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
					m_WordsShadow[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
				}
				else if (pos.y >= 20 && nCnt != 3 && !m_bMove[nCnt + 1])
				{
					m_bMove[nCnt + 1] = true;
				}
			}
		}
	}

	// ���͍Ñ��e�L�X�g
	if (--m_nTextTime <= 0)
	{
		if (m_nStandTime == STAND_MAX)
		{
			if (m_Menu[1] != NULL)
			{
				m_Menu[1]->Uninit();

				m_Menu[1] = NULL;
			}
		}
		m_nStandTime--;
		if (m_nStandTime <= 0)
		{
			FormFont pFont = {
				INIT_D3DXCOLOR,
				20.0f,
				5,
				10,
				-1
			};

			m_Menu[1] = CText::Create(CText::BOX_NORMAL_RECT,
				D3DXVECTOR3(640.0f, 600.0f, 0.0f),
				D3DXVECTOR2(1080.0f, 100.0f),
				"ENTER��A�{�^���������Ďn�߂Ă�!",
				CFont::FONT_BESTTEN,
				&pFont, false);

			m_nTextTime = TEXT_TIME;
			m_nStandTime = STAND_MAX;
		}
	}
}

//========================================
// ���j���[����
//========================================
void CTitle::MenuCreate(void)
{
	FormFont pFont = {
		INIT_D3DXCOLOR,
		20.0f,
		5,
		10,
		-1
	};

	{
		m_Menu[0] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 150.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"�Q�[��",
			CFont::FONT_BESTTEN,
			&pFont);
	}

	{
		m_Menu[1] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 300.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"�`���[�g���A��",
			CFont::FONT_BESTTEN,
			&pFont);
	}
	{
		m_Menu[2] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 450.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"�����L���O",
			CFont::FONT_BESTTEN,
			&pFont);
	}
	{
		m_Menu[3] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 600.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"�Q�[������߂�",
			CFont::FONT_BESTTEN,
			&pFont);
	}
}

//========================================
// ���j���[
//========================================
void CTitle::Menu(void)
{
	// �F
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_Menu[nCnt] != NULL)
		{
			if (nCnt == m_nSelectMenu)
			{
				m_Menu[nCnt]->SetBoxColor(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f));
			}
			else
			{
				m_Menu[nCnt]->SetBoxColor(INIT_D3DXCOLOR);
			}
		}
	}


	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g
	CSound *pSound = CManager::GetSound();

	// -- ���j���[�I�� ---------------------------
	if (pInputKeyboard->GetTrigger(DIK_W) || pInputKeyboard->GetTrigger(DIK_UP) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_UP) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_UP])
	{
		pSound->PlaySound(CSound::TYPE_SELECT);
		m_nSelectMenu--;
	}
	else if (pInputKeyboard->GetTrigger(DIK_S) || pInputKeyboard->GetTrigger(DIK_DOWN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_DOWN) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_DOWN])
	{
		pSound->PlaySound(CSound::TYPE_SELECT);
		m_nSelectMenu++;
	}

	// ���[�v����
	IntLoopControl(&m_nSelectMenu, MENU_MAX, 0);
}

//========================================
// �e�L�X�g�폜
//========================================
void CTitle::TextClear(int nWords, int nText, TITLE aTitle)
{
	for (int nCnt = 0; nCnt < nWords; nCnt++)
	{
		if (m_WordsShadow[nCnt] != NULL)
		{
			m_WordsShadow[nCnt]->Uninit();
			m_WordsShadow[nCnt] = NULL;
		}
		if (m_Words[nCnt] != NULL)
		{
			m_Words[nCnt]->Uninit();
			m_Words[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < nText; nCnt++)
	{
		if (m_Menu[nCnt] != NULL)
		{
			m_Menu[nCnt]->Uninit();
			m_Menu[nCnt] = NULL;
		}
	}

	Title = aTitle;
}

//========================================
// �e�L�X�g�ǂݍ���
//========================================
void CTitle::TextLoad(void)
{

}