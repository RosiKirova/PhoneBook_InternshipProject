
// CCitiesDoc.cpp : implementation of the CCitiesDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "CitiesDoc.h"
#include "CAutoDeleteTypedPtrArray.h"
#include "Structures.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCitiesDoc

IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()


// CCitiesDoc construction/destruction

CCitiesDoc::CCitiesDoc() noexcept
{
}

CCitiesDoc::~CCitiesDoc()
{
}

BOOL CCitiesDoc::OnNewDocument()
{
	if (!__super::OnNewDocument())
		return FALSE;

	// Filling the document with data
	CCitiesData oCitiesData;
	if (oCitiesData.SelectAll(m_oCitiesArray) == FALSE)
	{
		AfxMessageBox(_T(" An error occurred. The data cannot be displayed."));
		return FALSE;
	}

	return TRUE;
}




// CCitiesDoc serialization

void CCitiesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCitiesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCitiesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCitiesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCitiesDoc diagnostics

#ifdef _DEBUG
void CCitiesDoc::AssertValid() const
{
	__super::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}
#endif //_DEBUG


// CCitiesDoc commands
const CCitiesArray& CCitiesDoc::GetCitiesArray()
{
	return m_oCitiesArray;
}

BOOL CCitiesDoc::UpdateByIndex(const INT_PTR nRecordIndex, CITIES& recCity)
{
	// Index checking
	if (IsIndexInRange(nRecordIndex) == FALSE)
	{
		return FALSE;
	}

	// Modifying the record in the database
	CCitiesData oCitiesData;
	if (oCitiesData.UpdateWhereID(recCity.lID, recCity) == FALSE)
	{
		return FALSE;
	}

	// Modifying the record in the document
	m_oCitiesArray.DeleteCTypedPtrArrayElement(nRecordIndex);

	m_oCitiesArray.SetAt(nRecordIndex, new CITIES(recCity));

	// Modifying the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeUpdate, (CObject*)&nRecordIndex);

	return TRUE;
}
BOOL CCitiesDoc::InsertByIndex(CITIES& recCity)
{
	// Inserting the record in the database
	CCitiesData oCitiesData;
	if (oCitiesData.Insert(recCity) == FALSE)
	{
		return FALSE;
	}

	// Inserting the record in the document
	const INT_PTR nRecordIndex = m_oCitiesArray.Add(new CITIES(recCity));

	// Inserting the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeInsert, (CObject*)&nRecordIndex);

	return TRUE;
}
BOOL CCitiesDoc::DeleteByIndex(const INT_PTR nRecordIndex)
{
	// Index checking
	if (IsIndexInRange(nRecordIndex) == FALSE)
	{
		return FALSE;
	}

	// Deleting the record in the database
	CCitiesData oCitiesData;
	if (oCitiesData.DeleteWhereID(m_oCitiesArray.GetAt(nRecordIndex)->lID) == FALSE)
	{
		return FALSE;
	}

	// Deleting the record in the document
	m_oCitiesArray.DeleteCTypedPtrArrayElement(nRecordIndex);

	m_oCitiesArray.RemoveAt(nRecordIndex);

	// Deleting the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeDelete, (CObject*)&nRecordIndex);

	return TRUE;
}

BOOL CCitiesDoc::IsIndexInRange(const INT_PTR nIndex)
{
	if (nIndex < 0 || nIndex > m_oCitiesArray.GetCount())
	{
		AfxMessageBox(_T("The index is not in the existing range."));
		return FALSE;
	}

	return TRUE;
}