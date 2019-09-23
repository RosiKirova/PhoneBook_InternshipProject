#pragma once
#include "TemplateTable.h"
#include "Structures.h"
#include "PersonsAccessor.h"

/// <summary>
/// Template class for work with the PERSONS table
///</summary>
class CPersonsTable : public CTemplateTable <PERSONS, CPersonsAccessor>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------

public:
	/// <summary>
	/// Constructor
	/// </summary>
	CPersonsTable();

	/// <summary>
	/// Constructor
	/// </summary>
	CPersonsTable(CSession& oSessionMutual);

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CPersonsTable();

	// Methods
	// ----------------

	// Overrides
	// ----------------
public:
	/// <summary>
	/// A function for getting record of the PersonsAccessor
	/// </summary>
	/// <returns> The function returns a PERSONS struct </returns>
	virtual PERSONS& GetAccessorRecord();

	/// <summary>
	/// A function for getting the element from the PERSONS struct which counts the updates of a record
	/// </summary>
	/// <param name ="recPerson"> PERSONS struct </param>
	/// <returns> The function returns long value </returns>
	virtual long& GetUpdateCounterValue(PERSONS& recPerson);

	// Members
	// ----------------
};