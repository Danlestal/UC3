#include "CaveRegionGenerator.h"

CaveRegionGenerator::CaveRegionGenerator(IDensityCubeGenerator *densityGenerator, ICubeSmoother *smoother) : mDensityGenerator(densityGenerator), mSmoother(smoother)
{
}

void CaveRegionGenerator::SetDensityGenerator(IDensityCubeGenerator *densityGenerator)
{
    mDensityGenerator = densityGenerator;
}


CaveRegion* CaveRegionGenerator::GenerateCaveRegion(Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance, Ogre::Vector3 cubeExit)
{
    UberCube *cube = new UberCube();
    mDensityGenerator->GenerateDensityCube(cube, cubeEntrance, cubeExit);
    mSmoother->Smooth(cube);
    return new CaveRegion(cubePosition.x, cubePosition.y, cubePosition.z, cube);
}
