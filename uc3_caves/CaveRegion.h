#ifndef CAVEREGION_H
#define CAVEREGION_H

#include "UberCube.h"

class CaveRegion
{
    protected:
        UberCube *mCube;
        int mGlobalPosX;
        int mGlobalPosY;
        int mGlobalPosZ;

        CaveRegion(){}

    
    public:
        CaveRegion(int globalPosX, int globalPosY,int globalPosZ, UberCube *cube);
        ~CaveRegion();
        

        int GetGlobalPosX();
        int GetGlobalPosY();
        int GetGlobalPosZ();
        UberCube* GetDensityCube();
};
#endif