#include <iostream>
#include "simlib.hpp"

using namespace std;

int main()
{
    sim::Console C;
    C.ClearColor(sim::Console::BrightWhite, sim::Console::LightBlue);

    cout << sim::Gcd(60, 12) << endl;
    cout << sim::Lcm(60, 12) << endl;

    cin.get();
    return 0;
}
