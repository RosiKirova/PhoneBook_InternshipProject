#pragma once
#include "Structures.h"
#include <atldbcli.h>

#define NUMBER_ACCESSORS 2
#define SELECT_ACCESSOR 0
#define MODIFY_ACCESSOR 1
#define COLUMN_FIRST 1
#define COLUMN_SECOND 2
#define COLUMN_THIRD 3
#define COLUMN_FORTH 4
#define COLUMN_FIFTH 5

class CPhoneNumbersAccessor
{
protected:
	PHONE_NUMBERS m_recPhoneNumbers;

	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, NUMBER_ACCESSORS)
		BEGIN_ACCESSOR(SELECT_ACCESSOR, true)
		COLUMN_ENTRY(COLUMN_FIRST, m_recPhoneNumbers.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(MODIFY_ACCESSOR, true)
		COLUMN_ENTRY(COLUMN_SECOND, m_recPhoneNumbers.lUpdateCounter)
		COLUMN_ENTRY(COLUMN_THIRD, m_recPhoneNumbers.lPersonId)
		COLUMN_ENTRY(COLUMN_FORTH, m_recPhoneNumbers.lPhoneTypeId)
		COLUMN_ENTRY(COLUMN_FIFTH, m_recPhoneNumbers.szPhoneNumber)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};