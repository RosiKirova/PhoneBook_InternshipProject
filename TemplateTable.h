#pragma once
#include <afxtempl.h>
#include <atldbcli.h>
#include "CAutoDeleteTypedPtrArray.h"
#include "DataSourceAccessor.h"

#define MODIFY_ACCESSOR 1

/// <summary>
/// Template class for work with a certain table
///</summary>
template<class TYPE, class ACCESSOR>
class CTemplateTable : public CCommand<CAccessor<ACCESSOR>>
{
	// Constants
	// ----------------
	typedef CAutoDeleteTypedPtrArray <CPtrArray, TYPE*> CAutoDeleteTypedPtrArray;

	// Constructor / Destructor
	// ----------------

public:
	/// <summary>
	/// A constructor used when the session is a local one
	/// </summary>
	/// <param name ="strTableName"> The name of the table used </param>
	CTemplateTable(const CString strTableName) : m_strTableName(strTableName)
	{
		m_bIsSessionMutual = FALSE;
	}

	/// <summary>
	/// A constructor used when the session is a mutual one
	/// </summary>
	/// <param name ="strTableName"> The name of the table used </param>
	/// <param name ="oSession"> Mutual session </param>
	CTemplateTable(const CString strTableName, CSession& oSession) : m_strTableName(strTableName)
	{
		m_oSession = oSession;
		m_bIsSessionMutual = TRUE;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CTemplateTable()
	{

	}

	// Methods
	// ----------------

public:

	/// <summary>
	/// A function for selecting all the fields available in a certain table
	/// </summary>
	/// <param name ="oAutoDeleteTypedPtrArray"> array of type TYPE </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectAll(CAutoDeleteTypedPtrArray& oAutoDeleteTypedPtrArray)
	{
		if (!m_bIsSessionMutual)
		{
			// Opening a session
			if (InitializeSession() == FALSE)
			{
				return FALSE;
			}
		}

		// Building SQL query
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s"), m_strTableName);

		// Executing query
		if (ExecuteQuery(strQuery, FALSE) == FALSE)
		{
			return FALSE;
		}

		// Reading the needed data
		HRESULT hResult = MoveNext();
		while (hResult == S_OK)
		{
			oAutoDeleteTypedPtrArray.Add(new TYPE(GetAccessorRecord()));
			hResult = MoveNext();
		}

		// Checking whether all the needed data was selected
		if (hResult != DB_S_ENDOFROWSET)
		{
			AfxMessageBox(_T("The connection was interrupted. It has not been selected the whole table."));

			// Closing the command and the session
			CloseAll();

			return FALSE;
		}

		// Closing the command and the session
		CloseAll();

		return TRUE;
	}

	/// <summary>
	/// A function for selecting the fields in a certain table which contain the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <param name ="recType"> The needed struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectWhereID(const long lID, TYPE& recType)
	{
		if (!m_bIsSessionMutual)
		{
			// Opening a session
			if (InitializeSession() == FALSE)
			{
				return FALSE;
			}
		}

		// Executing query
		if (SelectRecordByID(lID, FALSE, FALSE) == FALSE)
		{
			return FALSE;
		}

		recType = GetAccessorRecord();

		// Closing the command and the session 
		CloseAll();

		return TRUE;
	}

	/// <summary>
	/// A function for selecting one or more records of a certain table which contain the certain column value
	/// </summary>
	/// <param name ="strColumnName"> The column name </param>
	/// <param name ="strColumnValue"> The column value </param>
	/// <param name ="oAutoDeleteTypedPtrArray"> array of type TYPE </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectWhereColumnName(const CString strColumnName, const CString strColumnValue, CAutoDeleteTypedPtrArray& oAutoDeleteTypedPtrArray)
	{
		if (!m_bIsSessionMutual)
		{
			// Opening a session
			if (InitializeSession() == FALSE)
			{
				return FALSE;
			}
		}

		// Building SQL query
		CString strQuery;
		strQuery.Format(_T("SELECT * FROM %s WHERE %s = %s"), m_strTableName, strColumnName, strColumnValue);

		// Executing query
		if (ExecuteQuery(strQuery, FALSE) == FALSE)
		{
			return FALSE;
		}

		// Reading the needed data
		HRESULT hResult = MoveNext();
		while (hResult == S_OK)
		{
			oAutoDeleteTypedPtrArray.Add(new TYPE(GetAccessorRecord()));
			hResult = MoveNext();
		}

		// Checking whether all the needed data was selected
		if (hResult != DB_S_ENDOFROWSET)
		{
			AfxMessageBox(_T("The connection was interrupted. It has not been selected the whole table."));

			// Closing the command and the session
			CloseAll();

			return FALSE;
		}

		// Closing the command and the session
		CloseAll();

		return TRUE;
	}

	/// <summary>
	/// A function for modifying the fields in a certain table selected by the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <param name ="recType"> The needed struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL UpdateWhereID(const long lID, TYPE& recType)
	{
		if (!m_bIsSessionMutual)
		{
			// Opening a session
			if (InitializeSession() == FALSE)
			{
				return FALSE;
			}
		}

		HRESULT hResult = S_FALSE;

		if (!m_bIsSessionMutual)
		{
			// Starting a transaction 
			hResult = m_oSession.StartTransaction();
			if (FAILED(hResult))
			{
				AfxMessageBox(_T("An error occurred. The transaction cannot be started."));

				// Closing the session
				m_oSession.Close();
				return FALSE;
			}
		}

		// Executing query
		if (SelectRecordByID(lID, TRUE, TRUE) == FALSE)
		{
			return FALSE;
		}

		// Optimistic concurrency control 
		if (GetUpdateCounterValue(recType) != GetUpdateCounterValue(GetAccessorRecord()))
		{
			AfxMessageBox(_T("An error occured. The record cannot be modified because it has been changed by someone else during your modification process."));

			// Closing the command and the session
			CloseAll();

			return FALSE;
		}

		GetAccessorRecord() = recType;
		GetUpdateCounterValue(GetAccessorRecord())++;

		hResult = SetData(MODIFY_ACCESSOR);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("An error occurred. The modification of the record cannot be achieved."));

			// Closing the command and the session
			CloseAll();

			return FALSE;
		}

