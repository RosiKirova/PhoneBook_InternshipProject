#include "stdafx.h"
#include "PhoneTypesData.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDataClass

// Constructor / Destructor
// ----------------

CPhoneTypesData::CPhoneTypesData()
{
}

CPhoneTypesData::~CPhoneTypesData()
{
}


// Methods
// ----------------
BOOL CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTypesArray)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (oPhoneTypesTable.SelectAll(oPhoneTypesArray) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (oPhoneTypesTable.SelectWhereID(lID, recPhoneType) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypesData::UpdateWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (oPhoneTypesTable.UpdateWhereID(lID, recPhoneType) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypesData::Insert(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (oPhoneTypesTable.Insert(recPhoneType) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypesData::DeleteWhereID(const long lID)
{
	CPhoneTypesTable oPhoneTypesTable;
	if (oPhoneTypesTable.DeleteWhereID(lID) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}


// Overrides
// ----------------