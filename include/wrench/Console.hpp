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
                          Grey = 8, BrightWhite = 15};
            enum Cursor {Hidden, Default = 25, Full = 100};
            enum Size {DefaultBufferWidth = 80, DefaultBufferHeight = 300, DefaultWindowWidth = 30, DefaultWindowHeight = 24};
        private:
            HANDLE Output;
        public:
            Console();
            Console(HANDLE);

            /** Handles */
            void SetHandleOutput(HANDLE);
            HANDLE GetHandleOutput();

            /** Cursor */
            void SetXY(int = 0, int = 0);
            void GetXY(int&, int&);
            void SetX(int = 0);
            int GetX();
            void SetY(int = 0);
            int GetY();

            void SetCursor(int);
            int GetCursor();

            /** Buffer size */
            void SetBufferSize(int = DefaultBufferWidth, int = DefaultBufferHeight);
            void GetBufferSize(int&, int&);
            void SetBufferWidth(int = DefaultBufferWidth);
            int GetBufferWidth();
            void SetBufferHeight(int = DefaultBufferHeight);
            int GetBufferHeight();

            /** Window size */
            void SetWindowSize(int = DefaultWindowWidth, int = DefaultWindowHeight);
            void GetWindowSize(int&, int&);
            void SetWindowWidth(int = DefaultWindowWidth);
            int GetWindowWidth();
            void SetWindowHeight(int = DefaultWindowHeight);
            int GetWindowHeight();

            /** Color */
            void SetColor(int = White, int = Black);
            void GetColor(int&, int&);
            void SetForeColor(int = White);
            int GetForeColor();
            void SetBackColor(int = Black);
            int GetBackColor();

            /** Clear */
            void ClearChar(char = ' ', bool = false);
            void ClearColor(int = White, int = Black, bool = false, bool = true);
            void Clear(bool = true);

            /** Title */
            void SetTitle(std::string);
            std::string GetTitle();
    };
}

#endif //WRENCH_CONSOLE_H
