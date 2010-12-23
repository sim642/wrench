#ifndef WRENCH_MATH_H
#define WRENCH_MATH_H

#include <cmath>

namespace wrench
{
    int Gcd(int, int);
    int Lcm(int, int);
    int Sign(int);
    int NumberLength(int);
    int NumberPos(int, int);
    int Map(int, int, int, int, int);
    int Constrain(int, int, int);
}

#endif // WRENCH_MATH_H
