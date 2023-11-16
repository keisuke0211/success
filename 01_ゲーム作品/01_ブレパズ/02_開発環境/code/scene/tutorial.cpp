//========================================
// 
// �`���[�g���A��
// 
//========================================
// *** tutorial.h ***
//========================================
#include "tutorial.h"
#include "title.h"
#include "../manager.h"
#include "../system/csv_file.h"
#include "../object\UI\score.h"
#include "../object\UI\time.h"
#include "../object\model\block.h"
#include "../object/model/bullet.h"
#include "../object/model/bullet_cube.h"
#include "../object\model\player.h"
#include "../object\model\enemy.h"
#include "../object\BG\bg_side.h"
#include "../object\BG\bg_ceiling.h"
#include "../object/BG/mesh_floor.h"
#include "../system/input.h"
#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/camera.h"
#include "../scene/pause.h"
#include "../system/sound.h"
#include "../object/model/model.h"
#include "fade.h"

// �ÓI�ϐ�
CTutorial::LoadTxt *CTutorial::m_LoadText = NULL;	// �e�L�X�g���

// �T�E���h�̃f�[�^�t�@�C���̑��΃p�X
const char* CTutorial::FILE_PATH = "data\\GAMEDATA\\TEXT\\TUTORIAL_DATA.csv";

CPlayer *CTutorial::m_pPlayer = NULL;
CTime *CTutorial::m_pTime = NULL;
CScore *CTutorial::m_pScore = NULL;
int CTutorial::m_nCurAction = 0;

const char* CTutorial::SIDE_FILE = "data\\GAMEDATA\\OBJECT\\SIDE_DATA .txt";
const char* CTutorial::FLOOR_FILE = "data\\GAMEDATA\\OBJECT\\FLOOR_DATA.txt";
const char* CTutorial::BLOCK_FILE1 = "data\\GAMEDATA\\BLOCK\\TUTORIAL_DATA.csv";
const char* CTutorial::ENEMY_FILE1 = "data\\GAMEDATA\\ENEMY\\TUTORIAL_ENEMY.csv";

//========================================
// �R���X�g���N�^
//========================================
CTutorial::CTutorial()
{
	for (int nTxt = 0; nTxt < 4; nTxt++)
	{
		m_Txt[nTxt] = NULL;
	}

	m_nStartTime = 0;

	Action = ACTION_MOVE;
	m_nEndTime = 0;
	m_bEnd = false;

	m_aCreateText.nCreateTime = 0;
	m_aCreateText.nCurAction = 0;
	m_aCreateText.nNumCur = 0;
	m_aCreateText.nNumCurAll = 0;

	for (int nCur = 0; nCur < ACTION_MAX; nCur++)
	{
		m_aCreateText.nCurMax[nCur] = 0;
		m_aCreateText.bCreate[nCur] = false;
	}
}

//========================================
// �f�X�g���N�^
//========================================
CTutorial::~CTutorial()
{

}

//========================================
// ������
//========================================
HRESULT CTutorial::Init(void)
{
	CEnemy::Reset();
	CBullet::Reset();
	CCube::Reset();

	CBlock::Load();			// �u���b�N
	CModel::InitModel();	// ���f��
	CTitle::SetStart(false);
	CTitle::SetClear(false);

	// �L���[�u�̎g�p��
	CCube::SetLimit(99);

	// �w�i(����)�̐���
	LoodSide();

	// �w�i(�V��)�̐���
	LoodCeiling();

	// ���̐���
	LoodFloor();

	// �u���b�N�̐���
	LoodBlock();

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 20.0f, 0.0f),0.0f);
	m_pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");


	CCamera *pCamera = CManager::GetCamera();					// �J����
	pCamera->Init();
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetHeigth(0.4f);
	pCamera->SetDistance(500.0f);

	// �ǂݍ���
	TextLoad();

	// �e�L�X�g����
	TxtCreate(ACTION_MOVE);

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::TYPE_GAME01);

	return S_OK;
}

