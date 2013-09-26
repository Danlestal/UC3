#ifndef CAVEREGION_H
#define CAVEREGION_H

#include "Ogre.h"
#include "UberCube.h"

class CaveRegion
{
    protected:
        UberCube *mCube;
        Ogre::Vector3 mGlobalVector;
        std::vector<Ogre::Vector3> mLocalPositionExits;  //A vector because I am not planning to remove anything from this list.

        CaveRegion(){}

    public:
        CaveRegion(Ogre::Vector3 globalPos, UberCube *cube);
        ~CaveRegion();

        void AddLocalPositionExits(Ogre::Vector3 newExit);
        Ogre::Vector3 GetLocalPositionExit(int exitNumber);
        Ogre::Vector3 GetGlobalPos();
        
        UberCube* GetDensityCube();

};
#endif