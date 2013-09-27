#ifndef CAVEREGION_H
#define CAVEREGION_H

#include "Ogre.h"
#include "UberCube.h"
#include "RandomNumberGenerator.h"


enum CubeFace
{
    TOP,
    BOTTON,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

class CaveRegion
{
    protected:
        UberCube *mCube;
        Ogre::Vector3 mGlobalVector;
        std::map<CubeFace, Ogre::Vector3> mRegionExits;
        

        CaveRegion(){}

    public:
        CaveRegion(Ogre::Vector3 globalPos, UberCube *cube);
        ~CaveRegion();

        Ogre::Vector3 GetGlobalPos();
        void AddRegionExitOnCubeFace(CubeFace newExit);
        Ogre::Vector3 GetExitPointOnCubeFace(CubeFace face);
        

        UberCube* GetDensityCube();

};
#endif