#pragma once
#include "PhoneTypesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDataClass

/// <summary>
/// Class representing the business logic layer
///</summary>
class CPhoneTypesData
{

	// Constants
	// ----------------



	// Constructor / Destructor
	// ----------------
public:
	/// <summary>
	/// Constructor
	/// </summary>
	CPhoneTypesData();

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CPhoneTypesData();


	// Methods
	// ----------------
public:
	/// <summary>
	/// A function for selecting all the fields available in the PHONE_TYPES table
	/// </summary>
	/// <param name ="oCPhoneTypesArray"> array of type PHONE_TYPES </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectAll(CPhoneTypesArray& oPhoneTypesArray);

	/// <summary>
	/// A function for selecting the fields in the PHONE_TYPES table which contain the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <param name ="recPhoneType"> PHONE_TYPES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectWhereID(const long lID, PHONE_TYPES& recPhoneType);

	/// <summary>
	/// A function for modifying the fields in the PHONE_TYPES table which contain the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <param name ="recPhoneTypes"> PHONE_TYPES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL UpdateWhereID(const long lID, PHONE_TYPES& recPhoneType);

	/// <summary>
	/// A function for inserting new records in the PHONE_TYPES table
	/// </summary>
	/// <param name ="recPhoneTypes"> PHONE_TYPES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL Insert(PHONE_TYPES& recPhoneType);

	/// <summary>
	/// A function for deleting the fields in the PHONE_TYPES table which contain the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL DeleteWhereID(const long lID);


	// Overrides
	// ----------------



	// Members
	// ----------------
};