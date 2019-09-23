#pragma once
#include "Structures.h"
#include <atldbcli.h>

#define NUMBER_ACCESSORS 2
#define SELECT_ACCESSOR 0
#define MODIFY_ACCESSOR 1
#define COLUMN_FIRST 1
#define COLUMN_SECOND 2
#define COLUMN_THIRD 3

class CPhoneTypesAccessor
{
protected:
	PHONE_TYPES m_recPhoneTypes;

	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, NUMBER_ACCESSORS)
		BEGIN_ACCESSOR(SELECT_ACCESSOR, true)
		COLUMN_ENTRY(COLUMN_FIRST, m_recPhoneTypes.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(MODIFY_ACCESSOR, true)
		COLUMN_ENTRY(COLUMN_SECOND, m_recPhoneTypes.lUpdateCounter)
		COLUMN_ENTRY(COLUMN_THIRD, m_recPhoneTypes.szTYPE)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};