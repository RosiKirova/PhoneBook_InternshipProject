// PersonDetailsClass.cpp
//

#include "stdafx.h"
#include "PersonDetails.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonDetailsClass

// Constructor / Destructor
// ----------------

CPersonDetails::CPersonDetails()
{
}

CPersonDetails::~CPersonDetails()
{
}


// Methods
// ----------------
PERSONS& CPersonDetails::GetPerson()
{
	return m_recPerson;
}

CPhoneNumbersArray& CPersonDetails::GetPhoneNumbersArray()
{
	return m_oPhoneNumbersArray;
}

// Overrides
// ----------------