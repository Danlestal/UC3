#ifndef CAVEREGION_H
#define CAVEREGION_H

#include "Ogre.h"
#include "UberCube.h"
#include "RandomNumberGenerator.h"
#include "CubeFaceUtils.h"

class CaveRegion
{
    protected:
        UberCube *mCube;
        Ogre::Vector3 mGlobalVector;
		bool mRegionInitialized;
        
        std::map<CubeFace, Ogre::Vector3> mRegionExits;
        std::map<CubeFace, CaveRegion*> mRegionNeighbours;

        CaveRegion(){}

    public:
        CaveRegion(Ogre::Vector3 globalPos, UberCube *cube);
        ~CaveRegion();

        Ogre::Vector3 GetGlobalPos();
		void GetID(char* name);

        void AddRegionExitOnCubeFace(CubeFace newExit);
        Ogre::Vector3 GetExitPointOnCubeFace(CubeFace face);
        

		void AddCaveNeighbour(CubeFace newExit, CaveRegion* neighbourRegion);
		std::map<CubeFace, CaveRegion*> GetNeighbours();

        UberCube* GetDensityCube();

};
#endif