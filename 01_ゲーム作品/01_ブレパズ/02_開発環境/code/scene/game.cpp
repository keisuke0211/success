//========================================
// 
// �Q�[��
// 
//========================================
// *** game.cpp ***
//========================================
#include "title.h"
#include "game.h"
#include "ranking.h"
#include "../system/csv_file.h"
#include "../object\model\block.h"
#include "../object/model/bullet.h"
#include "../object/model/enemy.h"
#include "../object/model/bullet_cube.h"
#include "../object\model\player.h"
#include "../object\model\enemy.h"
#include "../object\BG\bg_side.h"
#include "../object\BG\bg_ceiling.h"
#include "../object/BG/mesh_floor.h"
#include "../object/BG/blackout.h"
#include "../object\UI\score.h"
#include "../object\UI\time.h"
#include "../object/UI/crown.h"
#include "../system/input.h"
#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/camera.h"
#include "../system/sound.h"
#include "../scene/pause.h"
#include "../object/model/model.h"
#include "fade.h"

// �ÓI�ϐ�
CPlayer *CGame::m_pPlayer = NULL;
CTime *CGame::m_pTime = NULL;
CScore *CGame::m_pScore = NULL;
bool CGame::m_bTime = false;
bool CGame::m_bEnd = false;
bool CGame::m_bGemeOver = false;
int CGame::m_nStage = STAGE_00;
int CGame::m_nSelectStage = STAGE_00;
int CGame::m_nScore = 0;
CGame::StageInfo CGame::m_aStageInfo = { NULL,NULL };

const char* CGame::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE_DATA.txt";
const char* CGame::SIDE_STAGE_FILE = "data\\GAMEDATA\\OBJECT\\SIDE_DATA .txt";
const char* CGame::FLOOR_STAGE_FILE = "data\\GAMEDATA\\OBJECT\\FLOOR_DATA.txt";

//========================================
// �R���X�g���N�^
//========================================
CGame::CGame()
{
	m_rot = INIT_D3DXVECTOR3;
	m_nMoveRot = INIT_FLOAT;
	m_nStartTime = 0;
	m_nEndTime = 0;
	m_nRstStgType = 0;
	m_nTextCreate = 0;

	m_nTimeTotal = 0;
	m_nClearTotal = 0;
	m_nTotal = 0;
	m_nAddTime = 0;
	m_nStandTime = -1;
	m_nEveGame = 1;
	m_bAddScore = false;

	m_bSpecial = false;
	m_bTime = false;
	m_bEnd = false;
	m_bGemeOver = false;


	for (int nRst = 0; nRst < RST_ADD_SCORE; nRst++)
	{
		m_RstText[nRst] = NULL;
	}
}

//========================================
// �f�X�g���N�^
//========================================
CGame::~CGame()
{

}

