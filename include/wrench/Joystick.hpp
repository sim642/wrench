#ifndef WRENCH_JOYSTICK_H
#define WRENCH_JOYSTICK_H

#include <windows.h>
#include <wrench/Math.hpp>

#warning You must link against winmm (libwinmm.a) to be able to use Joystick class

namespace wrench
{
    class Joystick
    {
        public:
            enum POV
            {
                Neutral = -1,
                Top = 0,
                Right = 90,
                Bottom = 180,
                Left = 270
            };

            Joystick();
            Joystick(int);

            static int Supported();

            void SetNum(int);
            int GetNum();

            bool Available();


            int Axes();
            int MaxAxes();
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

            bool HasPOV();
            bool HasCTS();
            int GetPOV();

            int Buttons();
            int MaxButtons();
            int GetBtns();
            bool GetBtn(int);
        private:
            int Num;
            JOYCAPS Caps;
            JOYINFOEX Info;

            bool LoadCaps();
            bool LoadInfo();
    };
}

#endif // WRENCH_JOYSTICK_H
