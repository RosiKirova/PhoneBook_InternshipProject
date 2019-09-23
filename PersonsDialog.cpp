// PersonsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Phonebook.h"
#include "PersonsDialog.h"
#include "PhoneNumbersDialog.h"
#include "PersonsView.h"
#include "afxdialogex.h"

#define UCN_SIZE 10

enum PhoneNumbersColumns
{
	PhoneNumbersColumnNumber,
	PhoneNumbersColumnType
};

// CPersonsDialog dialog
IMPLEMENT_DYNAMIC(CPersonsDialog, CDialogEx)
BEGIN_MESSAGE_MAP(CPersonsDialog, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_NOTIFY(NM_DBLCLK, IDC_LSC_PERSONS_PHONE_NUMBERS, &CPersonsDialog::OnLButtonDblClk)
	ON_COMMAND(ID_PHONE_NUMBERS_EDIT_DELETE, &CPersonsDialog::PhoneNumbersDelete)
	ON_COMMAND(ID_PHONE_NUMBERS_EDIT_UPDATE, &CPersonsDialog::PhoneNumbersUpdate)
	ON_COMMAND(ID_PHONE_NUMBERS_EDIT_INSERT, &CPersonsDialog::PhoneNumbersInsert)
	ON_COMMAND(ID_PHONE_NUMBERS_EDIT_REVIEW, &CPersonsDialog::PhoneNumbersRead)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsDialog::CPersonsDialog(DialogModes eDialogMode, CPersonDetails& oPersonDetails,
	CCitiesMap& oCitiesNamesMap, CPhoneTypesMap& oPhoneTypesMap, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent),
	m_eDialogMode(eDialogMode), m_oPersonDetails(oPersonDetails), m_oCitiesNamesMap(oCitiesNamesMap), m_oPhoneTypesMap(oPhoneTypesMap)
{
	
}

CPersonsDialog::~CPersonsDialog()
{
}

// MFC Overrides
// ----------------
void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSONS_FIRST_NAME, m_edbPersonsFirstName);
	DDX_Control(pDX, IDC_EDB_PERSONS_MIDDLE_NAME, m_edbPersonsMiddleName);
	DDX_Control(pDX, IDC_EDB_PERSONS_LAST_NAME, m_edbPersonsLastName);
	DDX_Control(pDX, IDC_EDB_PERSONS_UCN, m_edbPersonsUCN);
	DDX_Control(pDX, IDC_EDB_PERSONS_ADDRESS, m_edbPersonsAddress);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITY, m_cmbPersonsCity);
	DDX_Control(pDX, IDC_LSC_PERSONS_PHONE_NUMBERS, m_lscPersonsPhoneNumbers);
}


// CPersonsDialog message handlers


// Methods
// ----------------

