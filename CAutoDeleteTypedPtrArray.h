#pragma once
#include <afxtempl.h>

/// <summary>
/// Template class for work with CTypedPtrArray
///</summary>
template<class BaseArray, class TYPE>
class CAutoDeleteTypedPtrArray : public CTypedPtrArray<BaseArray, TYPE>
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	/// <summary>
	/// Constructor
	/// </summary>
	CAutoDeleteTypedPtrArray()
	{
	}
	
	/// <summary>
	/// Destructor which frees memory
	/// </summary>
	virtual ~CAutoDeleteTypedPtrArray()
	{
		DeleteCTypedPtrArray();
	}


	// Methods
	// ----------------
private:
	void DeleteCTypedPtrArray()
	{
		for (INT_PTR nIndex = GetCount() - 1; nIndex >= 0; nIndex--)
		{
			TYPE pType = GetAt(nIndex);
			delete pType;
			pType = NULL;
		}

		RemoveAll();
	}

public:
	void DeleteCTypedPtrArrayElement(const INT_PTR nIndex)
	{
		
		TYPE pType = GetAt(nIndex);
		delete pType;
		pType = NULL;
	}

	// Overrides
	// ----------------


	// Members
	// ----------------
};
