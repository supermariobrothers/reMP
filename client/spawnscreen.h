#pragma once

#include "d3d9/common/DXUTgui.h"

#define ID_CONTROL_LEFT		1
#define ID_CONTROL_RIGHT	2
#define ID_CONTROL_SPAWN	3

class CSpawnScreen
{
private:
	CDXUTDialog* m_pDialog;

public:
	void SetupUI();
	void ToggleVisibility(BOOL bVisible);
	BOOL MsgProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
	static VOID CALLBACK OnEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext);
	void Draw();

	void RestoreDeviceObjects() {};
	void DeleteDeviceObjects() {};
	void SetSpawnText(CHAR* szSpawnText) {};

	BOOL IsVisible() { return (m_pDialog && m_pDialog->GetVisible()) ? TRUE : FALSE; };

	CSpawnScreen(IDirect3DDevice9 *pD3DDevice = NULL);
	~CSpawnScreen();
};