		recType = GetAccessorRecord();

		if (!m_bIsSessionMutual)
		{
			// Ending a transaction
			hResult = m_oSession.Commit();
			if (FAILED(hResult))
			{
				AfxMessageBox(_T("An error occurred. The transaction cannot be ended."));

				// Closing the command and the session
				CloseAll();

				return FALSE;
			}
		}

		// Closing the command and the session
		CloseAll();

		return TRUE;
	}

	/// <summary>
	/// A function for synchronizing the content of two arrays by the unique identifier of the elements
	/// </summary>
	/// <param name ="oAutoDeleteTypedPtrArrayNew"> The actualised array </param>
	/// <param name ="oAutoDeleteTypedPtrArrayOld"> The out-of-date array </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL UpdateAll(CAutoDeleteTypedPtrArray& oAutoDeleteTypedPtrArrayNew, CAutoDeleteTypedPtrArray& oAutoDeleteTypedPtrArrayOld)
	{
		TYPE* recTypeOld = NULL;

		while (oAutoDeleteTypedPtrArrayOld.GetCount() > 0)
		{
			BOOL bIsExisting = FALSE;
			recTypeOld = oAutoDeleteTypedPtrArrayOld.GetAt(0);
			TYPE* recTypeNew = NULL;

			for (INT_PTR nIndex = 0; nIndex < oAutoDeleteTypedPtrArrayNew.GetCount(); nIndex++)
			{
				recTypeNew = oAutoDeleteTypedPtrArrayNew.GetAt(nIndex);
				if (recTypeNew->lID == recTypeOld->lID)
				{
					bIsExisting = TRUE;
					oAutoDeleteTypedPtrArrayNew.RemoveAt(nIndex);
					break;
				}
			}

			if (bIsExisting)
			{
				UpdateWhereID(recTypeNew->lID, *recTypeNew);
			}
			else
			{
				DeleteWhereID(recTypeOld->lID);
			}

			oAutoDeleteTypedPtrArrayOld.DeleteCTypedPtrArrayElement(0);
			oAutoDeleteTypedPtrArrayOld.RemoveAt(0);
		}

		TYPE* recType = NULL;
		while(oAutoDeleteTypedPtrArrayNew.GetCount() > 0)
		{
			recType = oAutoDeleteTypedPtrArrayNew.GetAt(0);
			Insert(*recType);

			oAutoDeleteTypedPtrArrayNew.DeleteCTypedPtrArrayElement(0);
			oAutoDeleteTypedPtrArrayNew.RemoveAt(0);
		}

		return TRUE;
	}

	/// <summary>
	/// A function for inserting a new record in a certain table
	/// </summary>
	/// <param name ="recType"> The needed struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL Insert(TYPE& recType)
	{
		if (!m_bIsSessionMutual)
		{
			// Opening a session
			if (InitializeSession() == FALSE)
			{
				return FALSE;
			}
		}

		// Building SQL query
		CString strQuery;
		strQuery.Format(_T("SELECT TOP 0 * FROM %s"), m_strTableName);

		// Executing query
		if (ExecuteQuery(strQuery, TRUE) == FALSE)
		{
			return FALSE;
		}

		GetAccessorRecord() = recType;

		// Creating and adding a new row
		HRESULT hResult = __super::Insert(MODIFY_ACCESSOR, true);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("An error occurred. The insert of a new record cannot be achieved."));

			// Closing the command and the session
			CloseAll();

			return FALSE;
		}
		
		hResult = MoveFirst();
		if (hResult != S_OK)
		{
			AfxMessageBox(_T("An error occurred. An access to the needed record cannot be achieved."));

			// Closing the command and the session
			CloseAll();

			return FALSE;
		}

		recType = GetAccessorRecord();

		// Closing the command and the session
		CloseAll();

		return TRUE;
	}

	/// <summary>
	/// A function for deleting the fields in a certain table selected by the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL DeleteWhereID(const long lID)
	{
		if (!m_bIsSessionMutual)
		{
			// Opening a session
			if (InitializeSession() == FALSE)
			{
				return FALSE;
			}
		}

		// Executing query
		if (SelectRecordByID(lID, TRUE, FALSE) == FALSE)
		{
			return FALSE;
		}

		HRESULT hResult = Delete();
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("An error occurred. The delete of the record cannot be achieved."));

			// Closing the command and the session
			CloseAll();

			return FALSE;
		}

		// Closing the command and the session
		CloseAll();

		return TRUE;
	}

