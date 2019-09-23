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
#define COLUMN_SIXTH 6
#define COLUMN_SEVENTH 7
#define COLUMN_EIGHTH 8

class CPersonsAccessor
{
protected:
	PERSONS m_recPersons;

	BEGIN_ACCESSOR_MAP(CPersonsAccessor, NUMBER_ACCESSORS)
		BEGIN_ACCESSOR(SELECT_ACCESSOR, true)
		COLUMN_ENTRY(COLUMN_FIRST, m_recPersons.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(MODIFY_ACCESSOR, true)
		COLUMN_ENTRY(COLUMN_SECOND, m_recPersons.lUpdateCounter)
		COLUMN_ENTRY(COLUMN_THIRD, m_recPersons.szFirstName)
		COLUMN_ENTRY(COLUMN_FORTH, m_recPersons.szMiddleName)
		COLUMN_ENTRY(COLUMN_FIFTH, m_recPersons.szLastName)
		COLUMN_ENTRY(COLUMN_SIXTH, m_recPersons.szUCN)
		COLUMN_ENTRY(COLUMN_SEVENTH, m_recPersons.lCityId)
		COLUMN_ENTRY(COLUMN_EIGHTH, m_recPersons.szADDRESS)

		END_ACCESSOR()
	END_ACCESSOR_MAP()
};