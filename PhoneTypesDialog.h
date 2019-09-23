#pragma once

#include "Structures.h"
#include "PhoneTypesView.h"

// CPhoneTypesDialog dialog

class CPhoneTypesDialog : public CDialogEx
{
	// Macros
	// ----------------
	DECLARE_DYNAMIC(CPhoneTypesDialog)
	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------
private:
	enum { IDD = IDD_PHONE_TYPES };

	// Constructor / Destructor
	// ----------------
public:
	CPhoneTypesDialog(DialogModes eDialogMode, PHONE_TYPES& recPhoneType, CWnd* pParent = nullptr);	// implicit constructor
	virtual ~CPhoneTypesDialog();

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
	/// A function for initializing the dialog
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
	/// A reference to PHONE_TYPES struct
	/// </summary>
	PHONE_TYPES& m_recPhoneType;

	/// <summary>
	/// Dialog field meant to contain the phone number type
	/// </summary>
	CEdit m_edbPhoneTypesType;
};