#ifndef WRENCH_JOYSTICK_H
#define WRENCH_JOYSTICK_H

#include <wrench/Config.hpp>

#include <windows.h>
#include <wrench/Math.hpp>

#ifndef WRENCH_NO_LINKWARN
#warning You must link against winmm (libwinmm.a) to be able to use Joystick class
#endif

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

            Joystick()
            {
                SetNum(0);
            }

            Joystick(int NewNum)
            {
                SetNum(NewNum);
            }

            static int Supported()
            {
                return joyGetNumDevs();
            }

            void SetNum(int NewNum)
            {
                Num = NewNum;
                LoadCaps();
            }

            int GetNum()
            {
                return Num;
            }

            bool Available()
            {
                JOYINFO Joy;
                return joyGetPos(Num, &Joy) == JOYERR_NOERROR;
            }


            int Axes()
            {
                return Caps.wNumAxes;
            }

            int MaxAxes()
            {
                return Caps.wMaxAxes;
            }

            bool HasX()
            {
                return true;
            }

            float GetX()
            {
                LoadInfo();
                return wrench::Map<float>(Info.dwXpos, Caps.wXmin, Caps.wXmax, -1.f, 1.f);
            }

            bool HasY()
            {
                return true;
            }

            float GetY()
            {
                LoadInfo();
                return wrench::Map<float>(Info.dwYpos, Caps.wYmin, Caps.wYmax, -1.f, 1.f);
            }

            bool HasZ()
            {
                return Caps.wCaps & JOYCAPS_HASZ;
            }

            float GetZ()
            {
                LoadInfo();
                return wrench::Map<float>(Info.dwZpos, Caps.wZmin, Caps.wZmax, -1.f, 1.f);
            }

            bool HasR()
            {
                return Caps.wCaps & JOYCAPS_HASR;
            }

            float GetR()
            {
                LoadInfo();
                return wrench::Map<float>(Info.dwRpos, Caps.wRmin, Caps.wRmax, -1.f, 1.f);
            }

            bool HasU()
            {
                return Caps.wCaps & JOYCAPS_HASU;
            }

            float GetU()
            {
                LoadInfo();
                return wrench::Map<float>(Info.dwUpos, Caps.wUmin, Caps.wUmax, -1.f, 1.f);
            }

            bool HasV()
            {
                return Caps.wCaps & JOYCAPS_HASV;
            }

            float GetV()
            {
                LoadInfo();
                return wrench::Map<float>(Info.dwVpos, Caps.wVmin, Caps.wVmax, -1.f, 1.f);
            }

            bool HasPOV()
            {
                return Caps.wCaps & JOYCAPS_HASPOV;
            }

            bool HasCTS()
            {
                return Caps.wCaps & JOYCAPS_POVCTS;
            }

            int GetPOV()
            {
                LoadInfo();
                if (Info.dwPOV == JOY_POVCENTERED)
                    return Neutral; // Neutral position
                else
                    return Info.dwPOV / 100; // Values *100
            }

            int Buttons()
            {
                return Caps.wNumButtons;
            }

            int MaxButtons()
            {
                return Caps.wMaxButtons;
            }

            int GetBtns()
            {
                LoadInfo();
                return Info.dwButtons;
            }

            bool GetBtn(int Button)
            {
                return GetBtns() & (1 << Button);
            }
        private:
            int Num;
            JOYCAPS Caps;
            JOYINFOEX Info;

            bool LoadCaps()
            {
                return joyGetDevCaps(Num, &Caps, sizeof(Caps)) == JOYERR_NOERROR;
            }

            bool LoadInfo()
            {
                ZeroMemory(&Info, sizeof(Info));
                Info.dwSize = sizeof(Info);
                Info.dwFlags = JOY_RETURNALL;
                return joyGetPosEx(Num, &Info) == JOYERR_NOERROR;
            }
    };
}

#endif // WRENCH_JOYSTICK_H
