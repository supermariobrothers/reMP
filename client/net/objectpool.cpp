#include "../main.h"
#include "../game/util.h"

extern CGame	*pGame;

CObjectPool::CObjectPool()
{
	for(int i = 0; i < MAX_OBJECTS; i++)
	{
		m_bObjectSlotState[i]	= FALSE;
		m_pObjects[i]			= NULL;
	}
}

CObjectPool::~CObjectPool()
{
	for(int i = 0; i < MAX_OBJECTS; i++)
	{
		Delete((WORD)i);
	}
}

BOOL CObjectPool::Delete(WORD wObjectID)
{
	if(wObjectID >= MAX_OBJECTS || !GetSlotState(wObjectID) || !m_pObjects[wObjectID])
	{
		return FALSE; // Object already deleted or not used.
	}

	m_bObjectSlotState[wObjectID] = FALSE;
	delete m_pObjects[wObjectID];
	m_pObjects[wObjectID] = NULL;

	return TRUE;
}

BOOL CObjectPool::New(WORD wObjectID, int iModel, VECTOR vecPos, VECTOR vecRot)
{
	if (wObjectID >= MAX_OBJECTS) return FALSE;

	if (m_pObjects[wObjectID] != NULL)
	{
		Delete(wObjectID);
	}

	m_pObjects[wObjectID] = pGame->NewObject(iModel, vecPos.X, vecPos.Y, vecPos.Z, vecRot);

	if (m_pObjects[wObjectID])
	{
		m_bObjectSlotState[wObjectID] = TRUE;

		return TRUE;
	}

	return FALSE; // Will only be called if m_pObjects[wObjectID] is null
}

//----------------------------------------------------

CObject* CObjectPool::GetObjFromGtaPtr(ENTITY_TYPE * pGtaObject)
{
	for (int x = 0; x < MAX_OBJECTS; x++) {
		if (m_pObjects[x])
		{
			if(pGtaObject == m_pObjects[x]->m_pEntity) return m_pObjects[x];
		}
	}

	return NULL;
}

int CObjectPool::FindIDFromGtaPtr(ENTITY_TYPE * pGtaObject)
{
	for (int x = 0; x < MAX_OBJECTS; x++) {
		if (m_pObjects[x])
		{
			if(pGtaObject == m_pObjects[x]->m_pEntity) return x;
		}
	}

	return INVALID_OBJECT_ID;
}

void CObjectPool::Process()
{
	static unsigned long s_ulongLastCall = 0;
	if (!s_ulongLastCall) s_ulongLastCall = GetTickCount();
	unsigned long ulongTick = GetTickCount();
	float fElapsedTime = ((float)(ulongTick - s_ulongLastCall)) / 1000.0f;
	// Get elapsed time in seconds
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (m_bObjectSlotState[i] && m_pObjects[i]) m_pObjects[i]->Process(fElapsedTime);
	}
	s_ulongLastCall = ulongTick;
}