BOOL CPersonsDialog::OnInitDialog()
{
	__super::OnInitDialog();

	m_lscPersonsPhoneNumbers.SetExtendedStyle(m_lscPersonsPhoneNumbers.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	// Centalizing the dialog
	CenterWindow();

	PERSONS recPerson;

	CCitiesMap::CPair* pPair;
	pPair = m_oCitiesNamesMap.PGetFirstAssoc();
	INT_PTR nIndex = 0;
	while (pPair != NULL)
	{
		CITIES* pCity = pPair->value;
		m_cmbPersonsCity.InsertString(nIndex, pCity->szNAME);
		m_cmbPersonsCity.SetItemData(nIndex, pCity->lID);

		nIndex++;
		pPair = m_oCitiesNamesMap.PGetNextAssoc(pPair);
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

		recPerson = m_oPersonDetails.GetPerson();

		// Filling the city of the chosen person in the combo box
		INT_PTR nStringIndex = CB_ERR;
		for (INT_PTR nIndex = 0; nIndex < m_cmbPersonsCity.GetCount(); nIndex++)
		{
			if (m_cmbPersonsCity.GetItemData(nIndex) == recPerson.lCityId)
			{
				nStringIndex = nIndex;
			}
		}
		m_cmbPersonsCity.SetCurSel(nStringIndex);

		break;
	}

	case DialogModeRead:
	{
		const CString strTitleUpdate = _T("Read");
		SetWindowText(strTitleUpdate);

		m_edbPersonsFirstName.SetReadOnly(TRUE);
		m_edbPersonsMiddleName.SetReadOnly(TRUE);
		m_edbPersonsLastName.SetReadOnly(TRUE);
		m_edbPersonsUCN.SetReadOnly(TRUE);
		m_edbPersonsAddress.SetReadOnly(TRUE);

		recPerson = m_oPersonDetails.GetPerson();

		// Filling the city of the chosen person in the combo box
		INT_PTR nStringIndex;
		for (INT_PTR nIndex = 0; nIndex < m_cmbPersonsCity.GetCount(); nIndex++)
		{
			if (m_cmbPersonsCity.GetItemData(nIndex) == recPerson.lCityId)
			{
				nStringIndex = nIndex;
				m_cmbPersonsCity.SetCurSel(nStringIndex);
				m_cmbPersonsCity.EnableWindow(FALSE);
				break;
			}
		}
	
		break;
	}
	}


	// Clearing the empty spaces on the right side of the text
	CString strFirstName = recPerson.szFirstName;
	strFirstName.TrimRight(' ');
	CString strMiddleName = recPerson.szMiddleName;
	strMiddleName.TrimRight(' ');
	CString strLastName = recPerson.szLastName;
	strLastName.TrimRight(' ');
	CString strUCN = recPerson.szUCN;
	strUCN.TrimRight(' ');
	CString strAddress = recPerson.szADDRESS;
	strAddress.TrimRight(' ');
	

	// Limiting the text length
	m_edbPersonsFirstName.SetLimitText(PERSONS_FIRST_NAME_SIZE);
	m_edbPersonsMiddleName.SetLimitText(PERSONS_MIDDLE_NAME_SIZE);
	m_edbPersonsLastName.SetLimitText(PERSONS_LAST_NAME_SIZE);
	m_edbPersonsUCN.SetLimitText(UCN_SIZE);
	m_edbPersonsAddress.SetLimitText(PERSONS_ADDRESS_SIZE);

	// Defining what value the Edit fields to contain
	m_edbPersonsFirstName.SetWindowText(strFirstName);
	m_edbPersonsMiddleName.SetWindowText(strMiddleName);
	m_edbPersonsLastName.SetWindowText(strLastName);
	m_edbPersonsUCN.SetWindowText(strUCN);
	m_edbPersonsAddress.SetWindowText(strAddress);

	// Setting columns and their names for the list with the phone numbers
	m_lscPersonsPhoneNumbers.InsertColumn(PhoneNumbersColumnNumber,_T("NUMBER"), 0, 128);
	m_lscPersonsPhoneNumbers.InsertColumn(PhoneNumbersColumnType, _T("TYPE"), 0, 128);

	CPhoneNumbersArray* pPhoneNumbersArray = &(m_oPersonDetails.GetPhoneNumbersArray());
	for (INT_PTR nIndex = 0; nIndex < (*pPhoneNumbersArray).GetCount(); nIndex++)
	{
		CString strPhoneNumber = (*pPhoneNumbersArray).GetAt(nIndex)->szPhoneNumber;
		strPhoneNumber.TrimRight(' ');
		PHONE_TYPES* recPhoneType;
		m_oPhoneTypesMap.Lookup((*pPhoneNumbersArray).GetAt(nIndex)->lPhoneTypeId, recPhoneType);
		CString strPhoneType = recPhoneType->szTYPE;

		const long lIndexItem = m_lscPersonsPhoneNumbers.InsertItem(nIndex, strPhoneNumber);
		m_lscPersonsPhoneNumbers.SetItemText(nIndex, PhoneNumbersColumnType, strPhoneType);
	}

	return TRUE;
}


