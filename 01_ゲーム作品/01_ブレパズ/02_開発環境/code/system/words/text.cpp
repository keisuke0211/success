//========================================
// 
// �e�L�X�g�\��
// 
//========================================
// *** text.cpp ***
//========================================
#include "text.h"
#include "../../scene/pause.h"
#include "../../object/object.h"
#include "../../system/texture.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../scene/pause.h"

//========================================
// �R���X�g���N�^
//========================================
CText::CText(int nPriority) : CObject2D(nPriority)
{
	m_Info.TextBoxCol = INIT_D3DXCOLOR;
	m_Info.FontCol = INIT_D3DXCOLOR;
	m_Info.TextBoxColOld = INIT_D3DXCOLOR;
	m_Info.FontColOld = INIT_D3DXCOLOR;
	m_Info.bCol = false;

	m_Info.fTextSize = 0.0f;
	m_Info.nTextLength = 0;
	m_Info.nAppearTime = 0;
	m_Info.nAddCount = 0;
	m_Info.nAddLetter = 0;
	m_Info.nLetterPopCount = 0;
	m_Info.nLetterPopCountX = 0;
	m_Info.nNiCount = 0;

	m_Info.nStandTime = 0;
	m_Info.bStand = false;

	m_Info.nDisapTime = 0;
	m_Info.nDisapTimeMax = 0;
	m_Info.bRelease = false;

	m_Info.bTextBok = true;
	m_Info.bPause = false;
	m_Info.bSpace = false;

	m_Info.aShadow.col = INIT_D3DXCOLOR;
	m_Info.aShadow.AddPos = INIT_D3DXVECTOR3;
	m_Info.aShadow.AddSize = INIT_D3DXVECTOR2;
	m_Info.aShadow.bShadow = false;
}

//========================================
// �f�X�g���N�^
//========================================
CText::~CText()
{

}

//================================================================================
//--------------------------------------------------------------------------------
//********************************** ���C������ **********************************
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// ������
//========================================
HRESULT CText::Init()
{
	m_Info.TextBoxCol = INIT_D3DXCOLOR;
	m_Info.FontCol = INIT_D3DXCOLOR;
	m_Info.TextBoxColOld = INIT_D3DXCOLOR;
	m_Info.FontColOld = INIT_D3DXCOLOR;
	m_Info.bCol = false;
	m_Info.fTextSize = 0.0f;
	m_Info.nTextLength = 0;
	m_Info.nAppearTime = 0;
	m_Info.nAddCount = 0;
	m_Info.nAddLetter = 0;
	m_Info.nLetterPopCount = 0;
	m_Info.nLetterPopCountX = 0;
	m_Info.nNiCount = 0;
	m_Info.sText = "";

	SetType(TYPE_FONT);

	CObject2D::Init();

	SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	m_Info.nStandTime = 0;
	m_Info.bStand = false;

	m_Info.nDisapTime = 0;
	m_Info.nDisapTimeMax = 0;
	m_Info.bRelease = false;
	m_Info.bPause = false;

	return S_OK;
}

