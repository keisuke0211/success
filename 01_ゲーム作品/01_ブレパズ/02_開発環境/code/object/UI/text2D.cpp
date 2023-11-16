//========================================
// 
// �e�L�X�g(2D)
// 
//========================================
//  *** text2D.cpp ***
//========================================
#include "text2D.h"
#include "../object2D.h"
#include "../../system/texture.h"

//========================================
// �R���X�g���N�^
//========================================
CText2D::CText2D(int nPriority) : CObject(nPriority)
{
	sprintf(m_aString, "");		// ������̃|�C���^
	m_disp = DISPLAY_LEFT;		// �\���`��
	m_pos = INIT_D3DXVECTOR3;	// �ʒu
	m_rot = INIT_D3DXVECTOR3;	// ����
	m_fWidth = 0.0f;			// ��
	m_fHeight = 0.0f;			// ����

	// �I�u�W�F�N�g2D�̃|�C���^�z��
	for (int nCntObj = 0; nCntObj < TXT_MAX; nCntObj++)
	{
		m_apObject2D[nCntObj] = NULL;
	}
}

//========================================
// �f�X�g���N�^
//========================================
CText2D::~CText2D() 
{

}

//========================================
// ����������
//========================================
HRESULT CText2D::Init(void) 
{
	// �I�u�W�F�N�g2D�̃|�C���^�z����
	for (int nCntObj = 0; nCntObj < TXT_MAX; nCntObj++)
	{
		if (m_apObject2D[nCntObj] != NULL)
		{
			m_apObject2D[nCntObj]->Uninit();
			m_apObject2D[nCntObj] = NULL;
		}
	}

	// ��ސݒ�
	SetType(TYPE_TEXT2D);

	return S_OK;
}

//========================================
// �I������
//========================================
void CText2D::Uninit(void) 
{
	// �I�u�W�F�N�g2D�̃|�C���^�z����
	for (int nCntObj = 0; nCntObj < TXT_MAX; nCntObj++)
	{
		if (m_apObject2D[nCntObj] != NULL)
		{
			m_apObject2D[nCntObj]->Uninit();
			m_apObject2D[nCntObj] = NULL;
		}
	}

	Release();
}

//========================================
// �X�V����
//========================================
void CText2D::Update(void) 
{

}

//========================================
// �`�揈��
//========================================
void CText2D::Draw(void)
{

}

//========================================
// ������ݒ菈��
//========================================
void CText2D::SetString(char *pString) 
{
	// ��������
	sprintf(m_aString, pString);

	int nStrLen = (int)strlen(m_aString);

	for (int nCntDigit = 0; nCntDigit < TXT_MAX; nCntDigit++)
	{
		if (nCntDigit >= nStrLen)
		{// �����J�E���g��������̒����ɒB���Ă������A
		 // �I�u�W�F�N�g�̉��
			if (m_apObject2D[nCntDigit] != NULL)
			{
				m_apObject2D[nCntDigit]->Uninit();
				m_apObject2D[nCntDigit] = NULL;
			}
			continue;	// �܂�Ԃ�
		}
		else if (m_aString[nCntDigit] == ' ')
		{// �J�E���g�̕������󔒂̎��A
		 // �I�u�W�F�N�g�̉��
			if (m_apObject2D[nCntDigit] != NULL)
			{
				m_apObject2D[nCntDigit]->Uninit();
				m_apObject2D[nCntDigit] = NULL;
			}
			continue;	// �܂�Ԃ�
		}

		// ����
		if (m_apObject2D[nCntDigit] == NULL)
		{
			// �I�u�W�F�N�g2D
			CObject2D *pObject2D = NULL;

			// �I�u�W�F�N�g2D�̐���
			pObject2D = new CObject2D(PRIO_UI);

			// ����������
			pObject2D->Init();

			// �A�h���X���
			m_apObject2D[nCntDigit] = pObject2D;
		}

		// �ݒ�ʒu
		D3DXVECTOR3 setPos = m_pos;

		// �\���`���ɉ������ݒ�ʒu�̐ݒ�
		switch (m_disp)
		{
		case DISPLAY_CENTER:
			// �ݒ�ʒu�ɕ����̍ŏI�I�Ȓ����̔��������Z
			setPos.x -= m_fWidth * nStrLen * 0.5f;
			// �ݒ�ʒu�ɔz�u�ԊuX��K�p(���Z)
			setPos.x += ((float)nCntDigit + 0.5f) * m_fWidth;
			break;
		case DISPLAY_LEFT:
			// �ݒ�ʒu�ɔz�u�ԊuX��K�p(���Z)
			setPos.x += nCntDigit * m_fWidth;
			break;
		case DISPLAY_RIGHT:
			// �ݒ�ʒu�ɕ����̍ŏI�I�Ȓ��������Z
			setPos.x -= m_fWidth * (nStrLen - 1);
			// �ݒ�ʒu�ɔz�u�ԊuX��K�p(���Z)
			setPos.x += nCntDigit * m_fWidth;
			break;
		}

		// �ʒu�ݒ�
		m_apObject2D[nCntDigit]->SetPos(setPos);

		// �����ݒ�
		m_apObject2D[nCntDigit]->SetRot(INIT_D3DXVECTOR3);

		// �T�C�Y�ݒ�
		m_apObject2D[nCntDigit]->SetSize(m_fWidth, m_fHeight);

		// �p�^�[�����ݒ�
		m_apObject2D[nCntDigit]->SetPtn((int)m_aString[nCntDigit] - START_CHAR);
		m_apObject2D[nCntDigit]->SetPtnInfo(PTN_WIDTH, PTN_HEIGHT, PTN_MAX);

		// �e�N�X�`�����蓖��
		m_apObject2D[nCntDigit]->BindTexture(CTexture::TEX_SEA01);
	}
}

//========================================
// ��������
//========================================
CText2D *CText2D::Create(void)
{
	CText2D *pText2D = NULL;

	// �e�L�X�g2D�̐���
	pText2D = new CText2D;

	// ����������
	pText2D->Init();

	return pText2D;
}