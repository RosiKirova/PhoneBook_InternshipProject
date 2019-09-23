#pragma once

#include "Structures.h"
#include "PersonsView.h"

// CPhoneNumbersDialog dialog

class CPhoneNumbersDialog : public CDialogEx
{
	// Macros
	// ----------------
	DECLARE_DYNAMIC(CPhoneNumbersDialog)
	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------
private:
	enum { IDD = IDD_PHONE_NUMBERS };

	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersDialog(DialogModes eDialogMode, PHONE_NUMBERS& recPhoneNumber, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent = nullptr);	// implicit constructor
	virtual ~CPhoneNumbersDialog();

	// MFC Overrides
	// ----------------
private:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	// Overrides
	// ----------------


	// Methods
	// ----------------
private:
	/// <summary>
	/// A function for initializing a dialog
	/// </summary>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	virtual BOOL OnInitDialog();

	/// <summary>
	/// A function which takes the demanded actions after clicking the OK button
	/// </summary>
	virtual void OnOK();

	/// <summary>
	/// A function for validating the text from a certain field
	/// </summary>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL ValidateText(CString& strBoxText);

	// MFC Message Handlers
	// ----------------


	// Members
	// ----------------
private:
	/// <summary>
	/// A flag defining the dialog type
	/// </summary>
	DialogModes m_eDialogMode;

	/// <summary>
	/// PHONE_NUMBERS struct
	/// </summary>
	PHONE_NUMBERS& m_recPhoneNumber;

	/// <summary>
	/// Map: the key is the unique identifier of the PHONE_TYPES and is mapped to the whole PHONE_TYPES object
	/// </summary>
	CMap<long, long, PHONE_TYPES*, PHONE_TYPES*>& m_oPhoneTypesMap;

	/// <summary>
	/// Dialog field meant to contain the phone number
	/// </summary>
	CEdit m_edbPhoneNumbersNumber;

	/// <summary>
	/// Combo box menu containing the phone number types
	/// </summary>
	CComboBox m_cmbPhoneNumbersType;
};

