#pragma once
#include "CitiesTable.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDataClass

/// <summary>
/// Class representing the business logic layer
///</summary>
class CCitiesData
{

	// Constants
	// ----------------



	// Constructor / Destructor
	// ----------------
public:
	/// <summary>
	/// Constructor
	/// </summary>
	CCitiesData();

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CCitiesData();


	// Methods
	// ----------------
public:
	/// <summary>
	/// A function for selecting all the fields available in the CITIES table
	/// </summary>
	/// <param name ="oCitiesArray"> CITIES array </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectAll(CCitiesArray& oCitiesArray);

	/// <summary>
	/// A function for selecting the fields in the CITIES table which contain the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <param name ="recCity"> CITIES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectWhereID(const long lID, CITIES& recCity);

	/// <summary>
	/// A function for modifying the fields in the CITIES table selected by the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <param name ="recCity"> CITIES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL UpdateWhereID(const long lID, CITIES& recity);

	/// <summary>
	/// A function for inserting new records in the CITIES table
	/// </summary>
	/// <param name ="recCity"> CITIES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL Insert(CITIES& recity);

	/// <summary>
	/// A function for deleting the fields in the CITIES table selected by the certain unique identifier
	/// </summary>
	/// <param name ="lID"> Unique identifier </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL DeleteWhereID(const long lID);


	// Overrides
	// ----------------



	// Members
	// ----------------
};