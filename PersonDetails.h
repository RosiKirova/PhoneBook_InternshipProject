#pragma once

#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonDetailsClass

class CPersonDetails
{

	// Constants
	// ----------------



	// Constructor / Destructor
	// ----------------
public:
	/// <summary>
	/// Constructor
	/// </summary>
	CPersonDetails();

	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CPersonDetails();


	// Methods
	// ----------------
	/// <summary>
	/// A function for getting a PERSONS object
	/// </summary>
	/// <returns> This function returns a PERSONS object </returns>
	PERSONS& GetPerson();

	/// <summary>
	/// A function for getting a CPhoneNumbersArray
	/// </summary>
	/// <returns> array of type PHONE_NUMBERS </returns>
	CPhoneNumbersArray& GetPhoneNumbersArray();

	// Overrides
	// ----------------

	// Members
	// ----------------
private:
	/// <summary>
	/// PERSONS object
	/// </summary>
	PERSONS m_recPerson;

	/// <summary>
	/// array of type PHONE_NUMBERS
	/// </summary>
	CPhoneNumbersArray m_oPhoneNumbersArray;
};