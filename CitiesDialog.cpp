// CitiesUpdate.cpp : implementation file
//

#include "stdafx.h"
#include "Phonebook.h"
#include "CitiesDialog.h"
#include "afxdialogex.h"

// CCitiesDialog dialog
IMPLEMENT_DYNAMIC(CCitiesDialog, CDialogEx)
BEGIN_MESSAGE_MAP(CCitiesDialog, CDialogEx)

END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCitiesDialog::CCitiesDialog(DialogModes eDialogMode, CITIES& recCity, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent),
	m_eDialogMode(eDialogMode), m_recCity(recCity)
{
}

CCitiesDialog::~CCitiesDialog()
{
}

// MFC Overrides
// ----------------
void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_edbCitiesName);
	DDX_Control(pDX, IDC_EDB_CITIES_REGION, m_edbCitiesRegion);
}


// CCitiesDialog message handlers


// Methods
// ----------------

BOOL CCitiesDialog::OnInitDialog()
{
	__super::OnInitDialog();

	// Centralizing the dialog
	CenterWindow();

	// Setting the dialog type
	switch(m_eDialogMode)
	{
		case DialogModeInsert:
		{
			const CString strTitleInsert = _T("Insert");
			SetWindowText(strTitleInsert);
			break;
		}

		case DialogModeUpdate:
		{
			const CString strTitleUpdate = _T("Modify");
			SetWindowText(strTitleUpdate);
			break;
		}

		case DialogModeRead:
		{
			const CString strTitleUpdate = _T("Read");
			SetWindowText(strTitleUpdate);

			m_edbCitiesName.SetReadOnly(TRUE);
			m_edbCitiesRegion.SetReadOnly(TRUE);

			break;
		}
	}

	// Clearing the empty spaces on the right side of the text
	CString strName = m_recCity.szNAME;
	strName.TrimRight(' ');
	CString strRegion = m_recCity.szREGION;
	strRegion.TrimRight(' ');

	// Limiting the text length
	m_edbCitiesName.SetLimitText(CITIES_NAME_SIZE);
	m_edbCitiesRegion.SetLimitText(CITIES_REGION_SIZE);

	// Defining what value the Edit fields to contain
	m_edbCitiesName.SetWindowTextW(strName);
	m_edbCitiesRegion.SetWindowTextW(strRegion);

	return TRUE;
}


void CCitiesDialog::OnOK()
{
	// Taking the inserted from the user text
	CString strEditBoxName;
	m_edbCitiesName.GetWindowTextW(strEditBoxName);

	CString strEditBoxRegion;
	m_edbCitiesRegion.GetWindowTextW(strEditBoxRegion);

	// Validating the text
	BOOL bIsThereEmpty = FALSE;
	CString strEditBoxes;
	CString strMessage = _T("Please fill the empty fields:\n");

	if (ValidateText(strEditBoxRegion) == FALSE)
	{
		m_edbCitiesRegion.SetFocus();
		strEditBoxes.Format(_T(" Region\n"));
		bIsThereEmpty = TRUE;
	}

	if (ValidateText(strEditBoxName) == FALSE)
	{
		m_edbCitiesName.SetFocus();
		strEditBoxes.Format(_T(" Name\n") + strEditBoxes);
		bIsThereEmpty = TRUE;
	}

	if (bIsThereEmpty)
	{
		strMessage.Format(strMessage + strEditBoxes);
		AfxMessageBox(strMessage);

		return;
	}

	// Taking the already validated text so we can modify the database
	_tcscpy_s(m_recCity.szNAME, strEditBoxName);

	_tcscpy_s(m_recCity.szREGION, strEditBoxRegion);

	__super::OnOK();
}

BOOL CCitiesDialog::ValidateText(CString& strBoxText)
{
	// Checking whether there is any text inserted
	if (strBoxText.IsEmpty())
	{
		return FALSE;
	}

	// Checking whether the text starts with a capital letter; if not - we change the first letter to a capital one
	TCHAR cFirstLetter = strBoxText.GetAt(0);
	if (iswlower(cFirstLetter))
	{
		strBoxText.SetAt(0, cFirstLetter - LETTER_CASE_NUMERICAL_DIFFERENCE);
	}

	return TRUE;
}
