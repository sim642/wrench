#ifndef SIMLIB_STRING_H
#define SIMLIB_STRING_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

namespace sim
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

    std::vector<std::string> Explode(std::string String, std::string Separator = DefaultSeparator, int Limit = 0)
    {
        std::vector<std::string> Return;
        size_t StartPosition = 0, EndPosition;

        int Count = 1;
        while ((EndPosition = String.find(Separator, StartPosition)) != std::string::npos && (Limit > 0 ? Count < Limit : true))
        {
        	Return.push_back(String.substr(StartPosition, EndPosition - StartPosition));
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
}

#endif // SIMLIB_STRING_H
