#include "CaveRegion.h"


CaveRegion::CaveRegion(Ogre::Vector3 globalVector, UberCube *cube): mGlobalVector(globalVector), mCube(cube)
{
}

CaveRegion::~CaveRegion()
{
    delete mCube;
}

Ogre::Vector3 CaveRegion::GetGlobalPos()
{
    return mGlobalVector;
}

UberCube* CaveRegion::GetDensityCube()
{
    return mCube;
}

Ogre::Vector3 CaveRegion::GetLocalPositionExit(int exitNumber)
{
    return mLocalPositionExits.at(exitNumber);
}

void CaveRegion::AddLocalPositionExits(Ogre::Vector3 newExit)
{
    mLocalPositionExits.push_back(newExit);
}