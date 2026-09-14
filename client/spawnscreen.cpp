#include "main.h"
#include "spawnscreen.h"

extern CDXUTDialogResourceManager *pDialogResourceManager;
extern CNetGame *pNetGame;
extern CGame *pGame;

CSpawnScreen::CSpawnScreen(IDirect3DDevice9 *pD3DDevice)
{
	m_pDialog = NULL;
	SetupUI();
}

CSpawnScreen::~CSpawnScreen()
{
	ToggleVisibility(FALSE);
	SAFE_DELETE(m_pDialog);
}

void CSpawnScreen::Draw()
{
	if (m_pDialog && m_pDialog->GetVisible()) {
		RECT rect;
		GetClientRect(pGame->GetMainWindowHwnd(), &rect);

		m_pDialog->SetLocation(
			(rect.right / 2) - (m_pDialog->GetWidth() / 2),
			rect.bottom - m_pDialog->GetHeight() - 50);

		m_pDialog->OnRender(10.0f);
	}
}

void CSpawnScreen::SetupUI()
{
	SAFE_DELETE(m_pDialog);

	m_pDialog = new CDXUTDialog();
	if (m_pDialog && pDialogResourceManager) {
		m_pDialog->Init(pDialogResourceManager);
		m_pDialog->SetCallback(CSpawnScreen::OnEvent);
		m_pDialog->SetLocation(0, 0);
		m_pDialog->SetSize(310, 40);
		m_pDialog->SetBackgroundColors(0x960A0A0A);
		m_pDialog->EnableMouseInput(true);
		m_pDialog->EnableKeyboardInput(false);
		m_pDialog->SetVisible(false);

		m_pDialog->AddButton(ID_CONTROL_LEFT, "<<", 10, 5, 90, 30, 0, false, NULL);
		m_pDialog->AddButton(ID_CONTROL_RIGHT, ">>", 110, 5, 90, 30, 0, false, NULL);
		m_pDialog->AddButton(ID_CONTROL_SPAWN, "Spawn", 210, 5, 90, 30, 0, false, NULL);
	}
}

BOOL CSpawnScreen::MsgProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (!m_pDialog || !m_pDialog->GetVisible()) return FALSE;

	if (uiMsg == WM_KEYDOWN) {
		if (wParam == VK_LEFT || wParam == 'A') {
			OnEvent(EVENT_BUTTON_CLICKED, ID_CONTROL_LEFT, NULL, NULL);
			return TRUE;
		} else if (wParam == VK_RIGHT || wParam == 'D') {
			OnEvent(EVENT_BUTTON_CLICKED, ID_CONTROL_RIGHT, NULL, NULL);
			return TRUE;
		} else if (wParam == VK_RETURN || wParam == VK_SPACE || wParam == VK_SHIFT) {
			OnEvent(EVENT_BUTTON_CLICKED, ID_CONTROL_SPAWN, NULL, NULL);
			return TRUE;
		}
	}

	return m_pDialog->MsgProc(hwnd, uiMsg, wParam, lParam) ? TRUE : FALSE;
}

VOID CALLBACK CSpawnScreen::OnEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext)
{
	if (pNetGame && nEvent == EVENT_BUTTON_CLICKED) {
		CLocalPlayer* pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();
		if (pLocalPlayer) {
			pLocalPlayer->ProcessClassSelection(nControlID);
		}
	}
}

void CSpawnScreen::ToggleVisibility(BOOL bVisible)
{
	if (m_pDialog) {
		m_pDialog->SetVisible(bVisible ? true : false);
	}
	if (pGame) {
		pGame->SetCursorMode(bVisible ? 2 : 0, bVisible ? FALSE : TRUE);
	}
}