//========================================
// �I��
//========================================
void CTutorial::Uninit(void)
{
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();

	CBlock::Reset();
	CModel::UninitModel();

	CObject::ReleaseAll(CObject::TYPE_BG);
	CObject::ReleaseAll(CObject::TYPE_BLOCK);
	CObject::ReleaseAll(CObject::TYPE_CUBE);
	CObject::ReleaseAll(CObject::TYPE_PLAYER);
	CObject::ReleaseAll(CObject::TYPE_ENEMY);
	CObject::ReleaseAll(CObject::TYPE_EFFECT);
	CObject::ReleaseAll(CObject::TYPE_PARTICLE);
	CObject::ReleaseAll(CObject::TYPE_TIME);
	CObject::ReleaseAll(CObject::TYPE_SCORE);
	CObject::ReleaseAll(CObject::TYPE_FONT);

	// �������J��
	delete m_LoadText;
	m_LoadText = NULL;
}

//========================================
// �X�V
//========================================
void CTutorial::Update(void)
{
	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// �|�[�Y
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_START))
	{
		CPause::SetPause(true);
	}

	bool bPause = CPause::IsPause();
	if (!bPause)
	{
		// �e�e�L�X�g�̏���
		TutorialTex();
	}

	// �J�n�t���O
	{
		bool bStart = CTitle::IsStart();
		if (!bStart && --m_nStartTime <= 0)
		{
			CTitle::SetStart(true);
		}
	}

	// �G�l�~�[�̑S��
	{
		bool bClear = CTitle::IsClear();
		if (!bClear && CEnemy::GetEnemyAll() <= 0 && m_aCreateText.nCurAction >= ACTION_ENEMY)
		{
			CTitle::SetClear(true);
		}
	}
}

//========================================
// �`��
//========================================
void CTutorial::Draw(void)
{

}

//========================================
// ����
//========================================
CTutorial *CTutorial::Create(void)
{
	CTutorial *pTutorial = new CTutorial;

	pTutorial->Init();

	return pTutorial;
}

//========================================
// �ǂݍ���
//========================================
void CTutorial::TextLoad(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood(FILE_PATH, true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �������m��
	m_LoadText = new CTutorial::LoadTxt[nRowMax];

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// ������
		TxtInit(nRow);

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(m_LoadText[nRow].nType, sData); break;		// ���
			case 1:	pFile->ToValue(m_LoadText[nRow].pos.x, sData); break;		// �ʒu X
			case 2:	pFile->ToValue(m_LoadText[nRow].pos.y, sData); break;		// �@�@ Y
			case 3:	pFile->ToValue(m_LoadText[nRow].size.x, sData); break;		// �T�C�Y X
			case 4:	pFile->ToValue(m_LoadText[nRow].size.y, sData); break;		// �@�@�@ Y
			case 5:	pFile->ToValue(m_LoadText[nRow].nStartTime, sData); break;	// �\������
			case 6:	pFile->ToValue(m_LoadText[nRow].nStandTime, sData); break;	// �ҋ@����
			case 7:	pFile->ToValue(m_LoadText[nRow].nDisapTime, sData); break;	// �����鎞��
			case 8:	pFile->ToValue(m_LoadText[nRow].nCreateTime, sData); break;	// �����ҋ@����
			case 9:	pFile->ToValue(m_LoadText[nRow].bTextBok, sData); break;	// Box�\��
			case 10:pFile->ToValue(m_LoadText[nRow].nTextSize, sData); break;	// �e�L�X�g �T�C�Y
			case 11:pFile->ToValue(*m_LoadText[nRow].ActionTex, sData); break;	// �e�L�X�g
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			delete pFile;
			pFile = NULL;
			return;
		}

		{
			int nType = m_LoadText[nRow].nType;
			m_aCreateText.nCurMax[nType]++;
		}
	}

	delete pFile;
	pFile = NULL;
}

//========================================
// �e�L�X�g���̏�����
//========================================
void CTutorial::TxtInit(int nIdx)
{
	m_LoadText[nIdx].pos = INIT_D3DXVECTOR3;
	m_LoadText[nIdx].size = INIT_D3DXVECTOR2;
	m_LoadText[nIdx].nType = 0;
	m_LoadText[nIdx].nStartTime = 0;
	m_LoadText[nIdx].nStandTime = 0;
	m_LoadText[nIdx].nDisapTime = 0;
	*m_LoadText[nIdx].ActionTex = NULL;
	m_LoadText[nIdx].nTextSize = 0;
	m_LoadText[nIdx].bTextBok = false;
}

