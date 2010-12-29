#ifndef WRENCH_JOYSTICK_H
#define WRENCH_JOYSTICK_H

#include <windows.h>
#include <wrench/Math.hpp>

namespace wrench
{
    class Joystick
    {
        public:
            Joystick();
            Joystick(int);

            static int Supported();

            void SetNum(int);
            int GetNum();

            bool Available();

            bool HasX();
            float GetX();

            bool HasY();
            float GetY();

            bool HasZ();
            float GetZ();

            bool HasR();
            float GetR();

            bool HasU();
            float GetU();

            bool HasV();
            float GetV();
        private:
            int Num;
            JOYCAPS Caps;
            JOYINFOEX Info;

            bool LoadCaps();
            bool LoadInfo();
    };
}

#endif // WRENCH_JOYSTICK_H
