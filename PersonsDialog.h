#pragma once

#include "Structures.h"
#include "PersonDetails.h"
#include "PersonsView.h"

// CPersonsDialog dialog

class CPersonsDialog : public CDialogEx
{
	// Macros
	// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)

protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(NMHDR *, LRESULT *);
	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------
private:
	enum { IDD = IDD_PERSONS };

	// Constructor / Destructor
	// ----------------
public:
	CPersonsDialog(DialogModes eDialogMode, CPersonDetails& oPersonDetails,
		CCitiesMap& oCitiesNamesMap, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent = nullptr);
	virtual ~CPersonsDialog();

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
	/// A function for validating the text from a certain field in the following manner:
	/// checks whether there is text at all and if yes, then whether the text starts with capital letter
	/// </summary>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL ValidateText(CString& strBoxText);

	/// <summary>
	/// A function for checking whether the certain field is empty
	/// </summary>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL ValidateOnlyIfEmpty(CString& strBoxText);

	/// <summary>
	/// A function for deleting a phone number
	/// </summary>
	void PhoneNumbersDelete();

	/// <summary>
	/// A function for modifying a phone number
	/// </summary>
	void PhoneNumbersUpdate();

	/// <summary>
	/// A function for inserting a phone number
	/// </summary>
	void PhoneNumbersInsert();

	/// <summary>
	/// A function for reading a phone number
	/// </summary>
	void PhoneNumbersRead();

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
	/// Object containing the person details
	/// </summary>
	CPersonDetails& m_oPersonDetails;

	/// <summary>
	/// Map: the key is the unique identifier of the CITIES and is mapped to the whole CITIES object
	/// </summary>
	CCitiesMap& m_oCitiesNamesMap;

	/// <summary>
	/// Map: the key is the unique identifier of the PHONE_TYPES and is mapped to the whole PHONE_TYPES object
	/// </summary>
	CPhoneTypesMap& m_oPhoneTypesMap;

	/// <summary>
	/// Dialog field meant to contain the first name of a person
	/// </summary>
	CEdit m_edbPersonsFirstName;

	/// <summary>
	/// Dialog field meant to contain the middle name of a person
	/// </summary>
	CEdit m_edbPersonsMiddleName;

	/// <summary>
	/// Dialog field meant to contain the last name of a person
	/// </summary>
	CEdit m_edbPersonsLastName;

	/// <summary>
	/// Dialog field meant to contain the UCN of a person
	/// </summary>
	CEdit m_edbPersonsUCN;

	/// <summary>
	/// Dialog field meant to contain the address of a person
	/// </summary>
	CEdit m_edbPersonsAddress;

	/// <summary>
	/// Combo box menu containing the cities choices
	/// </summary>
	CComboBox m_cmbPersonsCity;

	/// <summary>
	/// A list of the phone numbers of the chosen person
	/// </summary>
	CListCtrl m_lscPersonsPhoneNumbers;
};