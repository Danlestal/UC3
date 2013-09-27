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
        CaveRegion* GenerateCaveRegion(Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance, CubeFace cubeFaceExit);
        CaveRegion* GenerateCaveRegion(UberCube *fetchedUberCube, Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance, CubeFace cubeFaceExit);
};
#endif