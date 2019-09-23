
// CCitiesView.h : interface of the CCitiesView class
//

#pragma once

#include "CitiesDoc.h"

enum DialogModes
{
	DialogModeInsert,
	DialogModeUpdate,
	DialogModeRead
};

class CCitiesView : public CListView
{
protected: // create from serialization only
	CCitiesView() noexcept;
	DECLARE_DYNCREATE(CCitiesView)
	virtual ~CCitiesView();

// Attributes
public:
	CCitiesDoc* GetDocument() const;
	
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
	/// A function for inserting an element from the View
	/// </summary>
	void Insert();

	/// <summary>
	/// A function for looking at an element from the View
	/// </summary>
	void Read();

private:
	/// <summary>
	/// A function for modifying the View
	/// </summary>
	/// <param name ="lHint"> Modification type </param>
	/// <param name ="nElementIndex"> Element index </param>
	void ModifyViewList(LPARAM lHint, INT_PTR nElementIndex);

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
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CCitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif

