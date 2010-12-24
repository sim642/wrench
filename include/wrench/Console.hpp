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
            const static int DefaultWidth = 80,
                             DefaultHeight = 24;
        private:
            HANDLE Output;
        public:
            Console();
            Console(HANDLE);

            void SetHandleOutput(HANDLE);
            HANDLE GetHandleOutput();

            void SetXY(int = 0, int = 0);
            void GetXY(int&, int&);
            void SetX(int = 0);
            int GetX();
            void SetY(int = 0);
            int GetY();

            void SetBufferSize(int = DefaultWidth, int = DefaultHeight);
            void GetBufferSize(int&, int&);
            void SetBufferWidth(int = DefaultWidth);
            int GetBufferWidth();
            void SetBufferHeight(int = DefaultWidth);
            int GetBufferHeight();

            void SetColor(int = White, int = Black);
            void GetColor(int&, int&);
            void SetForeColor(int = White);
            int GetForeColor();
            void SetBackColor(int = Black);
            int GetBackColor();

            void ClearChar(char = ' ', bool = false);
            void ClearColor(int = White, int = Black, bool = false, bool = true);
            void Clear(bool = true);

            void SetCursor(int);
            int GetCursor();

            void SetTitle(std::string);
            std::string GetTitle();
    };
}

#endif //WRENCH_CONSOLE_H
