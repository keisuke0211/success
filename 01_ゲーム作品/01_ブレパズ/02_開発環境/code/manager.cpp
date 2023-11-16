//========================================
// 
// �}�l�[�W���[����
// 
//========================================
// *** manager.cpp ***
//========================================
#include "manager.h"
#include "system/renderer.h"
#include "system/camera.h"
#include "system/light.h"
#include "system/sound.h"
#include "system/texture.h"
#include "system/input.h"
#include "system\words\font.h"
#include "object\object.h"
#include "scene\title.h"
#include "scene\tutorial.h"
#include "scene\game.h"
#include "scene\ranking.h"
#include "scene\pause.h"
#include "scene\fade.h"

// �ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CKeyboard *CManager::m_InputKeyboard = NULL;
CMouse *CManager::m_InputMouse = NULL;
CJoypad *CManager::m_InputJoypad = NULL;
CFont *CManager::m_pFont = NULL;
CScene *CManager::m_pScene = NULL;
CScene::MODE CScene::m_mode = MODE_TITLE;
CTitle *CScene::m_pTitle = NULL;
CTutorial *CScene::m_pTutorial = NULL;
CGame *CScene::m_pGame = NULL;
CRanking *CScene::m_pRanking = NULL;
CPause *CScene::m_pPause = NULL;
CFade *CManager::m_pFade = NULL;

//========================================
// �R���X�g���N�^
//========================================
CManager::CManager()
{
	
}

//========================================
// �f�X�g���N�^
//========================================
CManager::~CManager()
{

}

//========================================
// ������
//========================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[
	m_pRenderer = new CRenderer;

	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h
	m_InputKeyboard = new CKeyboard;

	if (FAILED(m_InputKeyboard->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// �}�E�X
	m_InputMouse = new CMouse;

	if (FAILED(m_InputMouse->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// �W���C�p�b�g
	m_InputJoypad = new CJoypad;

	if (FAILED(m_InputJoypad->Init()))
	{
		return E_FAIL;
	}

	// �J����
	m_pCamera = new CCamera;

	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	// ���C�g
	m_pLight = new CLight;

	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	// �T�E���h
	m_pSound = new CSound;
	m_pSound->Load();

	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}
	
	// �e�N�X�`��
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
		m_pTexture->Load();
	}

	m_pFont = NULL;
	// �t�H���g
	if (m_pFont == NULL)
	{
		m_pFont = new CFont;
	}

	// �t�F�[�h
	if (m_pFade == NULL)
	{
		m_pFade = new CFade;
		m_pFade->Init();
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CManager::Uninit(void)
{
	// �V�[��
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = NULL;
	}

	// �L�[�{�[�h
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Uninit();

		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// �}�E�X
	if (m_InputMouse != NULL)
	{
		m_InputMouse->Uninit();

		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// �W���C�p�b�g
	if (m_InputJoypad != NULL)
	{
		m_InputJoypad->Uninit();

		delete m_InputJoypad;
		m_InputJoypad = NULL;
	}

	// �����_���[
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// ���C�g
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	// �J����
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// �T�E���h
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	// �e�N�X�`��
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}

	// �t�H���g
	if (m_pFont != NULL)
	{
		m_pFont->ReleaseAll();

		delete m_pFont;
		m_pFont = NULL;
	}
}

//========================================
// �X�V
//========================================
void CManager::Update(void)
{
	m_pScene->Update();				// �V�[��
	m_InputKeyboard->Update();		// �L�[�{�[�h
	m_InputMouse->Update();			// �}�E�X
	m_InputJoypad->Update();		// �W���C�p�b�g(�{�^��)
	m_InputJoypad->UpdateStick();	// �W���C�p�b�g(�X�e�B�b�N)	
	m_pCamera->Update();			// �J����
	m_pLight->Update();				// ���C�g
	m_pRenderer->Update();			// �����_���[
}

//========================================
// �`��
//========================================
void CManager::Draw(void)
{
	m_pScene->Draw();		// �V�[��
	m_pRenderer->Draw();	// �����_���[
}

//========================================
//----------------------------------------
// scene �N���X
//----------------------------------------
//========================================

//========================================
// �R���X�g���N�^
//========================================
CScene::CScene()
{

}

//========================================
// �f�X�g���N�^
//========================================
CScene::~CScene()
{

}

//========================================
// �V�[������
//========================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = new CScene;
	m_mode = mode;

	pScene->Init();

	return pScene;
}

//========================================
// ������
//========================================
HRESULT CScene::Init()
{
	// ���݂̃��[�h�̔j��
	switch (m_mode)
	{
	case CScene::MODE_TITLE:
	{
		m_pTitle = CTitle::Create();
		break;
	}
	case CScene::MODE_TUTORIAL:
	{
		m_pPause = CPause::Create();
		m_pTutorial = CTutorial::Create();
		break;
	}
	case CScene::MODE_GAME:
	{
		m_pPause = CPause::Create();
		m_pGame = CGame::Create();
		break;
	}
	case CScene::MODE_RANKING:
	{
		m_pRanking = CRanking::Create();
		break;
	}
	break;
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CScene::Uninit(void)
{
	// ���݂̃��[�h�̔j��
	switch (m_mode)
	{
	case CScene::MODE_TITLE:
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;

		break;
	}
	case CScene::MODE_TUTORIAL:
	{
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;

		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;

		break;
	}
	case CScene::MODE_GAME:
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;

		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;

		break;
	}
	case CScene::MODE_RANKING:
	{
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;

		break;
	}
	break;
	}
}

//========================================
// �X�V
//========================================
void CScene::Update(void)
{
	// ���݂̃��[�h�̔j��
	switch (m_mode)
	{
	case CScene::MODE_TITLE:
	{
		m_pTitle->Update();
		break;
	}
	case CScene::MODE_TUTORIAL:
	{
		if (!m_pPause->IsPause())
		{
			m_pTutorial->Update();
		}
		else
		{
			m_pPause->Update();
		}
		break;
	}
	case CScene::MODE_GAME:
	{

		if (!m_pPause->IsPause())
		{
			m_pGame->Update();
		}
		else
		{
			m_pPause->Update();
		}

		break;
	}
	case CScene::MODE_RANKING:
	{
		m_pRanking->Update();
		break;
	}
	}
}

//========================================
// �`��
//========================================
void CScene::Draw(void)
{
	// ���݂̃��[�h�̔j��
	switch (m_mode)
	{
	case CScene::MODE_TITLE:
	{
		m_pTitle->Draw();
		break;
	}
	case CScene::MODE_TUTORIAL:
	{
		m_pGame->Draw();
		m_pTutorial->Draw();
		break;
	}
	case CScene::MODE_GAME:
	{
		m_pGame->Draw();
		m_pPause->Draw();

		break;
	}
	case CScene::MODE_RANKING:
	{
		m_pRanking->Draw();
		break;
	}
	}
}

//========================================
// ���[�h�ݒ�
//========================================
void CManager::SetMode(CScene::MODE mode)
{
	// �T�E���h��~
	m_pSound->StopSound();

	if (m_pScene != NULL)
	{
		// ���݂̃��[�h�̔j��
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = NULL;
	}

	// �V�������[�h�̐���
	m_pScene = CScene::Create(mode);
}

//========================================
// ���[�h�擾
//========================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}