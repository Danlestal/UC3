#ifndef CAVEREGION_H
#define CAVEREGION_H

#include "UberCube.h"

class CaveRegion
{
    private:
        UberCube *mCube;
        int mGlobalPosX;
        int mGlobalPosY;
        int mGlobalPosZ;
    
    public:
        CaveRegion(int globalPosX, int globalPosY,int globalPosZ, UberCube *mCube);

        int GetGlobalPosX();
        int GetGlobalPosY();
        int GetGlobalPosZ();
};
#endif