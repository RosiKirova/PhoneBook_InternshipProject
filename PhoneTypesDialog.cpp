#include "stdafx.h"
#include "Phonebook.h"
#include "PhoneTypesDialog.h"
#include "afxdialogex.h"

// CPhoneTypesDialog dialog
IMPLEMENT_DYNAMIC(CPhoneTypesDialog, CDialogEx)
BEGIN_MESSAGE_MAP(CPhoneTypesDialog, CDialogEx)

END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneTypesDialog::CPhoneTypesDialog(DialogModes eDialogMode, PHONE_TYPES& recPhoneType, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent),
	m_eDialogMode(eDialogMode), m_recPhoneType(recPhoneType)
{
}

CPhoneTypesDialog::~CPhoneTypesDialog()
{
}

// MFC Overrides
// ----------------
void CPhoneTypesDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_TYPES_TYPE, m_edbPhoneTypesType);
}


// CPhoneTypesDialog message handlers


// Methods
// ----------------

BOOL CPhoneTypesDialog::OnInitDialog()
{
	__super::OnInitDialog();

	// Centralizing the dialog
	CenterWindow();

	// Setting the dialog type
	switch (m_eDialogMode)
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

		m_edbPhoneTypesType.SetReadOnly(TRUE);

		break;
	}
	}

	// Clearing the empty spaces on the right side of the text
	CString strType = m_recPhoneType.szTYPE;
	strType.TrimRight(' ');

	// Limiting the text length
	m_edbPhoneTypesType.SetLimitText(PHONE_TYPES_TYPE_SIZE);

	// Defining what value the Edit fields to contain
	m_edbPhoneTypesType.SetWindowTextW(strType);

	return TRUE;
}


void CPhoneTypesDialog::OnOK()
{
	// Taking the inserted from the user textí
	CString strEditBoxName;
	m_edbPhoneTypesType.GetWindowTextW(strEditBoxName);

	// Validating the text
	if (ValidateText(strEditBoxName) == FALSE)
	{
		m_edbPhoneTypesType.SetFocus();
		AfxMessageBox(_T("Please fill the type field."));

		return;
	}

	// Taking the already validated text so we can modify the database
	_tcscpy_s(m_recPhoneType.szTYPE, strEditBoxName);

	__super::OnOK();
}

BOOL CPhoneTypesDialog::ValidateText(CString& strBoxText)
{
	// Checking whether there is any text inserted
	if (strBoxText.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}