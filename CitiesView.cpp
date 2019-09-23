// CCitiesView.cpp : implementation of the CCitiesView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "CitiesDoc.h"
#include "CitiesView.h"
#include "CitiesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum CitiesColumns
{
	CitiesColumnName,
	CitiesColumnRegion
};

// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCitiesView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_DELETE, &CCitiesView::Delete)
	ON_COMMAND(ID_EDIT_UPDATE, &CCitiesView::Update)
	ON_COMMAND(ID_EDIT_INSERT, &CCitiesView::Insert)
	ON_COMMAND(ID_EDIT_REVIEW, &CCitiesView::Read)
END_MESSAGE_MAP()

// CCitiesView construction/destruction

CCitiesView::CCitiesView() noexcept
{
}

CCitiesView::~CCitiesView()
{
}

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;

	return __super::PreCreateWindow(cs);
}

//Operations
//public

void CCitiesView::Delete()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a city to delete."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CCitiesDoc* oCitiesDoc = GetDocument();
	if (oCitiesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	oCitiesDoc->DeleteByIndex(nRecordIndex);
}

void CCitiesView::Update()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a city to modify."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CCitiesDoc* oCitiesDoc = GetDocument();
	if (oCitiesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}

	CITIES* recCity = oCitiesDoc->GetCitiesArray().GetAt(nRecordIndex);
	if (recCity == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the needed data cannot be achieved."));
	}

	DialogModes eDialogMode = DialogModes::DialogModeUpdate;

	CCitiesDialog oCitiesDialog(eDialogMode, *recCity);

	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	oCitiesDoc->UpdateByIndex(nRecordIndex, *recCity);
}

void CCitiesView::Insert()
{
	CITIES recCity;

	DialogModes eDialogMode = DialogModes::DialogModeInsert;

	CCitiesDialog oCitiesDialog(eDialogMode, recCity);

	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	CCitiesDoc* oCitiesDoc = GetDocument();
	if (oCitiesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	oCitiesDoc->InsertByIndex(recCity);
}

void CCitiesView::Read()
{
	POSITION recPosition = GetListCtrl().GetFirstSelectedItemPosition();

	if (recPosition == NULL)
	{
		AfxMessageBox(_T("Please choose a city to look at."));
		return;
	}

	const INT_PTR nIndex = GetListCtrl().GetNextSelectedItem(recPosition);
	const INT_PTR nRecordIndex = GetListCtrl().GetItemData(nIndex);

	CCitiesDoc* oCitiesDoc = GetDocument();
	if (oCitiesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}
	CITIES* recCity = oCitiesDoc->GetCitiesArray().GetAt(nRecordIndex);
	if (recCity == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the needed data cannot be achieved."));
	}

	DialogModes eDialogMode = DialogModes::DialogModeRead;

	CCitiesDialog oCitiesDialog(eDialogMode, *recCity);

	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}
}

//private
void CCitiesView::ModifyViewList(LPARAM lHint, INT_PTR nElementIndex)
{
	CListCtrl &m_ListCtrl = GetListCtrl();

	CCitiesDoc* oCitiesDoc = GetDocument();
	if (oCitiesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}

	CString strName = oCitiesDoc->GetCitiesArray().GetAt(nElementIndex)->szNAME;
	strName.TrimRight(' ');
	CString strRegion = oCitiesDoc->GetCitiesArray().GetAt(nElementIndex)->szREGION;
	strRegion.TrimRight(' ');

	switch (lHint)
	{
		case UpdateViewsTypeInsert:
		{
			const long lIndexItem = m_ListCtrl.InsertItem(nElementIndex, strName);
			m_ListCtrl.SetItemText(nElementIndex, CitiesColumnRegion, strRegion);
			m_ListCtrl.SetItemData(nElementIndex, (DWORD) nElementIndex);
			break;
		}

		case UpdateViewsTypeUpdate:
		{
			m_ListCtrl.SetItemText(nElementIndex, CitiesColumnName, strName);
			m_ListCtrl.SetItemText(nElementIndex, CitiesColumnRegion, strRegion);
			break;
		}
	}
}


void CCitiesView::OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint)
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

void CCitiesView::OnDraw(CDC* /*pDC*/)
{
	CCitiesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void CCitiesView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	CCitiesDoc* oCitiesDoc = GetDocument();
	if (oCitiesDoc == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the document cannot be achieved."));
		return;
	}

	// Insert columns
	GetListCtrl().InsertColumn(CitiesColumnName, _T("NAME"), LVCFMT_LEFT, 256);
	GetListCtrl().InsertColumn(CitiesColumnRegion, _T("REGION"), LVCFMT_LEFT, 256);

	for (INT_PTR nIndex = 0; nIndex < oCitiesDoc->GetCitiesArray().GetCount(); nIndex++ )
	{
		ModifyViewList(UpdateViewsTypeInsert, nIndex);
	}
	
}


// CCitiesView printing


void CCitiesView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCitiesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCitiesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCitiesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnLButtonDblClk(UINT /* nFlags */, CPoint point)
{
	Read();
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CMenu îMenu;
	îMenu.LoadMenu(IDR_CITIES_EDIT_MENU);
	CMenu* pSubMenu = îMenu.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this, 0);
}


// CCitiesView diagnostics

#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	__super::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers
