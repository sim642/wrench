#include <iostream>
#include "simlib.hpp"

using namespace std;

int main()
{
    sim::Console C;
    C.ClearColor(sim::Console::BrightWhite, sim::Console::LightBlue);

    string str("  \n\n asdasdasd \r\t  ");
    str = sim::Trim(str);

    cout << str << endl;

    cin.get();
    return 0;
}
