// CPersonsDoc.cpp : implementation of the CPersonsDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "PersonsDoc.h"
#include "CAutoDeleteTypedPtrArray.h"
#include "CitiesData.h"
#include "PhoneTypesData.h"
#include "Structures.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPersonsDoc

IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)
END_MESSAGE_MAP()


// CPersonsDoc construction/destruction

CPersonsDoc::CPersonsDoc() noexcept
{
}

CPersonsDoc::~CPersonsDoc()
{
}

BOOL CPersonsDoc::OnNewDocument()
{
	if (!__super::OnNewDocument())
		return FALSE;

	// Filling the document with data
	CPersonsData oPersonsData;
	if (oPersonsData.SelectAll(m_PersonsArray) == FALSE)
	{
		AfxMessageBox(_T(" An error occurred. The data cannot be displayed."));
		return FALSE;
	}

	CCitiesData oCitiesData;
	if (oCitiesData.SelectAll(m_oCitiesArray) == FALSE)
	{
		AfxMessageBox(_T(" An error occurred. An access to the cities data cannot be achieved."));
		return FALSE;
	}

	CPhoneTypesData oPhoneTypesData;
	if (oPhoneTypesData.SelectAll(m_oPhoneTypesArray) == FALSE)
	{
		AfxMessageBox(_T("An error occurred. An access to the phone types data cannot be achieved."));
		return FALSE;
	}

	return TRUE;
}


// CPersonsDoc serialization

void CPersonsDoc::Serialize(CArchive& ar)
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

// CPersonsDoc diagnostics

#ifdef _DEBUG
void CPersonsDoc::AssertValid() const
{
	__super::AssertValid();
}

void CPersonsDoc::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}
#endif //_DEBUG


// CPersonsDoc commands
const CPersonsArray& CPersonsDoc::GetPersonsArray()
{
	return m_PersonsArray;
}

const CCitiesArray& CPersonsDoc::GetCitiesArray()
{
	return m_oCitiesArray;
}

const CPhoneTypesArray& CPersonsDoc::GetPhoneTypesArray()
{
	return m_oPhoneTypesArray;
}


BOOL CPersonsDoc::SelectByIndex(const INT_PTR nIndex, CPersonDetails& oPersonDetails)
{
	// Index checking
	if (IsIndexInRange(nIndex) == FALSE)
	{
		return FALSE;
	}

	PERSONS* pPerson = m_PersonsArray.GetAt(nIndex);
	if (pPerson == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the person's data cannot be achieved."));
	}
	long lSelectedElementID = pPerson->lID;

	if (lSelectedElementID <= 0)
	{
		AfxMessageBox(_T("An error occurred. An access to the person's data cannot be achieved."));
		return FALSE;
	}

	CPersonsData oPersonsData;
	if (oPersonsData.SelectPerson(lSelectedElementID, oPersonDetails) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPersonsDoc::UpdateByIndex(const INT_PTR nIndex, CPersonDetails& oPersonDetails)
{
	// Index checking
	if (IsIndexInRange(nIndex) == FALSE)
	{
		return FALSE;
	}

	PERSONS* pPerson = m_PersonsArray.GetAt(nIndex);
	if (pPerson == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the person's data cannot be achieved."));
	}
	long lSelectedElementID = pPerson->lID;

	if (lSelectedElementID <= 0)
	{
		AfxMessageBox(_T("An error occurred. An access to the person's data cannot be achieved."));
		return FALSE;
	}

	// Modifying the record in the database
	CPersonsData oPersonsData;
	if (oPersonsData.UpdatePerson(lSelectedElementID, oPersonDetails) == FALSE)
	{
		return FALSE;
	}

	// Modifying the record in the document
	PERSONS recPerson = oPersonDetails.GetPerson();

	m_PersonsArray.DeleteCTypedPtrArrayElement(nIndex);

	m_PersonsArray.SetAt(nIndex, new PERSONS(recPerson));

	// Modifying the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeUpdate, (CObject*)&nIndex);

	return TRUE;
}
BOOL CPersonsDoc::InsertByIndex(CPersonDetails& oPersonDetails)
{
	// Inserting the record in the database
	CPersonsData oPersonsData;
	if (oPersonsData.InsertPerson(oPersonDetails) == FALSE)
	{
		return FALSE;
	}

	// Inserting the record in the document
	PERSONS recPerson = oPersonDetails.GetPerson();

	const INT_PTR nIndex = m_PersonsArray.Add(new PERSONS(recPerson));

	// Inserting the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeInsert, (CObject*)&nIndex);

	return TRUE;
}
BOOL CPersonsDoc::DeleteByIndex(const INT_PTR nIndex)
{
	// Index checking
	if (IsIndexInRange(nIndex) == FALSE)
	{
		return FALSE;
	}

	PERSONS* pPerson = m_PersonsArray.GetAt(nIndex);
	if (pPerson == NULL)
	{
		AfxMessageBox(_T("An error occurred. An access to the person's data cannot be achieved."));
	}
	long lSelectedElementID = pPerson->lID;

	if (lSelectedElementID <= 0)
	{
		AfxMessageBox(_T("An error occurred. An access to the person's data cannot be achieved."));
		return FALSE;
	}

	// Deleting the record in the database
	CPersonsData oPersonsData;
	if (oPersonsData.DeletePerson(lSelectedElementID) == FALSE)
	{
		return FALSE;
	}

	// Deleting the record in the document
	m_PersonsArray.DeleteCTypedPtrArrayElement(nIndex);

	m_PersonsArray.RemoveAt(nIndex);

	// Deleting the record in the view
	UpdateAllViews(NULL, UpdateViewsTypeDelete, (CObject*)&nIndex);

	return TRUE;
}

BOOL CPersonsDoc::IsIndexInRange(const INT_PTR nIndex)
{
	if (nIndex < 0 || nIndex > m_PersonsArray.GetCount())
	{
		AfxMessageBox(_T("The index is not in the existing range."));
		return FALSE;
	}

	return TRUE;
}