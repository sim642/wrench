#include <wrench/Timer.hpp>

namespace wrench
{
    Timer::Timer() : Active(false)
    {
        StartCount.QuadPart = 0;
    }

    Timer::~Timer()
    {
        //dtor
    }

    bool Timer::Start()
    {
        Active = true;
        return QueryPerformanceCounter(&StartCount);
    }

    bool Timer::Stop()
    {
        Active = false;
        return QueryPerformanceCounter(&StopCount);
    }

    bool Timer::IsRunning()
    {
        return Active;
    }

    double Timer::GetMicroSec()
    {
        LARGE_INTEGER Frequency;
        QueryPerformanceFrequency(&Frequency);

        double StartTime, StopTime;
        StartTime = StartCount.QuadPart * (1000000.0 / Frequency.QuadPart);
        StopTime = StopCount.QuadPart * (1000000.0 / Frequency.QuadPart);

        return StopTime - StartTime;
    }

    double Timer::GetMilliSec()
    {
        return GetMicroSec() * 0.001;
    }

    double Timer::GetSec()
    {
        return GetMicroSec() * 0.000001;
    }
}