//========================================
// �I��
//========================================
void CText::Uninit()
{
	// �����̍폜
	for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
	{
		if (m_Info.words[wordsCount] != NULL)
		{
			m_Info.words[wordsCount]->Uninit();
		}
	}
	delete[] m_Info.words;
	m_Info.words = NULL;

	if (m_Info.aShadow.bShadow)
	{
		for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
		{
			if (m_Info.aShadow.shadow[wordsCount] != NULL)
			{
				m_Info.aShadow.shadow[wordsCount]->Uninit();
			}
		}

		delete[] m_Info.aShadow.shadow;
		m_Info.aShadow.shadow = NULL;
	}

	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CText::Update()
{
	bool bPause = CPause::IsPause();

	if (!m_Info.bPause && bPause)
	{
		if (!m_Info.bCol)
		{
			if (m_Info.bTextBok)
			{
				m_Info.TextBoxColOld = m_Info.TextBoxCol;
				SetBoxColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
				CObject2D::SetColar(m_Info.TextBoxCol);
			}
			m_Info.FontColOld = m_Info.FontCol;
			SetTextColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_Info.bCol = true;
		}
		return;
	}
	else if(m_Info.bCol && !bPause)
	{
		if (m_Info.bTextBok)
		{
			SetBoxColor(m_Info.TextBoxColOld);
			CObject2D::SetColar(m_Info.TextBoxCol);
		}
		SetTextColor(m_Info.FontColOld);
		m_Info.bCol = false;
	}

	// �e�L�X�g����
	if (!m_Info.bStand)
	{
		if (CScene::GetMode() == CScene::MODE_GAME && !m_Info.bPause && bPause)
		{
			return;
		}

		LetterForm();
	}

	// �ҋ@����
	StandTime();

	// �폜����
	DisapTime();
}

//========================================
// �`��
//========================================
void CText::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	// �V�K�[�x�l <= Z�o�b�t�@�[�x�l (�����ݒ�)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//========================================
// ����
//========================================
CText *CText::Create(Box type, D3DXVECTOR3 pos, D3DXVECTOR2 size, const char *Text, CFont::FONT FontType, FormFont *pFont, bool bTextBok, FormShadow *Shadow)
{
	CText *pText = new CText;

	if (pText != NULL)
	{
		pText->Init();

		// -- ���b�Z�[�W�{�b�N�X ----------------

		// �e�N�X�`���ݒ�
		switch (type)
		{
		case CText::BOX_NORMAL_RECT:
			pText->BindTexture(CTexture::TEX_TEXBOX);
			break;
		case CText::BOX_NORMAL_SQR:
			pText->BindTexture(CTexture::TEX_TEXBOX1);
			break;
		case CText::BOX_MAX:
			pText->BindTexture(-1);
			break;
		default:
			break;
		}
		pText->SetPos(pos);
		pText->SetSize(size.x, size.y);

		pText->m_Info.bTextBok = bTextBok;
		if (!pText->m_Info.bTextBok)
		{
			pText->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}

		// -- �e�L�X�g -----------------------
		pText->m_Info.FontType = FontType;

		if (pFont != NULL)
		{
			pText->m_Info.FontCol = pFont->col;
			pText->SetTextSize(pFont->fTextSize);
			pText->SetStandTime(pFont->nStandTime);
			pText->EraseTime(pFont->nEraseTime);
			pText->TextLetter(Text, pFont->nAppearTime);
		}
		else if (pFont == NULL)
		{
			pText->m_Info.FontCol = INIT_D3DXCOLOR;
			pText->SetTextSize(20.0f);
			pText->SetStandTime(10);
			pText->EraseTime(1);
			pText->TextLetter(Text, 1);
		}

		if (Shadow == NULL)
		{
			pText->m_Info.aShadow.col = INIT_D3DXCOLOR;
			pText->m_Info.aShadow.AddPos = INIT_D3DXVECTOR3;
			pText->m_Info.aShadow.AddSize = INIT_D3DXVECTOR2;
			pText->m_Info.aShadow.bShadow = false;
		}
		else if (Shadow != NULL)
		{
			if (Shadow->bShadow)
			{
				pText->m_Info.aShadow.shadow = new CWords*[pText->m_Info.nTextLength];

				for (int wordsCount = 0; wordsCount < pText->m_Info.nTextLength; wordsCount++)
				{
					pText->m_Info.aShadow.shadow[wordsCount] = NULL;
				}

				pText->m_Info.aShadow.col = Shadow->col;
				pText->m_Info.aShadow.AddPos = Shadow->AddPos;
				pText->m_Info.aShadow.AddSize = Shadow->AddSize;
				pText->m_Info.aShadow.bShadow = Shadow->bShadow;
			}
		}
	}

	return pText;
}

//================================================================================
//--------------------------------------------------------------------------------
//********************************** ���̑����� **********************************
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// ��������
//========================================
void CText::LetterForm(void)
{
	float fTxtSize = m_Info.fTextSize;

	if (++m_Info.nAddCount >= m_Info.nAppearTime)
	{// �\�����鎞�Ԃ���������A

		if (m_Info.nAddLetter <= m_Info.nTextLength)
		{// �e�L�X�g�T�C�Y��������Ă���A

			m_Info.sText += m_Info.sALLText[m_Info.nAddLetter];
			string Text = m_Info.sText;
			D3DXVECTOR3 pos = GetPos();

			pos.x = pos.x - (GetWidth() / 2);

			if (Text != "" && m_Info.nAddLetter < m_Info.nTextLength)
			{// �󔒂���Ȃ�������A && �e�L�X�g�T�C�Y��������Ă���A

				if (CheckLeadByte(m_Info.sALLText[m_Info.nAddLetter]))
				{// 1�o�C�g�������V�t�gJIS��������A

					m_Info.nAddLetter++;
					m_Info.sText += m_Info.sALLText[m_Info.nAddLetter];
					m_Info.nAddLetter++;

					// �e
					if (m_Info.aShadow.bShadow)
					{
						D3DXVECTOR3 AddPos = m_Info.aShadow.AddPos;
						D3DXVECTOR2 AddSize = m_Info.aShadow.AddSize;

						m_Info.aShadow.shadow[m_Info.nLetterPopCount] = CWords::Create(m_Info.sText.c_str(),
							D3DXVECTOR3((pos.x + (10.0f + AddPos.x)) + ((fTxtSize * 2) * (m_Info.nLetterPopCountX + 1)), (pos.y + AddPos.y) + m_Info.nNiCount * 40.0f, pos.z),
							D3DXVECTOR3(fTxtSize + AddSize.x, fTxtSize + AddSize.y, 0.0f),
							m_Info.FontType, m_Info.aShadow.col);
					}

					m_Info.words[m_Info.nLetterPopCount] = CWords::Create(m_Info.sText.c_str(),
						D3DXVECTOR3((pos.x + 10.0f) + ((fTxtSize * 2) * (m_Info.nLetterPopCountX + 1)), pos.y + m_Info.nNiCount*40.0f, pos.z),
						D3DXVECTOR3(fTxtSize, fTxtSize, 0.0f),
						m_Info.FontType,m_Info.FontCol);

					m_Info.nLetterPopCount++;
					m_Info.nLetterPopCountX++;
				}
				else
				{
					if (m_Info.sText != "\n")
					{// �I�[�����Ȃ�A

						m_Info.nAddLetter++;

						if (m_Info.bSpace && m_Info.sText == " ")
						{
							m_Info.nLetterPopCount++;
							m_Info.nLetterPopCountX++;
							m_Info.sText = "";
							m_Info.nAddCount = 0;
							return;
						}

						// �e
						if (m_Info.aShadow.bShadow)
						{
							D3DXVECTOR3 AddPos = m_Info.aShadow.AddPos;
							D3DXVECTOR2 AddSize = m_Info.aShadow.AddSize;

							m_Info.aShadow.shadow[m_Info.nLetterPopCount] = CWords::Create(m_Info.sText.c_str(),
								D3DXVECTOR3((pos.x + (10.0f + AddPos.x)) + ((fTxtSize * 2) * (m_Info.nLetterPopCountX + 1)), (pos.y + AddPos.y) + m_Info.nNiCount * 40.0f, pos.z),
								D3DXVECTOR3(fTxtSize + AddSize.x, fTxtSize + AddSize.y, 0.0f),
								m_Info.FontType, m_Info.aShadow.col);
						}

						m_Info.words[m_Info.nLetterPopCount] = CWords::Create(m_Info.sText.c_str(),
							D3DXVECTOR3((pos.x + 10.0f) + ((fTxtSize * 2) * (m_Info.nLetterPopCountX + 1)), pos.y + m_Info.nNiCount*40.0f, pos.z),
							D3DXVECTOR3(fTxtSize, fTxtSize, 0.0f),
							m_Info.FontType,m_Info.FontCol);

						m_Info.nLetterPopCount++;
						m_Info.nLetterPopCountX++;
					}
					else
					{
						m_Info.nLetterPopCountX = 0;
						m_Info.nAddLetter++;
						m_Info.nNiCount++;
					}
				}
			}
			else
			{
				m_Info.bStand = true;
			}
		}

		m_Info.sText = "";
		m_Info.nAddCount = 0;
	}
}

//========================================
// �ҋ@
//========================================
void CText::StandTime(void)
{
	if (m_Info.bStand && m_Info.nStandTime >= 1)
	{
		if (--m_Info.nStandTime <= 0)
		{
			if (m_Info.nDisapTimeMax >= 1)
			{
				m_Info.bRelease = true;
			}
		}
	}
}

//========================================
// �폜
//========================================
void CText::DisapTime(void)
{
	if (m_Info.bRelease)
	{
		if (--m_Info.nDisapTime <= 0)
		{
			Uninit();
			return;
		}

		// �F�̐���
		m_Info.TextBoxCol.a *= ((float)m_Info.nDisapTime / m_Info.nDisapTimeMax);
		m_Info.FontCol.a *= ((float)m_Info.nDisapTime / m_Info.nDisapTimeMax);

		// �����F�̐���
		for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
		{
			if (m_Info.words[wordsCount] != NULL)
			{
				m_Info.words[wordsCount]->SetColar(m_Info.FontCol);
			}
		}

		if (m_Info.aShadow.bShadow)
		{
			m_Info.aShadow.col.a *= ((float)m_Info.nDisapTime / m_Info.nDisapTimeMax);

			for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
			{
				if (m_Info.aShadow.shadow[wordsCount] != NULL)
				{
					m_Info.aShadow.shadow[wordsCount]->SetColar(m_Info.aShadow.col);
				}
			}
		}
	}

	if (m_Info.bTextBok)
	{
		CObject2D::SetColar(m_Info.TextBoxCol);
	}
	CObject2D::Update();
}

//================================================================================
//--------------------------------------------------------------------------------
//*********************************** �ݒ菈�� ***********************************
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// �����T�C�Y
//========================================
void CText::SetTextSize(float TextSize)
{
	if (TextSize <= 1.0f)
	{
		TextSize = 1.0f;
	}
	m_Info.fTextSize = TextSize;
}

//========================================
// �ҋ@����
//========================================
void CText::SetStandTime(int StandTime)
{
	if (StandTime <= 0)
	{
		StandTime = 0;
	}
	m_Info.nStandTime = StandTime;
}

//========================================
// �����܂ł̎���
//========================================
void CText::EraseTime(int Time)
{
	if (Time <= 0)
	{
		Time = 0;
	}
	m_Info.nDisapTime = Time;
	m_Info.nDisapTimeMax = m_Info.nDisapTime;
}

//========================================
// �\������܂ł̎���
//========================================
void CText::TextLetter(const char * Text, int AppearTime)
{
	m_Info.sALLText = Text;
	m_Info.nTextLength = m_Info.sALLText.size();
	m_Info.nAddCount = AppearTime;
	m_Info.nAppearTime = m_Info.nAddCount;
	m_Info.nAddLetter = 0;
	m_Info.words = new CWords*[m_Info.nTextLength];

	for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
	{
		m_Info.words[wordsCount] = NULL;
	}
}

//========================================
// �폜�t���O
//========================================
void CText::Disap(bool bDisap, int nTime)
{
	m_Info.bRelease = bDisap;
	EraseTime(nTime);
}

//=============================================
// 1�o�C�g�������V�t�gJIS���ǂ������肷��֐�
//=============================================
bool CText::CheckLeadByte(int nLetter)
{
	return (((nLetter & 0xffu) ^ 0x20u) - 0xa1) < 94u / 2;
}

//========================================
// �|�[�Y���ł��e�L�X�g�������邩
//========================================
void CText::SetTetPause(bool bPause)
{
	m_Info.bPause = bPause;
}

//========================================
// ���b�Z�[�W�{�b�N�X�̐F�ݒ�
//========================================
void CText::SetBoxColor(D3DXCOLOR col)
{
	m_Info.TextBoxCol = col;
}

//========================================
// �e�L�X�g�̐F�ݒ�
//========================================
bool CText::SetTextColor(D3DXCOLOR col)
{

	for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
	{
		if (m_Info.words[wordsCount] != NULL)
		{
			m_Info.words[wordsCount]->SetColar(col);
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

//========================================
// �����ύX(�P��)
//========================================
bool CText::ChgWords(char* Text, int nIdx, D3DXCOLOR col)
{
	if (m_Info.words[nIdx] != NULL)
	{
		float fTxtSize = m_Info.fTextSize;
		D3DXVECTOR3 pos = m_Info.words[nIdx]->GetPos();

		m_Info.words[nIdx]->Uninit();

		// �e�̍Đ���
		if (m_Info.aShadow.bShadow)
		{
			D3DXVECTOR3 AddPos = m_Info.aShadow.AddPos;
			D3DXVECTOR2 AddSize = m_Info.aShadow.AddSize;
			D3DXCOLOR ShadowCol = m_Info.aShadow.col;

			m_Info.aShadow.shadow[nIdx]->Uninit();

			if (Text != NULL)
			{
				m_Info.aShadow.shadow[nIdx] = CWords::Create(Text,
					D3DXVECTOR3(pos.x + AddPos.x, pos.y + AddPos.y, pos.z + AddPos.z),
					D3DXVECTOR3(fTxtSize + AddSize.x, fTxtSize + AddSize.y, 0.0f),
					m_Info.FontType, ShadowCol);
			}
		}

		// �e�L�X�g�̍Đ���
		if (Text != NULL)
		{
			m_Info.words[nIdx] = CWords::Create(Text,
				pos,
				D3DXVECTOR3(fTxtSize, fTxtSize, 0.0f),
				m_Info.FontType, col);
		}

		return TRUE;
	}
	return FALSE;
}

//========================================
// �����ύX(�S��)�@���p�̂�
//========================================
bool CText::ChgText(char* Text, D3DXCOLOR col)
{
	int nDigit = strlen(Text);
	char aString[TXT_MAX];

	sprintf(aString,Text);

	if (m_Info.words != NULL)
	{
		if (nDigit <= m_Info.nLetterPopCount)
		{
			for (int nIdx = 0; nIdx < nDigit; nIdx++)
			{
				if (!ChgWords(&aString[nIdx], nIdx, col))
				{
					return FALSE;
				}
			}

			int nRest = m_Info.nLetterPopCount - nDigit;

			if (nRest > 0)
			{
				for (int nIdx = 0; nIdx < nRest; nIdx++)
				{
					int nCntRest = nIdx + nDigit;

					if (!ChgWords("", nCntRest, col))
					{
						return FALSE;
					}
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}