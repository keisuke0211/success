//========================================
// 
// �����L���O
// 
//========================================
// *** ranking.h ***
//========================================
#include "ranking.h"
#include "game.h"
#include "fade.h"
#include "../system/sound.h"
#include "../object/UI/UI_title.h"
#include "../system/csv_file.h"
#include "../system/input.h"
#include "../system/words/text.h"
#include "../system/words/font.h"

// ��`
const char* CRanking::STAGE_FILE = "data\\SAVEDATA\\RANKING_DATA.csv";
const char* CRanking::TEXT_FILE_PATH = "data\\GAMEDATA\\TEXT\\WORDS_DATA.txt";
int CRanking::m_nGameScore = 0;
bool CRanking::m_bSetScore = false;
bool CRanking::m_bRankingAll = false;

//========================================
// �R���X�g���N�^
//========================================
CRanking::CRanking()
{
	// ���Z�b�g
	CGame::Reset();

	for (int nRank = 0; nRank < RANK_NUM; nRank++)
	{
		m_Ranking[nRank].nScore = 100 + (100 * nRank);
		*m_Ranking[nRank].aName = NULL;
	}

	m_Info.nCounterState = 0;
	m_Info.bNameEntry = false;
	m_Info.nCntName = 0;
	m_Info.nUpdateRank = -1;
	m_Info.nCntBlink = 0;
	m_Info.bNameInput = true;
	m_Info.nCntChar = 0;

	m_Info.nCntString = 0;
	m_Info.nCntLetter = 0;
	m_pString = NULL;
	m_Info.nCntBlink = 0;
	nStringMax = 0;

	strinit(m_aNameData, TXT_MAX);

	for (int nCnt = 0; nCnt < EXPLAIN_MAX; nCnt++)
	{
		m_Explain[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
	{
		m_Words[nCnt] = NULL;
	}
	for (int nCnt = 0; nCnt < NAME_NUM; nCnt++)
	{
		m_Info.nNameChar[nCnt] = 0;
	}
}

//========================================
// �f�X�g���N�^
//========================================
CRanking::~CRanking()
{

}

//========================================
// ������
//========================================
HRESULT CRanking::Init(void)
{
	int nUpdateRank = -1;	// �X�R�A���X�V��������

	CUiTitle::Create();		// �^�C�g���w�i

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::TYPE_RANKING);

	// �ǂݍ���
	Load();			// �v���C�����X�e�[�W����

	WordsLoad();	// �e�L�X�g

	// �\�[�g
	SortDesc(&nUpdateRank);

	FormFont pFont = { INIT_D3DXCOLOR,20.0f,1,1,-1 };
	FormShadow pShadow = { INIT_D3DXCOLOR, true, D3DXVECTOR3(1.0f,1.0f,0.0f), D3DXVECTOR2(1.0f,1.0f) };

	// �e�L�X�g����
	for (int nRank = 0; nRank < RANK_NUM; nRank++)
	{
		switch (nRank)
		{
		case 0:
			pFont = { D3DXCOLOR(1.0f,0.96f,0,1)	, 20.0f, 1, 1, -1 };
			break;
		case 1:
			pFont = { D3DXCOLOR(0.6f,0.6f,0.6f,1), 20.0f, 1, 1, -1 };
			break;
		case 2:
			pFont = { D3DXCOLOR(0.78f,0.54f,0,1), 20.0f, 1, 1, -1 };
			break;
		default:
			pFont = { INIT_D3DXCOLOR, 20.0f, 1, 1, -1 };
			break;
		}

		char aString[TXT_MAX];
		sprintf(aString, " %s %-5s %6d", GetRankText(nRank), m_Ranking[nRank].aName, m_Ranking[nRank].nScore);

		m_Text[nRank] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(10.0f, 155 + ( 40 * nRank), 0.0f),
			D3DXVECTOR2(0.0f, 100.0f),
			aString,
			CFont::FONT_BESTTEN,
			&pFont,false,&pShadow);
		m_Text[nRank]->SetSpace(true);
	}

	// �g(�����L���O�t���[��)
	CText::Create(CText::BOX_NORMAL_SQR, D3DXVECTOR3(400.0f, 290, 0.0f), D3DXVECTOR2(740.0f, 400.0f),
		"", CFont::FONT_BESTTEN, &pFont, true);

	int nRank = SetScore(m_nGameScore);

	if (nRank < RANK_NUM && nRank > -1)
	{
		m_bSetScore = true;
	}
	else
	{
		m_bSetScore = false;
	}

	// �X�R�A�X�V������
	if (m_bSetScore)
	{
		// ����e�L�X�g�̐���
		{
			pFont = {INIT_D3DXCOLOR,15.0f,1,1,-1};
			FormShadow pShadow = {D3DXCOLOR(0.0f,0.0f,0.0f,1.0f), true, D3DXVECTOR3(2.0f,2.0f,0.0f), D3DXVECTOR2(1.0f,1.0f)};

			m_Explain[0] = CText::Create(CText::BOX_NORMAL_RECT,D3DXVECTOR3(50.0f, 550, 0.0f),D3DXVECTOR2(0.0f, 0.0f),
				"���E���F�s�̕ύX",CFont::FONT_BESTTEN,&pFont, false,&pShadow);

			m_Explain[1] = CText::Create(CText::BOX_NORMAL_RECT,D3DXVECTOR3(50.0f, 590, 0.0f),D3DXVECTOR2(0.0f, 0.0f),
				"���E���F�����̕ύX",CFont::FONT_BESTTEN,&pFont, false, &pShadow);

			m_Explain[2] = CText::Create(CText::BOX_NORMAL_RECT,D3DXVECTOR3(50.0f, 630, 0.0f),D3DXVECTOR2(0.0f, 0.0f),
				"X�EY�F�ϊ�",CFont::FONT_BESTTEN,&pFont, false, &pShadow);

			m_Explain[3] = CText::Create(CText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 550, 0.0f),D3DXVECTOR2(0.0f, 100.0f),
				"A�F����",CFont::FONT_BESTTEN,&pFont, false, &pShadow);

			m_Explain[4] = CText::Create(CText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 590, 0.0f),D3DXVECTOR2(0.0f, 100.0f),
				"B�F�폜",CFont::FONT_BESTTEN,&pFont, false, &pShadow);

			m_Explain[5] = CText::Create(CText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 630, 0.0f),D3DXVECTOR2(0.0f, 100.0f),
				"�r���œ��͂���߂�ꍇ�́���I��!",CFont::FONT_BESTTEN,&pFont, false, &pShadow);
		}

		SetNameEntry(nRank);
	}

	// �^�C�g�����痈����
	if (m_bRankingAll)
	{
		/*pFont = { INIT_D3DXCOLOR,15.0f,1,1,-1 };
		FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f), true, D3DXVECTOR3(2.0f,2.0f,0.0f), D3DXVECTOR2(1.0f,1.0f) };

		m_Explain[0] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(50.0f, 590, 0.0f),
			D3DXVECTOR2(0.0f, 0.0f),
			"���E���F�X�e�[�W�̕ύX",
			CFont::FONT_BESTTEN,
			&pFont, false,&pShadow);

		m_Explain[1] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 590, 0.0f),
			D3DXVECTOR2(0.0f, 0.0f),
			"���݂̃X�e�[�W�FSTAGE1",
			CFont::FONT_BESTTEN,
			&pFont, false,&pShadow);*/
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CRanking::Uninit(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();

	// �����o������
	if (!m_bRankingAll)
	{
		Save();
	}

	for (int nStr = 0; nStr < nStringMax; nStr++)
	{
		for (int nCpnv = 0; nCpnv < m_pString[nStr].nConvMax; nCpnv++)
		{
			if (m_pString[nStr].pConv[nCpnv].pLetter != NULL)
			{
				delete[] m_pString[nStr].pConv[nCpnv].pLetter;
				m_pString[nStr].pConv[nCpnv].pLetter = NULL;
			}
		}
		if (m_pString[nStr].pConv != NULL)
		{
			delete[] m_pString[nStr].pConv;
			m_pString[nStr].pConv = NULL;
		}
	}

	if (m_pString != NULL)
	{
		delete[] m_pString;
		m_pString = NULL;
	}

	CObject::ReleaseAll(CObject::TYPE_BG);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// �X�V
//========================================
void CRanking::Update(void)
{
	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// ���
	State();

	// ���O����
	NameEntry();

	// �����L���O�ؑ�
	if (m_bRankingAll)
	{
		RankingSwitch();
	}

	if ((pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A)) && m_Info.bNameEntry == false)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(MODE_TITLE);
		}
	}
}

