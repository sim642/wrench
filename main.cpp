#include <iostream>
#include "simlib.hpp"

using namespace std;

int main()
{
    sim::Console C;
    C.ClearColor(sim::Console::BrightWhite, sim::Console::LightBlue);

    sim::Timer T;
    T.Start();
    Sleep(500);
    T.Stop();
    cout << T.GetMilliSec() << endl;

    cin.get();
    return 0;
}
