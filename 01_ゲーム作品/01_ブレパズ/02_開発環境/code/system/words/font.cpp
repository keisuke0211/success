//========================================
// 
// �t�H���g
// 
//========================================
// *** font.cpp ***
//========================================
#include "font.h"
#include "../../manager.h"
#include "../renderer.h"

//�@�t�H���g�p�X
const char* CFont::s_FileName[] =
{
	"data/font/Nosutaru.ttf",
	"data/font/BestTen-CRT.otf",
	"data/font/FZ�S���^����.otf",
	"data/font/meiryob.ttc",
};
static_assert(sizeof(CFont::s_FileName) / sizeof(CFont::s_FileName[0]) == CFont::FONT_MAX, "bagu");

// �t�H���g��
const char* CFont::s_FontName[] =
{
	"�m�X�^���h�b�g�iM+�j",
	"BestTen-CRT",
	"FZ�S���^����",
	"���C���I",
};
static_assert(sizeof(CFont::s_FontName) / sizeof(CFont::s_FontName[0]) == CFont::FONT_MAX, "aho");


//========================================
// �R���X�g���N�^
//========================================
CFont::CFont() :
	m_texFont()
{
	memset(m_texFont, 0, sizeof(m_texFont));
}

//========================================
// �f�X�g���N�^
//========================================
CFont::~CFont()
{

}

//========================================
// �t�H���g�쐬
//========================================
void CFont::FontCreate(FONT nFont)
{
	assert(nFont >= 0 && nFont < FONT_MAX);

	if (m_texFont[nFont] != NULL)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �t�H���g���g����悤�ɂ���
	DESIGNVECTOR design;

	AddFontResourceEx(
		s_FileName[nFont], //ttf�t�@�C���ւ̃p�X
		FR_PRIVATE,
		&design
	);

	// �t�H���g�̐���
	int fontsize = 60;
	m_logFont[nFont] = { fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN };

	strcpy(m_logFont[nFont].lfFaceName, s_FontName[nFont]);
}

//========================================
// �e�N�X�`���쐬
//========================================
void CFont::TextureCreate(string nWords, FONT nFont)
{
	if (!(m_hFont[nFont] = CreateFontIndirect(&m_logFont[nFont])))
	{

	}

	// �f�o�C�X�R���e�L�X�g�擾
	// ���f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ɂȂ�
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, m_hFont[nFont]);

	string words = nWords;
	// �����R�[�h�擾
	const char *c = words.c_str();
	UINT code = 0;
#if _UNICODE
	// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ�
	code = (UINT)*c;
#else
	// �}���`�o�C�g�����̏ꍇ�A
	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]
	if (IsDBCSLeadByte(*c))
		code = (BYTE)c[0] << 8 | (BYTE)c[1];
	else
		code = c[0];
#endif

	// �t�H���g�r�b�g�}�b�v�擾
	TEXTMETRIC TM;
	GetTextMetrics(hdc, &TM);
	GLYPHMETRICS GM;
	CONST MAT2 Mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 2, NULL, &Mat);
	BYTE *ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
	SelectObject(hdc, oldFont);
	DeleteObject(m_hFont[nFont]);
	ReleaseDC(NULL, hdc);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���쐬
	if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_texFont[nFont], NULL)))
		if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_texFont[nFont], NULL)))
		{

		}

	// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v��������
	D3DLOCKED_RECT LockedRect;
	if (FAILED(m_texFont[nFont]->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
		if (FAILED(m_texFont[nFont]->LockRect(0, &LockedRect, NULL, 0)))
		{

		}

	// �t�H���g���̏�������
	// iOfs_x, iOfs_y : �����o���ʒu(����)
	// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
	// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	DWORD Alpha, Color;
	FillMemory(LockedRect.pBits, LockedRect.Pitch * TM.tmHeight, 0);

	int nBlackBox = GM.gmBlackBoxX;
	for (int y = iOfs_y; y<iOfs_y + iBmp_h; y++)
		for (int x = iOfs_x; x<iOfs_x + nBlackBox; x++) {
			Alpha = (255 * ptr[x - iOfs_x + iBmp_w*(y - iOfs_y)]) / (Level - 1);
			Color = 0x00ffffff | (Alpha << 24);
			memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch*y + 4 * x, &Color, sizeof(DWORD));
		}

	// �e�N�X�`���̃��b�N
	m_texFont[nFont]->UnlockRect(0);

	delete[] ptr;
}

//========================================
// �S�Ĕj��
//========================================
void CFont::ReleaseAll(void)
{
	for (int nFont = 0; nFont < FONT_MAX; ++nFont)
	{
		if (m_texFont[nFont] != NULL)
		{// �e�N�X�`���̉��
			m_texFont[nFont]->Release();
			m_texFont[nFont] = NULL;
		}
	}
}

//========================================
// �w��̔j��
//========================================
void CFont::Release(FONT nFont)
{
	assert(nFont >= 0 && nFont < FONT_MAX);
	DESIGNVECTOR design;

	if (m_texFont[nFont] != NULL)
	{// �e�N�X�`���̉��
		m_texFont[nFont]->Release();
		m_texFont[nFont] = NULL;
	}
	if (s_FileName[nFont] != NULL)
	{
		// �t�H���g�폜
		RemoveFontResourceEx(
			TEXT(s_FileName[nFont]), //ttf�t�@�C���ւ̃p�X
			FR_PRIVATE,
			&design
		);
	}
}

//========================================
// �e�N�X�`�����̎擾
//========================================
LPDIRECT3DTEXTURE9 CFont::GetFont(string words, FONT nFont)
{
	if (nFont == FONT_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return NULL;
	}

	assert(nFont >= 0 && nFont < FONT_MAX);

	// �ǂݍ���
	FontCreate(nFont);

	TextureCreate(words, nFont);

	return m_texFont[nFont];
}