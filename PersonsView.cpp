
// CPersonsView.cpp : implementation of the CPersonsView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "PersonsDoc.h"
#include "PersonsView.h"
#include "PersonsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum PersonsColumns
{
	PersonsColumnFirstName,
	PersonsColumnMiddleName,
	PersonsColumnLastName,
	PersonsColumnUCN,
	PersonsColumnAddress,
	PersonsColumnCity
};

IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPersonsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_DELETE, &CPersonsView::Delete)
	ON_COMMAND(ID_EDIT_UPDATE, &CPersonsView::Update)
	ON_COMMAND(ID_EDIT_INSERT, &CPersonsView::Insert)
	ON_COMMAND(ID_EDIT_REVIEW, &CPersonsView::Read)
END_MESSAGE_MAP()

// CPersonsView construction/destruction

CPersonsView::CPersonsView() noexcept
{
}

CPersonsView::~CPersonsView()
{
}

BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;

	return __super::PreCreateWindow(cs);
}

//Operations
//public

void CPersonsView::Delete()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a person to delete."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CPersonsDoc* pPersonsDoc = GetDocument();
	if (pPersonsDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	pPersonsDoc->DeleteByIndex(nRecordIndex);
}

void CPersonsView::Update()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a person to modify."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CPersonsDoc* pPersonsDoc = GetDocument();
	if (pPersonsDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	
	CPersonDetails oPersonDetails;
	pPersonsDoc->SelectByIndex(nRecordIndex, oPersonDetails);

	DialogModes eDialogMode = DialogModes::DialogModeUpdate;

	CPersonsDialog oPersonsDialog(eDialogMode, oPersonDetails, GetCitiesNamesMap(), GetPhoneTypesMap());

	if (oPersonsDialog.DoModal() != IDOK)
	{
		return;
	}

	pPersonsDoc->UpdateByIndex(nRecordIndex, oPersonDetails);
}

void CPersonsView::Insert()
{
	CPersonDetails oPersonDetails;

	DialogModes eDialogMode = DialogModes::DialogModeInsert;

	CPersonsDialog oPersonsDialog(eDialogMode, oPersonDetails, GetCitiesNamesMap(), GetPhoneTypesMap());

	if (oPersonsDialog.DoModal() != IDOK)
	{
		return;
	}

	CPersonsDoc* pPersonsDoc = GetDocument();
	if (pPersonsDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	pPersonsDoc->InsertByIndex(oPersonDetails);
}

void CPersonsView::Read()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a person to look at."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CPersonsDoc* pPersonsDoc = GetDocument();
	if (pPersonsDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}

	CPersonDetails oPersonDetails;
	pPersonsDoc->SelectByIndex(nRecordIndex, oPersonDetails);

	DialogModes eDialogMode = DialogModes::DialogModeRead;

	CPersonsDialog oPersonsDialog(eDialogMode, oPersonDetails, GetCitiesNamesMap(), GetPhoneTypesMap());

	if (oPersonsDialog.DoModal() != IDOK)
	{
		return;
	}
}


//private
void CPersonsView::ModifyViewList(LPARAM lHint, INT_PTR nElementIndex)
{
	CListCtrl &m_ListCtrl = GetListCtrl();

	CPersonsDoc* pPersonsDoc = GetDocument();
	if (pPersonsDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}

	CString strFirstName = pPersonsDoc->GetPersonsArray().GetAt(nElementIndex)->szFirstName;
	strFirstName.TrimRight(' ');
	CString strMiddleName = pPersonsDoc->GetPersonsArray().GetAt(nElementIndex)->szMiddleName;
	strMiddleName.TrimRight(' ');
	CString strLastName = pPersonsDoc->GetPersonsArray().GetAt(nElementIndex)->szLastName;
	strLastName.TrimRight(' ');
	CString strUCN = pPersonsDoc->GetPersonsArray().GetAt(nElementIndex)->szUCN;
	strUCN.TrimRight(' ');
	CString strAddress = pPersonsDoc->GetPersonsArray().GetAt(nElementIndex)->szADDRESS;
	strAddress.TrimRight(' ');
	CITIES* recCity;
	GetCitiesNamesMap().Lookup(pPersonsDoc->GetPersonsArray().GetAt(nElementIndex)->lCityId, recCity);
	CString strCity = recCity->szNAME;

	switch (lHint)
	{
	case UpdateViewsTypeInsert:
	{
		const long lIndexItem = m_ListCtrl.InsertItem(nElementIndex, strFirstName);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnMiddleName, strMiddleName);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnLastName, strLastName);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnUCN, strUCN);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnAddress, strAddress);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnCity, strCity);
		m_ListCtrl.SetItemData(nElementIndex, (DWORD)nElementIndex);
		break;
	}

	case UpdateViewsTypeUpdate:
	{
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnFirstName, strFirstName);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnMiddleName, strMiddleName);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnLastName, strLastName);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnUCN, strUCN);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnAddress, strAddress);
		m_ListCtrl.SetItemText(nElementIndex, PersonsColumnCity, strCity);
		break;
	}
	}
}

