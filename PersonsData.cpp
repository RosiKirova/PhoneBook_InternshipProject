#include "stdafx.h"
#include "PersonsData.h"
#include "DataSourceAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDataClass

// Constructor / Destructor
// ----------------

CPersonsData::CPersonsData()
{
}

CPersonsData::~CPersonsData()
{
}


// Methods
// ----------------

BOOL CPersonsData::SelectPerson(const long lID, CPersonDetails& oPersonDetails)
{
	// Getting the searched person
	CPersonsTable oPersonsTable;
	
	if (oPersonsTable.SelectWhereID(lID, oPersonDetails.GetPerson()) == FALSE)
	{
		return FALSE;
	}

	// Getting the phone numbers of the searched person
	CPhoneNumbersTable oPhoneNumbersTable;

	CString strID;
	strID.Format(_T("%d"), lID);

	if (oPhoneNumbersTable.SelectWhereColumnName(CPhoneNumbersTable::_strColumnPersonID, strID, oPersonDetails.GetPhoneNumbersArray()) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::DeletePerson(const long lID)
{
	// Opening a session
	CSession oSession;
	InitializeSession(oSession);

	// Starting a transaction
	HRESULT hResult = oSession.StartTransaction();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("An error occurred. A transaction cannot be started."));

		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Deleting the phone numbers of a person
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	CPhoneNumbersArray oPhoneNumbersArray;

	CString strID;
	strID.Format(_T("%d"), lID);

	if (oPhoneNumbersTable.SelectWhereColumnName(CPhoneNumbersTable::_strColumnPersonID, strID, oPhoneNumbersArray) == FALSE)
	{
		if (Abort(oSession) == FALSE)
		{
			return FALSE;
		}

		// Closing the session
		oSession.Close();

		return FALSE;
	}

	for (INT_PTR nIndex = 0; nIndex < oPhoneNumbersArray.GetCount(); nIndex++)
	{
		long lID = oPhoneNumbersArray.GetAt(nIndex)->lID;
		if (oPhoneNumbersTable.DeleteWhereID(lID) == FALSE)
		{
			if (Abort(oSession) == FALSE)
			{
				return FALSE;
			}
			
			// Closing the session
			oSession.Close();

			return FALSE;
		}
	}

	// Deleting the person
	CPersonsTable oPersonsTable(oSession);

	if (oPersonsTable.DeleteWhereID(lID) == FALSE)
	{
		if (Abort(oSession) == FALSE)
		{
			return FALSE;
		}
		
		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Ending the transaction
	hResult = oSession.Commit();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("An error occurred. A transaction cannot be ended."));
 
		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Closing the session
	oSession.Close();

	return TRUE;
}

BOOL CPersonsData::InsertPerson(CPersonDetails& oPersonDetails)
{
	// Opening a session
	CSession oSession;
	InitializeSession(oSession);

	// Starting a transaction
	HRESULT hResult = oSession.StartTransaction();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("An error occurred. A transaction cannot be started."));

		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Adding a person
	CPersonsTable oPersonsTable(oSession);

	if (oPersonsTable.Insert(oPersonDetails.GetPerson()) == FALSE)
	{
		if (Abort(oSession) == FALSE)
		{
			return FALSE;
		}
		
		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Adding the phone numbers of the just added person
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	PERSONS recPerson = oPersonDetails.GetPerson();

	for (INT_PTR nIndex = 0; nIndex < oPersonDetails.GetPhoneNumbersArray().GetCount(); nIndex++)
	{
		PHONE_NUMBERS* pPhoneNumber = oPersonDetails.GetPhoneNumbersArray().GetAt(nIndex);
		pPhoneNumber->lPersonId = recPerson.lID;

		if (oPhoneNumbersTable.Insert(*pPhoneNumber) == FALSE)
		{
			if (Abort(oSession) == FALSE)
			{
				return FALSE;
			}
			
			// Closing the session
			oSession.Close();

			return FALSE;
		}
	}

	// Ending the transaction
	hResult = oSession.Commit();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("An error occurred. A transaction cannot be ended."));

		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Closing the session
	oSession.Close();

	return TRUE;
}

BOOL CPersonsData::UpdatePerson(const long lID, CPersonDetails& oPersonDetails)
{
	// Opening a session
	CSession oSession;
	InitializeSession(oSession);

	// Starting a transaction
	HRESULT hResult = oSession.StartTransaction(ISOLATIONLEVEL_SERIALIZABLE);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("An error occurred. A transaction cannot be started."));

		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Modifying the person
	CPersonsTable oPersonsTable(oSession);

	if (oPersonsTable.UpdateWhereID(lID, oPersonDetails.GetPerson()) == FALSE)
	{
		if (Abort(oSession) == FALSE)
		{
			return FALSE;
		}
		
		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Modifying the phone numbers of the just modified person
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	CPhoneNumbersArray oPhoneNumbersArrayDataBase;

	CString strID;
	strID.Format(_T("%d"), lID);

	if (oPhoneNumbersTable.SelectWhereColumnName(CPhoneNumbersTable::_strColumnPersonID, strID, oPhoneNumbersArrayDataBase) == FALSE)
	{
		if (Abort(oSession) == FALSE)
		{
			return FALSE;
		}
		
		// Closing the session
		oSession.Close();

		return FALSE;
	}

	if (oPhoneNumbersTable.UpdateAll(oPersonDetails.GetPhoneNumbersArray(), oPhoneNumbersArrayDataBase) == FALSE)
	{
		if (Abort(oSession) == FALSE)
		{
			return FALSE;
		}
		
		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Ending the transaction
	hResult = oSession.Commit();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("An error occurred. A transaction cannot be ended."));

		// Closing the session
		oSession.Close();

		return FALSE;
	}

	// Closing the session
	oSession.Close();

	return TRUE;
}

BOOL CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	CPersonsTable oPersonsTable;
	if (oPersonsTable.SelectAll(oPersonsArray) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CPersonsData::InitializeSession(CSession& oSession)
{
	HRESULT hResult = oSession.Open(CDataSourceAccessor::GetDataSource());
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("An error occurred. A session cannot be opened."));

		return FALSE;
	}
	return TRUE;
}

BOOL CPersonsData::Abort(CSession& oSession)
{
	HRESULT hResult = oSession.Abort();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("An error occurred. The transaction cannot be aborted."));

		return FALSE;
	}
	return TRUE;
}

// Overrides
// ----------------