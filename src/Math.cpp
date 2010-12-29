#include <wrench/Math.hpp>

namespace wrench
{
    int Gcd(int A, int B)
    {
        int T;
        while (B != 0)
        {
            T = B;
            B = A % B;
            A = T;
        }
        return A;
    }

    int Lcm(int A, int B)
    {
        return std::abs(double(A * B)) / Gcd(A, B);
    }

    int Sign(int X)
    {
        if (X == 0)
            return 0;
        else if (X > 0)
            return 1;
        else
            return -1;
    }

    double Sign(double X)
    {
        if (X == 0)
            return 0;
        else if (X > 0)
            return 1;
        else
            return -1;
    }

    int NumberLength(int X)
    {
        if (X == 0)
            return 1;
        else
            return std::ceil(std::log10(std::abs(std::floor(X)) + 1));
    }

    int NumberPos(int X, int I)
    {
        return int(X / std::pow(10.0, I)) % 10;
    }

    int Map(int X, int InLow, int InHigh, int OutLow, int OutHigh)
    {
        return (X - InLow) * (OutHigh - OutLow) / (InHigh - InLow) + OutLow;
    }

    double Map(double X, double InLow, double InHigh, double OutLow, double OutHigh)
    {
        return (X - InLow) * (OutHigh - OutLow) / (InHigh - InLow) + OutLow;
    }

    int Constrain(int X, int Low, int High)
    {
        return X < Low ? Low : (X > High ? High : X);
    }

    double Constrain(double X, double Low, double High)
    {
        return X < Low ? Low : (X > High ? High : X);
    }
}
