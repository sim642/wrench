#include <wrench/Console.hpp>

namespace wrench
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
        SetXY(NewX, GetY());
    }

    int Console::GetX()
    {
        int X, Y;
        GetXY(X, Y);
        return X;
    }

    void Console::SetY(int NewY)
    {
        SetXY(GetX(), NewY);
    }

    int Console::GetY()
    {
        int X, Y;
        GetXY(X, Y);
        return Y;
    }

    void Console::SetBufferSize(int NewWidth, int NewHeight)
    {
        COORD Size = {NewWidth, NewHeight};
        SetConsoleScreenBufferSize(Output, Size);
    }

    void Console::GetBufferSize(int& Width, int& Height)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(Output, &Info);
        Width = Info.dwSize.X;
        Height = Info.dwSize.Y;
    }

    void Console::SetBufferWidth(int NewWidth)
    {
        SetBufferSize(NewWidth, GetBufferHeight());
    }

    int Console::GetBufferWidth()
    {
        int Width, Height;
        GetBufferSize(Width, Height);
        return Width;
    }

    void Console::SetBufferHeight(int NewHeight)
    {
        SetBufferSize(GetBufferWidth(), NewHeight);
    }

    int Console::GetBufferHeight()
    {
        int Width, Height;
        GetBufferSize(Width, Height);
        return Height;
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

    void Console::SetTitle(std::string NewTitle)
    {
        SetConsoleTitle(NewTitle.c_str());
    }

    std::string Console::GetTitle()
    {
        char Title[MAX_PATH];
        GetConsoleTitle(Title, MAX_PATH);
        return std::string(Title);
    }
}