//========================================
// �`��
//========================================
void CRanking::Draw(void)
{

}

//========================================
// ����
//========================================
CRanking *CRanking::Create(void)
{
	CRanking *pRanking = new CRanking;

	pRanking->Init();

	return pRanking;
}

//========================================
// �v���C�����X�e�[�W�̂ݓǂݍ���
//========================================
void CRanking::Load(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood(STAGE_FILE, true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:
				char *pNama;
				pFile->ToValue(pNama, sData);

				strcat(m_Ranking[nRow].aName,pNama);
				break;	// ���O
			case 1:	pFile->ToValue(m_Ranking[nRow].nScore, sData);		break;	// �X�R�A
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}
	}

	delete pFile;
	pFile = NULL;
}

//========================================
// �����o��
//========================================
void CRanking::Save(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �w�b�_�[�̐ݒ�
	pFile->SetHeader("���O,�X�R�A,", ',');

	// �f�[�^�̐ݒ�
	for (int nRow = 0; nRow < RANK_NUM; nRow++)
	{
		// �C���f�b�N�X�̐ݒ�
		pFile->SetIndex(GetRankText(nRow), ',');

		for (int nLine = 0; nLine < 2; nLine++)
		{
			string sData;	// ������̊i�[����ϐ�

			// ������ɕϊ�
			switch (nLine)
			{
			case 0:	sData = m_Ranking[nRow].aName; break;	// ���O
			case 1:	sData = pFile->CastCell(m_Ranking[nRow].nScore); break;	// �X�R�A
			}

			// �f�[�^�̒ǉ�
			pFile->SetCell(sData, nRow, nLine);
		}
	}

	// �����o��
	pFile->FileSave(STAGE_FILE, ',');
}

//========================================
// ��ԏ���
//========================================
void CRanking::State(void)
{
	for (int nCntRanking = 0; nCntRanking < RANK_NUM; nCntRanking++)
	{
		if (m_Info.nUpdateRank == nCntRanking)
		{
			m_Text[nCntRanking]->SetTextColor(RANKING_COLOR);
		}
	}
}

//========================================
// �X�R�A�ݒ�
//========================================
int CRanking::SetScore(int nScore)
{
	int nUpdateRank = -1;	// �X�R�A���X�V��������

	// �X�R�A���~���Ƀ\�[�g����
	SortDesc(&nUpdateRank);

	if (nScore > m_Ranking[RANK_NUM - 1].nScore)
	{// �ł��������l���}������l���傫��������
	 // �ł��������l�ɑ}������l��������
		m_Ranking[RANK_NUM - 1].nScore = nScore;

		// �X�R�A���X�V�������ʂ�������
		nUpdateRank = RANK_NUM - 1;
	}

	// �X�R�A���~���Ƀ\�[�g����
	SortDesc(&nUpdateRank);

	// �X�R�A���X�V�������ʂ�Ԃ�
	return nUpdateRank;
}

//========================================
// �X�R�A�ݒ�
//========================================
void CRanking::SetScore11(int nScore)
{
	m_nGameScore = nScore;
}

//========================================
// ���O���͐ݒ�
//========================================
void CRanking::SetNameEntry(int nUpdateRank)
{
	m_Info.nUpdateRank = nUpdateRank;

	if (m_Info.nUpdateRank != -1)
	{// �X�V���ʂ�-1(�X�V����)�łȂ����A
		m_Info.bNameEntry = true;
		m_bSetScore = true;
		m_Info.nCntName = 0;
		m_Info.nCntBlink = 0;

		// �X�V�������ʂ̖��O��������
		strinit(m_Ranking[nUpdateRank].aName, TXT_MAX);

		strcat(m_aNameData, "_____");

		char aString[TXT_MAX];
		sprintf(aString, " %s %-5s %6d", GetRankText(m_Info.nUpdateRank), m_aNameData, m_Ranking[m_Info.nUpdateRank].nScore);

		m_Text[m_Info.nUpdateRank]->Uninit();

		FormFont pFont = {
			INIT_D3DXCOLOR,
			20.0f,
			1,
			1,
			-1
		};

		m_Text[m_Info.nUpdateRank] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(10.0f, 155 + (40 * m_Info.nUpdateRank), 0.0f),
			D3DXVECTOR2(0.0f, 100.0f),
			aString,
			CFont::FONT_BESTTEN,
			&pFont, false);
	}
	else
	{// �X�V������-1(�X�V����)�̎��A
		m_Info.bNameEntry = false;
	}

	SetWords();
}

