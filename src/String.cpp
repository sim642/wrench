#include <wrench/String.hpp>

namespace wrench
{
    std::string TrimLeft(std::string String, std::string Remove)
    {
        return String.substr(String.find_first_not_of(Remove));
    }

    std::string TrimRight(std::string String, std::string Remove)
    {
        return String.substr(0, String.find_last_not_of(Remove) + 1);
    }

    std::string Trim(std::string String, std::string Remove)
    {
        return TrimLeft(TrimRight(String, Remove), Remove);
    }

    std::vector<std::string> Explode(std::string String, std::string Separator, int Limit)
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

    std::string Implode(std::vector<std::string> Strings, std::string Separator)
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
    std::string operator*(const std::string& lhs, std::size_t rhs)
    {
        std::string Return;
        for (Return.reserve(lhs.size() * rhs); rhs > 0; rhs--)
            Return.append(lhs);
        return Return;
    }

    std::string operator*(std::size_t lhs, const std::string& rhs)
    {
        return operator*(rhs, lhs);
    }
}
