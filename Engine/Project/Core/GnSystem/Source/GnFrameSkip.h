class GNSYSTEM_ENTRY GnFrameSkip : public GnMemoryObject
{
public:
    GnFrameSkip(float fps);
    
    void Reset(float fps);
    
    void SetFramePerSec(float fps);
    
	
    bool Update(float sec);
    
    // 프레임을 스킵할것인지 여부//
    inline bool IsFrameSkip();
    
private:
    // 원하는 프레임 초//
	float mSecPerFrame;

    // 누적되는 시간//
	float mSkipTimer;
};

inline bool GnFrameSkip::IsFrameSkip()
{
    return (bool)(mSkipTimer >= 0);
}