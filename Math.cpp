#include "Math.hpp"

namespace sim
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
}
