#include "Timer.h"

Timer::Timer()
{




}

Timer::~Timer()
{



}

float Timer::GetDeltaTime()
{
    static float t_DeltaTime = 0.0f;
    static ULONG t_TimeStart = 0.0f;
    ULONG t_TimeCurrent = GetTickCount64();

    if (t_TimeStart == 0) { t_TimeStart = t_TimeCurrent; }

    t_DeltaTime = (t_TimeCurrent - t_TimeStart) / 1000.0f;
    t_TimeStart = t_TimeCurrent;

    static float t_CummulativeTime = 0;
    t_CummulativeTime += t_DeltaTime;

    if (t_CummulativeTime >= FPS_60)
    {
        t_CummulativeTime -= FPS_60;
    }
    else
    {
        return 0;
    }

    return t_DeltaTime;
}
