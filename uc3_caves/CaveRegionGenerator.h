#ifndef CaveRegionGenerator_h
#define CaveRegionGenerator_h

#include "IDensityCubeGenerator.h"
#include "CaveRegion.h"
#include "ICubeSmoother.h"

class CaveRegionGenerator
{
    private:
        IDensityCubeGenerator *mDensityGenerator;
        ICubeSmoother *mSmoother;

    public:
        CaveRegionGenerator(IDensityCubeGenerator *densityGenerator, ICubeSmoother *smoother);

        void SetDensityGenerator(IDensityCubeGenerator *densityGenerator);
        void SetSmoother(ICubeSmoother *smoother);
        
		CaveRegion* GenerateCaveRegion(Ogre::Vector3 cubePosition);

		void AddBlindPathToCaveRegion(CaveRegion* caveToModified, Ogre::Vector3 pathStart, Ogre::Vector3 pathEnd);
		void AddExitToCaveRegion(CaveRegion* caveToModified, Ogre::Vector3 cubeEntrance, CubeFace cubeFaceExit);
		void SmoothCave(CaveRegion* caveToModified);

		void PrepareCaveJoint(CaveRegion* nextCave, const CaveRegion* currentRegion, CubeFace currentRegionExit);


        
};
#endif