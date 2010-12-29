#include <wrench/Joystick.hpp>

namespace wrench
{
    Joystick::Joystick()
    {
        SetNum(0);
    }

    Joystick::Joystick(int NewNum)
    {
        SetNum(NewNum);
    }

    int Joystick::Supported()
    {
        return joyGetNumDevs();
    }

    void Joystick::SetNum(int NewNum)
    {
        Num = NewNum;
        LoadCaps();
    }

    int Joystick::GetNum()
    {
        return Num;
    }

    bool Joystick::Available()
    {
        JOYINFO Joy;
        return joyGetPos(Num, &Joy) == JOYERR_NOERROR;
    }

    bool Joystick::HasX()
    {
        return true;
    }

    float Joystick::GetX()
    {
        LoadInfo();
        return wrench::Map(Info.dwXpos, Caps.wXmin, Caps.wXmax, -1.f, 1.f);
    }

    bool Joystick::HasY()
    {
        return true;
    }

    float Joystick::GetY()
    {
        LoadInfo();
        return wrench::Map(Info.dwYpos, Caps.wYmin, Caps.wYmax, -1.f, 1.f);
    }

    bool Joystick::HasZ()
    {
        return Caps.wCaps & JOYCAPS_HASZ;
    }

    float Joystick::GetZ()
    {
        LoadInfo();
        return wrench::Map(Info.dwZpos, Caps.wZmin, Caps.wZmax, -1.f, 1.f);
    }

    bool Joystick::HasR()
    {
        return Caps.wCaps & JOYCAPS_HASR;
    }

    float Joystick::GetR()
    {
        LoadInfo();
        return wrench::Map(Info.dwRpos, Caps.wRmin, Caps.wRmax, -1.f, 1.f);
    }

    bool Joystick::HasU()
    {
        return Caps.wCaps & JOYCAPS_HASU;
    }

    float Joystick::GetU()
    {
        LoadInfo();
        return wrench::Map(Info.dwUpos, Caps.wUmin, Caps.wUmax, -1.f, 1.f);
    }

    bool Joystick::HasV()
    {
        return Caps.wCaps & JOYCAPS_HASV;
    }

    float Joystick::GetV()
    {
        LoadInfo();
        return wrench::Map(Info.dwVpos, Caps.wVmin, Caps.wVmax, -1.f, 1.f);
    }

    bool Joystick::LoadCaps()
    {
        return joyGetDevCaps(Num, &Caps, sizeof(Caps)) == JOYERR_NOERROR;
    }

    bool Joystick::LoadInfo()
    {
        ZeroMemory(&Info, sizeof(Info));
        Info.dwSize = sizeof(Info);
        Info.dwFlags = JOY_RETURNALL;
        return joyGetPosEx(Num, &Info) == JOYERR_NOERROR;
    }
}
