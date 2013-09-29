#ifndef CaveGenerationManager_h
#define CaveGenerationManager_h

#include "Ogre.h"
#include "CaveRegionGenerator.h"



class CaveGenerationManager
{
    private:
        CaveRegionGenerator mGenerator;
   
    public:
        CaveGenerationManager(CaveRegionGenerator generator) : mGenerator(generator)
        {};

		CaveRegion* CreateFirstRegion(CubeFace regionExit);
        CaveRegion* CreateNextRegion(CaveRegion* previousRegion, CubeFace previousRegionExit, CubeFace nextRegionExit);
};
#endif