void CPersonsDialog::OnOK()
{
	// Taking the inserted from the user text
	CString strEditBoxFirstName;
	m_edbPersonsFirstName.GetWindowTextW(strEditBoxFirstName);

	CString strEditBoxMiddleName;
	m_edbPersonsMiddleName.GetWindowTextW(strEditBoxMiddleName);

	CString strEditBoxLastName;
	m_edbPersonsLastName.GetWindowTextW(strEditBoxLastName);

	CString strEditBoxUCN;
	m_edbPersonsUCN.GetWindowTextW(strEditBoxUCN);

	CString strEditBoxAddress;
	m_edbPersonsAddress.GetWindowTextW(strEditBoxAddress);

	// Validating the text
	BOOL bIsThereEmpty = FALSE;
	BOOL bIsUCNValid = TRUE;
	CString strEditBoxes;
	CString strMessage = _T("Please fill the empty fields:\n");

	if (ValidateOnlyIfEmpty(strEditBoxAddress) == FALSE)
	{
		m_edbPersonsAddress.SetFocus();
		strEditBoxes.Format(_T(" Address"));
		bIsThereEmpty = TRUE;
	}

	if (ValidateOnlyIfEmpty(strEditBoxUCN) == FALSE)
	{
		m_edbPersonsUCN.SetFocus();
		strEditBoxes.Format(_T(" UCN\n") + strEditBoxes);
		bIsThereEmpty = TRUE;
	}

	if ((strEditBoxUCN.SpanIncluding(_T("0123456789")) != strEditBoxUCN) || strEditBoxUCN.GetLength() < 10 )
	{
		m_edbPersonsUCN.SetFocus();
		bIsUCNValid = FALSE;
	}

	if (ValidateText(strEditBoxLastName) == FALSE)
	{
		m_edbPersonsLastName.SetFocus();
		strEditBoxes.Format(_T(" Last Name\n" + strEditBoxes));
		bIsThereEmpty = TRUE;
	}

	if (ValidateText(strEditBoxMiddleName) == FALSE)
	{
		m_edbPersonsMiddleName.SetFocus();
		strEditBoxes.Format(_T(" Middle Name\n" + strEditBoxes));
		bIsThereEmpty = TRUE;
	}

	if (ValidateText(strEditBoxFirstName) == FALSE)
	{
		m_edbPersonsFirstName.SetFocus();
		strEditBoxes.Format(_T(" First Name\n" + strEditBoxes));
		bIsThereEmpty = TRUE;
	}

	if (bIsThereEmpty)
	{
		strMessage.Format(strMessage + strEditBoxes);
		AfxMessageBox(strMessage);
		
		return;
	}

	if (!bIsUCNValid)
	{
		AfxMessageBox(_T("Please insert a valid UCN.\nAn UCN contains exactly ten numbers."));

		return;
	}

	// Taking the already validated text so we can modify the database
	_tcscpy_s(m_oPersonDetails.GetPerson().szFirstName, strEditBoxFirstName);

	_tcscpy_s(m_oPersonDetails.GetPerson().szMiddleName, strEditBoxMiddleName);

	_tcscpy_s(m_oPersonDetails.GetPerson().szLastName, strEditBoxLastName);

	_tcscpy_s(m_oPersonDetails.GetPerson().szUCN, strEditBoxUCN);

	_tcscpy_s(m_oPersonDetails.GetPerson().szADDRESS, strEditBoxAddress);

	// Taking the chosen city value so we can modify the database
	PERSONS* pPerson = NULL;
	pPerson = &(m_oPersonDetails.GetPerson());
	INT_PTR nIndexRow = m_cmbPersonsCity.GetCurSel();
	if (nIndexRow < 0)
	{
		AfxMessageBox(_T("Please select a city."));
		return;
	}
	pPerson->lCityId = m_cmbPersonsCity.GetItemData(nIndexRow);

	__super::OnOK();
}

BOOL CPersonsDialog::ValidateText(CString& strBoxText)
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

