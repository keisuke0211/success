//========================================
// 
// �e�N�X�`���Ǘ�
// 
//========================================
// *** texture.cpp ***
//========================================
#include "texture.h"
#include "../manager.h"
#include "renderer.h"

// ��`
const char* CTexture::FILE_PATH = "data\\GAMEDATA\\TEXTURE\\TEXTURE_DATA.txt";

// �ÓI�����o�ϐ�
int CTexture::m_NumAll = 0;
char CTexture::m_FileName[CTexture::MAX_TEXTURE][TXT_MAX] = { NULL };

//========================================
// �R���X�g���N�^
//========================================
CTexture::CTexture()
{

}

//========================================
// �f�X�g���N�^
//========================================
CTexture::~CTexture()
{

}

//========================================
// �ǂݍ���
//========================================
HRESULT CTexture::Load(void)
{
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return S_OK;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", &aDataSearch[0]);

		if (!strcmp(aDataSearch, "END"))
		{// �ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{// �܂�Ԃ�
			continue;
		}

		if (!strcmp(aDataSearch, "TEXTURE"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%s", &m_FileName[m_NumAll][0]); // �t�@�C����

			Regist(&m_FileName[m_NumAll][0]);
		}
	}

	return S_OK;
}

//========================================
// �e�N�X�`���j��
//========================================
void CTexture::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < m_NumAll; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//========================================
// �w��e�N�X�`���̓ǂݍ���
//========================================
int CTexture::Regist(const char* pFilename)
{
	int nIdx = -1;	// �e�N�X�`���ԍ�

	if (m_NumAll >= MAX_TEXTURE)
	{// �ő吔��������
		for (int nCntFile = 0; nCntFile < m_NumAll; nCntFile++)
		{
			if (strcmp(&m_FileName[nCntFile][0], pFilename) == 0)
			{
				return nCntFile;
			}
		}
		return 0;
	}

	// ���ɓǂݍ��񂾂����ׂ�
	for (int nCntFile = 0; nCntFile < m_NumAll; nCntFile++)
	{
		if (strcmp(&m_FileName[nCntFile][0], pFilename) == 0)
		{
			return nCntFile;
		}
	}

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, pFilename, &m_apTexture[m_NumAll])))
	{
		m_apTexture[m_NumAll] = NULL;
	}

	// �t�@�C���p�X��ۑ�
	strcpy(&m_FileName[m_NumAll][0],pFilename);

	nIdx = m_NumAll;

	m_NumAll++;	// ���������Z

	return nIdx;
}

//========================================
// �w��e�N�X�`���̎擾
//========================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx == -1)
	{// �e�N�X�`�����g�p���Ȃ�
		return NULL;
	}

	assert(nIdx >= -1 && nIdx <= m_NumAll + 1);

	return m_apTexture[nIdx];
}