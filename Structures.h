#pragma once
#include <tchar.h>
#include <afxtempl.h>
#include "CAutoDeleteTypedPtrArray.h"

using namespace std;

#define CITIES_NAME_SIZE 127
#define CITIES_REGION_SIZE 127
#define PHONE_TYPES_TYPE_SIZE 15
#define PERSONS_FIRST_NAME_SIZE 63
#define PERSONS_MIDDLE_NAME_SIZE 63
#define PERSONS_LAST_NAME_SIZE 63
#define PERSONS_UCN_SIZE 63
#define PERSONS_ADDRESS_SIZE 255
#define PHONE_NUMBERS_PHONE_NUMBER_SIZE 31
#define LETTER_CASE_NUMERICAL_DIFFERENCE 32

/// <summary>
/// Дискова структура на таблицата CITIES
/// </summary>
struct CITIES
{
	/// <summary>Член променлива - уникален идентификатор</summary>
	long lID;

	/// <summary>Член променлива - версия на ред</summary>
	long lUpdateCounter;

	/// <summary>Член променлива - име на град</summary>
	TCHAR szNAME[CITIES_NAME_SIZE + 1];

	/// <summary>Член променлива - област на град</summary>
	TCHAR szREGION[CITIES_REGION_SIZE + 1];

	/// <summary>Default конструктор</summary>
	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

typedef CAutoDeleteTypedPtrArray<CPtrArray, CITIES*> CCitiesArray;

/// <summary>
/// Дискова структура на таблицата PHONE_TYPES
/// </summary>
struct PHONE_TYPES
{
	/// <summary>Член променлива - уникален идентификатор</summary>
	long lID;

	/// <summary>Член променлива - версия на ред</summary>
	long lUpdateCounter;

	/// <summary>Член променлива - тип телефон</summary>
	TCHAR szTYPE[PHONE_TYPES_TYPE_SIZE + 1];

	/// <summary>Default конструктор</summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

typedef CAutoDeleteTypedPtrArray<CPtrArray, PHONE_TYPES*> CPhoneTypesArray;

/// <summary>
/// Дискова структура на таблицата PERSONS
/// </summary>
struct PERSONS
{
	/// <summary>Член променлива - уникален идентификатор</summary>
	long lID;

	/// <summary>Член променлива - версия на ред</summary>
	long lUpdateCounter;

	/// <summary>Член променлива - първото име на абоната</summary>
	TCHAR szFirstName[PERSONS_FIRST_NAME_SIZE + 1];

	/// <summary>Член променлива - презиме на абоната</summary>
	TCHAR szMiddleName[PERSONS_MIDDLE_NAME_SIZE + 1];

	/// <summary>Член променлива - фамилия на абоната</summary>
	TCHAR szLastName[PERSONS_LAST_NAME_SIZE + 1];

	/// <summary>Член променлива - ЕГН на абоната</summary>
	TCHAR szUCN[PERSONS_UCN_SIZE + 1];

	/// <summary>Член променлива - уникалният идентификатор на града на абоната</summary>
	long lCityId;

	/// <summary>Член променлива - адрес на абоната</summary>
	TCHAR szADDRESS[PERSONS_ADDRESS_SIZE + 1];

	/// <summary>Default конструктор</summary>
	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

typedef CAutoDeleteTypedPtrArray<CPtrArray, PERSONS*> CPersonsArray;


/// <summary>
/// Дискова структура на таблицата PHONE_NUMBERS
/// </summary>
struct PHONE_NUMBERS
{
	/// <summary>Член променлива - уникален идентификатор</summary>
	long lID;

	/// <summary>Член променлива - версия на ред</summary>
	long lUpdateCounter;

	/// <summary>Член променлива - уникалният идентификатор на абоната, притежаващ този номер</summary>
	long lPersonId;

	/// <summary>Член променлива - уникалният идентификатор на типа телефон с този номер</summary>
	long lPhoneTypeId;

	/// <summary>Член променлива - телефонен номер</summary>
	TCHAR szPhoneNumber[PHONE_NUMBERS_PHONE_NUMBER_SIZE + 1];

	/// <summary>Default конструктор</summary>
	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	};

};

typedef CAutoDeleteTypedPtrArray<CPtrArray, PHONE_NUMBERS*> CPhoneNumbersArray;