private:

	/// <summary>
	/// A function for getting record of the needed accessor
	/// </summary>
	virtual TYPE& GetAccessorRecord() = 0;

	/// <summary>
	/// A function for getting the element from the TYPE struct which counts the updates of a record
	/// </summary>
	virtual long& GetUpdateCounterValue(TYPE& recType) = 0;

	/// <summary>
	/// A function for opening a session
	/// </summary>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL InitializeSession()
	{
		// Opening a session
		HRESULT hResult = m_oSession.Open(CDataSourceAccessor::GetDataSource());
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("An error occurred. The session cannot be opened."));

			return FALSE;
		}
		return TRUE;
	}

	/// <summary>
	/// A function for executing a query
	/// </summary>
	/// <param name ="strQuery"> The query </param>
	/// <param name = "bAddModificationProperties"> A flag defining whther properties change of the Rowset is needed so the wanted modification can go through </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL ExecuteQuery(CString strQuery, const BOOL bAddModificationProperties)
	{
		HRESULT hResult = S_FALSE;

		if (bAddModificationProperties == TRUE)
		{
			// Adding needed properties of the Rowset so modification is possible
			CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);

			oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
			oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
			oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
			oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
			oUpdateDBPropSet.AddProperty(DBPROP_RETURNPENDINGINSERTS, true);

			// Executing query
			hResult = Open(m_oSession, strQuery, &oUpdateDBPropSet);
		}
		else
		{
			// Executing query
			hResult = Open(m_oSession, strQuery);
		}

		if (FAILED(hResult))
		{
			AfxMessageBox(_T("An error occurred. The query cannot be executed."));

			if (!m_bIsSessionMutual)
			{
				// Closing the session
				m_oSession.Close();
			}

			return FALSE;
		}
		return TRUE;
	}

	/// <summary>
	/// A function for executing a SelectWhereID query with or without an Update lock
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <param name ="recCities"> CITIES struct </param>
	/// <param name = "bAddModificationProperties"> A flag defining whther properties change of the Rowset is needed so the wanted modification can go through </param>
	/// <param name ="bSetUpdateLock"> A flag defining whether an Updatelock is needed </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectRecordByID(const long lID, const BOOL bAddModificationProperties, const BOOL bSetUpdateLock)
	{
		// Building SQL query
		CString strQuery;

		if (bSetUpdateLock == TRUE)
		{
			strQuery.Format(_T("SELECT * FROM %s WITH(UPDLOCK) WHERE ID = %d"), m_strTableName, lID);
		}
		else
		{
			strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d"), m_strTableName, lID);
		}

		// Executing query
		if (ExecuteQuery(strQuery, bAddModificationProperties) == FALSE)
		{
			return FALSE;
		}

		// Reading all the needed data
		HRESULT hResult = MoveFirst();
		if (hResult != S_OK)
		{
			AfxMessageBox(_T("An error occurred. An access to the needed record cannot be achieved."));

			// Closing the command and the session 
			CloseAll();

			return FALSE;
		}

		return TRUE;
	}

	/// <summary>
	/// A function for closing the command and the session
	/// </summary>
	void CloseAll()
	{
		// Closing the command
		Close();

		if (!m_bIsSessionMutual)
		{
			// Closing the session 
			m_oSession.Close();
		}
	}

	// Overrides
	// ----------------

	// Members
	// ----------------
private:
	/// <summary>
	/// Object through which we open a session
	/// </summary>
	CSession m_oSession;

	/// <summary>
	/// A flag defining whether the session is mutual or not
	/// </summary>
	BOOL m_bIsSessionMutual;

	/// <summary>
	/// The name of the table used 
	/// </summary>
	const CString m_strTableName;
};