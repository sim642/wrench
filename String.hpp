#ifndef SIMLIB_STRING_H
#define SIMLIB_STRING_H

#include <string>
#include <vector>
#include <algorithm>

namespace sim
{
    const std::string DefaultSpaces = " \t\n\r\0\x0B";
    const std::string DefaultSeparator = " ";

    std::string TrimLeft(std::string, std::string = DefaultSpaces);
    std::string TrimRight(std::string, std::string = DefaultSpaces);
    std::string Trim(std::string, std::string = DefaultSpaces);

    std::vector<std::string> Explode(std::string, std::string = DefaultSeparator, int = 0);
    std::string Implode(std::vector<std::string>, std::string = DefaultSeparator);
}

#endif // SIMLIB_STRING_H
