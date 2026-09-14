#pragma once

#define INVALID_OBJECT_ID	0xFFFF

class CObjectPool
{
private:
	BOOL		m_bObjectSlotState[MAX_OBJECTS];
	CObject		*m_pObjects[MAX_OBJECTS];


public:
	CObjectPool();
	~CObjectPool();

	BOOL New(WORD wObjectID, int iModel, VECTOR vecPos, VECTOR vecRot);
	BOOL Delete(WORD wObjectID);

	// Find out if the slot is inuse.
	BOOL GetSlotState(WORD wObjectID) {
		if(wObjectID >= MAX_OBJECTS) { return FALSE; }
		return m_bObjectSlotState[wObjectID];
	};

	// Retrieve an object
	CObject* GetAt(WORD wObjectID) {
		if(wObjectID >= MAX_OBJECTS || !m_bObjectSlotState[wObjectID]) { return NULL; }
		return m_pObjects[wObjectID];
	};

	int FindIDFromGtaPtr(ENTITY_TYPE * pGtaObject);
	
	CObject* GetObjFromGtaPtr(ENTITY_TYPE *pGtaObject);

	void Process();
};