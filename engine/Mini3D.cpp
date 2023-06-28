#include "Mini3D.h"

void* CMini3D::tempVertexBuffer;
float    CMini3D::ambientRed;
float    CMini3D::ambientGreen;
float    CMini3D::ambientBlue;
int      CMini3D::polyFlag;
int      CMini3D::blendFlag;
int      CMini3D::destBlendFlag;
int      CMini3D::fogFlag;
int      CMini3D::clipFlag;
float    CMini3D::fogMin;
float    CMini3D::fogMax;
float    CMini3D::invFogMaxMin;

//API
int     CMini3D::APImode;
void*   CMini3D::pAPIDLLsetFog;
void    (*CMini3D::pAPIDLLsetAmbientLightColor)(float r, float g, float b);
void    (*CMini3D::pAPIDLLsetAmbientLight)(float val);
void    (*CMini3D::pAPIDLLsetDestBlend)(int val);

void* CMini3D::alloc32(int size)
{

    if (size < 1 || size > 500000)
    {
        //gtfoSourceFile = "..\\engine\\MINI3D.CPP";
        //gtfoSourceLine = 0x19BA;
        CUtils::reallyGTFO("CMini3D::alloc32 - vertexCount=%d", size);
    } 

    void* newMem = malloc(size * 0x20 + 0x24);
    if (newMem == nullptr)
    {
        //gtfoSourceFile = "..\\engine\\MINI3D.CPP";
        //gtfoSourceLine = 0x19C8;
        CUtils::reallyGTFO("CMini3D::allocVertexBuffer - Allocation of %d vertex failed", size);
    }

    unsigned int temp = (unsigned int)newMem + 0x24 & 0xFFFFFFE0;
    *(unsigned int*) (temp-4) = size;
    *(unsigned char*)(temp-5) = temp - (unsigned int)newMem;

    return (void*)temp;
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

void CMini3D::disableBlend()
{
    blendFlag = false;
}

void CMini3D::enableBlend()
{
    blendFlag = true;
}

void CMini3D::disableFog()
{
    fogFlag = false;
}

void CMini3D::enableFog()
{
    if (pAPIDLLsetFog != nullptr || APImode == 0)
    {
        fogFlag = true;
    }
}

void CMini3D::setAmbientLight(float val)
{
    ambientRed = val;
    ambientGreen = val;
    ambientBlue = val;

    if (pAPIDLLsetAmbientLightColor != nullptr && APImode != 0)
    {
        pAPIDLLsetAmbientLightColor(val, val, val);
    }
    else if (pAPIDLLsetAmbientLight != nullptr && APImode != 0)
    {
        pAPIDLLsetAmbientLight(val);
    }
}

void CMini3D::setAmbientLight(float r, float g, float b)
{
    ambientRed = r;
    ambientGreen = g;
    ambientBlue = b;

    if (pAPIDLLsetAmbientLightColor != nullptr && APImode != 0)
    {
        pAPIDLLsetAmbientLightColor(r, g, b);
    }
}

void CMini3D::setDestBlend(int val)
{
    destBlendFlag = val;

    if (pAPIDLLsetDestBlend != nullptr)
    {
        pAPIDLLsetDestBlend(val);
    }
}

void CMini3D::setPolyType(int val)
{
    polyFlag = val;
}