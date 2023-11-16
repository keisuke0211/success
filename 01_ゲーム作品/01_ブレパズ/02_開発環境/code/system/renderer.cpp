//========================================
// 
// �`�揈��
// 
//========================================
// *** renderer.cpp ***
//========================================
#include "renderer.h"
#include "../object\object.h"

// �ÓI�ϐ�
LPD3DXFONT CRenderer::m_pFont = NULL;	// �t�H���g

//========================================
// �R���X�g���N�^
//========================================
CRenderer::CRenderer()
{
	// �l���N���A����
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CRenderer::~CRenderer()
{

}

//========================================
// �`��̏���������
//========================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        //�f�B�X�v���C���[�h

								 //Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));   //�p�����[�^�̃[���N���A

	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;								//�Q�[����ʃT�C�Y(��)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y(����)
	m_d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	m_d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	m_d3dpp.EnableAutoDepthStencil = TRUE;								//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	m_d3dpp.Windowed = bWindow;											//�E�C���h�E���[�h
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//�C���^�[�o��

																		//Direct3D�f�o�C�X������
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,                     //�`�揈��
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,//���_����
		&m_d3dpp,
		&m_pD3DDevice)))                    //�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,//�`�揈��
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,//���_����
			&m_d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,                     //�`�揈��
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,//���_����
				&m_d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PALETTE,
		"Terminal", &m_pFont);

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//D3DCULL_NONE�@�J�����O���� D3DCULL_CW �\�ʃJ�����O�@D3DCULL_CCW�@���ʃJ�����O
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//========================================
// �`��̏I������
//========================================
void CRenderer::Uninit(void)
{
	// �I�u�W�F�N�g�̑S�̂̔j��
	CObject::ReleaseAll();

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}


	// �I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//========================================
// �`��̍X�V����
//========================================
void CRenderer::Update(void)
{
	CObject::UpdateAll();		// �I�u�W�F�N�g�S��
}

//========================================
// �`��̕`�揈��
//========================================
void CRenderer::Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

	 // �I�u�W�F�N�g�S�̂̕`�揈��
		CObject::DrawAll();

		//�`��I��
		m_pD3DDevice->EndScene();

#ifdef _DEBUG

		//FPS�̕\��
		DrawFPS();

#endif // _DEBUG
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================================
// FPS����
//========================================
void CRenderer::DrawFPS(void)
{
	//�e�L�X�g�̕`�揈��
	RECT rect = { 0,230,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[521];

	//������ɑ��
	sprintf(&aStr[0], "FPS:%d\n", GetFps());

	//�e�L�X�g�̕`��
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}