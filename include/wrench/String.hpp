#ifndef WRENCH_STRING_H
#define WRENCH_STRING_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

namespace wrench
{
    const std::string DefaultSpaces = " \t\n\r\0\x0B";
    const std::string DefaultSeparator = " ";

    std::string TrimLeft(std::string, std::string = DefaultSpaces);
    std::string TrimRight(std::string, std::string = DefaultSpaces);
    std::string Trim(std::string, std::string = DefaultSpaces);

    std::vector<std::string> Explode(std::string, std::string = DefaultSeparator, int = 0);
    std::string Implode(std::vector<std::string>, std::string = DefaultSeparator);

    std::string ToUpper(std::string);
    std::string ToLower(std::string);

    /** Repeating for std::string */
    std::string operator*(const std::string&, std::size_t);
    std::string operator*(std::size_t, const std::string&);
}

#endif // WRENCH_STRING_H
