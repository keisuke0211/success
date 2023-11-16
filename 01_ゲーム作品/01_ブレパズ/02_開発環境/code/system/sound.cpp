//========================================
// 
// �T�E���h����
// Author : AKIRA TANAKA
// |
// Arrange: KEISUKE OTONO
// 
//========================================
// *** sound.cpp ***
//========================================
#include "sound.h"
#include <stdio.h>

//****************************************
// �}�N����`
//****************************************
// �T�E���h�̃f�[�^�t�@�C���̑��΃p�X
const char* CSound::FILE_PATH = "data\\GAMEDATA\\SOUND\\SOUND_DATA.txt";

// �ÓI�����o�ϐ�
float CSound::m_aSoundVolume[SOUND_TYPE_MAX] = { 1.0f,1.0f };
float CSound::m_aSettingVolume[SOUND_TYPE_MAX] = { 1.0f,1.0f };

//========================================
// �R���X�g���N�^
//========================================
CSound::CSound()
{

}

//========================================
// �f�X�g���N�^
//========================================
CSound::~CSound()
{

}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// CheckChunk�֐� - �`�����N�̃`�F�b�N -
//========================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//========================================
// ReadChunkData�֐� - �`�����N�f�[�^�̓ǂݍ��� -
//========================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// LoadSound�֐� - �T�E���h�̓ǂݍ��ݏ��� -
//========================================
void CSound::Load(void)
{
	FILE *pFile;				// �t�@�C���|�C���^
	char aDataSearch[TXT_MAX];	// �f�[�^�����p
						
	SOUNDINFO *pSoundInfo = m_aSoundInfo;	// �T�E���h�̏��̃|�C���^

	// �T�E���h����������
	m_nSoundNum = 0;

	// ��ޖ��̏��̃f�[�^�t�@�C�����J��
	pFile = fopen(FILE_PATH, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
		//�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (m_nSoundNum == TYPE_MAX)
		{
			return;
		}

		if (!strcmp(aDataSearch, "END"))	{ fclose(pFile); break; }	// �ǂݍ��݂��I��
		if (aDataSearch[0] == '#'){ continue; }				// �܂�Ԃ�
		if (!strcmp(aDataSearch, "SOUND"))	{
			fscanf(pFile, "%s", &pSoundInfo->aFileName);	// �t�@�C����
			fscanf(pFile, "%d", &pSoundInfo->nCntLoop);		// ���[�v�J�E���g
			fscanf(pFile, "%f", &pSoundInfo->fVolume);		// ����
			fscanf(pFile, "%d", &pSoundInfo->type);			// ���
			pSoundInfo++;	// �|�C���^��i�߂�
			m_nSoundNum++;	// �T�E���h�������Z
		}
	}
}

//========================================
// InitSound�֐� - �T�E���h�̏��������� -
//========================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(m_pXAudio2 != NULL)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(m_aSoundInfo[nCntSound].aFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			char aString[TXT_MAX];
			sprintf(aString, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1) (�J�E���g%d)", nCntSound);
			MessageBox(hWnd, aString, "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �\�[�X�{�C�X�̐���
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = m_aSoundInfo[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}

//========================================
// UninitSound�֐� - �T�E���h�̏I������ -
//========================================
void CSound::Uninit(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;
	
	if(m_pXAudio2 != NULL)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

//========================================
// PlaySound�֐� - �Z�O�����g�Đ�(�Đ����Ȃ��~) -
//========================================
HRESULT CSound::PlaySound(int nSoundIdx)
{
	if (nSoundIdx == -1) 
	{// �T�E���h�ԍ���-1�̎��A
		return S_OK;	// �������I������
	}

	if (m_aSoundInfo[nSoundIdx].type == SOUND_TYPE_BGM) 
	{// �T�E���h�̎�ނ�BGM���������A
		StopSoundType(SOUND_TYPE_BGM);	// BGM���ꊇ��~����
	}

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[nSoundIdx];
	buffer.pAudioData = m_apDataAudio[nSoundIdx];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[nSoundIdx].nCntLoop;

	// ��Ԏ擾
	m_apSourceVoice[nSoundIdx]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[nSoundIdx]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[nSoundIdx]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[nSoundIdx]->SubmitSourceBuffer(&buffer);

	// ���ʂ�ݒ�
	m_apSourceVoice[nSoundIdx]->SetVolume(m_aSoundInfo[nSoundIdx].fVolume * m_aSoundVolume[m_aSoundInfo[nSoundIdx].type] * m_aSettingVolume[m_aSoundInfo[nSoundIdx].type]);

	// �Đ�
	m_apSourceVoice[nSoundIdx]->Start(0);

	return S_OK;
}

//========================================
// StopSound - �Z�O�����g��~(���x���w��) -
//========================================
void CSound::StopSound(int nSoundIdx)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_apSourceVoice[nSoundIdx]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[nSoundIdx]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[nSoundIdx]->FlushSourceBuffers();
	}
}

//========================================
// StopSound - �Z�O�����g��~(�S��) -
//========================================
void CSound::StopSound(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//========================================
// SoundTypeVolumeChange�֐� - ��ޖ��ɉ��ʕύX -
//========================================
void CSound::SoundTypeVolumeChange(SOUND_TYPE type, float fVolume)
{
	// ���ʂ𐧌�
	if (fVolume <= 0.0f) { fVolume = 0.0f; }
	if (fVolume >= 1.0f) { fVolume = 1.0f; }

	// ���ʂ�ݒ�
	m_aSoundVolume[type] = fVolume;

	for (int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++)
	{
		if (m_aSoundInfo[nCntSound].type == type)
		{// �T�E���h�̎�ނ���v�������A
			// ���ʂ�ݒ�
			m_apSourceVoice[nCntSound]->SetVolume(m_aSoundInfo[nCntSound].fVolume * m_aSoundVolume[type] * m_aSettingVolume[type]);
		}
	}
}

//========================================
// StopSoundType�֐� - ��ޖ��ɍĐ���~ -
//========================================
void CSound::StopSoundType(SOUND_TYPE type)
{
	XAUDIO2_VOICE_STATE xa2state;
	
	for (int nCntSound = 0; nCntSound < m_nSoundNum; nCntSound++)
	{
		if (m_aSoundInfo[nCntSound].type == type)
		{// �T�E���h�̎�ނ���v�������A
			// ��Ԏ擾
			m_apSourceVoice[nCntSound]->GetState(&xa2state);
			if (xa2state.BuffersQueued != 0)
			{// �Đ���
				// �ꎞ��~
				m_apSourceVoice[nCntSound]->Stop(0);

				// �I�[�f�B�I�o�b�t�@�̍폜
				m_apSourceVoice[nCntSound]->FlushSourceBuffers();
			}
		}
	}
}
