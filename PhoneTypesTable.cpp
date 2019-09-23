// PhoneTypesTable.cpp
//

#include "stdafx.h"
#include "PhoneTypesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTableClass

// Constructor / Destructor
// ----------------

CPhoneTypesTable::CPhoneTypesTable() : CTemplateTable(_T("PHONE_TYPES"))
{

}

CPhoneTypesTable::~CPhoneTypesTable()
{

}


// Methods
// ----------------
PHONE_TYPES& CPhoneTypesTable::GetAccessorRecord()
{
	return m_recPhoneTypes;
}

long& CPhoneTypesTable::GetUpdateCounterValue(PHONE_TYPES& recPhoneType)
{
	return recPhoneType.lUpdateCounter;
}

// Overrides
// ----------------