//========================================
// �e�L�X�g����
//========================================
void CTutorial::TxtCreate(int nType)
{
	m_nCurAction = nType;

	if (m_aCreateText.nCurAction == ACTION_MAX)
	{
		return;
	}

	if (--m_aCreateText.nCreateTime <= 0 && !m_aCreateText.bCreate[nType])
	{
		int nNumCur = m_aCreateText.nNumCur;
		int nNumCurAll = m_aCreateText.nNumCurAll;

		m_aCreateText.nCreateTime = 0;

		if (nNumCur < m_aCreateText.nCurMax[nType])
		{
			FormFont pFont = {
				INIT_D3DXCOLOR,
				m_LoadText[nNumCurAll].nTextSize,
				m_LoadText[nNumCurAll].nStartTime,
				m_LoadText[nNumCurAll].nStandTime,
				m_LoadText[nNumCurAll].nDisapTime
			};

			int nText = m_aCreateText.nNumCur;

			m_Txt[nText] = CText::Create(CText::BOX_NORMAL_RECT,
				m_LoadText[nNumCurAll].pos,
				m_LoadText[nNumCurAll].size,
				*m_LoadText[nNumCurAll].ActionTex,
				CFont::FONT_BESTTEN,
				&pFont,
				m_LoadText[nNumCurAll].bTextBok);

			// �Œ�l�̐ݒ�
			if (m_LoadText[nNumCurAll].nDisapTime <= -1)
			{
				m_LoadText[nNumCurAll].nDisapTime = 5;
			}

			int nStrlen = (strlen(*m_LoadText[nNumCurAll].ActionTex) / 2);

			m_aCreateText.nCreateTime = (nStrlen * m_LoadText[nNumCurAll].nStartTime) +
				m_LoadText[nNumCurAll].nStandTime + (m_LoadText[nNumCurAll].nDisapTime - 5);

			m_aCreateText.nNumCur++;
			m_aCreateText.nNumCurAll++;

			if (m_aCreateText.nNumCur == m_aCreateText.nCurMax[nType])
			{
				if (m_LoadText[nNumCurAll].nDisapTime >= 1)
				{
					m_aCreateText.nCreateTime = (nStrlen * m_LoadText[nNumCurAll].nStartTime) +
						m_LoadText[nNumCurAll].nStandTime;
				}
			}
		}
		if (m_aCreateText.nNumCur == m_aCreateText.nCurMax[nType])
		{
			m_aCreateText.bCreate[nType] = true;
		}
	}
	else if (m_aCreateText.nCreateTime <= 0 && m_aCreateText.bCreate[nType])
	{
		for (int nCnt = 0; nCnt < m_aCreateText.nCurMax[nType]; nCnt++)
		{
			if (m_LoadText[m_aCreateText.nNumCurAll - 1].nDisapTime >= 6)
			{
				if (m_Txt[nCnt] != NULL)
				{
					m_Txt[nCnt]->Disap(true, m_LoadText[m_aCreateText.nNumCurAll - 1].nDisapTime);
					m_Txt[nCnt] = NULL;
				}
			}
		}
	}
}

//========================================
// �e�L�X�g�폜
//========================================
void CTutorial::TxtDelete(int nType, int nNextType)
{
	for (int nCnt = 0; nCnt < m_aCreateText.nCurMax[nType]; nCnt++)
	{
		if (m_Txt[nCnt] != NULL)
		{
			m_Txt[nCnt]->Uninit();
			m_Txt[nCnt] = NULL;
		}
	}

	m_aCreateText.nNumCur = 0;
	m_aCreateText.nCurAction = nNextType;

	int nNumCurAll = m_aCreateText.nNumCurAll - 1;
	if (nNumCurAll >= 1)
	{
		m_aCreateText.nCreateTime = m_LoadText[nNumCurAll].nCreateTime;
	}
}

