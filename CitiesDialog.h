#pragma once

#include "Structures.h"
#include "CitiesView.h"

// CCitiesDialog dialog

class CCitiesDialog : public CDialogEx
{
	// Macros
	// ----------------
	DECLARE_DYNAMIC(CCitiesDialog)
	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------
private:
	enum { IDD = IDD_CITIES };

	// Constructor / Destructor
	// ----------------
public:
	CCitiesDialog(DialogModes eDialogMode, CITIES& recCity, CWnd* pParent = nullptr);	// implicit constructor
	virtual ~CCitiesDialog();

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
	/// A reference to CITIES struct
	/// </summary>
	CITIES& m_recCity;

	/// <summary>
	/// Dialog field meant to contain the cities' names
	/// </summary>
	CEdit m_edbCitiesName;

	/// <summary>
	/// Dialog field meant to contain the cities' regions
	/// </summary>
	CEdit m_edbCitiesRegion;
};
