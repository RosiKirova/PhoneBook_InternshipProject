#include "stdafx.h"
#include "CitiesData.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDataClass

// Constructor / Destructor
// ----------------

CCitiesData::CCitiesData()
{
}

CCitiesData::~CCitiesData()
{
}


// Methods
// ----------------
BOOL CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
{
	CCitiesTable oCitiesTable;
	if (oCitiesTable.SelectAll(oCitiesArray) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCity)
{
	CCitiesTable oCitiesTable;
	if (oCitiesTable.SelectWhereID(lID, recCity) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCitiesData::UpdateWhereID(const long lID, CITIES& recCity)
{
	CCitiesTable oCitiesTable;
	if (oCitiesTable.UpdateWhereID(lID, recCity) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCitiesData::Insert(CITIES& recCity)
{
	CCitiesTable oCitiesTable;
	if (oCitiesTable.Insert(recCity) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCitiesData::DeleteWhereID(const long lID)
{
	CCitiesTable oCitiesTable;
	if (oCitiesTable.DeleteWhereID(lID) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}


// Overrides
// ----------------