//========================================
// �`���[�g���A��
//========================================
void CTutorial::TutorialTex(void)
{
	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// �e�L�X�g�̐���
	TxtCreate(m_aCreateText.nCurAction);

	switch (m_aCreateText.nCurAction)
	{
	case ACTION_MOVE:// �ړ�
	{
		D3DXVECTOR3 move = m_pPlayer->GetPlayerMove();
		
		if (move.x <= -1.0f || move.x >= 1.0f)
		{
			if (m_aCreateText.bCreate[ACTION_MOVE])
			{
				TxtDelete(ACTION_MOVE,ACTION_CAMERA);
			}
		}
	}
		break;
	case ACTION_CAMERA:	// ���_�ړ�
	{
		D3DXVECTOR3 move = CManager::GetCamera()->GetInfo().spin;

		if (move.y <= -0.01f || move.y >= 0.01f)
		{
			if (m_aCreateText.bCreate[ACTION_CAMERA])
			{
				TxtDelete(ACTION_CAMERA, ACTION_SHOT);
			}
		}
	}
		break;
	case ACTION_SHOT:	// ����
	{
		int nNumAll = CBullet::GetNumAll();

		if (nNumAll > 0 && m_aCreateText.bCreate[ACTION_SHOT])
		{
			TxtDelete(ACTION_SHOT, ACTION_SET);
		}
	}
	break;
	case ACTION_SET1:	// �z�u(����)
	{
		if (m_aCreateText.bCreate[ACTION_SET1] && m_aCreateText.nCreateTime <= 0)
		{
			TxtDelete(ACTION_SET1, ACTION_ENEMY);

			// �G�̐���
			LoodEnemy();

			// �X�R�A����
			m_pScore = CScore::Create();
			CScore::SetScore();
		}
	}
	break;
	case ACTION_ENEMY:	// �G
	{
		int nNumEnemy = CEnemy::GetEnemyAll();

		if (nNumEnemy == 0 && m_aCreateText.bCreate[ACTION_ENEMY])
		{
			TxtDelete(ACTION_ENEMY, ACTION_CLEAR);

			// �^�C������
			m_pTime = CTime::Create(MAX_TIME);
		}
	}
	break;
	case ACTION_FREE:// �I��
	{
		if (m_aCreateText.nCreateTime <= 0 && m_aCreateText.bCreate[ACTION_FREE])
		{
			TxtDelete(ACTION_FREE, ACTION_MAX);

			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CManager::GetFade()->SetFade(MODE_TITLE);
			}
		}
	}
	break;
	default:
	{
		int nCurAction = m_aCreateText.nCurAction;

		if (m_aCreateText.nCreateTime <= 0)
		{
			if (m_aCreateText.bCreate[nCurAction] && nCurAction != ACTION_MAX)
			{
				TxtDelete(nCurAction, nCurAction + 1);
			}
		}
	}
		break;
	}
}

//========================================
// �V��
//========================================
void CTutorial::LoodCeiling(void)
{
	CBgCeiling *pBgCeiling = CBgCeiling::Create(0);
}

//========================================
// ����
//========================================
void CTutorial::LoodSide(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

									// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(SIDE_FILE, "r");

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
void CTutorial::LoodFloor(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

									// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(FLOOR_FILE, "r");

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
// �u���b�N�̓ǂݍ���
//========================================
void CTutorial::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood(BLOCK_FILE1, true, true, ',');

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
		if (nRow == 150)
		{
			int n = nRow;
		}

		// �z�u
		CBlock *pObj = CBlock::Create(nType, pos, nState);
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}

//========================================
// �G�l�~�[�̓ǂݍ���
//========================================
void CTutorial::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood(ENEMY_FILE1, true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		int nType, nMove, nTime;
		float fRotY;
		D3DXVECTOR3 pos;

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(nMove, sData); break;	// �ړ����
			case 2:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 3:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 4:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			case 5: pFile->ToValue(fRotY, sData); break;	// ����Y
			case 6: pFile->ToValue(nTime, sData); break;	// �s���J�E���g
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			delete pFile;
			pFile = NULL;
			return;
		}

		CEnemy *pObj = CEnemy::Create(nType, nMove, pos, D3DXVECTOR3(0.0f, fRotY, 0.0f), nTime);
	}

	delete pFile;
	pFile = NULL;
}