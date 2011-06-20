//������������������������������������������������������������
// Array1D.h
// Make in : 2005. 9. 6
// use : ������ ���ø� Ŭ����ȭ�Ͽ� ������ ��밡��
//������������������������������������������������������������

#ifndef GNARRAY_H
#define GNARRAY_H
#include "GnTAllocatorCollection.h"



template< class TAlloc, class DataType >
class GNSYSTEM_ENTRY GnTArray
{

protected:
	DataType* mpArray;
	gtuint mAllocatedSize; // �迭�� �Ҵ�� �� ũ��
	gtuint mCurrentSize; // �迭�� ���� �Ҵ�� ũ��
	gushort mGrowBy; // �迭�� �� á�� �� �߰��� �Ҵ��� ũ��


public:	

	// �迭 ������� add�� insert�ÿ� Ȯ��� ������ ����
	GnTArray(gtuint uiSize =  0, gushort usGrowBy = 5)  : mpArray(NULL), mAllocatedSize(0),
		mCurrentSize(0), mGrowBy(usGrowBy)
	{
		SetSize(uiSize);
	}

	~GnTArray()
	{
		if( mpArray )
		{
			TAlloc::Deallocate(mpArray);
			mpArray = 0;
		}
	}

	// ���ʿ� ������ �����ϰ� ����� �Ҵ������� �ʾҴٸ� 
	// �̰����� ũ�⸦ �������ش�
	inline void SetSize(gtuint size, gushort usGrowBy = GUSHORT_MAX)
	{	
		if(size)
		{
			if( mpArray )
				TAlloc::Deallocate(mpArray);

			mpArray = TAlloc::Allocate(size);
			for ( gtuint i = 0 ; i < size ; i++ )
			{
				GnT::PointerTraits<DataType>::SetNull(mpArray[i]);
			}
		}
		if( GUSHORT_MAX > usGrowBy )
			mGrowBy = usGrowBy;
		mAllocatedSize = size;
		mCurrentSize = 0;
	}

	DataType& GetAt(gtuint uiIndex)
	{
		GnAssert(uiIndex < mAllocatedSize);
		return mpArray[uiIndex];
	}

	inline void SetAt(gtuint uiIndex, const DataType data)
	{
		GnAssert(uiIndex < mAllocatedSize);
		if (uiIndex >= mCurrentSize)
			mCurrentSize=uiIndex+1;

		mpArray[uiIndex] = data;
	}

	inline void RemoveAll()
	{
		for( gtuint i = 0 ; i < mCurrentSize ; i++ )
			GnT::PointerTraits<DataType>::SetNull(mpArray[i]);
		mCurrentSize = 0;
	}

	inline void Remove(const DataType data)
	{
		for( gtuint i = 0 ; i < mCurrentSize ; i++ )
		{
			if( mpArray[i] == data )
			{
				GnT::PointerTraits<DataType>::SetNull(mpArray[i]);
				if( i == mCurrentSize - 1 )
					--mCurrentSize;				
				return;
			}
		}
	}

	inline void RemoveAt(gtuint uiIndex)
	{
		GnT::PointerTraits<DataType>::SetNull(mpArray[uiIndex]);
		if( uiIndex == mCurrentSize - 1 )
			--mCurrentSize;
	}

	inline void RemoveAndFill(const DataType data)
	{
		for( gtuint i = 0 ; i < mCurrentSize ; i++ )
		{
			if( mpArray[i] == data )
			{
				--mCurrentSize;
				mpArray[i] = mpArray[mCurrentSize];
				GnT::PointerTraits<DataType>::SetNull(mpArray[mCurrentSize]);
				return;
			}
		}
	}

	inline void RemoveAtAndFill(gtuint uiIndex)
	{
		if( uiIndex >= mCurrentSize )
			return;

		--mCurrentSize;
		mpArray[uiIndex] = mpArray[mCurrentSize];
		GnT::PointerTraits<DataType>::SetNull(mpArray[mCurrentSize]);
	}

