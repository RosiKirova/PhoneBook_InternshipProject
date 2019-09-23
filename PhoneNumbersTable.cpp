// PhoneNumbersTable.cpp
//

#include "stdafx.h"
#include "PhoneNumbersTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable


const CString CPhoneNumbersTable::_strColumnPersonID = _T("PERSON_ID");

// Constructor / Destructor
// ----------------

CPhoneNumbersTable::CPhoneNumbersTable() : CTemplateTable(_T("PHONE_NUMBERS"))
{

}

CPhoneNumbersTable::CPhoneNumbersTable(CSession& oSessionMutual) : CTemplateTable(_T("PHONE_NUMBERS"), oSessionMutual)
{

}

CPhoneNumbersTable::~CPhoneNumbersTable()
{
}


// Methods
// ----------------
PHONE_NUMBERS& CPhoneNumbersTable::GetAccessorRecord()
{
	return m_recPhoneNumbers;
}

long& CPhoneNumbersTable::GetUpdateCounterValue(PHONE_NUMBERS& recPhoneNumber)
{
	return recPhoneNumber.lUpdateCounter;
}


// Overrides
// ----------------