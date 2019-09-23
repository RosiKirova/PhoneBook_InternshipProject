#pragma once
#include "TemplateTable.h"
#include "Structures.h"
#include "PhoneNumbersAccessor.h"

/// <summary>
/// Template class for work with the PHONE_NUMBERS table
///</summary>
class CPhoneNumbersTable : public CTemplateTable <PHONE_NUMBERS, CPhoneNumbersAccessor>
{
	// Constants
	// ----------------
public:
	/// <summary>
	/// The name of the column which is used for selecting phone numbers of a certain person
	/// </summary>
	static const CString _strColumnPersonID;

	// Constructor / Destructor
	// ----------------

public:
	/// <summary>
	/// Constructor
	/// </summary>
	CPhoneNumbersTable();

	/// <summary>
	/// Constructor
	/// </summary>
	CPhoneNumbersTable(CSession& oSessionMutual);

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CPhoneNumbersTable();

	// Methods
	// ----------------

	// Overrides
	// ----------------
public:
	/// <summary>
	/// A function for getting record of the PhoneNumbersAccessor
	/// </summary>
	/// <returns> The function returns a PHONE_NUMBERS struct </returns>
	virtual PHONE_NUMBERS& GetAccessorRecord();

	/// <summary>
	/// A function for getting the element from the PHONE_NUMBERS struct which counts the updates of a record
	/// </summary>
	/// <param name ="recPhoneNumber"> PHONE_NUMBERS struct </param>
	/// <returns> The function returns long value </returns>
	virtual long& GetUpdateCounterValue(PHONE_NUMBERS& recPhoneNumber);

	// Members
	// ----------------
};