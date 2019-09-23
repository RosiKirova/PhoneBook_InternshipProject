#include "stdafx.h"
#include "Phonebook.h"
#include "PhoneNumbersDialog.h"
#include "afxdialogex.h"

#define PHONE_NUMBER_SIZE 13

// CPhoneNumbersDialog dialog
IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialogEx)
BEGIN_MESSAGE_MAP(CPhoneNumbersDialog, CDialogEx)

END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPhoneNumbersDialog::CPhoneNumbersDialog(DialogModes eDialogMode, PHONE_NUMBERS& recPhoneNumber, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent),
	m_eDialogMode(eDialogMode), m_recPhoneNumber(recPhoneNumber), m_oPhoneTypesMap(oPhoneTypesMap)
{
}

CPhoneNumbersDialog::~CPhoneNumbersDialog()
{
}

// MFC Overrides
// ----------------
void CPhoneNumbersDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBERS_NUMBER, m_edbPhoneNumbersNumber);
	DDX_Control(pDX, IDC_CMB_PHONE_NUMBERS_TYPE, m_cmbPhoneNumbersType);
}


// CPhoneNumbersDialog message handlers


// Methods
// ----------------

BOOL CPhoneNumbersDialog::OnInitDialog()
{
	__super::OnInitDialog();

	// Centralizing the dialog
	CenterWindow();

	CPhoneTypesMap::CPair* pPair;
	pPair = m_oPhoneTypesMap.PGetFirstAssoc();
	INT_PTR nIndex = 0;
	while (pPair != NULL)
	{
		PHONE_TYPES* pPhoneType = pPair->value;
		m_cmbPhoneNumbersType.InsertString(nIndex, pPhoneType->szTYPE);
		m_cmbPhoneNumbersType.SetItemData(nIndex, pPhoneType->lID);

		nIndex++;
		pPair = m_oPhoneTypesMap.PGetNextAssoc(pPair);
	}

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

		// Setting the type of the chosen phone number
		INT_PTR nStringIndex;
		for (INT_PTR nIndex = 0; nIndex < m_cmbPhoneNumbersType.GetCount(); nIndex++)
		{
			if (m_cmbPhoneNumbersType.GetItemData(nIndex) == m_recPhoneNumber.lPhoneTypeId)
			{
				nStringIndex = nIndex;
			}
		}
		m_cmbPhoneNumbersType.SetCurSel(nStringIndex);

		break;
	}

	case DialogModeRead:
	{
		const CString strTitleUpdate = _T("Read");
		SetWindowText(strTitleUpdate);

		m_edbPhoneNumbersNumber.SetReadOnly(TRUE);

		// Setting the type of the chosen phone number
		INT_PTR nStringIndex;
		for (INT_PTR nIndex = 0; nIndex < m_cmbPhoneNumbersType.GetCount(); nIndex++)
		{
			if (m_cmbPhoneNumbersType.GetItemData(nIndex) == m_recPhoneNumber.lPhoneTypeId)
			{
				nStringIndex = nIndex;
			}
		}
		m_cmbPhoneNumbersType.SetCurSel(nStringIndex);
		m_cmbPhoneNumbersType.EnableWindow(FALSE);

		break;
	}
	}

	// Clearing the empty spaces on the right side of the text
	CString strNumber = m_recPhoneNumber.szPhoneNumber;
	strNumber.TrimRight(' ');

	// Limiting the text length
	m_edbPhoneNumbersNumber.SetLimitText(PHONE_NUMBER_SIZE);

	// Defining what value the Edit fields to contain
	m_edbPhoneNumbersNumber.SetWindowTextW(strNumber);

	return TRUE;
}


void CPhoneNumbersDialog::OnOK()
{
	// Taking the inserted from the user text
	CString strEditBoxNumber;
	m_edbPhoneNumbersNumber.GetWindowTextW(strEditBoxNumber);

	// Validating the text
	if (ValidateText(strEditBoxNumber) == FALSE)
	{
		m_edbPhoneNumbersNumber.SetFocus();
		AfxMessageBox(_T("Please fill the number field."));

		return;
	}

	if ((strEditBoxNumber.SpanIncluding(_T("+0123456789")) != strEditBoxNumber) || strEditBoxNumber.GetLength() < 6)
	{
		m_edbPhoneNumbersNumber.SetFocus();
		AfxMessageBox(_T("Please fill a valid phone number.\n"));

		return;
	}

	// Taking the already validated text so we can modify the database
	_tcscpy_s(m_recPhoneNumber.szPhoneNumber, strEditBoxNumber);

	// Taking the type value so we can modify the database
	INT_PTR nIndexRow = m_cmbPhoneNumbersType.GetCurSel();
	if (nIndexRow < 0)
	{
		AfxMessageBox(_T("Please select a phone number type."));
		return;
	}
	m_recPhoneNumber.lPhoneTypeId = m_cmbPhoneNumbersType.GetItemData(nIndexRow);

	__super::OnOK();
}

BOOL CPhoneNumbersDialog::ValidateText(CString& strBoxText)
{
	//Checking whether there is any text inserted
	if (strBoxText.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}
