//========================================
//
// �X�R�A����
//
//========================================
// *** score2D.cpp ***
//========================================
#include "time.h"
#include "../model/block.h"
#include "../../scene/game.h"
#include "../../scene/title.h"
#include "../../scene/pause.h"
#include "../../system/words/text.h"
#include "../../system/words/words.h"
#include "../../system/words/font.h"

//========================================
// �R���X�g���N�^
//========================================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	m_nTime = 0;			// ����
	m_nTimeMax  = 0;		// ���Ԃ̍ő�l
	m_nCounter = 0;			// �J�E���^�[
	m_Digit = 0;			// ����
	m_bSetTime = false;		// �ݒ�t���O
	m_bUpdateTime = false;	// �X�V�t���O
	m_Time = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CTime::~CTime(void)
{

}

//========================================
// ��������
//========================================
CTime *CTime::Create(int nTime)
{
	CTime *pTime = new CTime;

	 // ����������
	pTime->Init();
	pTime->SetTime(nTime);

	return pTime;
}

//========================================
// ����������
//========================================
HRESULT CTime::Init(void)
{
	m_nTime = 0;	// �^�C��
	m_nCounter = 0;	// �J�E���^�[
	m_nNumWarn = 0;

	// ��ސݒ�
	SetType(TYPE_TIME);

	return S_OK;
}

//========================================
// �I������
//========================================
void CTime::Uninit(void)
{
	if (m_Time != NULL)
	{
		m_Time = NULL;
	}
}

//========================================
// �X�V����
//========================================
void CTime::Update(void)
{
	bool bStart = CTitle::IsStart();
	
	if (bStart)
	{
		bool bPause = CPause::IsPause();
		bool bTime = CGame::IsTime();

		if (!bPause && !bTime)
		{
			if (m_nTime > 0)
			{// �^�C����0�ȏ�̎��A

				// �J�E���^�[��0�ɂȂ������A
				m_nCounter = (m_nCounter + 1) % 60;
				if (m_nCounter == 0)
				{
					m_nTime--;			// �^�C�������Z
					SetTime(m_nTime);	// �^�C���ݒ�
				}
			}
		}

		// �e�L�X�g�̍X�V
		if (m_bUpdateTime)
		{
			// �^�C���𕶎���ɐݒ�
			char aTime[TXT_MAX];
			int nNumSet = 0;
			D3DXCOLOR col;

			sprintf(aTime, "%02d", m_nTime);

			// �������擾
			m_Digit = strlen(aTime);

			int n = (m_nTimeMax * 2) / 3;

			if (m_nTime <= 0)
			{
				col = D3DXCOLOR(0.45f, 0.45f, 0.45f, 1.0f);
			}
			else if (m_nTime <= m_nTimeMax / 3)
			{
				col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else if (m_nTime <= (m_nTimeMax * 2) / 3)
			{
				col = D3DXCOLOR(0.9f, 0.9f, 0.0f, 1.0f);
			}
			else if (m_nTime < m_nTimeMax)
			{
				col = INIT_D3DXCOLOR;
			}

			for (int nTime = 0; nTime < m_Digit; nTime++)
			{
				if (m_Time->ChgWords(&aTime[nTime], TIME_START_DEX + nTime, col))
				{
					nNumSet++;
				}
			}

			if (nNumSet == m_Digit)
			{
				m_bUpdateTime = false;
			}
		}

		// �x���e�L�X�g�̕\��
		{
			// �c�莞�Ԃ��e�L�X�g�ɐݒ�
			char aString[TXT_MAX];
			sprintf(aString, "�c�� %02d�b�I�I", m_nTime);
			D3DXCOLOR col;

			FormFont pFont = { INIT_D3DXCOLOR,20.0f,1,60,60 };
			FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),true,D3DXVECTOR3(2.0f,2.0f,0.0f),D3DXVECTOR2(1.0f,1.0f) };

			if (m_nTime == m_nTimeMax / 3 && m_nNumWarn == 1)
			{
				CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 50.0f, 0.0f), D3DXVECTOR2(350.0f, 100.0f),
					aString, CFont::FONT_BESTTEN, &pFont, true, &pShadow);
				m_nNumWarn++;
			}
			else if (m_nTime == m_nTimeMax * 2 / 3 && m_nNumWarn == 0)
			{
				CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 50.0f, 0.0f), D3DXVECTOR2(350.0f, 100.0f),
					aString, CFont::FONT_BESTTEN, &pFont, true, &pShadow);
				m_nNumWarn++;
			}
		}
	}
}

//========================================
// �`�揈��
//========================================
void CTime::Draw(void)
{

}

//========================================
// �ݒ�
//========================================
void CTime::SetTime(int nTime)
{
	// ���Ԑݒ�
	if (!m_bSetTime)
	{
		// �^�C�����
		m_nTime = nTime;
		m_nTimeMax = nTime;

		// �^�C���𕶎���ɐݒ�
		char aString[TXT_MAX];
		sprintf(aString, "TIME �F%02d", m_nTime);

		FormFont pFont = {
			INIT_D3DXCOLOR,
			11.0f,
			1,
			10,
			-1
		};

		FormShadow pShadow = {
			D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),
			true,
			D3DXVECTOR3(2.0f,2.0f,0.0f),
			D3DXVECTOR2(1.0f,1.0f)
		};

		m_Time = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(SCREEN_WIDTH - 290.0f, 21.0f, 0.0f),
			D3DXVECTOR2(0.0f, 0.0f),
			aString,
			CFont::FONT_BESTTEN,
			&pFont,false,&pShadow);

		m_bSetTime = true;
	}
	else
	{
		m_bUpdateTime = true;
	}
}