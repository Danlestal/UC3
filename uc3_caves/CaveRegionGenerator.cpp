#include "CaveRegionGenerator.h"

CaveRegionGenerator::CaveRegionGenerator(IDensityCubeGenerator *densityGenerator, ICubeSmoother *smoother) : mDensityGenerator(densityGenerator), mSmoother(smoother)
{
}

void CaveRegionGenerator::SetDensityGenerator(IDensityCubeGenerator *densityGenerator)
{
    mDensityGenerator = densityGenerator;
}

void CaveRegionGenerator::SetSmoother(ICubeSmoother *smoother)
{
    mSmoother = smoother;
}

CaveRegion* CaveRegionGenerator::GenerateCaveRegion(Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance, CubeFace cubeFaceExit)
{
    UberCube *cube = new UberCube();
    CaveRegion *region = new CaveRegion(cubePosition, cube);

    region->AddRegionExitOnCubeFace(cubeFaceExit);
    Ogre::Vector3 exitPoint = region->GetExitPointOnCubeFace(cubeFaceExit);

    mDensityGenerator->GenerateDensityCube(cube, cubeEntrance, exitPoint);
    mSmoother->Smooth(cube);

    return region;
}


CaveRegion* CaveRegionGenerator::GenerateCaveRegion(UberCube *fetchedUberCube, Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance, CubeFace cubeFaceExit)
{
    CaveRegion *region = new CaveRegion(cubePosition, fetchedUberCube);

    region->AddRegionExitOnCubeFace(cubeFaceExit);
    Ogre::Vector3 exitPoint = region->GetExitPointOnCubeFace(cubeFaceExit);

    mDensityGenerator->GenerateDensityCube(fetchedUberCube, cubeEntrance, exitPoint);
    mSmoother->Smooth(fetchedUberCube);

    return region;
}

