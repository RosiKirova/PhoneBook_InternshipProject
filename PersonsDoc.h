
// CPersonsDoc.h : interface of the CPersonsDoc class
//


#pragma once

#include "PersonsData.h"
#include "CitiesDoc.h"

class CPersonsDoc : public CDocument
{
protected: // create from serialization only
	CPersonsDoc() noexcept;
	DECLARE_DYNCREATE(CPersonsDoc)

	// Attributes
private:
	/// <summary>
	/// array of type PERSONS
	/// </summary>
	CPersonsArray m_PersonsArray;

	/// <summary>
	/// array of type CITIES
	/// </summary>
	CCitiesArray m_oCitiesArray;

	/// <summary>
	/// array of type PHONE_TYPES
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;

	// Operations
public:
	/// <summary>
	/// A function for getting the oPersonsArray
	/// </summary>
	/// <returns> The function returns a CPersonsArray object </returns>
	const CPersonsArray& GetPersonsArray();

	/// <summary>
	/// A function for getting the oCitiesArray
	/// </summary>
	/// <returns> The function returns a CCitiesArray object </returns>
	const CCitiesArray& GetCitiesArray();

	/// <summary>
	/// A function for getting the oPhoneTypesArray
	/// </summary>
	/// <returns> The function returns a CPhoneTypesArray object </returns>
	const CPhoneTypesArray& GetPhoneTypesArray();

	/// <summary>
	/// A function for selecting person's details by index
	/// </summary>
	/// <param name ="nIndex"> The array index where the needed record can be found </param>
	/// <param name ="oPersonDetails"> Object containing the person details </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL SelectByIndex(const INT_PTR nIndex, CPersonDetails& oPersonDetails);

	/// <summary>
	/// A function for modifying person's details by index
	/// </summary>
	/// <param name ="nIndex"> The array index where the needed record can be found </param>
	/// <param name ="oPersonDetails"> Object containing the person details </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL UpdateByIndex(const INT_PTR nIndex, CPersonDetails& oPersonDetails);

	/// <summary>
	/// A function for adding person's details
	/// </summary>
	/// <param name ="îPersonDetails"> Object containing the person details </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL InsertByIndex(CPersonDetails& oPersonDetails);

	/// <summary>
	/// A function for deleting person's details by index
	/// </summary>
	/// <param name ="nRecordIndex"> The array index where the needed record can be found </param>
	/// <returns> The function returns TRUE if succeeded and FALSE if failed </returns>
	BOOL DeleteByIndex(const INT_PTR nIndex);

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
	virtual ~CPersonsDoc();
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