//========================================
// ������
//========================================
HRESULT CGame::Init(void)
{
	CEnemy::Reset();
	CBullet::Reset();
	CCube::Reset();

	CBlock::Load();			// �u���b�N
	CModel::InitModel();	// ���f��

	m_rot = INIT_D3DXVECTOR3;
	m_nStartTime = 0;
	m_nEndTime = 0;
	m_bEnd = false;
	m_bGemeOver = false;
	m_bTime = false;

	m_nRstStgType = 0;
	m_nTextCreate = 0;
	m_nTimeTotal = 0;
	m_nClearTotal = 0;
	m_nEveGame = 0;
	m_nTotal = 0;
	m_nAddTime = ADDTIME_MAX;

	CTitle::SetStart(false);
	CTitle::SetClear(false);

	// �w�i(����)�̐���
	LoodSide();

	// �w�i(�V��)�̐���
	LoodCeiling();

	// ���̐���
	LoodFloor();

	// �u���b�N�̐���
	LoodBlock();

	CCamera *pCamera = CManager::GetCamera();					// �J����
	pCamera->Init();
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetHeigth(0.4f);
	pCamera->SetDistance(1400.0f);

	CPlayer *pPlayer = CPlayer::Create(m_aStageInfo.PlayerPos[m_nStage], m_aStageInfo.PlayerRot[m_nStage]);
	pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// �G�̐���
	LoodEnemy();

	// �L���[�u�̎g�p��
	CCube::SetLimit(m_aStageInfo.nCube[m_nStage]);

	// �^�C������
	m_pTime = CTime::Create(m_aStageInfo.nTime[m_nStage]);

	// �X�R�A����
	m_pScore = CScore::Create();
	CScore::SetScore(m_nScore);

	FormFont pFont = { INIT_D3DXCOLOR,20.0f,10,60,30 };

	FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),true,D3DXVECTOR3(2.0f,2.0f,0.0f),D3DXVECTOR2(1.0f,1.0f) };

	int nCntText = 0;
	char aString[TXT_MAX];
	char aCube[TXT_MAX];

	// �ǂݍ���
	if (m_nStage != STAGE_04)
	{
		sprintf(aString, "STAGE %d", m_nStage + 1);
	}
	else if (m_nStage == STAGE_04)
	{
		sprintf(aString, "LAST STAGE", m_nStage + 1);
	}
	sprintf(aCube, "CUBE  %d", m_aStageInfo.nCube[m_nStage]);

	int nStrlen = strlen(aString);

	CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 325.0f, 0.0f), D3DXVECTOR2(440.0f, 100.0f),
		aString, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

	CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 375.0f, 0.0f), D3DXVECTOR2(440.0f, 100.0f),
		aCube, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

	m_nStartTime = (nStrlen * 10) + 60 + 10;
	m_nMoveRot = ((D3DX_PI * 2) / m_nStartTime);

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::TYPE_GAME01);

	return S_OK;
}

//========================================
// �I��
//========================================
void CGame::Uninit(void)
{
	CBlock::Reset();
	CModel::UninitModel();

	CObject::ReleaseAll(CObject::TYPE_BG);
	CObject::ReleaseAll(CObject::TYPE_BLOCK);
	CObject::ReleaseAll(CObject::TYPE_CUBE);
	CObject::ReleaseAll(CObject::TYPE_PLAYER);
	CObject::ReleaseAll(CObject::TYPE_ENEMY);
	CObject::ReleaseAll(CObject::TYPE_BULLET);
	CObject::ReleaseAll(CObject::TYPE_EFFECT);
	CObject::ReleaseAll(CObject::TYPE_PARTICLE);
	CObject::ReleaseAll(CObject::TYPE_TIME);
	CObject::ReleaseAll(CObject::TYPE_SCORE);
	CObject::ReleaseAll(CObject::TYPE_FONT);

	CSound *pSound = CManager::GetSound();
	pSound->StopSound();
}

