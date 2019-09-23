#pragma once
#include <atldbcli.h>

class CDataSourceAccessor
{
	// Constants
	// ----------------
protected:
	/// <summary>
	/// CDataSource object
	/// </summary>
	static CDataSource _oDataSource;


// Constructor / Destructor
// ----------------
private:
	/// <summary>
	/// Constructor
	/// </summary>
	CDataSourceAccessor();

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CDataSourceAccessor();


	// Methods
	// ----------------
public:
	/// <summary>
	/// A function for connecting with the database
	/// </summary>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	static BOOL OpenConnection();

	/// <summary>
	/// A function for disconnecting with the database
	/// </summary>
	static void CloseConnection();

	/// <summary>
	/// A function for getting a CDataSource object
	/// </summary>
	/// <returns> This function returns a CDataSource object </returns>
	static const CDataSource& GetDataSource();


	// Overrides
	// ----------------



	// Members
	// ----------------
};