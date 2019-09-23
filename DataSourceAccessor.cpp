// DataSourceAccessor.cpp
//

#include "stdafx.h"
#include "DataSourceAccessor.h"


/////////////////////////////////////////////////////////////////////////////
// DataSourceAccessorClass


CDataSource CDataSourceAccessor::_oDataSource;

// Constructor / Destructor
// ----------------

CDataSourceAccessor::CDataSourceAccessor()
{
}

CDataSourceAccessor::~CDataSourceAccessor()
{
}


// Methods
// ----------------
BOOL CDataSourceAccessor::OpenConnection()
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	// Adding properties for achieving connection
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-3KR072E"));	// server
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));	// Windows Authentication
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("CSoft_Intern_Phonebook_Task1"));	// database
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	HRESULT hResult = _oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		return FALSE;
	}

	return TRUE;
}

void CDataSourceAccessor::CloseConnection()
{
	_oDataSource.Close();
}

const CDataSource& CDataSourceAccessor::GetDataSource()
{
	return _oDataSource;
}


// Overrides
// ----------------