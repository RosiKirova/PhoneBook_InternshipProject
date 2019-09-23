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
/// ������� ��������� �� ��������� CITIES
/// </summary>
struct CITIES
{
	/// <summary>���� ���������� - �������� �������������</summary>
	long lID;

	/// <summary>���� ���������� - ������ �� ���</summary>
	long lUpdateCounter;

	/// <summary>���� ���������� - ��� �� ����</summary>
	TCHAR szNAME[CITIES_NAME_SIZE + 1];

	/// <summary>���� ���������� - ������ �� ����</summary>
	TCHAR szREGION[CITIES_REGION_SIZE + 1];

	/// <summary>Default �����������</summary>
	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

typedef CAutoDeleteTypedPtrArray<CPtrArray, CITIES*> CCitiesArray;

/// <summary>
/// ������� ��������� �� ��������� PHONE_TYPES
/// </summary>
struct PHONE_TYPES
{
	/// <summary>���� ���������� - �������� �������������</summary>
	long lID;

	/// <summary>���� ���������� - ������ �� ���</summary>
	long lUpdateCounter;

	/// <summary>���� ���������� - ��� �������</summary>
	TCHAR szTYPE[PHONE_TYPES_TYPE_SIZE + 1];

	/// <summary>Default �����������</summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

typedef CAutoDeleteTypedPtrArray<CPtrArray, PHONE_TYPES*> CPhoneTypesArray;

/// <summary>
/// ������� ��������� �� ��������� PERSONS
/// </summary>
struct PERSONS
{
	/// <summary>���� ���������� - �������� �������������</summary>
	long lID;

	/// <summary>���� ���������� - ������ �� ���</summary>
	long lUpdateCounter;

	/// <summary>���� ���������� - ������� ��� �� �������</summary>
	TCHAR szFirstName[PERSONS_FIRST_NAME_SIZE + 1];

	/// <summary>���� ���������� - ������� �� �������</summary>
	TCHAR szMiddleName[PERSONS_MIDDLE_NAME_SIZE + 1];

	/// <summary>���� ���������� - ������� �� �������</summary>
	TCHAR szLastName[PERSONS_LAST_NAME_SIZE + 1];

	/// <summary>���� ���������� - ��� �� �������</summary>
	TCHAR szUCN[PERSONS_UCN_SIZE + 1];

	/// <summary>���� ���������� - ���������� ������������� �� ����� �� �������</summary>
	long lCityId;

	/// <summary>���� ���������� - ����� �� �������</summary>
	TCHAR szADDRESS[PERSONS_ADDRESS_SIZE + 1];

	/// <summary>Default �����������</summary>
	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

typedef CAutoDeleteTypedPtrArray<CPtrArray, PERSONS*> CPersonsArray;


/// <summary>
/// ������� ��������� �� ��������� PHONE_NUMBERS
/// </summary>
struct PHONE_NUMBERS
{
	/// <summary>���� ���������� - �������� �������������</summary>
	long lID;

	/// <summary>���� ���������� - ������ �� ���</summary>
	long lUpdateCounter;

	/// <summary>���� ���������� - ���������� ������������� �� �������, ���������� ���� �����</summary>
	long lPersonId;

	/// <summary>���� ���������� - ���������� ������������� �� ���� ������� � ���� �����</summary>
	long lPhoneTypeId;

	/// <summary>���� ���������� - ��������� �����</summary>
	TCHAR szPhoneNumber[PHONE_NUMBERS_PHONE_NUMBER_SIZE + 1];

	/// <summary>Default �����������</summary>
	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	};

};

typedef CAutoDeleteTypedPtrArray<CPtrArray, PHONE_NUMBERS*> CPhoneNumbersArray;