// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef GnTSet_H
#define GnTSet_H

// This template class implements an unordered set. Because it does not
// set removed elements to 0, it should not be used for smart pointers.
//
// Note that there is an additional template argument, TAlloc.
// This class must declare static functions matching the following prototypes:
//
//      static T* Allocate(gtuint uiNumElements)
//      static void Deallocate(T* pArray)

template <class T, class TAlloc> class GnTSet  : public GnMemoryObject
{
public:
    GnTSet(gtuint uiInitialSize = 0);
    ~GnTSet();

    gtuint GetSize() const;
    T *GetBase() const;
    const T& GetAt(gtuint uiIndex) const;
    T& GetAt(gtuint uiIndex);
    gtuint Add(const T& element);
    gtuint AddUnique(const T& element); // Slow. Use with caution.
    void RemoveAt(gtuint uiIndex);
    void OrderedRemoveAt(gtuint uiIndex); // Preserve order.
    void ReplaceAt(gtuint uiIndex, const T& element);
    void RemoveAll();
    int Find(const T& element) const; // Slow. Use with caution.
    
    // Resize the array to be the number of used items.
    void Realloc();

    // This method clamp the size to being >= m_uiUsed.
    void Realloc(gtuint uiNewSize);

    // This method will reallocate only if the new size is greater than
    // the size already allocated.
    void ReallocNoShrink(gtuint uiNewSize);

    // Get the maximum number of items before a reallocation
    // is forced.
    gtuint GetAllocationSize() const;
protected: 
    T *m_pBase;
    gtuint m_uiAlloced;
    gtuint m_uiUsed;

private:
    // To prevent an application from inadvertently causing the compiler to
    // generate the default copy constructor or default assignment operator,
    // these methods are declared as private. They are not defined anywhere,
    // so code that attempts to use them will not link.
    GnTSet(const GnTSet&);
    GnTSet& operator=(const GnTSet&);
};

template <class T> class GnTObjectSet : public GnTSet<T, GnTNewInterface<T> >
{
public:
    GnTObjectSet(gtuint uiInitialSize = 0);
};

template <class T> class GnTPrimitiveSet :public GnTSet<T, GnTMallocInterface<T> >
{
public:
    GnTPrimitiveSet(gtuint uiInitialSize = 0);
};


typedef GnTPrimitiveSet<gtuint> GnUnsignedIntSet;
typedef GnTPrimitiveSet<unsigned short> GnUnsignedShortSet;
typedef GnTPrimitiveSet<float> GnFloatSet;

template <class T, class TAlloc> inline
	GnTSet<T,TAlloc>::GnTSet(gtuint uiInitialSize)
{
	if (uiInitialSize > 0)
	{
		m_pBase = TAlloc::Allocate(uiInitialSize);
		GnAssert(m_pBase != NULL);
	}
	else
	{
		m_pBase = NULL;
	}
	m_uiAlloced = uiInitialSize;
	m_uiUsed = 0;
}

template <class T, class TAlloc> inline GnTSet<T,TAlloc>::~GnTSet()
{
	TAlloc::Deallocate(m_pBase);
}

template <class T, class TAlloc> inline gtuint GnTSet<T,TAlloc>::GetSize() const
{
	return m_uiUsed;
}

template <class T, class TAlloc> inline gtuint GnTSet<T,TAlloc>::GetAllocationSize() const
{
	return m_uiAlloced;
}

template <class T, class TAlloc> inline T* GnTSet<T,TAlloc>::GetBase() const
{
	return m_pBase;
}

template <class T, class TAlloc> inline const T& GnTSet<T,TAlloc>::GetAt(gtuint uiIndex) const
{
	GnAssert(uiIndex < m_uiUsed);
	return m_pBase[uiIndex];
}

template <class T, class TAlloc> inline T& GnTSet<T,TAlloc>::GetAt(gtuint uiIndex)
{
	GnAssert(uiIndex < m_uiUsed);
	return m_pBase[uiIndex];
}


