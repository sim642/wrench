#include "String.hpp"

namespace sim
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
}
