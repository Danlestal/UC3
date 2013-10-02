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


CaveRegion* CaveRegionGenerator::GenerateCaveRegion(Ogre::Vector3 cubePosition)
{
    UberCube *cube = new UberCube();
    CaveRegion *region = new CaveRegion(cubePosition, cube);
    return region;
}

void CaveRegionGenerator::AddBlindPathToCaveRegion(CaveRegion* caveToModified, Ogre::Vector3 pathStart, Ogre::Vector3 pathEnd)
{
	//TODO: CHECK THAT NEITHER PATH START OR PATHEND ARE ON THE CUBE BOUNDARIES.
	mDensityGenerator->GenerateDensityCube(caveToModified->GetDensityCube(), pathStart, pathEnd);
}

void CaveRegionGenerator::AddExitToCaveRegion(CaveRegion* caveToModified, Ogre::Vector3 cubeEntrance, CubeFace cubeFaceExit)
{
	caveToModified->AddRegionExitOnCubeFace(cubeFaceExit);
    Ogre::Vector3 exitPoint = caveToModified->GetExitPointOnCubeFace(cubeFaceExit);
	mDensityGenerator->GenerateDensityCube(caveToModified->GetDensityCube(), cubeEntrance, exitPoint);
}


void CaveRegionGenerator::SmoothCave(CaveRegion* caveToModified)
{
	mSmoother->Smooth(caveToModified->GetDensityCube());
}


void CaveRegionGenerator::PrepareCaveJoint(CaveRegion* nextCave, const CaveRegion* currentRegion, CubeFace currentRegionExit)
{
}
