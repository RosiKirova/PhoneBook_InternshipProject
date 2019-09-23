// CitiesTable.cpp
//

#include "stdafx.h"
#include "CitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

// Constructor / Destructor
// ----------------

CCitiesTable::CCitiesTable() : CTemplateTable(_T("CITIES"))
{
}

CCitiesTable::~CCitiesTable()
{
}


// Methods
// ----------------
CITIES& CCitiesTable::GetAccessorRecord()
{
	return m_recCities;
}

long& CCitiesTable::GetUpdateCounterValue(CITIES& recCity)
{
	return recCity.lUpdateCounter;
}


// Overrides
// ----------------