#include <iostream>
#include <vector>
#include <simlib/simlib.hpp>

using namespace std;

int main()
{
    sim::Console C;
    C.ClearColor(sim::Console::BrightWhite, sim::Console::LightBlue);

    string str = "abcABC123¤%&";

    cout << sim::ToUpper(str) << endl << sim::ToLower(str) << endl;

    cin.get();
    return 0;
}
