#ifndef WRENCH_MATH_H
#define WRENCH_MATH_H

#include <wrench/Config.hpp>

#include <cmath>

namespace wrench
{
    template<typename T>
    inline short Sgn(T X)
    {
        return X == 0 ? 0 : (X > 0 ? 1 : -1);
    }

    template<typename T>
    inline T Abs(T X)
    {
        return std::fabs(X);
    }

    template<typename T>
    inline T Mod(T A, T B)
    {
        return std::fmod(A, B);
    }

    template<typename T>
    inline T Gcd(T A, T B)
    {
        T C;
        while (B != 0)
        {
            C = B;
            B = Mod(A, B);
            A = C;
        }
        return A;
    }

    template<typename T>
    inline T Lcm(T A, T B)
    {
        return Abs(A * B) / Gcd(A, B);
    }

    template<typename T>
    inline unsigned int NumberLength(T X)
    {
        if (int(X) == 0)
            return 1;
        else
            return std::ceil(std::log10(std::floor(Abs(X)) + 1));
    }

    template<typename T>
    inline unsigned short NumberPos(T X, int I)
    {
        return int(X / std::pow(10.0, I)) % 10;
    }

    template<typename T>
    inline T Map(T X, T InLow, T InHigh, T OutLow, T OutHigh)
    {
        return (X - InLow) * (OutHigh - OutLow) / (InHigh - InLow) + OutLow;
    }

    template<typename T>
    inline T Constrain(T X, T Low, T High)
    {
        return X < Low ? Low : (X > High ? High : X);
    }
}

#endif // WRENCH_MATH_H
