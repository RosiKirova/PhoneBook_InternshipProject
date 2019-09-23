// PersonsTable.cpp
//

#include "stdafx.h"
#include "PersonsTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

// Constructor / Destructor
// ----------------

CPersonsTable::CPersonsTable() : CTemplateTable(_T("PERSONS"))
{
}

CPersonsTable::CPersonsTable(CSession& oSessionMutual) : CTemplateTable(_T("PERSONS"), oSessionMutual)
{

}

CPersonsTable::~CPersonsTable()
{
}


// Methods
// ----------------
PERSONS& CPersonsTable::GetAccessorRecord()
{
	return m_recPersons;
}

long& CPersonsTable::GetUpdateCounterValue(PERSONS& recPerson)
{
	return recPerson.lUpdateCounter;
}


// Overrides
// ----------------