//========================================
// ���O����
//========================================
void CRanking::NameEntry(void)
{
	if (!m_Info.bNameEntry)
	{
		return;
	}
	if (!m_Info.bNameInput)
	{
		++m_Info.nCounterBlink %= (BLINK_TIME * 2);	// �_�ŃJ�E���^�[�����Z����

		D3DXCOLOR col =
			!(m_Info.nCounterBlink / BLINK_TIME) ?
			RANKING_COLOR : BLINK_COLOR;

		int nRank = m_Info.nUpdateRank;

		if (m_Text[nRank]->ChgWords("_", NAME_START_DEX + m_Info.nCntName, col))
		{
			UpdateWords();
		}

		// ����
		NameInput();
	}
	
	if (m_Info.bNameInput)
	{
		int nString = m_Info.nCntString;
		int nLetter = m_Info.nCntLetter;
		int nConv = m_Info.nCntConv;
		int nRank = m_Info.nUpdateRank;

		UpdateWords();
		m_Info.bNameInput = false;
	}


}

//========================================
// ���O����(����)
//========================================
void CRanking::NameInput(void)
{
	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g
	CSound *pSound = CManager::GetSound();

	// -- ������ؑ� ---------------------------------------------
	if (pInputKeyboard->GetRepeat(DIK_A) || pInputKeyboard->GetRepeat(DIK_LEFT) ||
		pInputJoypad->GetRepeat(CJoypad::JOYKEY_LEFT) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_LEFT])
	{
		m_Info.nCntLetter--;
		m_Info.bNameInput = true;
		pSound->PlaySound(CSound::TYPE_SELECT);
	}
	else if (
		pInputKeyboard->GetRepeat(DIK_D) || pInputKeyboard->GetRepeat(DIK_RIGHT) ||
		pInputJoypad->GetRepeat(CJoypad::JOYKEY_RIGHT) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_RIGHT])
	{
		m_Info.nCntLetter++;
		m_Info.bNameInput = true;
		pSound->PlaySound(CSound::TYPE_SELECT);
	}

	// -- �����ؑ� ---------------------------------------------
	if (pInputKeyboard->GetRepeat(DIK_S) || pInputKeyboard->GetRepeat(DIK_DOWN) ||
		pInputJoypad->GetRepeat(CJoypad::JOYKEY_DOWN) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_DOWN])
	{
		m_Info.nCntLetter = 0;
		m_Info.nCntConv = 0;
		m_Info.nCntString++;
		m_Info.bNameInput = true;
		pSound->PlaySound(CSound::TYPE_SELECT);
	}
	else if (
		pInputKeyboard->GetRepeat(DIK_W) || pInputKeyboard->GetRepeat(DIK_UP) ||
		pInputJoypad->GetRepeat(CJoypad::JOYKEY_UP) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_UP])
	{
		m_Info.nCntLetter = 0;
		m_Info.nCntConv = 0;
		m_Info.nCntString--;
		m_Info.bNameInput = true;
		pSound->PlaySound(CSound::TYPE_SELECT);
	}

	// -- �ϊ� ---------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_Q) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_X))
	{
		m_Info.nCntConv--;
		m_Info.bNameInput = true;
	}
	else if (pInputKeyboard->GetTrigger(DIK_E) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_Y))
	{
		m_Info.nCntConv++;
		m_Info.bNameInput = true;
	}

	// �J�E���g����
	{
		int nString = m_Info.nCntString;
		int nLetterMax = m_pString[nString].nLettreMax;
		int nConvMax = m_pString[nString].nConvMax;

		IntLoopControl(&m_Info.nCntString, nStringMax, 0);
		IntLoopControl(&m_Info.nCntLetter, nLetterMax, 0);
		IntLoopControl(&m_Info.nCntConv, nConvMax, 0);
	}

	// -- ����E�폜 ---------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_B))
	{// �폜
		if (m_Info.nCntName > 0)
		{
			int nRank = m_Info.nUpdateRank;
			char aWords[] = "_";

			int nChar = m_Info.nNameChar[m_Info.nCntName - 1];

			// ���݂̃J�E���g�̕����𔽉f����
			for (int nCnt = 0; nCnt < nChar; nCnt++)// ���{��p
			{
				m_Ranking[nRank].aName[(m_Info.nCntChar - 1) - nCnt] = '\0';
			}
			m_Info.nCntChar -= nChar;

			if (m_Text[nRank]->ChgWords(aWords, NAME_START_DEX + m_Info.nCntName,INIT_D3DXCOLOR))
			{
				m_Info.bNameInput = false;
			}
			m_Info.nCntName--;

		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{// ����

		int nString = m_Info.nCntString;
		int nLetter = m_Info.nCntLetter;
		int nLetterMax = m_pString[nString].nLettreMax - 1;
		int nConv = m_Info.nCntConv;
		int nRank = m_Info.nUpdateRank;

		if (nLetter != nLetterMax)
		{
			// ���݂̃J�E���g�̕�����������
			strcat(m_Ranking[nRank].aName, m_pString[nString].pConv[nConv].pLetter[nLetter].aConv);

			// ���݂̃J�E���g�̕����𔽉f����
			strinit(m_aNameData, TXT_MAX);
			strcat(m_aNameData, m_Ranking[nRank].aName);

			int nStrlen = strlen(m_pString[nString].pConv[nConv].pLetter[nLetter].aConv);

			m_Info.nCntChar += nStrlen;
			m_Info.nNameChar[m_Info.nCntName] = nStrlen;

			if (m_Text[nRank]->ChgWords(m_pString[nString].pConv[nConv].pLetter[nLetter].aConv, NAME_START_DEX + m_Info.nCntName, RANKING_COLOR))
			{
				UpdateWords();
			}

			if (++m_Info.nCntName >= NAME_NUM)
			{// ���O���͂̃J�E���g�����Z�������ʁA�����L���O���̕������ɒB�������A
				m_Info.bNameEntry = false;
				return;
			}
		}
		else
		{
			// ���݂̃J�E���g�̕������I�[������������
			if (m_Info.nCntName != 0)
			{
				for (int nCnt = 0; nCnt < NAME_NUM - m_Info.nCntName; nCnt++)
				{
					// ���݂̃J�E���g�̕�����������
					strcat(m_Ranking[nRank].aName, " ");

					// ���݂̃J�E���g�̕����𔽉f����
					strinit(m_aNameData, TXT_MAX);
					strcat(m_aNameData, m_Ranking[nRank].aName);

					if (m_Text[nRank]->ChgWords(" ", NAME_START_DEX + (m_Info.nCntName + nCnt), RANKING_COLOR))
					{
						m_Info.bNameInput = false;
					}
				}
				m_Info.bNameEntry = false;
			}
			else
			{
				int nCntName = 0;
				for (int nCnt = 0; nCnt < NAME_NUM - m_Info.nCntName; nCnt++)
				{
					char aData[6][TXT_MAX] = { "��","��","��"," "," "};

					// ���݂̃J�E���g�̕�����������
					strcat(m_Ranking[nRank].aName,aData[nCntName]);

					// ���݂̃J�E���g�̕����𔽉f����
					strinit(m_aNameData, TXT_MAX);
					strcat(m_aNameData, m_Ranking[nRank].aName);

					if (m_Text[nRank]->ChgWords(aData[nCntName], NAME_START_DEX + (m_Info.nCntName + nCnt), RANKING_COLOR))
					{
						m_Info.bNameInput = false;
					}
					nCntName++;
				}
				m_Info.bNameEntry = false;
			}
		}

		pSound->PlaySound(CSound::TYPE_CYBER);

	}
}

//========================================
// �����L���O�ؑ�
//========================================
void CRanking::RankingSwitch(void)
{
	
}

//========================================
// �����\��(�ݒ�)
//========================================
void CRanking::SetWords(void)
{
	int nString = m_Info.nCntString;
	int nLetter = m_Info.nCntLetter;
	int nLetterMax = m_pString[nString].nLettreMax - 1;
	int nConv = m_Info.nCntConv;
	int nConvMax = m_pString[nString].nConvMax - 1;
	int nRank = m_Info.nUpdateRank;

	int nNextLetter = m_Info.nCntLetter + 1;				// ���̕���
	int nPrevLetter = m_pString[nString].nLettreMax - 1;	// �O�̕���
	int nNextString = m_Info.nCntString + 1;				// ���̍s
	int nPrevString = nStringMax - 1;						// �O�̍s

	FormFont pFont = {INIT_D3DXCOLOR,30.0f,1,1,-1};

	// ����
	m_Words[0] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(950.0f, 250, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		m_pString[nString].pConv[nConv].pLetter[nLetter].aConv, CFont::FONT_BESTTEN, &pFont, false);

	// ��
	m_Words[1] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(950.0f, 160, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		m_pString[nPrevString].pConv[nConv].pLetter[0].aConv, CFont::FONT_BESTTEN, &pFont, false);

	// ��
	m_Words[2] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(950.0f, 340, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		m_pString[nNextString].pConv[nConv].pLetter[0].aConv, CFont::FONT_BESTTEN, &pFont, false);

	// ��
	m_Words[3] = CText::Create(CText::BOX_NORMAL_RECT,D3DXVECTOR3(850.0f, 250, 0.0f),D3DXVECTOR2(0.0f, 0.0f),
		m_pString[nString].pConv[nConv].pLetter[nPrevLetter].aConv,CFont::FONT_BESTTEN,&pFont, false);

	// �E
	m_Words[4] = CText::Create(CText::BOX_NORMAL_RECT,D3DXVECTOR3(1050.0f, 250, 0.0f),D3DXVECTOR2(0.0f, 0.0f),
		m_pString[nString].pConv[nConv].pLetter[nNextLetter].aConv,CFont::FONT_BESTTEN,&pFont, false);

	pFont = {INIT_D3DXCOLOR,15.0f,1,1,-1};

	// ��
	m_Words[5] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(975.0f, 210, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		"��", CFont::FONT_BESTTEN, &pFont, false);

	// ��
	m_Words[6] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(975.0f, 300, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		"��", CFont::FONT_BESTTEN, &pFont, false);

	// ��
	m_Words[7] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(930.0f, 250, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		"��", CFont::FONT_BESTTEN, &pFont, false);

	// �E
	m_Words[8] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(1030.0f, 250, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		"��", CFont::FONT_BESTTEN, &pFont, false);

	// �g(����)
	m_Words[9] = CText::Create(CText::BOX_NORMAL_SQR, D3DXVECTOR3(1020.0f, 260, 0.0f), D3DXVECTOR2(320.0f, 320.0f),
		"", CFont::FONT_BESTTEN, &pFont, true);
}

//========================================
// �����\��(�X�V)
//========================================
void CRanking::UpdateWords(void)
{
	int nString = m_Info.nCntString;
	int nLetter = m_Info.nCntLetter;
	int nLetterMax = m_pString[nString].nLettreMax - 1;
	int nConv = m_Info.nCntConv;
	int nConvMax = m_pString[nString].nConvMax - 1;
	int nRank = m_Info.nUpdateRank;

	int nNextLetter = m_Info.nCntLetter + 1;	// ���̕���
	int nPrevLetter = m_Info.nCntLetter - 1;	// �O�̕���
	int nNextString = m_Info.nCntString + 1;	// ���̍s
	int nPrevString = m_Info.nCntString - 1;	// �O�̍s

	IntLoopControl(&nNextString, nStringMax, 0);
	IntLoopControl(&nPrevString, nStringMax, 0);
	IntLoopControl(&nNextLetter, nLetterMax+1, 0);
	IntLoopControl(&nPrevLetter, nLetterMax+1, 0);

	m_Words[0]->ChgWords(m_pString[nString].pConv[nConv].pLetter[nLetter].aConv, 0, INIT_D3DXCOLOR);
	m_Words[1]->ChgWords(m_pString[nPrevString].pConv[0].pLetter[0].aConv, 0, INIT_D3DXCOLOR);
	m_Words[2]->ChgWords(m_pString[nNextString].pConv[0].pLetter[0].aConv, 0, INIT_D3DXCOLOR);
	m_Words[3]->ChgWords(m_pString[nString].pConv[nConv].pLetter[nPrevLetter].aConv, 0, INIT_D3DXCOLOR);
	m_Words[4]->ChgWords(m_pString[nString].pConv[nConv].pLetter[nNextLetter].aConv, 0, INIT_D3DXCOLOR);

}

//========================================
// �\�[�g�~��
//========================================
void CRanking::SortDesc(int *nUpdateRank)
{
	int	 nTemp;					// �ꎞ�I�ɒl���i�[
	char aNameTemp[TXT_MAX];	// �ꎞ�I�ɒl���i�[
	bool bUpdateRank = false;	// ���ʍX�V�t���O

	for (int nCnt1 = 0; nCnt1 < RANK_NUM - 1; nCnt1++)
	{
		for (int nCnt2 = nCnt1 + 1; nCnt2 < RANK_NUM; nCnt2++)
		{
			if (m_Ranking[nCnt2].nScore > m_Ranking[nCnt1].nScore)
			{// �v�f2���v�f1�̒l�������Ă������A
			 // �l�����ւ���
				nTemp = m_Ranking[nCnt1].nScore;
				m_Ranking[nCnt1].nScore = m_Ranking[nCnt2].nScore;
				m_Ranking[nCnt2].nScore = nTemp;

				// ���O�����ւ���
				sprintf(aNameTemp, "%s", m_Ranking[nCnt1].aName);
				sprintf(m_Ranking[nCnt1].aName, "%s", m_Ranking[nCnt2].aName);
				sprintf(m_Ranking[nCnt2].aName, "%s", aNameTemp);

				if (bUpdateRank == false)
				{// ���ʍX�V�t���O���U�̎��A
				 // ���ʍX�V�t���O��^�ɂ���
					bUpdateRank = true;

					// �X�R�A���X�V�������ʂ�������
					*nUpdateRank = nCnt1;
				}
			}
		}
	}
}

//========================================
// �󔒖���
//========================================
void CRanking::strinit(char *pData, int nNum)
{
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		pData[nCnt] = '\0';
	}
}