CMap<long, long, CITIES*, CITIES*>& CPersonsView::GetCitiesNamesMap()
{
	return m_oCitiesNamesMap;
}

CMap<long, long, PHONE_TYPES*, PHONE_TYPES*>& CPersonsView::GetPhoneTypesMap()
{
	return m_oPhoneTypesMap;
}


void CPersonsView::OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint)
{
	INT_PTR* pElementIndex = (INT_PTR*)pHint;

	switch (lHint)
	{
	case UpdateViewsTypeInsert:
	{
		ModifyViewList(UpdateViewsTypeInsert, *pElementIndex);

		break;
	}

	case UpdateViewsTypeUpdate:
	{

		ModifyViewList(UpdateViewsTypeUpdate, *pElementIndex);
		break;
	}

	case UpdateViewsTypeDelete:
	{
		GetListCtrl().DeleteItem(*pElementIndex);
		break;
	}
	}

}

void CPersonsView::OnDraw(CDC* /*pDC*/)
{
	CPersonsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void CPersonsView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	CPersonsDoc* pPersonsDoc = GetDocument();
	if (pPersonsDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}

	//Initialize maps
	for (INT_PTR nIndex = 0; nIndex < pPersonsDoc->GetCitiesArray().GetCount(); nIndex++)
	{
		CITIES* pCities = pPersonsDoc->GetCitiesArray().GetAt(nIndex);
		if (pCities == NULL)
		{
			AfxMessageBox(_T("An error occurred. An access to the cities data cannot be achieved."));
		}
		m_oCitiesNamesMap.SetAt(pCities->lID, pCities);
	}

	for (INT_PTR nIndex = 0; nIndex < pPersonsDoc->GetPhoneTypesArray().GetCount(); nIndex++)
	{
		PHONE_TYPES* pPhoneType = pPersonsDoc->GetPhoneTypesArray().GetAt(nIndex);
		if (pPhoneType == NULL)
		{
			AfxMessageBox(_T("An error occurred. An access to the phone types data cannot be achieved."));
		}
		m_oPhoneTypesMap.SetAt(pPhoneType->lID, pPhoneType);
	}

	// Insert columns
	GetListCtrl().InsertColumn(PersonsColumnFirstName, _T("FIRST NAME"), LVCFMT_LEFT, 256);
	GetListCtrl().InsertColumn(PersonsColumnMiddleName, _T("MIDDLE NAME"), LVCFMT_LEFT, 256);
	GetListCtrl().InsertColumn(PersonsColumnLastName, _T("LAST NAME"), LVCFMT_LEFT, 256);
	GetListCtrl().InsertColumn(PersonsColumnUCN, _T("UCN"), LVCFMT_LEFT, 256);
	GetListCtrl().InsertColumn(PersonsColumnAddress, _T("ADDRESS"), LVCFMT_LEFT, 256);
	GetListCtrl().InsertColumn(PersonsColumnCity, _T("CITY"), LVCFMT_LEFT, 256);

	for (INT_PTR nIndex = 0; nIndex < pPersonsDoc->GetPersonsArray().GetCount(); nIndex++)
	{
		ModifyViewList(UpdateViewsTypeInsert, nIndex);
	}

}


// CCitiesView printing


void CPersonsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPersonsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CPersonsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CPersonsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CPersonsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPersonsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CMenu oMenu;
	oMenu.LoadMenu(IDR_CITIES_EDIT_MENU);
	CMenu* pSubMenu = oMenu.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this, 0);
}

void CPersonsView::OnLButtonDblClk(UINT /* nFlags */, CPoint point)
{
	Read();
}

// CCitiesView diagnostics

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	__super::AssertValid();
}

void CPersonsView::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}

CPersonsDoc* CPersonsView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDoc)));
	return (CPersonsDoc*)m_pDocument;
}
#endif //_DEBUG


// CPersonsView message handlers
