#pragma once
#include "TemplateTable.h"
#include "Structures.h"
#include "CitiesAccessor.h"

/// <summary>
/// Template class for work with the CITIES table
///</summary>
class CCitiesTable : public CTemplateTable<CITIES, CCitiesAccessor>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------

public:
	/// <summary>
	/// Constructor
	/// </summary>
	CCitiesTable();

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CCitiesTable();

	// Methods
	// ----------------

	// Overrides
	// ----------------
public:
	/// <summary>
	/// A function for getting record of the CitiesAccessor
	/// </summary>
	/// <returns> The function returns a CITIES struct </returns>
	virtual CITIES& GetAccessorRecord();

	/// <summary>
	/// A function for getting the element from the CITIES struct which counts the updates of a record
	/// </summary>
	/// <param name ="recCity"> CITIES struct </param>
	/// <returns> The function returns long value </returns>
	virtual long& GetUpdateCounterValue(CITIES& recCity);

	// Members
	// ----------------
};