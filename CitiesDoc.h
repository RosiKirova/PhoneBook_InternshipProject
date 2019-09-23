// CCitiesDoc.h : interface of the CCitiesDoc class
//

#pragma once

#include "CitiesData.h"

enum UpdateViewsTypes
{
	UpdateViewsTypeInsert = 1,
	UpdateViewsTypeUpdate,
	UpdateViewsTypeDelete
};

class CCitiesDoc : public CDocument
{
protected: // create from serialization only
	CCitiesDoc() noexcept;
	DECLARE_DYNCREATE(CCitiesDoc)

// Attributes
private:
	/// <summary>
	/// CITIES array
	/// </summary>
	CCitiesArray m_oCitiesArray;

// Operations
public:
	/// <summary>
	/// A function for getting the needed CITIES array
	/// </summary>
	/// <returns> The function returns a CCitiesArray object </returns>
	const CCitiesArray& GetCitiesArray();

	/// <summary>
	/// A function for modifying certain fields in the CITIES table
	/// </summary>
	/// <param name ="nRecordIndex"> The array index where the needed record can be found </param>
	/// <param name ="recCity"> CITIES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL UpdateByIndex(const INT_PTR nRecordIndex, CITIES& recCity);

	/// <summary>
	/// A function for inserting a record in the CITIES table
	/// </summary>
	/// <param name ="recCity"> CITIES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL InsertByIndex(CITIES& recCity);

	/// <summary>
	///  A function for deleting certain fields in the CITIES table
	/// </summary>
	/// <param name ="nRecordIndex"> The array index where the needed record can be found </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL DeleteByIndex(const INT_PTR nRecordIndex);

private:
	/// <summary>
	/// A function which checks whether the given index is in the existing range of the document
	/// </summary>
	/// <param name ="nIndex"> The index </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL IsIndexInRange(const INT_PTR nIndex);


// Overrides
public:
	/// <summary>
	/// A function for creating a new document and loading data in
	/// </summary>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	virtual BOOL OnNewDocument();

	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CCitiesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
