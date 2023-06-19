#pragma once

#include <stdlib.h>

class CMini3D
{
public:
    static float ambientRed;
    static float ambientGreen;
    static float ambientBlue;
    static unsigned int tempVertexBuffer;

    //Matching
    static unsigned int alloc32(int size);
    static float getAmbientLight();
    static int init();
};