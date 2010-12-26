#ifndef WRENCH_CONSOLE_H
#define WRENCH_CONSOLE_H

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

            Console();
            Console(HANDLE);

            /** Handles */
            void SetHandleOutput(HANDLE);
            HANDLE GetHandleOutput();

            /** Cursor */
            bool SetXY(int = 0, int = 0);
            void GetXY(int&, int&);
            bool SetX(int = 0);
            int GetX();
            bool SetY(int = 0);
            int GetY();

            bool SetCursor(int);
            int GetCursor();

            /** Buffer size */
            bool SetBufferSize(int = DefaultBufferWidth, int = DefaultBufferHeight);
            void GetBufferSize(int&, int&);
            bool SetBufferWidth(int = DefaultBufferWidth);
            int GetBufferWidth();
            bool SetBufferHeight(int = DefaultBufferHeight);
            int GetBufferHeight();

            /** Window size */
            bool SetWindowSize(int = DefaultWindowWidth, int = DefaultWindowHeight);
            void GetWindowSize(int&, int&);
            bool SetWindowWidth(int = DefaultWindowWidth);
            int GetWindowWidth();
            bool SetWindowHeight(int = DefaultWindowHeight);
            int GetWindowHeight();

            /** Color */
            bool SetColor(int = White, int = Black);
            void GetColor(int&, int&);
            bool SetForeColor(int = White);
            int GetForeColor();
            bool SetBackColor(int = Black);
            int GetBackColor();

            /** Clear */
            bool ClearChar(char = ' ', bool = false);
            bool ClearColor(int = White, int = Black, bool = false, bool = true);
            bool Clear(bool = true);

            /** Title */
            bool SetTitle(std::string);
            std::string GetTitle();

        private:
            HANDLE Output;
    };
}

#endif //WRENCH_CONSOLE_H
