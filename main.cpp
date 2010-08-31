#include <iostream>
#include "simlib.hpp"

using namespace std;

int main()
{
    sim::Console C;
    C.ClearColor(sim::Console::BrightWhite, sim::Console::LightBlue);

    cout << sim::NumberPos(12345, 4) << endl;

    cin.get();
    return 0;
}