	void RemoveAtAndFillAll(gtuint uiIndex)
	{
		if( uiIndex >= mCurrentSize )
			return;

		for( gtuint i = uiIndex, fill = uiIndex + 1; fill < mCurrentSize ; i++, fill++ )
		{
			mpArray[i] = mpArray[fill];
		}		
		--mCurrentSize;
		GnT::PointerTraits<DataType>::SetNull(mpArray[mCurrentSize]);
	}

	inline gtuint Add(DataType data)
	{
		return SetAtGrow(mCurrentSize, data);
	}

	inline gtuint SetAtGrow(gtuint uiIndex, DataType data)
	{
		if (uiIndex >= mAllocatedSize)
			Resize(uiIndex + mGrowBy, true);

		SetAt(uiIndex, data);
		return uiIndex;
	}

	void ChangePostion(gtuint uiIndex1, gtuint uiIndex2)
	{
		DataType data1 = GetAt( uiIndex1 );
		DataType data2 = GetAt( uiIndex2 );
		SetAt( uiIndex2, data1 );
		SetAt( uiIndex1, data2 );
	}

	//��������������������������������������������������������������������������������������
	// Description	: ������ ���� �迭�� ũ�⸦ �����Ѵ�.
	// Arguments	: size = ���� ������ �迭�� ũ��	
	void Resize(gtuint size, bool bSave)	
	{
		if( size == 0 )
		{
			if( mAllocatedSize )
			{
				mAllocatedSize = 0;
				mCurrentSize = 0;
				TAlloc::Deallocate(mpArray);
				mpArray	= NULL;				
			}
			return;
		}
		DataType* newarray = TAlloc::Allocate(size);
		if ( newarray == 0)
			return;

		gtuint min = 0;			// ������ �׸��� ����
		if( size < mAllocatedSize )
		{
			min = size;
			mCurrentSize = size;
		}
		else
			min = mAllocatedSize;
		mAllocatedSize = size;

		if( bSave )
		{
			for ( gtuint index = 0; index < min; index++ )
				newarray[index] = mpArray[index];
			for ( gtuint i = mCurrentSize ; i < mAllocatedSize ; i++ )
				GnT::PointerTraits<DataType>::SetNull(newarray[i]);
		}
		else
		{
			for ( gtuint index = 0; index < mAllocatedSize; index++ )
				GnT::PointerTraits<DataType>::SetNull(newarray[index]);
		}

		if( mpArray )
			TAlloc::Deallocate(mpArray);

		mpArray = newarray;
	}


	//��������������������������������������������������������������������������������������
	// Description	:	�迭�� ����� Ȯ���Ѵ�.
	inline gtuint GetSize()	{ return mCurrentSize; }

	inline gtuint GetAllocatedSize() { return mAllocatedSize;}

	DataType& operator[] ( gtuint uiIndex )
	{
		GnAssert(uiIndex < mAllocatedSize);
		return mpArray[uiIndex];
	}

	//��������������������������������������������������������������������������������������
	// Description	:	��ȯ �����ڷμ� � �Լ����� �迭 �����͸� �Ű������� ������ 
	//					�����Ϸ��� Array<�ڷ���>�� �ڷ���*���� ��ȯ�ϰ� ����� ����� �Ѵ�.	
	operator DataType* ()	{ return mpArray; }
};

template<class ArrayType, class DataType>
inline bool GnFindArray(ArrayType* pArray, DataType& findData, DataType& outData)
{
	for( gtuint i = 0 ; i < pArray->GetSize() ; i ++ )
	{
		if( pArray->GetAt( i ) == findData )
		{
			outData = pArray->GetAt();
			return true;
		}
	}
	return false;
}

template<class T>
class GnTObjectArray : public GnTArray<GnTNewInterface<T>, T>
{
public:
	GnTObjectArray(gtuint uiSize =  0, gushort usGrowBy = 5) 
        : GnTArray<GnTNewInterface<T>, T>(uiSize, usGrowBy)
	{}
};

template<class T>
class GnTPrimitiveArray : public GnTArray<GnTMallocInterface<T>, T>
{
public:
	GnTPrimitiveArray(gtuint uiSize =  0, gushort usGrowBy = 5)
        : GnTArray<GnTMallocInterface<T>, T>(uiSize, usGrowBy)
	{}
};


#endif // #ifndef GNARRAY_H