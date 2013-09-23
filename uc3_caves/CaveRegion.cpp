#include "CaveRegion.h"


CaveRegion::CaveRegion(int globalPosX, int globalPosY,int globalPosZ, UberCube *cube): mGlobalPosX(globalPosX), mGlobalPosY(globalPosY), mGlobalPosZ(globalPosZ), mCube(cube)
{
}


int CaveRegion::GetGlobalPosX()
{
    return mGlobalPosX;
}

int CaveRegion::GetGlobalPosY()
{
    return mGlobalPosY;
}

int CaveRegion::GetGlobalPosZ()
{
    return mGlobalPosZ;
}

UberCube* CaveRegion::GetDensityCube()
{
    return mCube;
}