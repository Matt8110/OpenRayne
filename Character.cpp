#include "Character.h"


//This is just weird, man
int CCharacter::getAimPoint(CVector& vec)
{
    if (getDeadState() != 0)
    {
        return 0;
    }

    CVector temp;
    CVector temp2;
    
    temp.x = boundingBox.x1 + boundingBox.x2;
    temp.y = boundingBox.y2 + boundingBox.y1;
    temp.z = boundingBox.z2 + boundingBox.z1;

    temp2.x = temp.x * 0.5f;
    temp2.y = temp.y * 0.5f;
    temp2.z = temp.z * 0.5f;

    vec.x = temp2.x;
    vec.z = temp2.z;
    vec.y = temp2.y + 1.0f;

    return 1;
}