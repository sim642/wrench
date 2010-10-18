#include "Timer.hpp"

namespace sim
{
    Timer::Timer() : Active(false)
    {
        StartCount.QuadPart = 0;
    }

    Timer::~Timer()
    {
        //dtor
    }

    void Timer::Start()
    {
        Active = true;
        QueryPerformanceCounter(&StartCount);
    }

    void Timer::Stop()
    {
        Active = false;
    }

    bool Timer::Running()
    {
        return Active;
    }

    double Timer::GetMicroSec()
    {
        LARGE_INTEGER StopCount;
        QueryPerformanceCounter(&StopCount);

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
