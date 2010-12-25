#ifndef WRENCH_TIMER_H
#define WRENCH_TIMER_H

#include <windows.h>

namespace wrench
{
    class Timer
    {
        public:
            Timer();

            bool Start();
            bool Stop();
            bool IsRunning();

            double GetMicroSec();
            double GetMilliSec();
            double GetSec();

        private:
            bool Active;
            LARGE_INTEGER StartCount, StopCount;
    };
}

#endif // WRENCH_TIMER_H