//========================================
// �X�V
//========================================
void CGame::Update(void)
{
	// -- �擾 -------------------------------------------
	CCamera *pCamera = CManager::GetCamera();					// �J����
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

																// �|�[�Y
	if (!m_bEnd)
	{
		if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_START))
		{
			CPause::SetPause(true);
		}
	}

	// �J�n�t���O
	{
		bool bStart = CTitle::IsStart();
		if (!bStart)
		{
			// �J�����̒����_��ݒ�
			pCamera->SetPosR(D3DXVECTOR3(0.0f, 95.0f, 0.0f));
			if (--m_nStartTime <= 0)
			{
				pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pCamera->SetHeigth(0.4f);
				pCamera->SetDistance(500.0f);
				CTitle::SetStart(true);
			}
		}
	}

	// �G�l�~�[�̑S��
	{
		bool bClear = CTitle::IsClear();
		if (!bClear && CEnemy::GetEnemyAll() <= 0)
		{
			CTitle::SetClear(true);
		}
	}

	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		// CLEAR
		{
			bool bClear = CTitle::IsClear();
			int nCubeRest = CCube::GetRest();

			if (bClear)
			{// �Q�[���N���A
				if (!m_bEnd || (m_bEnd && bClear && m_bGemeOver && m_nEndTime <= 0))
				{
					char aString[TXT_MAX];
					D3DXCOLOR color, ShadowColor;
					if (m_bEnd && bClear && m_bGemeOver && m_pTime->GetTime() <= 0)
					{
						m_bSpecial = true;
						sprintf(aString, "LIMIT CLEAR");
						color = D3DXCOLOR(0.02f, 0.6f, 1.0f, 1);
						ShadowColor = INIT_D3DXCOLOR;
					}
					else
					{
						sprintf(aString, "STAGE CLEAR");
						color = D3DXCOLOR(1.0f, 0.96f, 0, 1);
						ShadowColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					}

					m_bEnd = true;

					FormFont pFont = { color,20.0f,7,60,30 };
					FormShadow pShadow = { ShadowColor,true,D3DXVECTOR3(2.0f,2.0f,0.0f),D3DXVECTOR2(1.0f,1.0f) };

					CText::Create(CText::BOX_NORMAL_RECT,
						D3DXVECTOR3(640.0f, 300.0f, 0.0f),
						D3DXVECTOR2(440.0f, 100.0f),
						aString,
						CFont::FONT_BESTTEN,
						&pFont, false, &pShadow);

					int nLength = strlen(aString);

					m_nEndTime = (nLength * 7) + 60 + 15;
					m_bEnd = true;
					m_bTime = true;
					m_bGemeOver = false;
				}
				else
				{
					if (--m_nEndTime <= 0 && !m_bGemeOver)
					{
						// ���U���g���o
						Result();
					}
				}
			}
			else if (!bClear && (m_pTime->GetTime() <= 0 || nCubeRest <= 0))
			{// �Q�[���I�[�o�[
				if (!m_bEnd && m_nStandTime == -1)
				{
					m_nStandTime = 30;
				}
				else if (!m_bEnd && --m_nStandTime <= 0)
				{
					FormFont pFont = { D3DXCOLOR(0.7f,0.0f,0.0f,1),20.0f,8,60,30 };
					FormShadow pShadow = { D3DXCOLOR(0.1f,0.1f,0.1f,1),true,D3DXVECTOR3(2.0f,2.0f,0.0f),D3DXVECTOR2(1.0f,1.0f) };

					CText::Create(CText::BOX_NORMAL_RECT,
						D3DXVECTOR3(640.0f, 300.0f, 0.0f),
						D3DXVECTOR2(440.0f, 100.0f),
						"GAME OVER",
						CFont::FONT_BESTTEN,
						&pFont, false, &pShadow);

					m_nEndTime = (7 * 8) + 60 + 15;
					m_bEnd = true;
					m_bTime = true;
					m_bGemeOver = true;
				}
				else if (m_bEnd)
				{
					if (--m_nEndTime <= 0)
					{
						CManager::GetFade()->SetFade(MODE_RANKING);
						CRanking::SetScore11(m_nScore);
						CRanking::SetAllStage(false);
					}
				}
			}

		}
	}
}

//========================================
// �`��
//========================================
void CGame::Draw(void)
{

}

//========================================
// ����
//========================================
CGame *CGame::Create(void)
{
	CGame *pGame = new CGame;

	pGame->Init();

	return pGame;
}

