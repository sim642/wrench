#ifndef SIMLIB_CONSOLE_H
#define SIMLIB_CONSOLE_H

#include <windows.h>

namespace sim
{
    class Console
    {
        public:
            enum Color {Black, Blue, Green, Aqua, Red, Purple, Yellow, White,
                          LightBlack, LightBlue, LightGreen, LightAqua, LightRed,
                          LightPurple, LightYellow, LightWhite,
                          Grey = 8, BrightWhite = 15};
            enum Cursor {Hidden, Default = 25, Full = 100};
        private:
            HANDLE Output;
        public:
            Console()
            {
                Output = GetStdHandle(STD_OUTPUT_HANDLE);
            }

            Console(HANDLE NewOutput)
            {
                Output = NewOutput;
            }

            void SetHandleOutput(HANDLE NewOutput)
            {
                Output = NewOutput;
            }

            HANDLE GetHandleOutput()
            {
                return Output;
            }

            void SetXY(int NewX = 0, int NewY = 0)
            {
                COORD Pos = {NewX, NewY};
                SetConsoleCursorPosition(Output, Pos);
            }

            void GetXY(int& X, int& Y)
            {
                CONSOLE_SCREEN_BUFFER_INFO Info;
                GetConsoleScreenBufferInfo(Output, &Info);
                X = Info.dwCursorPosition.X;
                Y = Info.dwCursorPosition.Y;
            }

            void SetX(int NewX = 0)
            {
                int X, Y;
                GetXY(X, Y);
                SetXY(NewX, Y);
            }

            int GetX()
            {
                int X, Y;
                GetXY(X, Y);
                return X;
            }

            void SetY(int NewY = 0)
            {
                int X, Y;
                GetXY(X, Y);
                SetXY(X, NewY);
            }

            int GetY()
            {
                int X, Y;
                GetXY(X, Y);
                return Y;
            }

            void SetColor(int NewFore = White, int NewBack = Black)
            {
                SetConsoleTextAttribute(Output, NewFore | NewBack << 4);
            }

            void GetColor(int& Fore, int& Back)
            {
                CONSOLE_SCREEN_BUFFER_INFO Info;
                GetConsoleScreenBufferInfo(Output, &Info);
                Fore = Info.wAttributes & 15;
                Back = (Info.wAttributes >> 4) & 15;
            }

            void SetForeColor(int NewFore = White)
            {
                int Fore, Back;
                GetColor(Fore, Back);
                SetColor(NewFore, Back);
            }

            int GetForeColor()
            {
                int Fore, Back;
                GetColor(Fore, Back);
                return Fore;
            }

            void SetBackColor(int NewBack = Black)
            {
                int Fore, Back;
                GetColor(Fore, Back);
                SetColor(Fore, NewBack);
            }

            int GetBackColor()
            {
                int Fore, Back;
                GetColor(Fore, Back);
                return Back;
            }

            void ClearChar(char NewChar = ' ', bool Reset = false)
            {
                CONSOLE_SCREEN_BUFFER_INFO Info;
                COORD Pos = {0, 0};
                DWORD Count;
                GetConsoleScreenBufferInfo(Output, &Info);
                FillConsoleOutputCharacter(Output, NewChar, Info.dwSize.X*Info.dwSize.Y, Pos, &Count);
                if (Reset)
                    SetXY(0, 0);
            }

            void ClearColor(int NewFore = White, int NewBack = Black, bool Reset = false, bool SwapColor = true)
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

            void Clear(bool Reset = true)
            {
                ClearChar();
                ClearColor();
                if (Reset)
                    SetXY(0, 0);
            }

            void SetCursor(int NewPercent = Default)
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

            int GetCursor()
            {
                CONSOLE_CURSOR_INFO Info;
                GetConsoleCursorInfo(Output, &Info);
                return (Info.bVisible == TRUE ? Info.dwSize : 0);
            }
    };
}

#endif //SIMLIB_CONSOLE_H
