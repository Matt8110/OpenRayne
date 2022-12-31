#pragma once

#include <math.h>

class Utils
{
public:
    static float wrapPi(float x)
    {
        float temp;

        if (fabs(x) > 3.141593)
        {
            temp = x + 3.141593;
            x = floorf(temp * 0.1591549f);
            return (temp - x * 6.283185) - 3.141593;
        }

        return x;
    }
};