//========================================
// ���U���g���o
//========================================
void CGame::Result(void)
{
	FormFont pFont = { INIT_D3DXCOLOR, 18.0f, 2, 5, 0 };
	FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f), true, D3DXVECTOR3(2.0f,2.0f,0.0f), D3DXVECTOR2(2.0f,2.0f) };

	char aString[TXT_MAX];
	int nLength = 0;
	D3DXVECTOR3 pos = INIT_D3DXVECTOR3;

	switch (m_nRstStgType)
	{
	case RST_TEXT:
	{
		CBlackout::Create();
		if (!m_bSpecial)
		{
			sprintf(aString, "STAGE CLEAR RESULT BONUS");
		}
		else
		{
			sprintf(aString, "LIMIT CLEAR RESULT BONUS");
		}
		pos = D3DXVECTOR3(23.0f, 105.0f, 0.0f);

		int nUseCube = CCube::GetRest();
		int nPerfCube = m_aStageInfo.nCube[m_nStage];

		m_nEveGame = EVE_PERFECT;
	}
	break;
	case RST_TIME:
	{
		if (!m_bSpecial)
		{
			sprintf(aString, "TIME BONUS");
			CCrown::Create(m_nEveGame);
		}
		else
		{
			sprintf(aString, "CUBE BONUS");
		}
		pos = D3DXVECTOR3(100.0f, 190.0f, 0.0f);
	}
	break;
	case RST_TIME_CALC:
	{
		int nTime = m_pTime->GetTime();
		if (!m_bSpecial)
		{
			m_nTimeTotal = TIME_SCORE * nTime;
			sprintf(aString, "%d * %d = %d", TIME_SCORE, nTime, m_nTimeTotal);
		}
		else
		{
			nTime = CCube::GetRest();
			m_nTimeTotal = CUBE_SCORE * nTime;
			sprintf(aString, "%d * %d = %d", CUBE_SCORE, nTime, m_nTimeTotal);
		}
		pos = D3DXVECTOR3(100.0f, 260.0f, 0.0f);
	}
	break;
	case RST_CLEAR:
	{
		if (!m_bSpecial)
		{
			sprintf(aString, "STAGE CLEAR BONUS");
		}
		else
		{
			sprintf(aString, "LIMIT CLEAR BONUS");
		}
		pos = D3DXVECTOR3(100.0f, 340.0f, 0.0f);
	}
	break;
	case RST_CLEAR_CALC:
	{
		int nClear = m_aStageInfo.nClearBonus[m_nStage];

		int nPerfCube = m_aStageInfo.nCube[m_nStage];

		if (!m_bSpecial)
		{
			m_nClearTotal = nClear;
		}
		else
		{
			m_nClearTotal = nClear * (m_nStage + 2);
		}

		sprintf(aString, "%d", m_nClearTotal);
		pos = D3DXVECTOR3(100.0f, 410.0f, 0.0f);
	}
	break;
	case RST_BONUS:
	{
		sprintf(aString, "TOTAL BONUS");
		pos = D3DXVECTOR3(100.0f, 500.0f, 0.0f);
	}
	break;
	case RST_BONUS_CALC:
	{

		m_nTotal = m_nTimeTotal + m_nClearTotal;

		sprintf(aString, "%d", m_nTotal);
		pos = D3DXVECTOR3(100.0f, 550.0f, 0.0f);
	}
	break;
	case RST_ADD_SCORE:
	{
		if (m_bAddScore)
		{
			if (m_nTotal <= 0)
			{
				CSound *pSound = CManager::GetSound();
				pSound->StopSoundType(CSound::SOUND_TYPE_SE);

				if (++m_nStage < STAGE_MAX)
				{
					char aString[TXT_MAX];

					if (m_nStage != (STAGE_MAX - 1))
					{
						sprintf(aString, "NEXT��STAGE%d", m_nStage + 1);
						pos = D3DXVECTOR3(1000.0f, 650.0f, 0.0f);
					}
					else if (m_nStage == (STAGE_MAX - 1))
					{
						sprintf(aString, "NEXT��LAST STAGE", m_nStage + 1);
						pos = D3DXVECTOR3(900.0f, 650.0f, 0.0f);
					}
					int nStrlen = strlen(aString);

					CText::Create(CText::BOX_NORMAL_RECT,
						pos, D3DXVECTOR2(440.0f, 100.0f),
						aString, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

					m_nStandTime = (nStrlen * 2) + 30 + 10;
				}
				else if (m_nStage >= STAGE_MAX)
				{
					char aString[TXT_MAX];
					sprintf(aString, "NEXT��RANKING");

					int nStrlen = strlen(aString);

					CText::Create(CText::BOX_NORMAL_RECT,
						D3DXVECTOR3(1000.0f, 650.0f, 0.0f), D3DXVECTOR2(440.0f, 100.0f),
						aString, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

					m_nStandTime = 90;
				}

				m_nRstStgType++;
			}
			else
			{
				int AddScore;
				AddScore = (m_nTotal / m_nAddTime);
				m_nTotal -= AddScore;
				m_nAddTime--;

				if (m_nTotal <= 0)
				{
					m_nTotal = 0;
					AddScore = AddScore - m_nTotal;
				}

				CScore::SetScore(AddScore);

				char aTotal[TXT_MAX];

				sprintf(aTotal, "%d", m_nTotal);
				m_RstText[RST_BONUS_CALC]->ChgText(aTotal, INIT_D3DXCOLOR);
			}
		}
		else
		{
			if (--m_nTextCreate <= 0)
			{
				m_nTextCreate = 0;
				m_bAddScore = true;

				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::TYPE_ADD_SCORE);
			}
		}
	}
	break;
	case RST_STAND:
	{
		if (m_nStandTime-- <= 0)
		{
			m_nRstStgType++;
		}
	}
	break;
	case RST_END:
	{
		if (m_nStage < STAGE_MAX)
		{
			m_nScore = m_pScore->GetScore();
			CManager::GetFade()->SetFade(MODE_GAME);
		}
		else if (m_nStage >= STAGE_MAX)
		{
			CManager::GetFade()->SetFade(MODE_RANKING);
			m_nScore = m_pScore->GetScore();
			CRanking::SetScore11(m_nScore);
			CRanking::SetAllStage(false);
			CPause::SetPause(false);
		}
	}
	break;
	}

	// �e�L�X�g�̐���
	if (m_nRstStgType < RST_ADD_SCORE)
	{
		if (--m_nTextCreate <= 0)
		{
			if (m_nRstStgType == RST_TEXT || m_nRstStgType == RST_TIME || m_nRstStgType == RST_BONUS || m_nRstStgType == RST_CLEAR)
			{
				if (!m_bSpecial)
				{
					pFont = { D3DXCOLOR(1.0f,0.96f,0,1)	, 20.0f, 2, 5, 0 };
					pShadow = { INIT_D3DXCOLOR, true, D3DXVECTOR3(1.0f,1.0f,0.0f), D3DXVECTOR2(1.0f,1.0f) };
				}
				else
				{
					pFont = { D3DXCOLOR(0.02f,0.6f,1.0f,1)	, 20.0f, 2, 5, 0 };
					pShadow = { INIT_D3DXCOLOR, true, D3DXVECTOR3(1.0f,1.0f,0.0f), D3DXVECTOR2(1.0f,1.0f) };
				}
			}

			m_nTextCreate = 0;
			nLength = strlen(aString);

			m_RstText[m_nRstStgType] = CText::Create(CText::BOX_NORMAL_RECT, pos, D3DXVECTOR2(0.0f, 0.0f),
				aString, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

			if (m_nRstStgType == RST_TEXT)
			{
				m_nTextCreate = (nLength * 1) + 5;
			}
			else
			{
				m_nTextCreate = (nLength * 3) + 5;
			}
			m_nRstStgType++;
		}
	}
}

//========================================
// ���Z�b�g
//========================================
void CGame::Reset(void)
{
	m_bEnd = false;
	m_nStage = STAGE_00;
	m_nSelectStage = STAGE_00;
	m_bTime = false;
	m_nScore = 0;
	m_aStageInfo = { NULL,NULL };
}

//================================================================================
//--------------------------------------------------------------------------------
// �ݒ�
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// �X�e�[�W�I��
//========================================
void CGame::SetStage(int nStage)
{
	m_nSelectStage = nStage;
}

//================================================================================
//--------------------------------------------------------------------------------
// �ǂݍ���
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// �X�e�[�W���
//========================================
void CGame::LoodStage(void)
{
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

								// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(STAGE_INFO_FILE, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	// END_SCRIPT��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", &aDataSearch[0]);

		if (!strcmp(aDataSearch, "END_SCRIPT"))
		{// �ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		else if (aDataSearch[0] == '#')
		{// �܂�Ԃ�
			continue;
		}
		else if (!strcmp(aDataSearch, "SET_INFO"))
		{// �����J�n

			int nCntStage = 0;
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch);

				if (!strcmp(aDataSearch, "END_INFO"))
				{// �����I��
					break;
				}
				else if (!strcmp(aDataSearch, "SET_STAGE"))
				{
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch);

						if (!strcmp(aDataSearch, "END_STAGE"))
						{// �����I��
							nCntStage++;
							break;
						}
						else if (nCntStage > STAGE_MAX)
						{// �܂�Ԃ�
							continue;
						}
						else if (!strcmp(aDataSearch, "TIME"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%d", &m_aStageInfo.nTime[nCntStage]);
						}
						else if (!strcmp(aDataSearch, "CUBE"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%d", &m_aStageInfo.nCube[nCntStage]);
						}
						else if (!strcmp(aDataSearch, "CLEAR"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%d", &m_aStageInfo.nClearBonus[nCntStage]);
						}
						else if (!strcmp(aDataSearch, "BLOCK"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%s", &m_aStageInfo.aBlockFile[nCntStage][0]); // �t�@�C����
						}
						else if (!strcmp(aDataSearch, "PLAYER_POS"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%f", &m_aStageInfo.PlayerPos[nCntStage].x);
							fscanf(pFile, "%f", &m_aStageInfo.PlayerPos[nCntStage].y);
							fscanf(pFile, "%f", &m_aStageInfo.PlayerPos[nCntStage].z);
						}
						else if (!strcmp(aDataSearch, "PLAYER_ROT"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%f", &m_aStageInfo.PlayerRot[nCntStage]);
						}
					}
				}
				else if (!strcmp(aDataSearch, "ENEMY"))
				{
					fscanf(pFile, "%s", &aDataSearch[0]);
					fscanf(pFile, "%s", &m_aStageInfo.aEnemyFile[0]); // �t�@�C����
				}
			}
		}
	}
}

//========================================
// �V��
//========================================
void CGame::LoodCeiling(void)
{
	CBgCeiling *pBgCeiling = CBgCeiling::Create(m_nSelectStage);
}

//========================================
// ����
//========================================
void CGame::LoodSide(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

									// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(SIDE_STAGE_FILE, "r");

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
			else if (!strcmp(aDataSearch, "CREATE_SIDE"))
			{// �����J�n

				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);

					if (!strcmp(aDataSearch, "END_CREATE_SIDE"))
					{// �����I��
						break;
					}
					else if (!strcmp(aDataSearch, "SET_SIDE"))
					{// �������̓ǂݍ���
						D3DXVECTOR3 pos = INIT_D3DXVECTOR3;	// �ʒu
						D3DXVECTOR3 rot = INIT_D3DXVECTOR3;	// ����
						D3DXCOLOR	color = INIT_D3DXCOLOR;	// �F
						float fHeight = 0;					// ����
						float fRadius = 0;					// ���a
						int *nType = 0;						// �摜���
						int nNumTex = 0;					// �摜��
						int nDivisionX = 1;					// ������
						int nDivisionY = 1;					// ��������
						float *fTexV = 0;					// �e�N�X�`�����W�̊J�n�ʒu(X��)

						int nCntTex = 0; // �摜�J�E���g

						while (1)
						{
							fscanf(pFile, "%s", aDataSearch);

							if (!strcmp(aDataSearch, "END_SIDE"))
							{// �ǂݍ��݂��I��

								CBgSide *pBgSide = CBgSide::Create(
									pos, rot, color, fHeight, fRadius, nType, nNumTex,
									nDivisionX, nDivisionY, fTexV);

								delete[] nType;
								nType = NULL;

								delete[] fTexV;
								fTexV = NULL;

								break;
							}
							else if (!strcmp(aDataSearch, "POS"))
							{// �ʒu
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pos.x);
								fscanf(pFile, "%f", &pos.y);
								fscanf(pFile, "%f", &pos.z);
							}
							else if (!strcmp(aDataSearch, "ROT"))
							{// ����
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &rot.x);
								fscanf(pFile, "%f", &rot.y);
								fscanf(pFile, "%f", &rot.z);
							}
							else if (!strcmp(aDataSearch, "COLOR"))
							{// �F
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &color.r);
								fscanf(pFile, "%f", &color.g);
								fscanf(pFile, "%f", &color.b);
								fscanf(pFile, "%f", &color.a);
							}
							else if (!strcmp(aDataSearch, "HEIGHT"))
							{// ����
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fHeight);
							}
							else if (!strcmp(aDataSearch, "RADIUS"))
							{// ���a
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fRadius);
							}
							else if (!strcmp(aDataSearch, "NUMTEX"))
							{// �摜��
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nNumTex);

								// �������̉��
								nType = new int[nNumTex];
								fTexV = new float[nNumTex];
							}
							else if (!strcmp(aDataSearch, "SET_TEX"))
							{// �摜�֘A�̐ݒ�

								while (1)
								{
									fscanf(pFile, "%s", aDataSearch);

									if (!strcmp(aDataSearch, "END_TEX"))
									{// �ǂݍ��݂��I��
										nCntTex++;
										break;
									}
									else if (!strcmp(aDataSearch, "TYPE"))
									{// ���a
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%d", &nType[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_V"))
									{// �摜��
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexV[nCntTex]);
									}
								}
							}
							else if (!strcmp(aDataSearch, "DIVISION_X"))
							{// ������
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionX);
							}
							else if (!strcmp(aDataSearch, "DIVISION_Y"))
							{// ��������
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionY);
							}
						}
					}
				}
			}
		}
	}
}

