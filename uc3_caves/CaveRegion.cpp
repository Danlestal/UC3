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


Ogre::Vector3 GetRandomPointOnCubeFace(CubeFace face)
{
    RandomNumberGenerator generator = RandomNumberGenerator();
    switch (face)
    {
    case TOP:
        return Ogre::Vector3(generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5), UBERCUBE_SIZE, generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5));
    case BOTTON:
        return Ogre::Vector3(generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5), 0, generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5));
    case LEFT:
        return Ogre::Vector3(0, generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5), generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5));
    case RIGHT:
        return Ogre::Vector3(UBERCUBE_SIZE, generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5), generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5));
    case FRONT:
        return Ogre::Vector3(generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5), generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5) , UBERCUBE_SIZE);
    case BACK:
        return Ogre::Vector3(generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5), generator.GenerateRandomNumber(5,UBERCUBE_SIZE-5), 0);
    }


    return Ogre::Vector3::ZERO;
}

void CaveRegion::AddRegionExitOnCubeFace(CubeFace newExit)
{
    if ( mRegionExits.find(newExit) == mRegionExits.end() )
    {
        mRegionExits[newExit] = GetRandomPointOnCubeFace(newExit);
    }
}

Ogre::Vector3 CaveRegion::GetExitPointOnCubeFace(CubeFace face)
{
   if ( mRegionExits.find(face) != mRegionExits.end() )
    {
        return mRegionExits[face];
    }
}