BOOL CPersonsDialog::ValidateOnlyIfEmpty(CString& strBoxText)
{
	// Checking whether there is any text inserted
	if (strBoxText.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}

void CPersonsDialog::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPersonsDialog::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CMenu oMenu;
	oMenu.LoadMenuW(IDR_PHONE_NUMBERS_EDIT_MENU);
	CMenu* pSubMenu = oMenu.GetSubMenu(0);

	if (m_eDialogMode == DialogModeRead)
	{
		EnableMenuItem(*pSubMenu, ID_PHONE_NUMBERS_EDIT_DELETE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(*pSubMenu, ID_PHONE_NUMBERS_EDIT_UPDATE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(*pSubMenu, ID_PHONE_NUMBERS_EDIT_INSERT, MF_BYCOMMAND | MF_GRAYED);
	}

	pSubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this, 0);
}

void CPersonsDialog::OnLButtonDblClk(NMHDR *, LRESULT *)
{
	PhoneNumbersRead();
}

void CPersonsDialog::PhoneNumbersDelete()
{
	POSITION oPosition = m_lscPersonsPhoneNumbers.GetFirstSelectedItemPosition();

	if (oPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a phone number to delete."));
		return;
	}

	const INT_PTR nIndex = m_lscPersonsPhoneNumbers.GetNextSelectedItem(oPosition);

	m_oPersonDetails.GetPhoneNumbersArray().RemoveAt(nIndex);

	m_lscPersonsPhoneNumbers.DeleteItem(nIndex);
}

void CPersonsDialog::PhoneNumbersUpdate()
{
	POSITION oPosition = m_lscPersonsPhoneNumbers.GetFirstSelectedItemPosition();

	if (oPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a phone number to modify."));
		return;
	}

	const INT_PTR nIndex = m_lscPersonsPhoneNumbers.GetNextSelectedItem(oPosition);

	DialogModes eDialogMode = DialogModes::DialogModeUpdate;

	PHONE_NUMBERS* pPhoneNumber = m_oPersonDetails.GetPhoneNumbersArray().GetAt(nIndex);

	CPhoneNumbersDialog oPhoneNumbersDialog(eDialogMode, *pPhoneNumber, m_oPhoneTypesMap);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		return;
	}

	m_oPersonDetails.GetPhoneNumbersArray().SetAt(nIndex, pPhoneNumber);

	PHONE_TYPES* recPhoneType;
	m_oPhoneTypesMap.Lookup(pPhoneNumber->lPhoneTypeId, recPhoneType);
	CString strPhoneType = recPhoneType->szTYPE;

	m_lscPersonsPhoneNumbers.SetItemText(nIndex, PhoneNumbersColumnNumber, pPhoneNumber->szPhoneNumber);
	m_lscPersonsPhoneNumbers.SetItemText(nIndex, PhoneNumbersColumnType, strPhoneType);
}

void CPersonsDialog::PhoneNumbersInsert()
{
	PHONE_NUMBERS recPhoneNumber;

	DialogModes eDialogMode = DialogModes::DialogModeInsert;

	CPhoneNumbersDialog oPhoneNumbersDialog(eDialogMode, recPhoneNumber, m_oPhoneTypesMap);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		return;
	}

	PHONE_NUMBERS* pPhoneNumber = new PHONE_NUMBERS();
	recPhoneNumber.lPersonId = m_oPersonDetails.GetPerson().lID;
	*pPhoneNumber = recPhoneNumber;
	const INT_PTR nRecordIndex = m_oPersonDetails.GetPhoneNumbersArray().Add(pPhoneNumber);

	PHONE_TYPES* recPhoneType;
	m_oPhoneTypesMap.Lookup(pPhoneNumber->lPhoneTypeId, recPhoneType);
	CString strPhoneType = recPhoneType->szTYPE;

	const long lIndexItem = m_lscPersonsPhoneNumbers.InsertItem(nRecordIndex, pPhoneNumber->szPhoneNumber);
	m_lscPersonsPhoneNumbers.SetItemText(nRecordIndex, PhoneNumbersColumnType, strPhoneType);
}

void CPersonsDialog::PhoneNumbersRead()
{
	POSITION oPosition = m_lscPersonsPhoneNumbers.GetFirstSelectedItemPosition();

	if (oPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a phone number to look at."));
		return;
	}

	const INT_PTR nRecordIndex = m_lscPersonsPhoneNumbers.GetNextSelectedItem(oPosition);

	DialogModes eDialogMode = DialogModes::DialogModeRead;

	PHONE_NUMBERS* pPhoneNumber = m_oPersonDetails.GetPhoneNumbersArray().GetAt(nRecordIndex);

	CPhoneNumbersDialog oPhoneNumbersDialog(eDialogMode, *pPhoneNumber, m_oPhoneTypesMap);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		return;
	}
}

