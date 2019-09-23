// CPersonsView.h : interface of the CPersonsView class
//

#pragma once

#include "PersonsDoc.h"
#include "CitiesView.h"

typedef CMap<long, long, CITIES*, CITIES*> CCitiesMap;
typedef CMap<long, long, PHONE_TYPES*, PHONE_TYPES*> CPhoneTypesMap;

class CPersonsView : public CListView
{
protected: // create from serialization only
	CPersonsView() noexcept;
	DECLARE_DYNCREATE(CPersonsView)
	virtual ~CPersonsView();

	// Attributes
public:
	CPersonsDoc* GetDocument() const;

private:
	/// <summary>
	/// Map: the key is the unique identifier of the CITIES and is mapped to the whole CITIES objectò
	/// </summary>
	CCitiesMap m_oCitiesNamesMap;

	/// <summary>
	/// Map: the key is the unique identifier of the PHONE_TYPES and is mapped to the whole PHONE_TYPES object
	/// </summary>
	CPhoneTypesMap m_oPhoneTypesMap;

	// Operations
public:
	/// <summary>
	/// A function for deleting an element from the View
	/// </summary>
	void Delete();

	/// <summary>
	/// A function for modifying an element from the View
	/// </summary>
	void Update();

	/// <summary>
	/// A function for adding an element from the View
	/// </summary>
	void Insert();

	/// <summary>
	/// A function for reading an element from the View
	/// </summary>
	void Read();

private:
	/// <summary>
	/// A function for modifying the View
	/// </summary>
	/// <param name ="lHint"> Modification type </param>
	/// <param name ="nElementIndex"> Element index </param>
	void ModifyViewList(LPARAM lHint, INT_PTR nElementIndex);

	/// <summary>
	/// A function for getting the m_oCitiesNamesMap map
	/// </summary>
	/// <returns> The function returns CMap object </returns>
	CCitiesMap& GetCitiesNamesMap();

	/// <summary>
	/// A function for getting the m_oPhoneTypesMap map
	/// </summary>
	/// <returns> The function returns CMap object </returns>
	CPhoneTypesMap& GetPhoneTypesMap();

	// Overrides
public:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CPersonsView.cpp
inline CPersonsDoc* CPersonsView::GetDocument() const
{
	return reinterpret_cast<CPersonsDoc*>(m_pDocument);
}
#endif


