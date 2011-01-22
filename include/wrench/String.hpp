#ifndef WRENCH_STRING_H
#define WRENCH_STRING_H

#include <wrench/Config.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#ifndef WRENCH_NO_GLOBALOPS
using wrench::operator*;
#endif

namespace wrench
{
    const std::string DefaultSpaces = " \t\n\r\0\x0B";
    const std::string DefaultSeparator = " ";

    std::string TrimLeft(std::string String, std::string Remove = DefaultSpaces)
    {
        return String.substr(String.find_first_not_of(Remove));
    }

    std::string TrimRight(std::string String, std::string Remove = DefaultSpaces)
    {
        return String.substr(0, String.find_last_not_of(Remove) + 1);
    }

    std::string Trim(std::string String, std::string Remove = DefaultSpaces)
    {
        return TrimLeft(TrimRight(String, Remove), Remove);
    }

    std::vector<std::string> Explode(std::string String, std::string Separator = DefaultSeparator, bool Preserve = false, unsigned int Limit = 0)
    {
        std::vector<std::string> Return;
        size_t StartPosition = 0, EndPosition;

        unsigned int Count = 1;
        while ((EndPosition = String.find(Separator, StartPosition)) != std::string::npos && (Limit > 0 ? Count < Limit : true))
        {
            std::string Cut = String.substr(StartPosition, EndPosition - StartPosition);

            if (!Preserve && Cut.empty())
            {
                StartPosition = EndPosition + Separator.length();
                continue;
            }

            Return.push_back(Cut);
            StartPosition = EndPosition + Separator.length();

            if (Limit > 0)
            {
                Count++;
            }
        }
        Return.push_back(String.substr(StartPosition));

        return Return;
    }

    std::string Implode(std::vector<std::string> Strings, std::string Separator = DefaultSeparator)
    {
        std::string Return;

        for (std::vector<std::string>::iterator it = Strings.begin(); it != Strings.end(); ++it)
        {
            Return += *it;
            if (it != Strings.end() - 1)
            {
                Return += Separator;
            }
        }

        return Return;
    }

    std::string ToUpper(std::string String)
    {
        std::transform(String.begin(), String.end(), String.begin(), (int(*)(int))std::toupper);
        return String;
    }

    std::string ToLower(std::string String)
    {
        std::transform(String.begin(), String.end(), String.begin(), (int(*)(int))std::tolower);
        return String;
    }

    /** Repeating for std::string */
    std::string operator*(const std::string& Lhs, std::size_t Rhs)
    {
        std::string Return;
        for (Return.reserve(Lhs.size() * Rhs); Rhs > 0; Rhs--)
            Return.append(Lhs);
        return Return;
    }

    std::string operator*(std::size_t Lhs, const std::string& Rhs)
    {
        return operator*(Rhs, Lhs);
    }
}

#endif // WRENCH_STRING_H
