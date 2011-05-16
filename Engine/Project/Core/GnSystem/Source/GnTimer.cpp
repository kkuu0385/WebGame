#include "GnSystemPCH.h"
#include "GnTimer.h"

#ifdef WIN32

#else // #ifdef WIN32
#include <sys/time.h>
#endif // #ifdef WIN32

#ifdef WIN32
float GnGetTicks()
{
    // SetThreadAffinityMask 시간 보정에 관해서 
    // 여러개의 쓰레드에서 사용을 하게 되면 이상한 값이 들어 올 수 있단다.. 나중에 확인해 보자
    // 하긴 cpu마다 틱 돌아간게 다를 수도 있으니...
    static bool bFirst = true;
    static LARGE_INTEGER freq;
	static LARGE_INTEGER initial;
    
	if (bFirst)
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&initial);
		bFirst = false;
	}
    
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
    
    now.QuadPart -= initial.QuadPart;
    float tick = (float)((float)now.QuadPart / (float)freq.QuadPart);
	return tick;
}
#elif TARGET_OS_IPHONE // #ifdef WIN32
float GnGetTicks()
{
    static bool bFirst = true;
    static struct timeval start;
    
    if (bFirst)
    {
        gettimeofday(&start, NULL);
        bFirst = false;
    }
    
	struct timeval now;
	gettimeofday(&now, NULL);
    
    __darwin_time_t second = now.tv_sec-start.tv_sec;
    float micro = (float)((float)((float)now.tv_usec-(float)start.tv_usec) / 1000.0f);
    float tick = second + micro;
    return tick;
}
#else // #ifdef WIN32
float GnGetTicks()
{
    static bool bFirst = true;
    static struct timespec start;
    
    if (bFirst)
    {
        clock_gettime(CLOCK_MONOTONIC,&start); 
        bFirst = false;
    }
  
    struct timeval now;
    clock_gettime(CLOCK_MONOTONIC,&now);
  
    __darwin_time_t second = (now.tv_sec-start.tv_sec);
	float micro = (float)((float)now.tv_nsec-(float)start.tv_nsec) / 1000000.0f;
	float tick = second + micro;
    return tick;
}                      
#endif // #ifdef WIN32


GnTimer::GnTimer()
{
    Reset();
}

void GnTimer::Reset()
{
    mDeltaTime = 0.0f;
    mLastTime = 0.0f;
}

bool GnTimer::Update(float sec)
{
    mDeltaTime = sec - mLastTime;
    mLastTime = sec;
    
    return true;
}

inline bool GnTimer::Update()
{
    return Update(GnGetTicks());
}

inline float GnTimer::getDelta()
{
    return mDeltaTime;
}
