
// CPhoneTypesDoc.h : interface of the CPhoneTypesDoc class
//


#pragma once

#include "PhoneTypesData.h"
#include "CitiesDoc.h"

class CPhoneTypesDoc : public CDocument
{
protected: // create from serialization only
	CPhoneTypesDoc() noexcept;
	DECLARE_DYNCREATE(CPhoneTypesDoc)

	// Attributes
private:
	/// <summary>
	/// array of type PHONE_TYPES
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;

	// Operations
public:
	/// <summary>
	/// A function for getting the needed PhoneTypes array
	/// </summary>
	/// <returns> This function returns a CPhoneTypesArray object </returns>
	const CPhoneTypesArray& GetPhoneTypesArray();

	/// <summary>
	/// A function for modifying certain fields in the PHONE_TYPES table
	/// </summary>
	/// <param name ="nRecordIndex"> The array index where the needed record can be found </param>
	/// <param name ="recPhoneType"> PHONE_TYPES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL UpdateByIndex(const INT_PTR nRecordIndex, PHONE_TYPES& recPhoneType);

	/// <summary>
	/// A function for adding certain fields in the PHONE_TYPES table
	/// </summary>
	/// <param name ="recPhoneType"> PHONE_TYPES struct </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL InsertByIndex(PHONE_TYPES& recPhoneType);

	/// <summary>
	/// A function for deleting certain fields in the PHONE_TYPES table
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
	virtual ~CPhoneTypesDoc();
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