#pragma once

#include <d3d9.h>
#include "d3d9/include/d3dx9core.h"

#define MAX_CE_STRING_LENGTH 4096

void AllocateBufferForColorEmbed();
void RemoveColorEmbedsFromString(char* szString);
unsigned long GetColorFromStringEmbed(char* szString);
unsigned long GetColorFromStringEmbedW(wchar_t* wszString);
int ConvertMultiToWideString(const char* szSource, wchar_t* szDest, int iLen);

struct ID3DXFontCE : public ID3DXFont
{
public:
	HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall GetDevice(LPDIRECT3DDEVICE9* ppDevice);
	HRESULT __stdcall GetDescA(D3DXFONT_DESCA* pDesc);
	HRESULT __stdcall GetDescW(D3DXFONT_DESCW* pDesc);
	BOOL __stdcall GetTextMetricsA(TEXTMETRICA* pTextMetrics);
	BOOL __stdcall GetTextMetricsW(TEXTMETRICW* pTextMetrics);
	HDC __stdcall GetDC();
	HRESULT __stdcall GetGlyphData(UINT Glyph, LPDIRECT3DTEXTURE9* ppTexture, RECT* pBlackBox, POINT* pCellInc);
	HRESULT __stdcall PreloadCharacters(UINT First, UINT Last);
	HRESULT __stdcall PreloadGlyphs(UINT First, UINT Last);
	HRESULT __stdcall PreloadTextA(LPCSTR pString, INT Count);
	HRESULT __stdcall PreloadTextW(LPCWSTR pString, INT Count);
	INT __stdcall DrawTextA(LPD3DXSPRITE pSprite, LPCSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color);
	INT __stdcall DrawTextW(LPD3DXSPRITE pSprite, LPCWSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color);
	HRESULT __stdcall OnLostDevice();
	HRESULT __stdcall OnResetDevice();

	inline void SetDXFont(ID3DXFont* pFont) { m_pFont = pFont; }
	inline ID3DXFont* GetDXFont() { return m_pFont; }

private:
	ID3DXFont* m_pFont;
};

struct ID3DXSpriteCE : public ID3DXSprite
{
	HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall GetDevice(LPDIRECT3DDEVICE9* ppDevice);
	HRESULT __stdcall GetTransform(D3DXMATRIX* pTransform);
	HRESULT __stdcall SetTransform(CONST D3DXMATRIX* pTransform);
	HRESULT __stdcall SetWorldViewRH(CONST D3DXMATRIX* pWorld, CONST D3DXMATRIX* pView);
	HRESULT __stdcall SetWorldViewLH(CONST D3DXMATRIX* pWorld, CONST D3DXMATRIX* pView);
	HRESULT __stdcall Begin(DWORD Flags);
	HRESULT __stdcall Draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT* pSrcRect, CONST D3DXVECTOR3* pCenter, CONST D3DXVECTOR3* pPosition, D3DCOLOR Color);
	HRESULT __stdcall Flush();
	HRESULT __stdcall End();
	HRESULT __stdcall OnLostDevice();
	HRESULT __stdcall OnResetDevice();
};
