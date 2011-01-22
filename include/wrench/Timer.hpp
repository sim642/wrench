#ifndef WRENCH_TIMER_H
#define WRENCH_TIMER_H

#include <wrench/Config.hpp>

#include <windows.h>

namespace wrench
{
    class Timer
    {
        public:
            Timer() : Active(false)
            {
                StartCount.QuadPart = 0;
            }

            bool Start()
            {
                Active = true;
                return QueryPerformanceCounter(&StartCount);
            }

            bool Stop()
            {
                Active = false;
                return QueryPerformanceCounter(&StopCount);
            }

            bool IsRunning()
            {
                return Active;
            }

            double GetMicroSec()
            {
                LARGE_INTEGER Frequency;
                QueryPerformanceFrequency(&Frequency);

                double StartTime, StopTime;
                StartTime = StartCount.QuadPart * (1000000.0 / Frequency.QuadPart);
                StopTime = StopCount.QuadPart * (1000000.0 / Frequency.QuadPart);

                return StopTime - StartTime;
            }

            double GetMilliSec()
            {
                return GetMicroSec() * 0.001;
            }

            double GetSec()
            {
                return GetMicroSec() * 0.000001;
            }

        private:
            bool Active;
            LARGE_INTEGER StartCount, StopCount;
    };
}

#endif // WRENCH_TIMER_H
