#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

namespace sim
{
    class Timer
    {
        public:
            Timer() : Active(false)
            {
                StartCount.QuadPart = 0;
            }

            ~Timer()
            {
                //dtor
            }

            void Start()
            {
                Active = true;
                QueryPerformanceCounter(&StartCount);
            }

            void Stop()
            {
                Active = false;
            }

            bool Running()
            {
                return Active;
            }

            double GetMicroSec()
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
            LARGE_INTEGER StartCount;
    };
}

#endif // TIMER_H