template <class T, class TAlloc> inline gtuint GnTSet<T,TAlloc>::Add(const T& element)
{
	GnAssert(m_uiUsed <= m_uiAlloced);

	if (m_uiUsed == m_uiAlloced)
	{
		Realloc(m_uiAlloced > 0 ? (2 * m_uiAlloced) : 1);
	}

	GnAssert(m_uiUsed < m_uiAlloced);
	m_pBase[m_uiUsed++] = element;

	return m_uiUsed - 1;
}

template <class T, class TAlloc> inline gtuint GnTSet<T,TAlloc>::AddUnique(const T& element)
{
	GnAssert(m_uiUsed <= m_uiAlloced);

	int iFind = Find(element);
	if (iFind == -1)
	{
		return Add(element);
	}
	else
	{
		return (gtuint) iFind;
	}
}

template <class T, class TAlloc> inline int GnTSet<T,TAlloc>::Find(const T& element) const
{
	GnAssert(m_uiUsed <= m_uiAlloced);

	gtuint i;

	for (i = 0; i < m_uiUsed; i++)
	{
		if (m_pBase[i] == element)
			return i;
	}
	return -1;
}
template <class T, class TAlloc> inline void GnTSet<T,TAlloc>::RemoveAt(gtuint uiIndex)
{
	GnAssert(uiIndex < m_uiUsed);

	m_pBase[uiIndex] = m_pBase[--m_uiUsed];
}

template <class T, class TAlloc> inline void GnTSet<T,TAlloc>::OrderedRemoveAt(gtuint uiIndex)
{
	GnAssert(uiIndex < m_uiUsed);

	for (gtuint ui = uiIndex; ui < m_uiUsed - 1; ui++)
	{
		m_pBase[ui] = m_pBase[ui + 1];
	}
	m_uiUsed--;
}

template <class T, class TAlloc>
inline void GnTSet<T,TAlloc>::ReplaceAt(gtuint uiIndex, const T& element)
{
	if (uiIndex >= m_uiUsed)
	{
		return;
	}

	m_pBase[uiIndex] = element;
}

template <class T, class TAlloc>
inline void GnTSet<T,TAlloc>::RemoveAll()
{
	m_uiUsed = 0;
}

template <class T, class TAlloc>
inline void GnTSet<T,TAlloc>::Realloc()
{
	Realloc(m_uiUsed);
}

template <class T, class TAlloc>
inline void GnTSet<T,TAlloc>::ReallocNoShrink(gtuint uiNewSize)
{
	if (uiNewSize <= m_uiAlloced)
		return;
	Realloc(uiNewSize);
}

template <class T, class TAlloc>
inline void GnTSet<T,TAlloc>::Realloc(gtuint uiNewSize)
{
	if (uiNewSize < m_uiUsed)
		uiNewSize = m_uiUsed;

	if (uiNewSize != m_uiAlloced)
	{
		T *pNewBase;
		gtuint i;

		if (uiNewSize > 0)
		{
			pNewBase = TAlloc::Allocate(uiNewSize);
			GnAssert(pNewBase != NULL);

			for (i = 0; i < m_uiUsed; i++)
			{
				pNewBase[i] = m_pBase[i];
			}
		}
		else
		{
			pNewBase = NULL;
		}

		TAlloc::Deallocate(m_pBase);
		m_pBase = pNewBase;
		m_uiAlloced = uiNewSize;
	}
}

template <class T>
inline GnTObjectSet<T>::GnTObjectSet(gtuint uiInitialSize)
	: GnTSet<T, GnTNewInterface<T> >(uiInitialSize)
{
}

template <class T>
inline GnTPrimitiveSet<T>::GnTPrimitiveSet(gtuint uiInitialSize) 
	: GnTSet<T, GnTMallocInterface<T> >(uiInitialSize)
{
}


#endif // GnTSet_H
