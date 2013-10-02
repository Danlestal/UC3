#include "CaveGenerationManager.h"


CaveRegion* CaveGenerationManager::CreateFirstRegion(CubeFace regionExit)
{
	CaveRegion* firstCave =  mGenerator.GenerateCaveRegion(Ogre::Vector3::ZERO);
	mGenerator.AddExitToCaveRegion(firstCave, Ogre::Vector3(1,1,1), regionExit);
	mGenerator.SmoothCave(firstCave);
	return firstCave;
}


CubeFace GetOpossiteFace(CubeFace nextRegionExit)
{
	switch(nextRegionExit)
	{
		case TOP:
			return CubeFace::BOTTON;
        
        case BOTTON:
			return CubeFace::TOP;
        
        case LEFT:
			return CubeFace::RIGHT;
        
        case RIGHT:
			return CubeFace::LEFT;
        
        case FRONT:
			return CubeFace::BACK;
        
        case BACK:
			return CubeFace::FRONT;
	}
}

Ogre::Vector3 GetIncrementVector(CubeFace currentRegionExit)
{
	switch(currentRegionExit)
	{
		case TOP:
			return Ogre::Vector3(0, 1, 0);
        
        case BOTTON:
			return Ogre::Vector3(0, -1, 0);
        
        case LEFT:
			return Ogre::Vector3(-1, 0, 0);
        
        case RIGHT:
			return Ogre::Vector3(1, 0, 0);
        
        case FRONT:
			return Ogre::Vector3(0, 0, -1);
        
        case BACK:
			return Ogre::Vector3(0, 0, 1);
	}
}

CaveRegion* CaveGenerationManager::CreateNextRegion(CaveRegion* currentRegion, CubeFace currentRegionExit, CubeFace nextRegionExit)
{
	Ogre::Vector3 incrementVector = GetIncrementVector(currentRegionExit);
	Ogre::Vector3 nextRegionPosition = currentRegion->GetGlobalPos() + (incrementVector * UBERCUBE_SIZE);
	CaveRegion* nextRegion =  mGenerator.GenerateCaveRegion(nextRegionPosition);

	Ogre::Vector3 previousExitPoint = currentRegion->GetExitPointOnCubeFace(currentRegionExit);
	Ogre::Vector3 nextStartingPoint = previousExitPoint - (previousExitPoint * incrementVector.normalise());

	mGenerator.AddExitToCaveRegion(nextRegion, nextStartingPoint, nextRegionExit);
	mGenerator.SmoothCave(nextRegion);

	currentRegion->AddCaveNeighbour(currentRegionExit, nextRegion);
	nextRegion->AddCaveNeighbour(GetOpossiteFace(nextRegionExit), currentRegion);

	return nextRegion;
}

/*
CaveRegion* CaveGenerationManager::CreateNextRegion(CaveRegion* previousRegion, CubeFace previousRegionExit, CubeFace nextRegionExit)
{
    Ogre::Vector3 previousCubePosition = previousRegion->GetGlobalPos();
    Ogre::Vector3 newCubePosition = previousCubePosition;

    Ogre::Vector3 previousExitPoint = previousRegion->GetExitPointOnCubeFace(previousRegionExit);
    Ogre::Vector3 nextCubeStartingPoint = previousExitPoint;

    UberCube* newCube = new UberCube();

    switch(previousRegionExit)
    {
        case TOP:
            nextCubeStartingPoint.y = 10;
            newCubePosition += (Ogre::Vector3(0, 1, 0) * UBERCUBE_SIZE);

            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < UBERCUBE_SIZE; ++j)
                {
                    for(int k = 0; k < UBERCUBE_SIZE; ++k)
                    {
                        newCube->mDensityCube[j][i][k] = previousRegion->GetDensityCube()->mDensityCube[j][UBERCUBE_SIZE - i][k];
                    }
                }
            }

        break;
        
        case BOTTON:
            nextCubeStartingPoint.y = UBERCUBE_SIZE -10;
            newCubePosition += (Ogre::Vector3(0, -1, 0) * UBERCUBE_SIZE);
            
            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < UBERCUBE_SIZE; ++j)
                {
                    for(int k = 0; k < UBERCUBE_SIZE; ++k)
                    {
                        newCube->mDensityCube[j][UBERCUBE_SIZE - i][k] = previousRegion->GetDensityCube()->mDensityCube[j][i][k];
                    }
                }
            }

        break;
        
        case LEFT:
            nextCubeStartingPoint.x = UBERCUBE_SIZE -10;
            newCubePosition += (Ogre::Vector3(-1, 0, 0) * UBERCUBE_SIZE);

            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < UBERCUBE_SIZE; ++j)
                {
                    for(int k = 0; k < UBERCUBE_SIZE; ++k)
                    {
                        newCube->mDensityCube[UBERCUBE_SIZE - i][j][k] = previousRegion->GetDensityCube()->mDensityCube[i][j][k];
                    }
                }
            }

        break;
        
        case RIGHT:
            nextCubeStartingPoint.x = 10;
            newCubePosition += (Ogre::Vector3(1, 0, 0) * UBERCUBE_SIZE);

            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < UBERCUBE_SIZE; ++j)
                {
                    for(int k = 0; k < UBERCUBE_SIZE; ++k)
                    {
                        newCube->mDensityCube[i][j][k] = previousRegion->GetDensityCube()->mDensityCube[UBERCUBE_SIZE - i][j][k];
                    }
                }
            }

        break;
        
        case FRONT:
            nextCubeStartingPoint.z = UBERCUBE_SIZE -10;
            newCubePosition += (Ogre::Vector3(0, 0, -1) * UBERCUBE_SIZE);

            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < UBERCUBE_SIZE; ++j)
                {
                    for(int k = 0; k < UBERCUBE_SIZE; ++k)
                    {
                        newCube->mDensityCube[j][k][UBERCUBE_SIZE - i] = previousRegion->GetDensityCube()->mDensityCube[j][k][i];
                    }
                }
            }
        break;
        
        case BACK:
            nextCubeStartingPoint.z = 10;
            newCubePosition += (Ogre::Vector3(0, 0, 1) * UBERCUBE_SIZE);

            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < UBERCUBE_SIZE; ++j)
                {
                    for(int k = 0; k < UBERCUBE_SIZE; ++k)
                    {
                        newCube->mDensityCube[j][k][i] = previousRegion->GetDensityCube()->mDensityCube[j][k][UBERCUBE_SIZE - i];
                    }
                }
            }
        break;
    }

    return mGenerator.GenerateCaveRegion(newCube, newCubePosition, nextCubeStartingPoint, nextRegionExit);
}
*/