//========================================
// ��
//========================================
void CGame::LoodFloor(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

									// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(FLOOR_STAGE_FILE, "r");

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
			else if (!strcmp(aDataSearch, "CREATE_FLOOR"))
			{// �����J�n

				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);

					if (!strcmp(aDataSearch, "END_CREATE_FLOOR"))
					{// �����I��
						break;
					}
					else if (!strcmp(aDataSearch, "SET_FLOOR"))
					{// �������̓ǂݍ���
						D3DXVECTOR3 pos = INIT_D3DXVECTOR3;	// �ʒu
						D3DXVECTOR3 rot = INIT_D3DXVECTOR3;	// ����
						D3DXCOLOR	color = INIT_D3DXCOLOR;	// �F
						float fWidth = 0;					// ��
						float fHeight = 0;					// ����
						int *nType = 0;						// �摜���
						int nNumTex = 0;					// �摜��
						int nDivisionX = 1;					// ������
						int nDivisionY = 1;					// ��������
						bool bDivision = false;				// �e�N�X�`���̕������邩
						float *fTexX = 0;					// �e�N�X�`�����W�̊J�n�ʒu(X��)
						float *fTexY = 0;					// �e�N�X�`�����W�̊J�n�ʒu(Y��)


						int nCntTex = 0; // �摜�J�E���g

						while (1)
						{
							fscanf(pFile, "%s", aDataSearch);

							if (!strcmp(aDataSearch, "END_FLOOR"))
							{// �ǂݍ��݂��I��

								CFloor *pBgSide = CFloor::Create(
									pos, rot, color, fWidth, fHeight, nType, nNumTex, bDivision,
									nDivisionX, nDivisionY, fTexX, fTexY);

								break;
							}
							else if (!strcmp(aDataSearch, "POS"))
							{// �ʒu
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pos.x);
								fscanf(pFile, "%f", &pos.y);
								fscanf(pFile, "%f", &pos.z);
							}
							else if (!strcmp(aDataSearch, "ROT"))
							{// ����
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &rot.x);
								fscanf(pFile, "%f", &rot.y);
								fscanf(pFile, "%f", &rot.z);
							}
							else if (!strcmp(aDataSearch, "COLOR"))
							{// �F
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &color.r);
								fscanf(pFile, "%f", &color.g);
								fscanf(pFile, "%f", &color.b);
								fscanf(pFile, "%f", &color.a);
							}
							else if (!strcmp(aDataSearch, "WIDTH"))
							{// ��
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fWidth);
							}
							else if (!strcmp(aDataSearch, "HEIGHT"))
							{// ����
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fHeight);
							}
							else if (!strcmp(aDataSearch, "NUMTEX"))
							{// �摜��
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nNumTex);

								// �������̉��
								nType = new int[nNumTex];
								fTexX = new float[nNumTex];
								fTexY = new float[nNumTex];
							}
							else if (!strcmp(aDataSearch, "DIVISION"))
							{// �e�N�X�`���̕������邩
								int nData;

								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nData);

								if (nData <= 0)
								{
									bDivision = false;
								}
								else
								{
									bDivision = true;
								}
							}
							else if (!strcmp(aDataSearch, "SET_TEX"))
							{// �摜�֘A�̐ݒ�

								while (1)
								{
									fscanf(pFile, "%s", aDataSearch);

									if (!strcmp(aDataSearch, "END_TEX"))
									{// �ǂݍ��݂��I��
										nCntTex++;
										break;
									}
									else if (!strcmp(aDataSearch, "TYPE"))
									{// ���a
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%d", &nType[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_X"))
									{// �e�N�X�`���̈ړ���(X��)
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexX[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_Y"))
									{// �e�N�X�`���̈ړ���(Y��)
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexY[nCntTex]);
									}
								}
							}
							else if (!strcmp(aDataSearch, "DIVISION_X"))
							{// ������
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionX);
							}
							else if (!strcmp(aDataSearch, "DIVISION_Y"))
							{// ��������
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionY);
							}
						}
					}
				}
			}
		}
	}
}

