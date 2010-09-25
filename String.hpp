#ifndef SIMLIB_STRING_H
#define SIMLIB_STRING_H

#include <string>
#include <vector>
#include <algorithm>

namespace sim
{
    const std::string Spacers = " \t\r\n";
    std::string TrimLeft(std::string, std::string = Spacers);
    std::string TrimRight(std::string, std::string = Spacers);
    std::string Trim(std::string, std::string = Spacers);
}

#endif // SIMLIB_STRING_H
