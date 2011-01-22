#ifndef WRENCH_CONSOLE_H
#define WRENCH_CONSOLE_H

#include <wrench/Config.hpp>

#include <string>
#include <windows.h>

namespace wrench
{
    class Console
    {
        public:
            enum Color {Black, Blue, Green, Aqua, Red, Purple, Yellow, White,
                        LightBlack, LightBlue, LightGreen, LightAqua, LightRed,
                        LightPurple, LightYellow, LightWhite,
                        Grey = 8, BrightWhite = 15
                       };
            enum Cursor {Hidden, Default = 25, Full = 100};
            enum Size {DefaultBufferWidth = 80, DefaultBufferHeight = 300, DefaultWindowWidth = 30, DefaultWindowHeight = 24};

            Console()
            {
                SetOutputHandle(GetStdHandle(STD_OUTPUT_HANDLE));
            }

            Console(HANDLE NewOutput)
            {
                SetOutputHandle(NewOutput);
            }

            /** Handles */
            void SetOutputHandle(HANDLE NewOutput)
            {
                Output = NewOutput;
            }

            HANDLE GetOutputHandle()
            {
                return Output;
            }

            /** Cursor */
            bool SetXY(int NewX = 0, int NewY = 0)
            {
                COORD Pos = {NewX, NewY};
                return SetConsoleCursorPosition(Output, Pos);
            }

            void GetXY(int& X, int& Y)
            {
                CONSOLE_SCREEN_BUFFER_INFO Info;
                GetConsoleScreenBufferInfo(Output, &Info);
                X = Info.dwCursorPosition.X;
                Y = Info.dwCursorPosition.Y;
            }

            bool SetX(int NewX = 0)
            {
                return SetXY(NewX, GetY());
            }

            int GetX()
            {
                int X, Y;
                GetXY(X, Y);
                return X;
            }

            bool SetY(int NewY = 0)
            {
                return SetXY(GetX(), NewY);
            }

            int GetY()
            {
                int X, Y;
                GetXY(X, Y);
                return Y;
            }

            bool SetCursor(int NewPercent = Default)
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

            int GetCursor()
            {
                CONSOLE_CURSOR_INFO Info;
                GetConsoleCursorInfo(Output, &Info);
                return (Info.bVisible == TRUE ? Info.dwSize : 0);
            }

            /** Buffer size */
            bool SetBufferSize(int NewWidth = DefaultBufferWidth, int NewHeight = DefaultBufferHeight)
            {
                COORD Size = {NewWidth, NewHeight};
                return SetConsoleScreenBufferSize(Output, Size);
            }

            void GetBufferSize(int& Width, int& Height)
            {
                CONSOLE_SCREEN_BUFFER_INFO Info;
                GetConsoleScreenBufferInfo(Output, &Info);
                Width = Info.dwSize.X;
                Height = Info.dwSize.Y;
            }

            bool SetBufferWidth(int NewWidth = DefaultBufferWidth)
            {
                return SetBufferSize(NewWidth, GetBufferHeight());
            }

            int GetBufferWidth()
            {
                int Width, Height;
                GetBufferSize(Width, Height);
                return Width;
            }

            bool SetBufferHeight(int NewHeight = DefaultBufferHeight)
            {
                return SetBufferSize(GetBufferWidth(), NewHeight);
            }

            int GetBufferHeight()
            {
                int Width, Height;
                GetBufferSize(Width, Height);
                return Height;
            }

            /** Window size */
            bool SetWindowSize(int NewWidth = DefaultWindowWidth, int NewHeight = DefaultWindowHeight)
            {
                SMALL_RECT Size = {0, 0, NewWidth - 1, NewHeight - 1};
                return SetConsoleWindowInfo(Output, TRUE, &Size);
            }

            void GetWindowSize(int& Width, int& Height)
            {
                CONSOLE_SCREEN_BUFFER_INFO Info;
                GetConsoleScreenBufferInfo(Output, &Info);
                Width = Info.srWindow.Right;
                Height = Info.srWindow.Bottom;
            }

            bool SetWindowWidth(int NewWidth = DefaultWindowWidth)
            {
                return SetWindowSize(NewWidth, GetWindowHeight());
            }

            int GetWindowWidth()
            {
                int Width, Height;
                GetWindowSize(Width, Height);
                return Width;
            }

            bool SetWindowHeight(int NewHeight = DefaultWindowHeight)
            {
                return SetWindowSize(GetWindowWidth(), NewHeight);
            }

            int GetWindowHeight()
            {
                int Width, Height;
                GetWindowSize(Width, Height);
                return Height;
            }

            /** Color */
            bool SetColor(int NewFore = White, int NewBack = Black)
            {
                return SetConsoleTextAttribute(Output, NewFore | NewBack << 4);
            }

            void GetColor(int& Fore, int& Back)
            {
                CONSOLE_SCREEN_BUFFER_INFO Info;
                GetConsoleScreenBufferInfo(Output, &Info);
                Fore = Info.wAttributes & 0xF;
                Back = (Info.wAttributes >> 4) & 0xF;
            }
            bool SetForeColor(int NewFore = White)
            {
                return SetColor(NewFore, GetBackColor());
            }

            int GetForeColor()
            {
                int Fore, Back;
                GetColor(Fore, Back);
                return Fore;
            }

            bool SetBackColor(int NewBack = Black)
            {
                return SetColor(GetForeColor(), NewBack);
            }

            int GetBackColor()
            {
                int Fore, Back;
                GetColor(Fore, Back);
                return Back;
            }

            /** Clear */
            bool ClearChar(char NewChar = ' ', bool Reset = false)
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

            bool ClearColor(int NewFore = White, int NewBack = Black, bool SwapColor = true)
            {
                bool Return = true;
                CONSOLE_SCREEN_BUFFER_INFO Info;
                COORD Pos = {0, 0};
                DWORD Count;
                GetConsoleScreenBufferInfo(Output, &Info);
                Return &= FillConsoleOutputAttribute(Output, NewFore | NewBack << 4, Info.dwSize.X * Info.dwSize.Y, Pos, &Count);
                if (SwapColor)
                    Return &= SetColor(NewFore, NewBack);
                return Return;
            }

            bool Clear(bool Reset = true)
            {
                bool Return = true;
                Return &= ClearChar();
                Return &= ClearColor();
                if (Reset)
                    Return &= SetXY(0, 0);
                return Return;
            }

            /** Title */
            bool SetTitle(std::string NewTitle)
            {
                return SetConsoleTitle(NewTitle.c_str());
            }

            std::string GetTitle()
            {
                char Title[MAX_PATH];
                GetConsoleTitle(Title, MAX_PATH);
                return std::string(Title);
            }

        private:
            HANDLE Output;
    };
}

#endif //WRENCH_CONSOLE_H