//========================================
// �u���b�N
//========================================
void CGame::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood(m_aStageInfo.aBlockFile[m_nStage], true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �e�f�[�^�ɑ��
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �z�u���̐���
		int nType;				// ���
		int nState;				// ���
		D3DXVECTOR3 pos;		// �ʒu

								// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 2:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			case 4: pFile->ToValue(nState, sData); break;	// ���
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			delete pFile;
			pFile = NULL;
			return;
		}

		// �z�u
		CBlock *pObj = CBlock::Create(nType, pos, nState);
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}

//========================================
// �G�l�~�[
//========================================
void CGame::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood(m_aStageInfo.aEnemyFile, true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		int nStage, nType, nMove, nTime;
		float fRotY;
		D3DXVECTOR3 pos;

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0: pFile->ToValue(nStage, sData); break;	// �X�e�[�W
			case 1:	pFile->ToValue(nType, sData); break;	// ���
			case 2:	pFile->ToValue(nMove, sData); break;	// �ړ����
			case 3:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 4:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 5:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			case 6: pFile->ToValue(fRotY, sData); break;	// ����Y
			case 7: pFile->ToValue(nTime, sData); break;	// �s���J�E���g
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			delete pFile;
			pFile = NULL;
			return;
		}

		if (nStage == m_nStage)
		{
			CEnemy *pObj = CEnemy::Create(nType, nMove, pos, D3DXVECTOR3(0.0f, fRotY, 0.0f), nTime);
		}
	}

	delete pFile;
	pFile = NULL;
}