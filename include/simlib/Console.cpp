#include "Console.hpp"

namespace sim
{
    Console::Console()
    {
        Output = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    Console::Console(HANDLE NewOutput)
    {
        Output = NewOutput;
    }

    void Console::SetHandleOutput(HANDLE NewOutput)
    {
        Output = NewOutput;
    }

    HANDLE Console::GetHandleOutput()
    {
        return Output;
    }

    void Console::SetXY(int NewX, int NewY)
    {
        COORD Pos = {NewX, NewY};
        SetConsoleCursorPosition(Output, Pos);
    }

    void Console::GetXY(int& X, int& Y)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(Output, &Info);
        X = Info.dwCursorPosition.X;
        Y = Info.dwCursorPosition.Y;
    }

    void Console::SetX(int NewX)
    {
        int X, Y;
        GetXY(X, Y);
        SetXY(NewX, Y);
    }

    int Console::GetX()
    {
        int X, Y;
        GetXY(X, Y);
        return X;
    }

    void Console::SetY(int NewY)
    {
        int X, Y;
        GetXY(X, Y);
        SetXY(X, NewY);
    }

    int Console::GetY()
    {
        int X, Y;
        GetXY(X, Y);
        return Y;
    }

    void Console::SetColor(int NewFore, int NewBack)
    {
        SetConsoleTextAttribute(Output, NewFore | NewBack << 4);
    }

    void Console::GetColor(int& Fore, int& Back)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(Output, &Info);
        Fore = Info.wAttributes & 15;
        Back = (Info.wAttributes >> 4) & 15;
    }

    void Console::SetForeColor(int NewFore)
    {
        int Fore, Back;
        GetColor(Fore, Back);
        SetColor(NewFore, Back);
    }

    int Console::GetForeColor()
    {
        int Fore, Back;
        GetColor(Fore, Back);
        return Fore;
    }

    void Console::SetBackColor(int NewBack)
    {
        int Fore, Back;
        GetColor(Fore, Back);
        SetColor(Fore, NewBack);
    }

    int Console::GetBackColor()
    {
        int Fore, Back;
        GetColor(Fore, Back);
        return Back;
    }

    void Console::ClearChar(char NewChar, bool Reset)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        COORD Pos = {0, 0};
        DWORD Count;
        GetConsoleScreenBufferInfo(Output, &Info);
        FillConsoleOutputCharacter(Output, NewChar, Info.dwSize.X*Info.dwSize.Y, Pos, &Count);
        if (Reset)
            SetXY(0, 0);
    }

    void Console::ClearColor(int NewFore, int NewBack, bool Reset, bool SwapColor)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        COORD Pos = {0, 0};
        DWORD Count;
        GetConsoleScreenBufferInfo(Output, &Info);
        FillConsoleOutputAttribute(Output, NewFore | NewBack << 4, Info.dwSize.X*Info.dwSize.Y, Pos, &Count);
        if (Reset)
            SetXY(0, 0);
        if (SwapColor)
            SetColor(NewFore, NewBack);
    }

    void Console::Clear(bool Reset)
    {
        ClearChar();
        ClearColor();
        if (Reset)
            SetXY(0, 0);
    }

    void Console::SetCursor(int NewPercent)
    {
        CONSOLE_CURSOR_INFO Info;
        if (NewPercent > 0)
        {
            if (NewPercent <= 100)
            {
                Info.dwSize = NewPercent;
            }
            else
            {
                Info.dwSize = 100;
            }
            Info.bVisible = TRUE;
        }
        else
        {
            Info.dwSize = 1;
            Info.bVisible = FALSE;
        }
        SetConsoleCursorInfo(Output, &Info);
    }

    int Console::GetCursor()
    {
        CONSOLE_CURSOR_INFO Info;
        GetConsoleCursorInfo(Output, &Info);
        return (Info.bVisible == TRUE ? Info.dwSize : 0);
    }
}
