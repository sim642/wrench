#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

namespace sim
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
            LARGE_INTEGER StartCount;
    };
}

#endif // TIMER_H
