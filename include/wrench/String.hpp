#ifndef WRENCH_STRING_H
#define WRENCH_STRING_H

#include <wrench/Config.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

namespace wrench
{
    const std::string DefaultSpaces = " \t\n\r\0\x0B";
    const std::string DefaultSeparator = " ";
    const std::string DefaultPad = " ";

    /** Case change */
    inline std::string ToUpper(std::string String)
    {
        std::transform(String.begin(), String.end(), String.begin(), (int(*)(int))std::toupper);
        return String;
    }

    inline std::string ToLower(std::string String)
    {
        std::transform(String.begin(), String.end(), String.begin(), (int(*)(int))std::tolower);
        return String;
    }

    /** Repeating for std::string */
    inline std::string operator*(const std::string& Lhs, std::size_t Rhs)
    {
        std::string Return;
        for (Return.reserve(Lhs.size() * Rhs); Rhs > 0; Rhs--)
            Return.append(Lhs);
        return Return;
    }

    inline std::string operator*(std::size_t Lhs, const std::string& Rhs)
    {
        return operator*(Rhs, Lhs);
    }

    /** Trim std::string */
    inline std::string TrimLeft(std::string String, std::string Remove = DefaultSpaces)
    {
        return String.substr(String.find_first_not_of(Remove));
    }

    inline std::string TrimRight(std::string String, std::string Remove = DefaultSpaces)
    {
        return String.substr(0, String.find_last_not_of(Remove) + 1);
    }

    inline std::string Trim(std::string String, std::string Remove = DefaultSpaces)
    {
        return TrimLeft(TrimRight(String, Remove), Remove);
    }

    /** Pad std::string */
    /** Cut if necessary to be desired length*/
    inline std::string PadLeft(std::string String, unsigned int Length, std::string Pad = DefaultPad)
    {
        if (String.length() == Length)
            return String;
        if (String.length() > Length)
            return String.substr(0, Length);
        else
            return (Pad * ((Length - String.length() + 1) / Pad.length())).substr(0, Length - String.length()) + String;
    }

    inline std::string PadRight(std::string String, unsigned int Length, std::string Pad = DefaultPad)
    {
        if (String.length() == Length)
            return String;
        if (String.length() > Length)
            return String.substr(0, Length);
        else
            return String + (Pad * ((Length - String.length() + 1) / Pad.length())).substr(0, Length - String.length());
    }

    inline std::string Pad(std::string String, unsigned int Length, std::string Pad = DefaultPad)
    {
        if (String.length() == Length)
            return String;
        if (String.length() > Length)
            return String.substr(0, Length);
        else
        {
            unsigned int AddRight = (Length - String.length()) / 2 + 1;
            std::string PaddedRight;
            return PadLeft(PaddedRight = PadRight(String, String.length() + AddRight, Pad), Length - PaddedRight.length(), Pad);
        }
    }

    /** Break and merge std::string */
    inline std::vector<std::string> Explode(std::string String, std::string Separator = DefaultSeparator, bool Preserve = false, unsigned int Limit = 0)
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

    inline std::string Implode(std::vector<std::string> Strings, std::string Separator = DefaultSeparator)
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
}

#ifndef WRENCH_NO_GLOBALOPS
using wrench::operator*;
#endif

#endif // WRENCH_STRING_H
