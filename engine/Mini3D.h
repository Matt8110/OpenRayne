#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "../Utils.h"

class CMini3D
{
public:
    static float    ambientRed;
    static float    ambientGreen;
    static float    ambientBlue;
    static void* tempVertexBuffer;
    static int      polyFlag;
    static int      blendFlag;
    static int      destBlendFlag;
    static int      fogFlag;
    static int      clipFlag;
    static float    fogMin;
    static float    fogMax;
    static float    invFogMaxMin;

    //API
    static int APImode;
    static void* pAPIDLLsetFog;
    static void (*pAPIDLLsetAmbientLightColor)(float r, float g, float b);
    static void (*pAPIDLLsetAmbientLight)(float val);
    static void (*pAPIDLLsetDestBlend)(int val);

    //Matching
    static void* alloc32(int size);
    static float getAmbientLight();
    static int init();
    static void disableBlend();
    static void enableBlend();
    static void disableFog();
    static void enableFog();
    static void setAmbientLight(float val);
    static void setAmbientLight(float r, float g, float b);
    static void setDestBlend(int val);
    static void setPolyType(int val);
};