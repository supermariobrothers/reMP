#include "main.h"
#include "colorembed.h"

static ID3DXSprite* pSavedSprite = NULL;
static D3DCOLOR SavedColor = 0xFFFFFFFF;
static size_t nLastStringIndex = 0;
static char* szModifiedString = NULL;
static char* szOriginalString = NULL;
static wchar_t wszStringCopy[MAX_CE_STRING_LENGTH];

static ID3DXSpriteCE x;
static ID3DXSprite* pFakeSprite = &x;

void AllocateBufferForColorEmbed()
{
	if (!szModifiedString)
		szModifiedString = (char*)calloc(1, MAX_CE_STRING_LENGTH + 1);
	if (!szOriginalString)
		szOriginalString = (char*)calloc(1, MAX_CE_STRING_LENGTH + 1);
}

static inline bool IsHexChar(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

static inline bool IsHexCharW(wchar_t c)
{
	return (c >= L'0' && c <= L'9') || (c >= L'a' && c <= L'f') || (c >= L'A' && c <= L'F');
}

unsigned long GetColorFromStringEmbed(char* szString)
{
	char szHex[7] = { 0 };

	if (szString &&
		*szString == '{' &&
		*(szString + 1) && IsHexChar(*(szString + 1)) &&
		*(szString + 2) && IsHexChar(*(szString + 2)) &&
		*(szString + 3) && IsHexChar(*(szString + 3)) &&
		*(szString + 4) && IsHexChar(*(szString + 4)) &&
		*(szString + 5) && IsHexChar(*(szString + 5)) &&
		*(szString + 6) && IsHexChar(*(szString + 6)) &&
		*(szString + 7) && *(szString + 7) == '}')
	{
		strncpy(szHex, szString + 1, 6);
		szHex[6] = '\0';
		return strtoul(szHex, NULL, 16);
	}
	return (unsigned long)-1;
}

unsigned long GetColorFromStringEmbedW(wchar_t* wszString)
{
	wchar_t wszHex[7] = { 0 };

	if (wszString &&
		*wszString == L'{' &&
		*(wszString + 1) && IsHexCharW(*(wszString + 1)) &&
		*(wszString + 2) && IsHexCharW(*(wszString + 2)) &&
		*(wszString + 3) && IsHexCharW(*(wszString + 3)) &&
		*(wszString + 4) && IsHexCharW(*(wszString + 4)) &&
		*(wszString + 5) && IsHexCharW(*(wszString + 5)) &&
		*(wszString + 6) && IsHexCharW(*(wszString + 6)) &&
		*(wszString + 7) && *(wszString + 7) == L'}')
	{
		wcsncpy(wszHex, wszString + 1, 6);
		wszHex[6] = L'\0';
		return wcstoul(wszHex, NULL, 16);
	}
	return (unsigned long)-1;
}

int ConvertMultiToWideString(const char* szSource, wchar_t* szDest, int iLen)
{
	if (!szSource || !szDest || iLen <= 0) return 0;
	memset(szDest, 0, sizeof(wchar_t) * iLen);
	int nSourceLen = (int)strlen(szSource);
	int iResult = MultiByteToWideChar(CP_ACP, 0, szSource, nSourceLen, NULL, 0);
	if (iResult < iLen) {
		MultiByteToWideChar(CP_ACP, 0, szSource, nSourceLen, szDest, iResult);
		szDest[iResult] = L'\0';
	}
	return iResult;
}

void RemoveColorEmbedsFromString(char* szString)
{
	if (!szString) return;
	char* szCurrent = szString;
	char* szNext = szString + 8;
	while (*szCurrent)
	{
		if (GetColorFromStringEmbed(szCurrent) == (unsigned long)-1)
		{
			szCurrent++;
			szNext++;
		}
		else
		{
			char* src = szNext;
			char* dst = szCurrent;
			while (*src) {
				*dst++ = *src++;
			}
			*dst = '\0';
			szNext = szCurrent + 8;
		}
	}
	*szCurrent = '\0';
}

static int ProcessStringForColorEmbed()
{
	unsigned long i;
	size_t n1, n2;
	wchar_t c;

	n1 = nLastStringIndex;
	c = *(wszStringCopy + nLastStringIndex);
	if (c)
	{
		do {
			if (c != L' ' && c != L'\t' && c != L'\n' && c != L'\r')
				break;
			c = *(wszStringCopy + n1++ + 1);
		} while (c);
		nLastStringIndex = n1;
	}

	for (i = GetColorFromStringEmbedW(wszStringCopy + n1);
		i != (unsigned long)-1;
		i = GetColorFromStringEmbedW(wszStringCopy + n2))
	{
		n2 = nLastStringIndex + 8;
		SavedColor = (D3DCOLOR)(i | 0xFF000000);
		c = *(wszStringCopy + nLastStringIndex + 8);
		nLastStringIndex += 8;
		if (c)
		{
			do {
				if (c != L' ' && c != L'\t' && c != L'\n' && c != L'\r')
					break;
				c = *(wszStringCopy + n2++ + 1);
			} while (c);
			nLastStringIndex = n2;
		}
	}
	n1 = nLastStringIndex;
	if (szOriginalString && szOriginalString[nLastStringIndex])
		n1 = nLastStringIndex++ + 1;
	return (int)n1;
}

//----------------------------------------------------
// ID3DXFontCE
//----------------------------------------------------

HRESULT __stdcall ID3DXFontCE::QueryInterface(REFIID iid, LPVOID* ppv)
{
	return m_pFont->QueryInterface(iid, ppv);
}

ULONG __stdcall ID3DXFontCE::AddRef()
{
	return m_pFont->AddRef();
}

ULONG __stdcall ID3DXFontCE::Release()
{
	return m_pFont->Release();
}

HRESULT __stdcall ID3DXFontCE::GetDevice(LPDIRECT3DDEVICE9* ppDevice)
{
	return m_pFont->GetDevice(ppDevice);
}

HRESULT __stdcall ID3DXFontCE::GetDescA(D3DXFONT_DESCA* pDesc)
{
	return m_pFont->GetDescA(pDesc);
}

HRESULT __stdcall ID3DXFontCE::GetDescW(D3DXFONT_DESCW* pDesc)
{
	return m_pFont->GetDescW(pDesc);
}

BOOL __stdcall ID3DXFontCE::GetTextMetricsA(TEXTMETRICA* pTextMetrics)
{
	return m_pFont->GetTextMetricsA(pTextMetrics);
}

BOOL __stdcall ID3DXFontCE::GetTextMetricsW(TEXTMETRICW* pTextMetrics)
{
	return m_pFont->GetTextMetricsW(pTextMetrics);
}

HDC __stdcall ID3DXFontCE::GetDC()
{
	return m_pFont->GetDC();
}

HRESULT __stdcall ID3DXFontCE::GetGlyphData(UINT Glyph, LPDIRECT3DTEXTURE9* ppTexture, RECT* pBlackBox, POINT* pCellInc)
{
	return m_pFont->GetGlyphData(Glyph, ppTexture, pBlackBox, pCellInc);
}

HRESULT __stdcall ID3DXFontCE::PreloadCharacters(UINT First, UINT Last)
{
	return m_pFont->PreloadCharacters(First, Last);
}

HRESULT __stdcall ID3DXFontCE::PreloadGlyphs(UINT First, UINT Last)
{
	return m_pFont->PreloadGlyphs(First, Last);
}

HRESULT __stdcall ID3DXFontCE::PreloadTextA(LPCSTR pString, INT Count)
{
	return m_pFont->PreloadTextA(pString, Count);
}

HRESULT __stdcall ID3DXFontCE::PreloadTextW(LPCWSTR pString, INT Count)
{
	return m_pFont->PreloadTextW(pString, Count);
}

INT __stdcall ID3DXFontCE::DrawTextA(LPD3DXSPRITE pSprite, LPCSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color)
{
	if (pSprite && pString)
	{
		AllocateBufferForColorEmbed();
		pSavedSprite = pSprite;
		SavedColor = Color;
		nLastStringIndex = 0;

		strncpy(szOriginalString, pString, MAX_CE_STRING_LENGTH - 1);
		szOriginalString[MAX_CE_STRING_LENGTH - 1] = '\0';
		strncpy(szModifiedString, pString, MAX_CE_STRING_LENGTH - 1);
		szModifiedString[MAX_CE_STRING_LENGTH - 1] = '\0';
		ConvertMultiToWideString(szOriginalString, wszStringCopy, MAX_CE_STRING_LENGTH);
		RemoveColorEmbedsFromString(szModifiedString);
		return m_pFont->DrawTextA(pFakeSprite, szModifiedString, (INT)strlen(szModifiedString), pRect, Format, Color);
	}
	return m_pFont->DrawTextA(pSprite, pString, Count, pRect, Format, Color);
}

INT __stdcall ID3DXFontCE::DrawTextW(LPD3DXSPRITE pSprite, LPCWSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color)
{
	return m_pFont->DrawTextW(pSprite, pString, Count, pRect, Format, Color);
}

HRESULT __stdcall ID3DXFontCE::OnLostDevice()
{
	return m_pFont->OnLostDevice();
}

HRESULT __stdcall ID3DXFontCE::OnResetDevice()
{
	return m_pFont->OnResetDevice();
}

//----------------------------------------------------
// ID3DXSpriteCE
//----------------------------------------------------

HRESULT __stdcall ID3DXSpriteCE::QueryInterface(REFIID iid, LPVOID* ppv)
{
	return pSavedSprite ? pSavedSprite->QueryInterface(iid, ppv) : E_FAIL;
}

ULONG __stdcall ID3DXSpriteCE::AddRef()
{
	return pSavedSprite ? pSavedSprite->AddRef() : 0;
}

ULONG __stdcall ID3DXSpriteCE::Release()
{
	return pSavedSprite ? pSavedSprite->Release() : 0;
}

HRESULT __stdcall ID3DXSpriteCE::GetDevice(LPDIRECT3DDEVICE9* ppDevice)
{
	return pSavedSprite ? pSavedSprite->GetDevice(ppDevice) : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::GetTransform(D3DXMATRIX* pTransform)
{
	return pSavedSprite ? pSavedSprite->GetTransform(pTransform) : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::SetTransform(CONST D3DXMATRIX* pTransform)
{
	return pSavedSprite ? pSavedSprite->SetTransform(pTransform) : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::SetWorldViewRH(CONST D3DXMATRIX* pWorld, CONST D3DXMATRIX* pView)
{
	return pSavedSprite ? pSavedSprite->SetWorldViewRH(pWorld, pView) : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::SetWorldViewLH(CONST D3DXMATRIX* pWorld, CONST D3DXMATRIX* pView)
{
	return pSavedSprite ? pSavedSprite->SetWorldViewLH(pWorld, pView) : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::Begin(DWORD Flags)
{
	return pSavedSprite ? pSavedSprite->Begin(Flags) : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::Draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT* pSrcRect, CONST D3DXVECTOR3* pCenter, CONST D3DXVECTOR3* pPosition, D3DCOLOR Color)
{
	ProcessStringForColorEmbed();
	return pSavedSprite ? pSavedSprite->Draw(pTexture, pSrcRect, pCenter, pPosition, SavedColor) : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::Flush()
{
	return pSavedSprite ? pSavedSprite->Flush() : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::End()
{
	return pSavedSprite ? pSavedSprite->End() : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::OnLostDevice()
{
	return pSavedSprite ? pSavedSprite->OnLostDevice() : E_FAIL;
}

HRESULT __stdcall ID3DXSpriteCE::OnResetDevice()
{
	return pSavedSprite ? pSavedSprite->OnResetDevice() : E_FAIL;
}
