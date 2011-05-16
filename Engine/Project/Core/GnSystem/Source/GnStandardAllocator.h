#ifndef GNSTANDARDALLOCATOR_H
#define GNSTANDARDALLOCATOR_H
#include "GnAllocator.h"

class GNSYSTEM_ENTRY GnStandardAllocator : public GnAllocator
{
public:
	
	virtual void* Allocate(gsize& stSizeInBytes, gsize& stAlignment,
		GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate);

	virtual void* Reallocate(void* pvMemory, gsize& stSizeInBytes,
		gsize& stAlignment, GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate,
		gsize stSizeCurrent);

	virtual void Deallocate(void* pvMemory, GnMemoryEventType eEventType, 
		gsize stSizeInBytes);

	// Called by the memory manager during GnInit()
	virtual void Initialize();
	// Called by the memory manager during GnShutdown()
	virtual void Shutdown();

#ifdef GN_MEMORY_DEBUGGER
	GNFORCEINLINE virtual void* Allocate(gsize& stSizeInBytes, gsize& stAlignment,
		GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate,
		const gchar* pcFile, int iLine, const gchar* pcFunction);

	GNFORCEINLINE virtual void* Reallocate(void* pvMemory, gsize& stSizeInBytes,
		gsize& stAlignment, GnMemoryEventType eEventType, 
		bool bProvideAccurateSizeOnDeallocate, gsize stSizeCurrent,
		const gchar* pcFile, int iLine, const gchar* pcFunction);


	GNFORCEINLINE virtual bool TrackAllocate(const void* const pvMemory, gsize stSizeInBytes, 
		GnMemoryEventType eEventType, const gchar* pcFile, int iLine, const gchar* pcFunction);
	GNFORCEINLINE virtual bool TrackDeallocate(const void* const pvMemory,
		GnMemoryEventType eEventType);
	GNFORCEINLINE virtual bool SetMarker(const char* pcMarkerType, const char* pcClassifier,
		const char* pcString);
	GNFORCEINLINE virtual bool VerifyAddress(const void* pvMemory);

#endif // #ifdef GN_MEMORY_DEBUGGER

};

#ifdef GN_MEMORY_DEBUGGER
GNFORCEINLINE void* GnStandardAllocator::Allocate(gsize& stSizeInBytes, gsize& stAlignment,
	GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate,
	const gchar* pcFile, int iLine, const gchar* pcFunction)
{
	return Allocate(stSizeInBytes, stAlignment, eEventType, bProvideAccurateSizeOnDeallocate);
}

GNFORCEINLINE void* GnStandardAllocator::Reallocate(void* pvMemory, gsize& stSizeInBytes,
	gsize& stAlignment, GnMemoryEventType eEventType, bool bProvideAccurateSizeOnDeallocate,
	gsize stSizeCurrent, const gchar* pcFile, int iLine, const gchar* pcFunction)
{
	return Reallocate(pvMemory, stSizeInBytes, stAlignment, eEventType,
		bProvideAccurateSizeOnDeallocate, stSizeCurrent);
}

GNFORCEINLINE bool GnStandardAllocator::TrackAllocate(const void* const pvMemory, gsize stSizeInBytes,
	GnMemoryEventType eEventType, const gchar* pcFile, int iLine, const gchar* pcFunction)
{
	return true;
}

GNFORCEINLINE bool GnStandardAllocator::TrackDeallocate(const void* const pvMemory, GnMemoryEventType eEventType)
{
	return true;
}

GNFORCEINLINE bool GnStandardAllocator::SetMarker(const char* pcMarkerType, const char* pcClassifier,
	const char* pcString)
{
	return true;
}

GNFORCEINLINE bool GnStandardAllocator::VerifyAddress(const void* pvMemory)
{
	return false;
}
#endif // #ifdef GN_MEMORY_DEBUGGER

#endif // GNSTANDARDALLOCATOR_H
