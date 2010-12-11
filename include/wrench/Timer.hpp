#ifndef WRENCH_TIMER_H
#define WRENCH_TIMER_H

#include <windows.h>

namespace wrench
{
    class Timer
    {
        public:
            Timer();
            ~Timer();

            void Start();
            void Stop();
            bool Running();

            double GetMicroSec();
            double GetMilliSec();
            double GetSec();

        private:
            bool Active;
            LARGE_INTEGER StartCount, StopCount;
    };
}

#endif // WRENCH_TIMER_H
