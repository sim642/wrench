#include <iostream>
#include <vector>
#include "simlib.hpp"

using namespace std;

int main()
{
    sim::Console C;
    C.ClearColor(sim::Console::BrightWhite, sim::Console::LightBlue);

    vector<string> strs;

    strs = sim::Explode("one|two|three|four", "|", 2);

    for (int i = 0; i < strs.size(); i++)
        cout << strs[i] << endl;

    cin.get();
    return 0;
}
