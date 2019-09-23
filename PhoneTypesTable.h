#pragma once
#include "TemplateTable.h"
#include "Structures.h"
#include "PhoneTypesAccessor.h"

/// <summary>
/// Template class for work with the PHONE_TYPES table
///</summary>
class CPhoneTypesTable : public CTemplateTable <PHONE_TYPES, CPhoneTypesAccessor>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------

public:
	/// <summary>
	/// Constructor
	/// </summary>
	CPhoneTypesTable();

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CPhoneTypesTable();

	// Methods
	// ----------------

	// Overrides
	// ----------------
public:
	/// <summary>
	/// A function for getting record of the PhoneTypesAccessor
	/// </summary>
	/// <returns> The function returns a PHONE_TYPES struct </returns>
	virtual PHONE_TYPES& GetAccessorRecord();

	/// <summary>
	/// A function for getting the element from the PHONE_TYPES struct which counts the updates of a record
	/// </summary>
	/// <param name ="recPhoneNumber"> PHONE_TYPES struct </param>
	/// <returns> The function returns long value </returns>
	virtual long& GetUpdateCounterValue(PHONE_TYPES& recPhoneType);

	// Members
	// ----------------
};