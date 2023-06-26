#pragma once

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

class CUtils
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

    static void reallyGTFO(const char* format, ...)
    {
        va_list list;
        va_start(list, format);
        vfprintf(stdout, format, list);
        va_end(list);

        exit(0);
    }
};