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
        CaveRegion* GenerateCaveRegion(Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance, Ogre::Vector3 cubeExit);
};
#endif