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

    /** Handles */
    void Console::SetHandleOutput(HANDLE NewOutput)
    {
        Output = NewOutput;
    }

    HANDLE Console::GetHandleOutput()
    {
        return Output;
    }

    /** Cursor */
    bool Console::SetXY(int NewX, int NewY)
    {
        COORD Pos = {NewX, NewY};
        return SetConsoleCursorPosition(Output, Pos);
    }

    void Console::GetXY(int& X, int& Y)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(Output, &Info);
        X = Info.dwCursorPosition.X;
        Y = Info.dwCursorPosition.Y;
    }

    bool Console::SetX(int NewX)
    {
        return SetXY(NewX, GetY());
    }

    int Console::GetX()
    {
        int X, Y;
        GetXY(X, Y);
        return X;
    }

    bool Console::SetY(int NewY)
    {
        return SetXY(GetX(), NewY);
    }

    int Console::GetY()
    {
        int X, Y;
        GetXY(X, Y);
        return Y;
    }

    bool Console::SetCursor(int NewPercent)
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
        return SetConsoleCursorInfo(Output, &Info);
    }

    int Console::GetCursor()
    {
        CONSOLE_CURSOR_INFO Info;
        GetConsoleCursorInfo(Output, &Info);
        return (Info.bVisible == TRUE ? Info.dwSize : 0);
    }

    /** Buffer size */
    bool Console::SetBufferSize(int NewWidth, int NewHeight)
    {
        COORD Size = {NewWidth, NewHeight};
        return SetConsoleScreenBufferSize(Output, Size);
    }

    void Console::GetBufferSize(int& Width, int& Height)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(Output, &Info);
        Width = Info.dwSize.X;
        Height = Info.dwSize.Y;
    }

    bool Console::SetBufferWidth(int NewWidth)
    {
        return SetBufferSize(NewWidth, GetBufferHeight());
    }

    int Console::GetBufferWidth()
    {
        int Width, Height;
        GetBufferSize(Width, Height);
        return Width;
    }

    bool Console::SetBufferHeight(int NewHeight)
    {
        return SetBufferSize(GetBufferWidth(), NewHeight);
    }

    int Console::GetBufferHeight()
    {
        int Width, Height;
        GetBufferSize(Width, Height);
        return Height;
    }

    /** Window size */
    bool Console::SetWindowSize(int NewWidth, int NewHeight)
    {
        SMALL_RECT Size = {0, 0, NewWidth - 1, NewHeight - 1};
        return SetConsoleWindowInfo(Output, TRUE, &Size);
    }

    void Console::GetWindowSize(int& Width, int& Height)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(Output, &Info);
        Width = Info.srWindow.Right;
        Height = Info.srWindow.Bottom;
    }

    bool Console::SetWindowWidth(int NewWidth)
    {
        return SetWindowSize(NewWidth, GetWindowHeight());
    }

    int Console::GetWindowWidth()
    {
        int Width, Height;
        GetWindowSize(Width, Height);
        return Width;
    }

    bool Console::SetWindowHeight(int NewHeight)
    {
        return SetWindowSize(GetWindowWidth(), NewHeight);
    }

    int Console::GetWindowHeight()
    {
        int Width, Height;
        GetWindowSize(Width, Height);
        return Height;
    }

    /** Color */
    bool Console::SetColor(int NewFore, int NewBack)
    {
        return SetConsoleTextAttribute(Output, NewFore | NewBack << 4);
    }

    void Console::GetColor(int& Fore, int& Back)
    {
        CONSOLE_SCREEN_BUFFER_INFO Info;
        GetConsoleScreenBufferInfo(Output, &Info);
        Fore = Info.wAttributes & 0xF;
        Back = (Info.wAttributes >> 4) & 0xF;
    }

    bool Console::SetForeColor(int NewFore)
    {
        return SetColor(NewFore, GetBackColor());
    }

    int Console::GetForeColor()
    {
        int Fore, Back;
        GetColor(Fore, Back);
        return Fore;
    }

    bool Console::SetBackColor(int NewBack)
    {
        return SetColor(GetForeColor(), NewBack);
    }

    int Console::GetBackColor()
    {
        int Fore, Back;
        GetColor(Fore, Back);
        return Back;
    }

    /** Clear */
    bool Console::ClearChar(char NewChar, bool Reset)
    {
        bool Return = true;
        CONSOLE_SCREEN_BUFFER_INFO Info;
        COORD Pos = {0, 0};
        DWORD Count;
        GetConsoleScreenBufferInfo(Output, &Info);
        Return &= FillConsoleOutputCharacter(Output, NewChar, Info.dwSize.X * Info.dwSize.Y, Pos, &Count);
        if (Reset)
            Return &= SetXY(0, 0);
        return Return;
    }

    bool Console::ClearColor(int NewFore, int NewBack, bool Reset, bool SwapColor)
    {
        bool Return = true;
        CONSOLE_SCREEN_BUFFER_INFO Info;
        COORD Pos = {0, 0};
        DWORD Count;
        GetConsoleScreenBufferInfo(Output, &Info);
        Return &= FillConsoleOutputAttribute(Output, NewFore | NewBack << 4, Info.dwSize.X * Info.dwSize.Y, Pos, &Count);
        if (Reset)
            Return &= SetXY(0, 0);
        if (SwapColor)
            Return &= SetColor(NewFore, NewBack);
        return Return;
    }

    bool Console::Clear(bool Reset)
    {
        bool Return = true;
        Return &= ClearChar();
        Return &= ClearColor();
        if (Reset)
            Return &= SetXY(0, 0);
        return Return;
    }

    /** Title */
    bool Console::SetTitle(std::string NewTitle)
    {
        return SetConsoleTitle(NewTitle.c_str());
    }

    std::string Console::GetTitle()
    {
        char Title[MAX_PATH];
        GetConsoleTitle(Title, MAX_PATH);
        return std::string(Title);
    }
}
