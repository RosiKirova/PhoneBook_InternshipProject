#pragma once

#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
#include "CitiesTable.h"
#include "PhoneTypesTable.h"

#include "PersonDetails.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDataClass

/// <summary>
/// Class representing the business logic layer
///</summary>
class CPersonsData
{

	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	/// <summary>
	/// Constructor
	/// </summary>
	CPersonsData();

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CPersonsData();


	// Methods
	// ----------------
public:
	/// <summary>
	/// A function for selecting a person and their phone numbers
	/// </summary>
	/// <param name ="lID"> The unique identifier of the person </param>
	/// <param name ="oPersonDetails"> Object containing the person details </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectPerson(const long lID, CPersonDetails& oPersonDetails);

	/// <summary>
	/// A function for deleting a person and their phone numbers
	/// </summary>
	/// <param name ="lID"> The unique identifier of the person </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL DeletePerson(const long lID);

	/// <summary>
	/// A function for adding a person and their phone numbers
	/// </summary>
	/// <param name ="oPersonDetails"> Object containing the person details </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL InsertPerson(CPersonDetails& oPersonDetails);

	/// <summary>
	/// A function for modifying a person and their phone numbers
	/// </summary>
	/// <param name ="lID"> The unique identifier of the person </param>
	/// <param name ="oPersonDetails"> Object containing the person details </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL UpdatePerson(const long lID, CPersonDetails& oPersonDetails);

	/// <summary>
	/// A function for selecting all the fields available in the PERSONS table
	/// </summary>
	/// <param name ="oPersonsArray"> array of type PERSONS </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectAll(CPersonsArray& oPersonsArray);

private:
	/// <summary>
	/// A function for connecting with the database and opening a session
	/// </summary>
	/// <param name ="oDataSource"> An object through which the connection with the database is managed </param>
	/// <param name ="oSession"> An object through which the session is managed </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL InitializeSession(CSession& oSession);

	/// <summary>
	/// A function for interrupting and canceling an already started transaction
	/// </summary>
	/// <param name ="oSession"> An object through which the session is managed </param>
	BOOL Abort(CSession& oSession);

	// Overrides
	// ----------------

	// Members
	// ----------------
};
