#include "Mini3D.h"

unsigned int CMini3D::tempVertexBuffer;
float CMini3D::ambientRed;
float CMini3D::ambientGreen;
float CMini3D::ambientBlue;

unsigned int CMini3D::alloc32(int size)
{
    if (size < 1 || size > 500000)
    {
        //gtfoSourceFile = "..\\engine\\MINI3D.CPP";
        //gtfoSourceLine = 0x19BA;
        //reallyGTFO("CMini3D::alloc32 - vertexCount=%d", size);
    } 

    void* newMem = malloc(size * 0x20 + 0x24);
    if (newMem == nullptr)
    {
        //gtfoSourceFile = "..\\engine\\MINI3D.CPP";
        //gtfoSourceLine = 0x19C8;
        //reallyGTFO("CMini3D::allocVertexBuffer - Allocation of %d vertex failed", size);
    }

   // unsigned int temp = (unsigned int)newMem + 0x24 & 0xFFFFFFE0;
    //*(unsigned int*) (temp-4) = size;
    //*(unsigned char*)(temp-5) = (unsigned char)temp - (unsigned char)newMem;

    return 0;//temp
}

float CMini3D::getAmbientLight()
{
    return (ambientRed + ambientBlue + ambientGreen) / 3.0f;
}

int CMini3D::init()
{
    //debugPrint("CMini3D::init\n");
    tempVertexBuffer = alloc32(0x400);
    return 1;
}