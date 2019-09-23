
// CPhoneTypesView.cpp : implementation of the CPhoneTypesView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "PhoneTypesDoc.h"
#include "PhoneTypesView.h"
#include "PhoneTypesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum PhoneTypesColumns
{
	PhoneTypesColumnType
};

IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPhoneTypesView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_DELETE, &CPhoneTypesView::Delete)
	ON_COMMAND(ID_EDIT_UPDATE, &CPhoneTypesView::Update)
	ON_COMMAND(ID_EDIT_INSERT, &CPhoneTypesView::Insert)
	ON_COMMAND(ID_EDIT_REVIEW, &CPhoneTypesView::Read)
END_MESSAGE_MAP()

// CPhoneTypesView construction/destruction

CPhoneTypesView::CPhoneTypesView() noexcept
{
}

CPhoneTypesView::~CPhoneTypesView()
{
}

BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;

	return __super::PreCreateWindow(cs);
}

//Operations
//public

void CPhoneTypesView::Delete()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please select a phone type to delete."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CPhoneTypesDoc* oPhoneTypesDoc = GetDocument();
	if (oPhoneTypesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	oPhoneTypesDoc->DeleteByIndex(nRecordIndex);
}

void CPhoneTypesView::Update()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please select a phone type to modify."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CPhoneTypesDoc* oPhoneTypesDoc = GetDocument();
	if (oPhoneTypesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	PHONE_TYPES* pPhoneType = oPhoneTypesDoc->GetPhoneTypesArray().GetAt(nRecordIndex);
	if (pPhoneType == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the phone types data cannot be achieved."));
	}

	DialogModes eDialogMode = DialogModes::DialogModeUpdate;

	CPhoneTypesDialog oPhoneTypesDialog(eDialogMode, *pPhoneType);

	if (oPhoneTypesDialog.DoModal() != IDOK)
	{
		return;
	}

	oPhoneTypesDoc->UpdateByIndex(nRecordIndex, *pPhoneType);
}

void CPhoneTypesView::Insert()
{
	PHONE_TYPES recPhoneType;

	DialogModes eDialogMode = DialogModes::DialogModeInsert;

	CPhoneTypesDialog oPhoneTypesDialog(eDialogMode, recPhoneType);

	if (oPhoneTypesDialog.DoModal() != IDOK)
	{
		return;
	}

	CPhoneTypesDoc* oPhoneTypesDoc = GetDocument();
	if (oPhoneTypesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	oPhoneTypesDoc->InsertByIndex(recPhoneType);
}

void CPhoneTypesView::Read()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please select a phone type to look at."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CPhoneTypesDoc* oPhoneTypesDoc = GetDocument();
	if (oPhoneTypesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	PHONE_TYPES* pPhoneType = oPhoneTypesDoc->GetPhoneTypesArray().GetAt(nRecordIndex);
	if (pPhoneType == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the cities data cannot be achieved."));
	}

	DialogModes eDialogMode = DialogModes::DialogModeRead;

	CPhoneTypesDialog oPhoneTypesDialog(eDialogMode, *pPhoneType);

	if (oPhoneTypesDialog.DoModal() != IDOK)
	{
		return;
	}
}

//private
void CPhoneTypesView::ModifyViewList(LPARAM lHint, INT_PTR nElementIndex)
{
	CListCtrl &m_ListCtrl = GetListCtrl();

	CPhoneTypesDoc* oPhoneTypesDoc = GetDocument();
	if (oPhoneTypesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}

	CString strType = oPhoneTypesDoc->GetPhoneTypesArray().GetAt(nElementIndex)->szTYPE;
	strType.TrimRight(' ');

	switch (lHint)
	{
		case UpdateViewsTypeInsert:
		{
			m_ListCtrl.InsertItem(nElementIndex, strType);
			m_ListCtrl.SetItemData(nElementIndex, (DWORD) nElementIndex);
			break;
		}

		case UpdateViewsTypeUpdate:
		{
			m_ListCtrl.SetItemText(nElementIndex, PhoneTypesColumnType, strType);
			break;
		}
	}
}


void CPhoneTypesView::OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint)
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

void CPhoneTypesView::OnDraw(CDC* /*pDC*/)
{
	CPhoneTypesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void CPhoneTypesView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	CPhoneTypesDoc* oPhoneTypesDoc = GetDocument();
	if (oPhoneTypesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}

	// Insert columns
	GetListCtrl().InsertColumn(PhoneTypesColumnType, _T("TYPE"), LVCFMT_LEFT, 256);

	for (INT_PTR nIndex = 0; nIndex < oPhoneTypesDoc->GetPhoneTypesArray().GetCount(); nIndex++)
	{
		ModifyViewList(UpdateViewsTypeInsert, nIndex);
	}

}


// CCitiesView printing


void CPhoneTypesView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPhoneTypesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPhoneTypesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CPhoneTypesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CPhoneTypesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhoneTypesView::OnLButtonDblClk(UINT /* nFlags */, CPoint point)
{
	Read();
}

void CPhoneTypesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CMenu *pMenu = new CMenu;
	pMenu->LoadMenu(IDR_CITIES_EDIT_MENU);
	CMenu* pSubMenu = new CMenu;
	pSubMenu = pMenu->GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this, 0);

	delete pMenu;
	pMenu = NULL;
}


// CCitiesView diagnostics

#ifdef _DEBUG
void CPhoneTypesView::AssertValid() const
{
	__super::AssertValid();
}

void CPhoneTypesView::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}

CPhoneTypesDoc* CPhoneTypesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDoc)));
	return (CPhoneTypesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers
