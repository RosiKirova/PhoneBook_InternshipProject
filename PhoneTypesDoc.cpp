
// CPhoneTypesDoc.cpp : implementation of the CPhoneTypesDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "PhoneTypesDoc.h"
#include "CAutoDeleteTypedPtrArray.h"
#include "Structures.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPhoneTypesDoc

IMPLEMENT_DYNCREATE(CPhoneTypesDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhoneTypesDoc, CDocument)
END_MESSAGE_MAP()


// CPhoneTypesDoc construction/destruction

CPhoneTypesDoc::CPhoneTypesDoc() noexcept
{
}

CPhoneTypesDoc::~CPhoneTypesDoc()
{
}

BOOL CPhoneTypesDoc::OnNewDocument()
{
	if (!__super::OnNewDocument())
		return FALSE;

	// Filling the document with data
	CPhoneTypesData oPhoneTypesData;
	if (oPhoneTypesData.SelectAll(m_oPhoneTypesArray) == FALSE)
	{
		AfxMessageBox(_T("An error occurred. The data cannot be displayed."));
		return FALSE;
	}

	return TRUE;
}




// CPhoneTypesDoc serialization

void CPhoneTypesDoc::Serialize(CArchive& ar)
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

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
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

// CPhoneTypesDoc diagnostics

#ifdef _DEBUG
void CPhoneTypesDoc::AssertValid() const
{
	__super::AssertValid();
}

void CPhoneTypesDoc::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}
#endif //_DEBUG


// CPhoneTypesDoc commands
const CPhoneTypesArray& CPhoneTypesDoc::GetPhoneTypesArray()
{
	return m_oPhoneTypesArray;
}

BOOL CPhoneTypesDoc::UpdateByIndex(const INT_PTR nRecordIndex, PHONE_TYPES& recPhoneType)
{
	// Index checking
	if (IsIndexInRange(nRecordIndex) == FALSE)
	{
		return FALSE;
	}

	// Modifying the record in the database
	CPhoneTypesData oPhoneTypesData;
	if (oPhoneTypesData.UpdateWhereID(recPhoneType.lID, recPhoneType) == FALSE)
	{
		return FALSE;
	}

	// Modifying the record in the document
	m_oPhoneTypesArray.DeleteCTypedPtrArrayElement(nRecordIndex);

	m_oPhoneTypesArray.SetAt(nRecordIndex, new PHONE_TYPES(recPhoneType));

	// Modifying the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeUpdate, (CObject*)&nRecordIndex);

	return TRUE;
}
BOOL CPhoneTypesDoc::InsertByIndex(PHONE_TYPES& recPhoneType)
{
	// Inserting the record in the database
	CPhoneTypesData oPhoneTypesData;
	if (oPhoneTypesData.Insert(recPhoneType) == FALSE)
	{
		return FALSE;
	}

	// Inserting the record in the document
	const INT_PTR nRecordIndex = m_oPhoneTypesArray.Add(new PHONE_TYPES(recPhoneType));

	// Inserting the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeInsert, (CObject*)&nRecordIndex);

	return TRUE;
}
BOOL CPhoneTypesDoc::DeleteByIndex(const INT_PTR nRecordIndex)
{
	// Index checking
	if (IsIndexInRange(nRecordIndex) == FALSE)
	{
		return FALSE;
	}

	//  Deleting the record in the database
	CPhoneTypesData oPhoneTypesData;
	if (oPhoneTypesData.DeleteWhereID(m_oPhoneTypesArray.GetAt(nRecordIndex)->lID) == FALSE)
	{
		return FALSE;
	}

	// Deleting the record in the document
	m_oPhoneTypesArray.DeleteCTypedPtrArrayElement(nRecordIndex);

	m_oPhoneTypesArray.RemoveAt(nRecordIndex);

	// Deleting the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeDelete, (CObject*)&nRecordIndex);

	return TRUE;
}

BOOL CPhoneTypesDoc::IsIndexInRange(const INT_PTR nIndex)
{
	if (nIndex < 0 || nIndex > m_oPhoneTypesArray.GetCount())
	{
		AfxMessageBox(_T("The index is not in the existing range."));
		return FALSE;
	}

	return TRUE;
}