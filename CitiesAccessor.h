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

class CCitiesAccessor
{
protected:
	CITIES m_recCities;

	BEGIN_ACCESSOR_MAP(CCitiesAccessor, NUMBER_ACCESSORS)
		BEGIN_ACCESSOR(SELECT_ACCESSOR, true)
		COLUMN_ENTRY(COLUMN_FIRST, m_recCities.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(MODIFY_ACCESSOR, true)
		COLUMN_ENTRY(COLUMN_SECOND, m_recCities.lUpdateCounter)
		COLUMN_ENTRY(COLUMN_THIRD, m_recCities.szNAME)
		COLUMN_ENTRY(COLUMN_FORTH, m_recCities.szREGION)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};