//========================================
// �����ǂݍ���
//========================================
void CRanking::WordsLoad(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(TEXT_FILE_PATH, "r");

	// �t�@�C�����J������
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 // END_SCRIPT��������܂œǂݍ��݂��J��Ԃ�
		while (1)
		{
			fscanf(pFile, "%s", aDataSearch);	// ����

			if (!strcmp(aDataSearch, "END_SCRIPT"))
			{// �ǂݍ��݂��I��
				fclose(pFile);
				break;
			}
			else if (aDataSearch[0] == '#')
			{// �܂�Ԃ�
				continue;
			}
			else if (!strcmp(aDataSearch, "NUM_ROW"))
			{// �s��
				fscanf(pFile, "%s", &g_aEqual[0]);
				fscanf(pFile, "%d", &nStringMax);

				// �������̉��
				m_pString = new String[nStringMax];
			}
			else if (!strcmp(aDataSearch, "SET_TEXT"))
			{// ������̓ǂݍ���

				int nCntString = 0;	// ��

				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);	// ����

					if (!strcmp(aDataSearch, "END_TEXT"))
					{// �ǂݍ��݂��I��
						break;
					}
					else if (!strcmp(aDataSearch, "SET_ROW"))
					{// �����̓ǂݍ���
						while (1)
						{
							fscanf(pFile, "%s", aDataSearch);	// ����

							if (!strcmp(aDataSearch, "END_ROW"))
							{// �ǂݍ��݂��I��
								nCntString++;	// ����̉��Z
								break;
							}
							else if (!strcmp(aDataSearch, "NUM_CONV"))
							{// �ϊ����̓ǂݍ���

								int nConvMin = 1;
								int nConvMax = 0;

								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nConvMax);

								nConvMax = nConvMin + nConvMax;

								// �������̉��
								m_pString[nCntString].pConv = new Conv[nConvMax];

								m_pString[nCntString].nConvMax = nConvMax;
							}
							else if (!strcmp(aDataSearch, "NUM_WORDS"))
							{// �������̓ǂݍ���

								int nLettreMax = -1;

								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nLettreMax);

								for (int nConv = 0; nConv < m_pString[nCntString].nConvMax; nConv++)
								{
									m_pString[nCntString].pConv[nConv].pLetter = new Letter[nLettreMax];
								}
								m_pString[nCntString].nLettreMax = nLettreMax;
							}
							else if (!strcmp(aDataSearch, "SET_WORDS"))
							{// �^�C�v�̓ǂݍ���
								int nCountLetter = 0;	// ������
								int nCountConv = 0;

								while (1)
								{
									fscanf(pFile, "%s", &aDataSearch[0]);	// ����

									if (!strcmp(aDataSearch, "END_WORDS"))
									{// �ǂݍ��݂��I��
										break;
									}
									else if (!strcmp(aDataSearch, "WOARDS")) 
									{// �����̓ǂݍ���
										char aString[TXT_MAX];	// ������i�[
										char *ptr;				// ���������̊i�[

										fscanf(pFile, "%s", &aString[0]);

										// �J���}����؂�ɕ�����𕪊�
										ptr = strtok(aString, ",");

										if (nCountLetter < m_pString[nCntString].nLettreMax)
										{
											sprintf(m_pString[nCntString].pConv[nCountConv].pLetter[nCountLetter].aConv, "%s", ptr);
											nCountLetter++;
										}

										while (ptr != NULL)
										{
											// strtok�֐��ɂ��ύX���ꂽNULL�̃|�C���^���擪
											ptr = strtok(NULL, ",");

											// ptr��NULL�̏ꍇ�G���[����������̂őΏ�
											if (ptr != NULL) 
											{
												if (nCountLetter < m_pString[nCntString].nLettreMax)
												{
													sprintf(m_pString[nCntString].pConv[nCountConv].pLetter[nCountLetter].aConv, "%s", ptr);
													nCountLetter++;
												}
											}
										}
										nCountConv++;
									}
									else if (!strcmp(aDataSearch, "CONV"))
									{// �����̓ǂݍ���
										nCountLetter = 0;	// ������
										char aString[TXT_MAX];	// ������i�[
										char *ptr;				// ���������̊i�[

										fscanf(pFile, "%s", &aString[0]);

										// �ő吔�����Ă���
										if (nCountConv >= m_pString[nCntString].nConvMax)
										{
											return;
										}

										// �J���}����؂�ɕ�����𕪊�
										ptr = strtok(aString, ",");

										if (nCountLetter < m_pString[nCntString].nLettreMax)
										{
											// �X�V�������ʂ̖��O��������
											sprintf(m_pString[nCntString].pConv[nCountConv].pLetter[nCountLetter].aConv, "%s", ptr);
											nCountLetter++;
										}

										while (ptr != NULL)
										{
											// strtok�֐��ɂ��ύX���ꂽNULL�̃|�C���^���擪
											ptr = strtok(NULL, ",");

											// ptr��NULL�̏ꍇ�G���[����������̂őΏ�
											if (ptr != NULL)
											{
												if (nCountLetter < m_pString[nCntString].nLettreMax)
												{
													sprintf(m_pString[nCntString].pConv[nCountConv].pLetter[nCountLetter].aConv, "%s", ptr);	
													nCountLetter++;
												}
											}
										}

										nCountConv++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		assert(false);

		// �������I������
		return;
	}
}