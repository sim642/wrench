#ifndef WRENCH_MATH_H
#define WRENCH_MATH_H

#include <cmath>

namespace wrench
{
    int Gcd(int, int);
    int Lcm(int, int);

    int Sign(int);
    double Sign(double);

    int NumberLength(int);
    int NumberPos(int, int);
    int Map(int, int, int, int, int);
    double Map(double, double, double, double, double);

    int Constrain(int, int, int);
    double Constrain(double, double, double);
}

#endif // WRENCH_MATH_H
